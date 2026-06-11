# AGENTS

## Status
- Switch build: `--for_switch` uses clang++ with devkitA64 sysroot/target.
- NVN integration: `renderer/premake5_pls_renderer.lua` supports `--with_nvn` and compiles `renderer/src/nvn/**`.
- NVN shader helpers: `renderer/include/rive/renderer/nvn/nvn_shader_utils.hpp` and `renderer/include/rive/renderer/nvn/nvn_pipeline.hpp`.
- C API shim: expanded in `include/rive/capi.h` and `src/rive_capi.cpp`.

## Build
- Runtime: `.\build\build_rive.bat ninja release clean --for_switch`
- Renderer: `cd renderer` then `..\build\build_rive.bat ninja release clean --for_switch --with_nvn`

## NVN usage notes
- Atomic mode only: set `RenderContext::FrameDescriptor.disableRasterOrdering = true`.
- Use `rive::gpu::nvn::BuildAtomicProgramSources(...)` to get minified GLSL strings, then compile via NVN at runtime.

## Current C API surface (short list)
- File import/release + artboard count/name.
- Artboard: create default/at/named, advance, size/original size.
- Animations: count/name, create by index/name, advance/apply, get/set time.
- State machines: count/name, create by index/name, advance, set bool/number, fire trigger.

## Suggested next C API additions
- Rendering: create/destroy renderer/context, draw artboard, set render target, begin/end frame.
- Inputs: enumerate inputs, get/set by index, set via path, get input types.
- Events: access reported events from state machines, clear events.
- Artboard data: bounds/world bounds, layout rect, frame origin, hit testing.
- Assets: custom file asset loader hooks, image decode callbacks, audio callbacks.
- Scenes: expose default scene, advance/apply on scene, combine animations.
