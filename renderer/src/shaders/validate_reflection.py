#!/usr/bin/env python3
"""Build-time GLSL reflection check using glslangValidator."""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path


def _resolve_validator(cli_value: str | None, shader_dir: Path) -> str | None:
    if cli_value:
        candidate = Path(cli_value)
        if candidate.is_file():
            return str(candidate)
        found = shutil.which(cli_value)
        if found:
            return found

    repo_root = shader_dir.parents[4]
    local_candidates = [
        repo_root / "deps" / "glslang" / "bin" / "glslangValidator.exe",
        repo_root / "deps" / "glslang" / "bin" / "glslangValidator",
    ]
    for candidate in local_candidates:
        if candidate.is_file():
            return str(candidate)

    return shutil.which("glslangValidator") or shutil.which("glslang")


def _iter_compile_jobs(spirv_dir: Path) -> list[tuple[Path, str]]:
    jobs: list[tuple[Path, str]] = []
    for shader in sorted(spirv_dir.glob("*.main")):
        jobs.append((shader, "vert"))
        jobs.append((shader, "frag"))
    for shader in sorted(spirv_dir.glob("*.vert")):
        jobs.append((shader, "vert"))
    for shader in sorted(spirv_dir.glob("*.frag")):
        jobs.append((shader, "frag"))
    return jobs


def _frag_define_for_shader(shader: Path) -> str:
    name = shader.stem
    if "clockwise" in name and "clockwise_atomic" not in name:
        return "-DPLS_IMPL_STORAGE_TEXTURE"
    return "-DPLS_IMPL_SUBPASS_LOAD"


def _reflection_path(out_spirv_dir: Path, shader: Path, stage: str) -> Path:
    return out_spirv_dir / f"{shader.stem}.{stage}.reflect.txt"


def _validate_binding_lines(output: str, shader: Path, stage: str) -> list[str]:
    failures: list[str] = []
    pattern = re.compile(r"^([^:\n]+):[^\n]*\bbinding\s+(-?\d+)", re.MULTILINE)
    for symbol, binding in pattern.findall(output):
        if int(binding) < 0 and not symbol.startswith("gl_"):
            failures.append(
                f"{shader.name} [{stage}] has unresolved binding for '{symbol.strip()}'"
            )
    return failures


def _run_reflection(
    validator: str, shader: Path, stage: str, include_dir: Path
) -> tuple[int, str]:
    command = [
        validator,
        "-S",
        stage,
        "-DTARGET_VULKAN",
        f"-I{include_dir}",
        "-V",
        "-l",
        "-q",
    ]
    if stage == "vert":
        command.append("-DVERTEX")
    else:
        command.extend(["-DFRAGMENT", _frag_define_for_shader(shader)])
    command.append(str(shader))

    proc = subprocess.run(command, capture_output=True, text=True)
    output = (proc.stdout or "") + (proc.stderr or "")
    return proc.returncode, output


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", required=True, help="Shader OUT folder used by Makefile")
    parser.add_argument("--validator", default=None, help="Path or name of glslangValidator")
    args = parser.parse_args()

    shader_dir = Path(__file__).resolve().parent
    spirv_dir = shader_dir / "spirv"
    out_dir = Path(args.out).resolve()
    out_spirv_dir = out_dir / "spirv"
    out_spirv_dir.mkdir(parents=True, exist_ok=True)

    validator = _resolve_validator(args.validator, shader_dir)
    if validator is None:
        print("error: glslangValidator not found (set --validator or GLSLANG_VALIDATOR)")
        return 1

    jobs = _iter_compile_jobs(spirv_dir)
    if not jobs:
        print("error: no SPIR-V shader inputs found")
        return 1

    failures: list[str] = []
    for shader, stage in jobs:
        code, output = _run_reflection(validator, shader, stage, out_dir)
        if code != 0:
            failures.append(f"{shader.name} [{stage}] failed to compile for reflection")
            failures.append(output.strip())
            continue

        reflect_file = _reflection_path(out_spirv_dir, shader, stage)
        reflect_file.write_text(output, encoding="utf-8")
        failures.extend(_validate_binding_lines(output, shader, stage))

    if failures:
        print("Reflection validation failed:")
        for failure in failures:
            print(f"  - {failure}")
        return 1

    print(
        f"Validated reflection for {len(jobs)} shader-stage entries "
        f"(output: {out_spirv_dir})"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
