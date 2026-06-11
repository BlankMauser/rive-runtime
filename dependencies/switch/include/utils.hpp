#pragma once
#include "nn/diag.h"
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include "skyline/logger/TcpLogger.hpp"
#include "skyline/utils/cpputils.hpp"
#include "nn/err.h"
#include "nn/os.hpp"
#include "nn/fs.h" 
#include "nn/crypto.h"

#define SL_ASSERT(x) if (!(x)) debug_abort("Failed assertion: " #x, __LINE__, __FILE__);
#define SL_ASSERTM(x, msg) if (!(x)) debug_abort(msg, __LINE__, __FILE__);
#define SL_ALIGN(size, align) (((align - (size % align)) % align) + size)

struct Sha256Hash {
    char bytes[32];

    inline bool operator==(const Sha256Hash& other) {
        return memcmp(this, &other, sizeof(Sha256Hash)) == 0;
    }

    inline bool operator!=(const Sha256Hash& other) {
        return memcmp(this, &other, sizeof(Sha256Hash)) != 0;
    }
};

static_assert(sizeof(Sha256Hash) == 0x20);

inline void debug_abort(const char* msg, int ln, const char* file, unsigned int err = 0x0) {
    char buf[0x200] = { 0 };
    sprintf(buf, "File: %s, LN: %d", file, ln);

    skyline::TcpLogger::SendRawFormat("%s", buf);
    nn::err::ApplicationErrorArg* error =
        new nn::err::ApplicationErrorArg(69, "The software is aborting.", buf,
                                         nn::settings::LanguageCode::Make(nn::settings::Language::Language_English));
    nn::err::ShowApplicationError(*error);

    nn::diag::detail::AbortImpl("Comet is aborting.", msg, buf, err);
}

inline void debug_log(const char* format, ...) {
    va_list args;
    char buf[0x1000] = { 0 };
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    skyline::TcpLogger::SendRaw("\033[1:37m[comet]\033[0m: ");
    skyline::TcpLogger::SendRaw(buf);
    skyline::TcpLogger::SendRaw("\n");
    va_end (args);
}

inline void short_sleep() {
    nn::os::SleepThread(nn::TimeSpan::FromNanoSeconds(200000000));
}

inline void hash_bytes(const void* bytes, size_t amount, Sha256Hash* hash) {
    nn::crypto::GenerateSha256Hash(hash, sizeof(Sha256Hash), bytes, amount);
}

inline void read_file(const char* filepath, void** output, int64_t* size) {
    SL_ASSERT(output != nullptr && size != nullptr);
    nn::fs::FileHandle handle;
    Result result = nn::fs::OpenFile(&handle, filepath, nn::fs::OpenMode::OpenMode_Read);
    SL_ASSERTM(R_SUCCEEDED(result), filepath);
    result = nn::fs::GetFileSize(size, handle);
    SL_ASSERT(R_SUCCEEDED(result));
    *output = new char[*size];
    result = nn::fs::ReadFile(handle, 0, *output, *size);
    SL_ASSERT(R_SUCCEEDED(result));
    nn::fs::CloseFile(handle);
}

inline void* byte_search(const uint8_t* sequence, size_t length) {
    SL_ASSERT(sequence != nullptr);

    uint8_t* text = (uint8_t*)skyline::utils::getRegionAddress(skyline::utils::region::Text);
    uint8_t* rodata = (uint8_t*)skyline::utils::getRegionAddress(skyline::utils::region::Rodata);
    for (uint8_t* ptr = text; ptr != rodata; ptr++) {
        if (std::memcmp(ptr, sequence, length) == 0)
            return ptr;
    }
    return nullptr;
}