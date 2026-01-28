#include "../environment.hpp"
#include "gfx/debug.hpp"
#include "gfx/shape_renderer.hpp"
#include "gfx/rgba_renderer.hpp"
#include "gfx/ground_collision.hpp"
#include "gfx/collision.hpp"
#include "gfx/controller.hpp"
#include "gfx/ibuffer.hpp"
#include "gfx/swaps.hpp"
#include "gfx/font.hpp"
#include "gfx/hdr_pages.hpp"
#include "smash.hpp"

#include "skyline/inlinehook/And64InlineHook.hpp"
#include "utils.hpp"

#include "gfx/managed/command_buffer.hpp"

#include "nn/oe.h"

DrawSettings g_DrawSettings = DrawSettings{
    .input = true,
    .ecb = false,
    .ledge_grab = false,
    .hurtboxes = false,
    .camera_angle = 0};

constexpr const char *SUBMIT_COMMANDS = "nvnQueueSubmitCommands";

static nvn::NVN_TYPE(QueueSubmitCommands) nvnQueueSubmitCommands_orig;
static uint64_t s_FrameCounter = 0;

static int g_DisplayWidth = -1;
static int g_DisplayHeight = -1;

const uint64_t RENDER_DISPATCH_OFFSET = 0x3815348;

// void renderDispatch_hook(InlineCtx *ctx)
// {
//     // static GfxCommandBuffer* s_CmdBuffer = nullptr;
//     static Swaps<3> *s_Swaps = nullptr;
//     static Scissor *s_Scissor = nullptr;
//     static ClearColor *s_ClearColor = nullptr;
//     static float s_Time = 0.0f;

//     // Only initialize the buffer once, and we need to wait until we have the
//     // graphics device to do so
//     if (s_Scissor == nullptr)
//     {
//         // s_CmdBuffer = new GfxCommandBuffer(g_Device, 0x10000, 0x10000);
//         s_Swaps = new Swaps<3>(g_Device);
//         s_Scissor = new Scissor(0, 0, 1920, 1080);
//         s_ClearColor = new ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//         GroundCollisionManager::InstallHooks();
//         InputManager::InstallHooks();
//         // auto &instance = FontManager::Instance();
//         // instance.LoadFont("sd:/font.ttf");
//         // instance.SetScale(48);
//         // instance.SetFlags(nn::fontll::ScalableFontEngine::Flags_NoEffect);
//         // // instance.SetOutlineWidth(2);
//         // instance.InitializeTextureImage(64);
//         install_collision_hooks();
//     }

//     nn::oe::GetDefaultDisplayResolution(&g_DisplayWidth, &g_DisplayHeight);

//     uint64_t pipeline = ctx->registers[20].x + 0x18;
//     uint64_t nu_cmdbuf = *reinterpret_cast<uint64_t *>(pipeline + 0xC8);
//     nvn::CommandBuffer *cmdbuf = *reinterpret_cast<nvn::CommandBuffer **>(nu_cmdbuf + 0x10);

//     // If the display texture index is -1, it means that the window hasn't been initialized
//     //
//     // Since starlight is a graphics overlay engine, this would be problematic to attempt to start drawing
//     // if (g_DisplayTextureIndex != -1)
//     {
//         // Reallocate the command handles because we are adding one
//         // nvn::CommandHandle* new_handles = new nvn::CommandHandle[count + 1];
//         // memcpy(new_handles, handles, count * sizeof(nvn::CommandHandle));

//         // Reset our global command buffer and rerecord it
//         // s_CmdBuffer->Reset();
//         // s_CmdBuffer->Begin();
//         // s_Swaps->Bind(s_CmdBuffer->Get());

//         // cmdbuf->SetViewport(0, 0, 1920, 1080);
//         // s_Scissor->Bind(cmdbuf);
//         // s_ClearColor->Draw(cmdbuf);

//         // FontManager::DrawText(100, 100, 30.0, "da vinki");
//         // HDR_PageManager::DrawPages();
//         // HDR_PageManager::Render(cmdbuf);
//         // FontManager::Render(cmdbuf);

//         // GroundCollisionManager::Render(cmdbuf);

//         // InputManager::Update(cmdbuf);
//         // InputManager::Render(cmdbuf);

//         // ShapeRenderer::DrawSphere({0.0f, 10.0f, 0.0f}, { 0.5f, 2.0f, 1.0f }, 10.0f, {1.0f, 0.0f, 0.0f, 0.75f});
//         // ShapeRenderer::DrawCapsule2(
//         //     {-5.0f, 15.0f, -5.0f},
//         //     {5.0f, 5.0f, 5.0f},
//         //     { 0.5f, 2.0f, 1.0f },
//         //     3.0f,
//         //     { 1.0f, 0.0f, 0.0f, 0.75f }
//         // );

//         // s_Time += 3.141519f / 150.0f;
//         // ShapeRenderer::Render(cmdbuf);
//         // collision_render();

//         // sl_window_render_to_active_texture(cmdbuf);

