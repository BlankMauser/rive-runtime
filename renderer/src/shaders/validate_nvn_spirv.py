#!/usr/bin/env python3
"""Compile and lint shader SPIR-V against NVN-facing constraints."""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path


LIMITS = {
    "ssbo": 16,
    "ubo": 14,
    "combined_sampler": 32,
    "separate_sampler": 32,
    "separate_texture": 128,
    "image": 8,
}


def resolve_tool(cli_value: str | None, env_name: str, fallback: str) -> str | None:
    if cli_value:
        p = Path(cli_value)
        if p.is_file():
            return str(p)
        found = shutil.which(cli_value)
        if found:
            return found

    env_value = os.getenv(env_name)
    if env_value:
        p = Path(env_value)
        if p.is_file():
            return str(p)
        found = shutil.which(env_value)
        if found:
            return found

    return shutil.which(fallback)


def local_glslang(shader_dir: Path) -> str | None:
    repo_root = shader_dir.parents[4]
    candidates = [
        repo_root / "deps" / "glslang" / "bin" / "glslangValidator.exe",
        repo_root / "deps" / "glslang" / "bin" / "glslangValidator",
    ]
    for candidate in candidates:
        if candidate.is_file():
            return str(candidate)
    return None


def compile_jobs(spirv_dir: Path) -> list[tuple[Path, str]]:
    jobs: list[tuple[Path, str]] = []
    for shader in sorted(spirv_dir.glob("*.main")):
        jobs.append((shader, "vert"))
        jobs.append((shader, "frag"))
    for shader in sorted(spirv_dir.glob("*.vert")):
        jobs.append((shader, "vert"))
    for shader in sorted(spirv_dir.glob("*.frag")):
        jobs.append((shader, "frag"))
    return jobs


def frag_define(shader: Path) -> str:
    _ = shader
    return "-DPLS_IMPL_STORAGE_TEXTURE"


def run_cmd(command: list[str]) -> tuple[int, str]:
    proc = subprocess.run(command, capture_output=True, text=True)
    return proc.returncode, (proc.stdout or "") + (proc.stderr or "")


