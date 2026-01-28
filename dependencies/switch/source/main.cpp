#include "main.hpp"
#include "utils.hpp"
#include "smash.hpp"
#include "gfx/hooks/hook.hpp"

#include "nn/os.hpp"
#include "nn/err.h"
#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"

#include "gfx/environment.hpp"
#include "gfx/hitbox.hpp"

#include "gfx/game_camera.hpp"
#include "skyline/logger/TcpLogger.hpp"

bool g_IsCameraUpdateOnly = false;
bool g_IsReplay = false;
bool g_ShouldDoubleSpeed = false;

void (*main_game_loop_orig)(uint32_t*, bool) = nullptr;

void main_game_loop_hook(uint32_t* ptr, bool camera_only) {
    g_IsCameraUpdateOnly = camera_only;
    main_game_loop_orig(ptr, camera_only);
    if (g_ShouldDoubleSpeed)
        main_game_loop_orig(ptr, camera_only);
} 

void setup_inline_hook(InlineCtx* ctx) {
    g_IsReplay = true;
}

void exit_inline_hook(InlineCtx* ctx) {
    g_IsReplay = false;
}


void (*VAbortImpl)(char const*, char const*, char const*, int, Result const*, nn::os::UserExceptionInfo const*, char const*, va_list args);
void handleNnDiagDetailVAbortImpl(char const* str1, char const* str2, char const* str3, int int1, Result const* code, nn::os::UserExceptionInfo const* ExceptionInfo, char const* fmt, va_list args) {
    int len = vsnprintf(nullptr, 0, fmt, args);
    char* fmt_info = new char[len + 1];
    vsprintf(fmt_info, fmt, args);

    const char* fmt_str = "%s\n%s\n%s\n%d\nError: 0x%x\n%s";
    len = snprintf(nullptr, 0, fmt_str, str1, str2, str3, int1, *code, fmt_info);
    char* report = new char[len + 1];
    sprintf(report, fmt_str, str1, str2, str3, int1, *code, fmt_info);

    skyline::TcpLogger::SendRawFormat("%s", report);
    nn::err::ApplicationErrorArg* error =
        new nn::err::ApplicationErrorArg(69, "The software is aborting.", report,
                                         nn::settings::LanguageCode::Make(nn::settings::Language::Language_English));
    nn::err::ShowApplicationError(*error);
    delete[] report;
    delete[] fmt_info;
    VAbortImpl(str1, str2, str3, int1, code, ExceptionInfo, fmt, args);
}

int main() {
    install_device_hooks();
    install_hitbox_hooks();
    install_camera();
    // uintptr_t VAbort_ptr = 0;
    // nn::ro::LookupSymbol(&VAbort_ptr, "_ZN2nn4diag6detail10VAbortImplEPKcS3_S3_iPKNS_6ResultEPKNS_2os17UserExceptionInfoES3_RSt9__va_list");
    // A64HookFunction(reinterpret_cast<void*>(VAbort_ptr), reinterpret_cast<void*>(handleNnDiagDetailVAbortImpl), (void**)&VAbortImpl);

    A64HookFunction(
        skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x137b3d0,
        reinterpret_cast<void*>(main_game_loop_hook),
        reinterpret_cast<void**>(&main_game_loop_orig)
    );

    A64InlineHook(
        skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x2339500,
        reinterpret_cast<void*>(setup_inline_hook)
    );

    A64InlineHook(
        skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x2339210,
        reinterpret_cast<void*>(exit_inline_hook)
    );

    nn::hid::InitializeNpad();
}


struct ControllerClass {
public:
    void** vtable;              // _x0
    uint32_t buttons;           // _x8
    uint32_t prev_buttons;      // _xC
    double left_x;              // _x10
    double left_y;              // _x18
    double right_x;             // _x20
    double right_y;             // _x28
    phx::Vector4f unk_vec;      // _x30
    uint64_t _x40;
    uint64_t _x48;
    bool _x50;
    uint8_t _x51[7];
    uint64_t _x58;
    uint64_t _x60;
    bool _x68;
    uint8_t _x69[7];
    uint64_t _x70;
    uint64_t _x78;
    bool _x80;
    uint8_t _x81[7];
    uint32_t buttons_press;
    uint32_t buttons_release;
    uint32_t _x90;
    uint32_t _x94;
    uint32_t _x98;
    uint8_t _x9C[25];
    bool _xB5;
    bool _xB6;
    bool _xB7;
    uint8_t _xB8[0x18];
};

static_assert(sizeof(ControllerClass) == 0xD0);

const uint32_t LSTICK_MASK = 0xF0000;
// _____________________________________  
// 0b01010101_01010101_01010101_01010101 param_2

/**
 * Smash Controller Mapping
 * BIT(0) UP
 * BIT(1) RIGHT
 * BIT(2) DOWN
 * BIT(3) LEFT
 * BIT(4) X
 * BIT(5) A
 * BIT(6) B
 * BIT(7) Y
 * BIT(8) L
 * BIT(9) R
 * BIT(10) ZL
 * BIT(11) ZR
 * BIT(12) SL_LEFT
 * BIT(13) SR_LEFT
 * BIT(14) SL_RIGHT
 * BIT(15) SR_RIGHT
 * BIT(16) STICK_L
 * BIT(17) STICK_R
 * BIT(18) PLUS
 * BIT(19) MINUS
 * BIT(20) lstick_y <= 0.5
 * BIT(21) lstick_x <= 0.5
 * BIT(22) lstick_y <= -0.5
 * BIT(23) lstick_x <= -0.5
 * BIT(24) rstick_y <= 0.5
 * BIT(25) rstick_x <= 0.5
 * BIT(26) rstick_y <= -0.5
 * BIT(27) rstick_x <= -0.5
 */

void process_inputs(ControllerClass* ctrl, uint hid_buttons, int lstick_x, int lstick_y, int rstick_x, int rstick_y) {
    ctrl->left_x = (float)lstick_x / INT32_MAX;
    ctrl->left_y = (float)lstick_y / INT32_MAX;
    ctrl->right_x = (float)rstick_x / INT32_MAX;
    ctrl->right_y = (float)rstick_y / INT32_MAX;
    
}