//         // s_Swaps->BindForDraw(cmdbuf);
//         // auto handle = s_Swaps->GetHandleForDraw();
//         // s_Swaps->Advance();
//         // if (handle)
//         // {
//         //     const nvn::DrawTextureRegion src_region = nvn::DrawTextureRegion{
//         //         .x0 = 0.0f,
//         //         .y0 = 0.0f,
//         //         .x1 = 1920.0f,
//         //         .y1 = 1080.0f};

//         //     const nvn::DrawTextureRegion dst_region = nvn::DrawTextureRegion{
//         //         .x0 = 0.0f,
//         //         .y0 = 0.0f,
//         //         .x1 = (float)g_DisplayWidth,
//         //         .y1 = (float)g_DisplayHeight};

//         //     cmdbuf->DrawTexture(handle.value(), &dst_region, &src_region);
//         // }
//         // Finish up our global command buffer and put it at the end of the hadnle list
//         // new_handles[count] = s_CmdBuffer->End();
//         // nvnQueueSubmitCommands_orig(queue, count + 1, new_handles);
//     }
//     // else
//     // {
//     //     nvnQueueSubmitCommands_orig(queue, count, handles);
//     // }
// }

void nvnQueueSubmitCommands_hook(nvn::Queue *queue, int count, const nvn::CommandHandle *handles)
{
    static GfxCommandBuffer *s_CmdBuffer = nullptr;
    static Swaps<3> *s_Swaps = nullptr;
    static Scissor *s_Scissor = nullptr;
    static ClearColor *s_ClearColor = nullptr;
    static bool s_HasRegistered = false;
    static float s_Time = 0.0f;

    // Only initialize the buffer once, and we need to wait until we have the
    // graphics device to do so
    if (s_CmdBuffer == nullptr)
    {
        s_CmdBuffer = new GfxCommandBuffer(g_Device, 0x10000, 0x10000);
        s_Swaps = new Swaps<3>(g_Device);
        s_Scissor = new Scissor(0, 0, 1920, 1080);
        s_ClearColor = new ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        GroundCollisionManager::InstallHooks();
        InputManager::InstallHooks();
        ShapeRenderer::InstallHooks();
        // auto &instance = FontManager::Instance();
        // instance.LoadFont("sd:/font.ttf");
        // instance.SetScale(48);
        // instance.SetFlags(nn::fontll::ScalableFontEngine::Flags_NoEffect);
        // instance.SetOutlineWidth(2);
        // instance.InitializeTextureImage(64);
        install_collision_hooks();
    }

    nn::oe::GetDefaultDisplayResolution(&g_DisplayWidth, &g_DisplayHeight);

    // If the display texture index is -1, it means that the window hasn't been initialized
    //
    // Since starlight is a graphics overlay engine, this would be problematic to attempt to start drawing
    if (g_DisplayTextureIndex != -1)
    {
        // Reallocate the command handles because we are adding one
        nvn::CommandHandle *new_handles = new nvn::CommandHandle[count + 1];
        memcpy(new_handles, handles, count * sizeof(nvn::CommandHandle));

        // Reset our global command buffer and rerecord it
        s_CmdBuffer->Reset();
        s_CmdBuffer->Begin();
        s_Swaps->Bind(s_CmdBuffer->Get());

        sl_window_render_to_active_texture(s_CmdBuffer->Get());

        s_CmdBuffer->Get()->SetViewport(0, 0, 1920, 1080);
        s_Scissor->Bind(s_CmdBuffer->Get());
        GroundCollisionManager::Render(s_CmdBuffer->Get());

        InputManager::Update(s_CmdBuffer->Get());
        InputManager::Render(s_CmdBuffer->Get());

        s_Time += 3.141519f / 150.0f;
        ShapeRenderer::Render(s_CmdBuffer->Get());
        collision_render();

        s_Swaps->BindForDraw(s_CmdBuffer->Get());
        auto handle = s_Swaps->GetHandleForDraw();
        s_Swaps->Advance();
        if (handle)
        {
            const nvn::DrawTextureRegion src_region = nvn::DrawTextureRegion{
                .x0 = 0.0f,
                .y0 = 0.0f,
                .x1 = 1920.0f,
                .y1 = 1080.0f};

            const nvn::DrawTextureRegion dst_region = nvn::DrawTextureRegion{
                .x0 = 0.0f,
                .y0 = 0.0f,
                .x1 = (float)g_DisplayWidth,
                .y1 = (float)g_DisplayHeight};

            // s_CmdBuffer->Get()->DrawTexture(handle.value(), &dst_region, &src_region);
        }
        // Finish up our global command buffer and put it at the end of the hadnle list
        new_handles[count] = s_CmdBuffer->End();
        nvnQueueSubmitCommands_orig(queue, count + 1, new_handles);
    }
    else
    {
        nvnQueueSubmitCommands_orig(queue, count, handles);
    }
}

void install_queue_hooks()
{
    A64HookFunction(
        reinterpret_cast<void *>(g_Device->GetProcAddress(SUBMIT_COMMANDS)),
        reinterpret_cast<void *>(nvnQueueSubmitCommands_hook),
        (void **)&nvnQueueSubmitCommands_orig);

    // A64InlineHook(reinterpret_cast<char *>(skyline::utils::getRegionAddress(skyline::utils::region::Text)) + RENDER_DISPATCH_OFFSET, renderDispatch_hook);
}