def parse_spirv(disasm: str) -> list[str]:
    errors: list[str] = []

    version_match = re.search(r"^;\s*Version:\s*(\d+)\.(\d+)", disasm, re.MULTILINE)
    if not version_match:
        errors.append("could not read SPIR-V version")
    else:
        major = int(version_match.group(1))
        minor = int(version_match.group(2))
        if (major, minor) > (1, 0):
            errors.append(f"SPIR-V version {major}.{minor} is newer than 1.0")

    descriptor_set_by_id: dict[str, int] = {}
    binding_by_id: dict[str, int] = {}
    pointer_pointee_by_id: dict[str, str] = {}
    sampled_image_type_ids: set[str] = set()
    sampler_type_ids: set[str] = set()
    image_sampled_operand_by_type: dict[str, int] = {}
    block_type_ids: set[str] = set()
    buffer_block_type_ids: set[str] = set()
    variable_ptr_by_id: dict[str, str] = {}
    storage_class_by_var: dict[str, str] = {}

    for raw in disasm.splitlines():
        line = raw.split(";", 1)[0].strip()
        if not line:
            continue

        m = re.match(r"OpDecorate\s+%(\S+)\s+DescriptorSet\s+(\d+)$", line)
        if m:
            descriptor_set_by_id[m.group(1)] = int(m.group(2))
            continue
        m = re.match(r"OpDecorate\s+%(\S+)\s+Binding\s+(\d+)$", line)
        if m:
            binding_by_id[m.group(1)] = int(m.group(2))
            continue
        m = re.match(r"OpDecorate\s+%(\S+)\s+Block$", line)
        if m:
            block_type_ids.add(m.group(1))
            continue
        m = re.match(r"OpDecorate\s+%(\S+)\s+BufferBlock$", line)
        if m:
            buffer_block_type_ids.add(m.group(1))
            continue

        m = re.match(r"%(\S+)\s*=\s*OpTypePointer\s+\S+\s+%(\S+)$", line)
        if m:
            pointer_pointee_by_id[m.group(1)] = m.group(2)
            continue
        m = re.match(r"%(\S+)\s*=\s*OpTypeSampledImage\s+%\S+$", line)
        if m:
            sampled_image_type_ids.add(m.group(1))
            continue
        m = re.match(r"%(\S+)\s*=\s*OpTypeSampler$", line)
        if m:
            sampler_type_ids.add(m.group(1))
            continue
        m = re.match(r"%(\S+)\s*=\s*OpTypeImage\s+(.+)$", line)
        if m:
            type_id = m.group(1)
            tokens = m.group(2).split()
            if len(tokens) >= 7:
                sampled_token = tokens[5]
                if sampled_token.isdigit():
                    image_sampled_operand_by_type[type_id] = int(sampled_token)
            continue
        m = re.match(r"%(\S+)\s*=\s*OpVariable\s+%(\S+)\s+(\S+)", line)
        if m:
            var_id = m.group(1)
            variable_ptr_by_id[var_id] = m.group(2)
            storage_class_by_var[var_id] = m.group(3)
            continue

    usage: dict[str, set[int]] = {key: set() for key in LIMITS}

    for var_id, storage_class in storage_class_by_var.items():
        ptr_id = variable_ptr_by_id.get(var_id)
        pointee_type = pointer_pointee_by_id.get(ptr_id or "")
        binding = binding_by_id.get(var_id)
        descriptor_set = descriptor_set_by_id.get(var_id, 0)

        if descriptor_set != 0 and binding is not None:
            errors.append(
                f"variable %{var_id} uses descriptor set {descriptor_set}; NVN expects set 0"
            )

        if storage_class == "PushConstant":
            errors.append(f"variable %{var_id} uses PushConstant storage class")
            continue

        kind: str | None = None
        if storage_class == "StorageBuffer":
            kind = "ssbo"
        elif storage_class == "Uniform":
            if pointee_type in buffer_block_type_ids:
                kind = "ssbo"
            elif pointee_type in block_type_ids:
                kind = "ubo"
        elif storage_class == "UniformConstant":
            if pointee_type in sampled_image_type_ids:
                kind = "combined_sampler"
            elif pointee_type in sampler_type_ids:
                kind = "separate_sampler"
            elif pointee_type in image_sampled_operand_by_type:
                sampled = image_sampled_operand_by_type[pointee_type]
                if sampled == 2:
                    kind = "image"
                else:
                    kind = "separate_texture"

        if kind is None or binding is None:
            continue

        limit = LIMITS[kind]
        if binding < 0 or binding >= limit:
            errors.append(
                f"{kind} binding {binding} out of range [0, {limit - 1}] for %{var_id}"
            )
        usage[kind].add(binding)

    for kind, used in usage.items():
        limit = LIMITS[kind]
        if len(used) > limit:
            errors.append(f"{kind} uses {len(used)} bindings (limit {limit})")

    return errors


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", required=True)
    parser.add_argument("--validator", default=None)
    parser.add_argument("--spirv-dis", default=None)
    parser.add_argument("--spirv-val", default=None)
    args = parser.parse_args()

    shader_dir = Path(__file__).resolve().parent
    spirv_dir = shader_dir / "spirv"
    out_dir = Path(args.out).resolve()
    lint_out = out_dir / "spirv" / "nvn_lint"
    lint_out.mkdir(parents=True, exist_ok=True)

    validator = args.validator or local_glslang(shader_dir) or shutil.which("glslangValidator")
    spirv_dis = args.spirv_dis or shutil.which("spirv-dis")
    spirv_val = args.spirv_val or shutil.which("spirv-val")

    missing = []
    if not validator:
        missing.append("glslangValidator")
    if not spirv_dis:
        missing.append("spirv-dis")
    if not spirv_val:
        missing.append("spirv-val")
    if missing:
        print("error: missing required tools: " + ", ".join(missing))
        return 1

    jobs = compile_jobs(spirv_dir)
    if not jobs:
        print("error: no SPIR-V shader inputs found")
        return 1

    failures: list[str] = []
    for shader, stage in jobs:
        output_spv = lint_out / f"{shader.stem}.{stage}.spv"
        command = [
            validator,
            "-S",
            stage,
            "-DTARGET_VULKAN",
            "-DTARGET_NVN_SPIRV",
            "-DRIVE_NVN",
            "-DRIVE_NVN_PLS_FIXED_LAYOUT",
            "-DRIVE_NVN_PLS_FORCE_2D",
            f"-I{out_dir}",
            "-V",
        ]
        if stage == "vert":
            command.append("-DVERTEX")
        else:
            command.extend(["-DFRAGMENT", frag_define(shader)])
        command.extend(["-o", str(output_spv), str(shader)])

        code, output = run_cmd(command)
        if code != 0:
            failures.append(f"{shader.name} [{stage}] compile failed")
            failures.append(output.strip())
            continue

        code, output = run_cmd([spirv_val, "--target-env", "opengl4.5", str(output_spv)])
        if code != 0:
            failures.append(f"{shader.name} [{stage}] spirv-val failed for opengl4.5")
            failures.append(output.strip())
            continue

        code, disasm = run_cmd([spirv_dis, str(output_spv)])
        if code != 0:
            failures.append(f"{shader.name} [{stage}] spirv-dis failed")
            failures.append(disasm.strip())
            continue

        parse_errors = parse_spirv(disasm)
        for parse_error in parse_errors:
            failures.append(f"{shader.name} [{stage}] {parse_error}")

    if failures:
        print("NVN SPIR-V lint failed:")
        for failure in failures:
            print(f"  - {failure}")
        return 1

    print(f"NVN SPIR-V lint passed for {len(jobs)} shader-stage entries.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
