
/*--------------------------------------------------------------------------------*
  Copyright (C)Nintendo All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/



/// \file nvn_CppFastpath.h
///      Implementation of NVN C++ interface fastpath functions for API version 55.13.

#ifndef __nvn_cppfastpath_h_
#define __nvn_cppfastpath_h_

#include "nvn_Cpp.h"
#include "nvn_CppFuncPtr.h"

#include <string.h>

extern "C" {
#ifdef _WIN32
__declspec(dllimport) uint32_t nvnPrivate0;
#else
extern uint32_t nvnPrivate0;
#endif
}

namespace nvn {
#ifdef NVN_OVERLOAD_CPP_OBJECTS
namespace objects {
#endif

inline DeviceFlagBits DeviceBuilder::GetFlags_fastpath() const
{
    if (nvnPrivate0) {
        return (*((DeviceFlagBits *)(this->reserved + 4)));
    }
    return pfncpp_nvnDeviceBuilderGetFlags(this);
}

inline void Device::SetWindowOriginMode_fastpath(WindowOriginMode windowOriginMode)
{
    if (nvnPrivate0) {
        *((WindowOriginMode *)(this->reserved)) = windowOriginMode;
    } else {
        pfncpp_nvnDeviceSetWindowOriginMode(this, windowOriginMode);
    }
}

inline void Device::SetDepthMode_fastpath(DepthMode depthMode)
{
    if (nvnPrivate0) {
        *((DepthMode *)(this->reserved + 4)) = depthMode;
    } else {
        pfncpp_nvnDeviceSetDepthMode(this, depthMode);
    }
}

inline WindowOriginMode Device::GetWindowOriginMode_fastpath() const
{
    if (nvnPrivate0) {
        return (*((WindowOriginMode *)(this->reserved)));
    }
    return pfncpp_nvnDeviceGetWindowOriginMode(this);
}

inline DepthMode Device::GetDepthMode_fastpath() const
{
    if (nvnPrivate0) {
        return (*((DepthMode *)(this->reserved + 4)));
    }
    return pfncpp_nvnDeviceGetDepthMode(this);
}

inline QueueBuilder & QueueBuilder::SetQueuePriority_fastpath(QueuePriority priority)
{
    if (nvnPrivate0) {
        *((QueuePriority *)(this->reserved + 56)) = priority;
    } else {
        pfncpp_nvnQueueBuilderSetQueuePriority(this, priority);
    }
    return *this;
}

inline const Device * QueueBuilder::GetDevice_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Device **)(this->reserved + 8)));
    }
    return pfncpp_nvnQueueBuilderGetDevice(this);
}

inline int QueueBuilder::GetFlags_fastpath() const
{
    if (nvnPrivate0) {
        return (*((int *)(this->reserved + 16)));
    }
    return pfncpp_nvnQueueBuilderGetFlags(this);
}

inline void * QueueBuilder::GetMemory_fastpath() const
{
    if (nvnPrivate0) {
        return (*((void **)(this->reserved + 48)));
    }
    return pfncpp_nvnQueueBuilderGetMemory(this);
}

inline WindowBuilder & WindowBuilder::SetNativeWindow_fastpath(NVNnativeWindow nativeWindow)
{
    if (nvnPrivate0) {
        *((NVNnativeWindow *)(this->reserved + 24)) = nativeWindow;
    } else {
        pfncpp_nvnWindowBuilderSetNativeWindow(this, nativeWindow);
    }
    return *this;
}

inline WindowBuilder & WindowBuilder::SetTextures_fastpath(int numTextures, Texture *const * textures)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 16)) = numTextures;
        *((Texture *const **)(this->reserved + 40)) = textures;
    } else {
        pfncpp_nvnWindowBuilderSetTextures(this, numTextures, textures);
    }
    return *this;
}

inline WindowBuilder & WindowBuilder::SetNumActiveTextures_fastpath(int numActiveTextures)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 20)) = numActiveTextures;
    } else {
        pfncpp_nvnWindowBuilderSetNumActiveTextures(this, numActiveTextures);
    }
    return *this;
}

inline const Device * WindowBuilder::GetDevice_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Device **)(this->reserved + 8)));
    }
    return pfncpp_nvnWindowBuilderGetDevice(this);
}

inline int WindowBuilder::GetNumTextures_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 16)));
    }
    return pfncpp_nvnWindowBuilderGetNumTextures(this);
}

inline NVNnativeWindow WindowBuilder::GetNativeWindow_fastpath() const
{
    if (nvnPrivate0) {
        return (*((NVNnativeWindow *)(this->reserved + 24)));
    }
    return pfncpp_nvnWindowBuilderGetNativeWindow(this);
}

inline int WindowBuilder::GetNumActiveTextures_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 20)));
    }
    return pfncpp_nvnWindowBuilderGetNumActiveTextures(this);
}

inline NVNnativeWindow Window::GetNativeWindow_fastpath() const
{
    if (nvnPrivate0) {
        return (*((NVNnativeWindow *)(this->reserved + 8)));
    }
    return pfncpp_nvnWindowGetNativeWindow(this);
}

inline int Window::GetPresentInterval_fastpath() const
{
    if (nvnPrivate0) {
        return (*((int *)(this->reserved + 40)));
    }
    return pfncpp_nvnWindowGetPresentInterval(this);
}

inline int Window::GetNumTextures_fastpath() const
{
    if (nvnPrivate0) {
        return (*((int *)(this->reserved + 32)));
    }
    return pfncpp_nvnWindowGetNumTextures(this);
}

inline int Program::GetSubtileSize_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint8_t *)(this->reserved)));
    }
    return pfncpp_nvnProgramGetSubtileSize(this);
}

inline const Device * MemoryPoolBuilder::GetDevice_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Device **)(this->reserved + 8)));
    }
    return pfncpp_nvnMemoryPoolBuilderGetDevice(this);
}

inline void * MemoryPoolBuilder::GetMemory_fastpath() const
{
    if (nvnPrivate0) {
        return (*((void **)(this->reserved + 16)));
    }
    return pfncpp_nvnMemoryPoolBuilderGetMemory(this);
}

inline size_t MemoryPoolBuilder::GetSize_fastpath() const
{
    if (nvnPrivate0) {
        return (*((intptr_t *)(this->reserved + 24)));
    }
    return pfncpp_nvnMemoryPoolBuilderGetSize(this);
}

inline MemoryPoolFlags MemoryPoolBuilder::GetFlags_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPoolFlags *)(this->reserved + 4)));
    }
    return pfncpp_nvnMemoryPoolBuilderGetFlags(this);
}

inline const MemoryPool * TexturePool::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved)));
    }
    return pfncpp_nvnTexturePoolGetMemoryPool(this);
}

inline ptrdiff_t TexturePool::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((ptrdiff_t *)(this->reserved + 8)));
    }
    return pfncpp_nvnTexturePoolGetMemoryOffset(this);
}

inline int TexturePool::GetSize_fastpath() const
{
    if (nvnPrivate0) {
        return (*((int *)(this->reserved + 16)));
    }
    return pfncpp_nvnTexturePoolGetSize(this);
}

inline const MemoryPool * SamplerPool::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved)));
    }
    return pfncpp_nvnSamplerPoolGetMemoryPool(this);
}

inline ptrdiff_t SamplerPool::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((ptrdiff_t *)(this->reserved + 8)));
    }
    return pfncpp_nvnSamplerPoolGetMemoryOffset(this);
}

inline int SamplerPool::GetSize_fastpath() const
{
    if (nvnPrivate0) {
        return (*((int *)(this->reserved + 16)));
    }
    return pfncpp_nvnSamplerPoolGetSize(this);
}

inline BufferBuilder & BufferBuilder::SetStorage_fastpath(MemoryPool * pool, ptrdiff_t offset, size_t size)
{
    if (nvnPrivate0) {
        *((MemoryPool **)(this->reserved + 16)) = pool;
        *((uintptr_t *)(this->reserved + 24)) = offset;
        *((intptr_t *)(this->reserved + 32)) = size;
    } else {
        pfncpp_nvnBufferBuilderSetStorage(this, pool, offset, size);
    }
    return *this;
}

inline const Device * BufferBuilder::GetDevice_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Device **)(this->reserved + 8)));
    }
    return pfncpp_nvnBufferBuilderGetDevice(this);
}

inline MemoryPool * BufferBuilder::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved + 16)));
    }
    return pfncpp_nvnBufferBuilderGetMemoryPool(this);
}

inline ptrdiff_t BufferBuilder::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uintptr_t *)(this->reserved + 24)));
    }
    return pfncpp_nvnBufferBuilderGetMemoryOffset(this);
}

inline size_t BufferBuilder::GetSize_fastpath() const
{
    if (nvnPrivate0) {
        return (*((intptr_t *)(this->reserved + 32)));
    }
    return pfncpp_nvnBufferBuilderGetSize(this);
}

inline MemoryPool * Buffer::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved + 16)));
    }
    return pfncpp_nvnBufferGetMemoryPool(this);
}

inline ptrdiff_t Buffer::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uintptr_t *)(this->reserved + 24)));
    }
    return pfncpp_nvnBufferGetMemoryOffset(this);
}

inline size_t Buffer::GetSize_fastpath() const
{
    if (nvnPrivate0) {
        return (*((intptr_t *)(this->reserved + 32)));
    }
    return pfncpp_nvnBufferGetSize(this);
}

inline TextureBuilder & TextureBuilder::SetTarget_fastpath(TextureTarget target)
{
    if (nvnPrivate0) {
        *((TextureTarget *)(this->reserved + 36)) = target;
    } else {
        pfncpp_nvnTextureBuilderSetTarget(this, target);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetWidth_fastpath(int width)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 40)) = width;
    } else {
        pfncpp_nvnTextureBuilderSetWidth(this, width);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetHeight_fastpath(int height)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 44)) = height;
    } else {
        pfncpp_nvnTextureBuilderSetHeight(this, height);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetDepth_fastpath(int depth)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 48)) = depth;
    } else {
        pfncpp_nvnTextureBuilderSetDepth(this, depth);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetSize3D_fastpath(int width, int height, int depth)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 40)) = width;
        *((uint32_t *)(this->reserved + 44)) = height;
        *((uint32_t *)(this->reserved + 48)) = depth;
    } else {
        pfncpp_nvnTextureBuilderSetSize3D(this, width, height, depth);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetLevels_fastpath(int numLevels)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 52)) = numLevels;
    } else {
        pfncpp_nvnTextureBuilderSetLevels(this, numLevels);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetFormat_fastpath(Format format)
{
    if (nvnPrivate0) {
        *((Format *)(this->reserved + 56)) = format;
    } else {
        pfncpp_nvnTextureBuilderSetFormat(this, format);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetSamples_fastpath(int samples)
{
    if (nvnPrivate0) {
        *((uint32_t *)(this->reserved + 60)) = samples;
    } else {
        pfncpp_nvnTextureBuilderSetSamples(this, samples);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetDepthStencilMode_fastpath(TextureDepthStencilMode mode)
{
    if (nvnPrivate0) {
        *((TextureDepthStencilMode *)(this->reserved + 80)) = mode;
    } else {
        pfncpp_nvnTextureBuilderSetDepthStencilMode(this, mode);
    }
    return *this;
}

inline TextureBuilder & TextureBuilder::SetStorage_fastpath(MemoryPool * pool, ptrdiff_t offset)
{
    if (nvnPrivate0) {
        *((MemoryPool **)(this->reserved + 16)) = pool;
        *((ptrdiff_t *)(this->reserved + 24)) = offset;
    } else {
        pfncpp_nvnTextureBuilderSetStorage(this, pool, offset);
    }
    return *this;
}

inline const Device * TextureBuilder::GetDevice_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Device **)(this->reserved + 8)));
    }
    return pfncpp_nvnTextureBuilderGetDevice(this);
}

inline TextureFlags TextureBuilder::GetFlags_fastpath() const
{
    if (nvnPrivate0) {
        return (*((TextureFlags *)(this->reserved + 32)));
    }
    return pfncpp_nvnTextureBuilderGetFlags(this);
}

inline TextureTarget TextureBuilder::GetTarget_fastpath() const
{
    if (nvnPrivate0) {
        return (*((TextureTarget *)(this->reserved + 36)));
    }
    return pfncpp_nvnTextureBuilderGetTarget(this);
}

inline int TextureBuilder::GetWidth_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 40)));
    }
    return pfncpp_nvnTextureBuilderGetWidth(this);
}

inline int TextureBuilder::GetHeight_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 44)));
    }
    return pfncpp_nvnTextureBuilderGetHeight(this);
}

inline int TextureBuilder::GetDepth_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 48)));
    }
    return pfncpp_nvnTextureBuilderGetDepth(this);
}

inline int TextureBuilder::GetLevels_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 52)));
    }
    return pfncpp_nvnTextureBuilderGetLevels(this);
}

inline Format TextureBuilder::GetFormat_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Format *)(this->reserved + 56)));
    }
    return pfncpp_nvnTextureBuilderGetFormat(this);
}

inline int TextureBuilder::GetSamples_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 60)));
    }
    return pfncpp_nvnTextureBuilderGetSamples(this);
}

inline TextureDepthStencilMode TextureBuilder::GetDepthStencilMode_fastpath() const
{
    if (nvnPrivate0) {
        return (*((TextureDepthStencilMode *)(this->reserved + 80)));
    }
    return pfncpp_nvnTextureBuilderGetDepthStencilMode(this);
}

inline ptrdiff_t TextureBuilder::GetStride_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 88)));
    }
    return pfncpp_nvnTextureBuilderGetStride(this);
}

inline uint32_t TextureBuilder::GetGLTextureName_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(this->reserved + 92)));
    }
    return pfncpp_nvnTextureBuilderGetGLTextureName(this);
}

inline MemoryPool * TextureBuilder::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved + 16)));
    }
    return pfncpp_nvnTextureBuilderGetMemoryPool(this);
}

inline ptrdiff_t TextureBuilder::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((ptrdiff_t *)(this->reserved + 24)));
    }
    return pfncpp_nvnTextureBuilderGetMemoryOffset(this);
}

inline SamplerBuilder & SamplerBuilder::SetLodClamp_fastpath(float min, float max)
{
    if (nvnPrivate0) {
        *((float *)(this->reserved + 8)) = min;
        *((float *)(this->reserved + 12)) = max;
    } else {
        pfncpp_nvnSamplerBuilderSetLodClamp(this, min, max);
    }
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetLodBias_fastpath(float bias)
{
    if (nvnPrivate0) {
        *((float *)(this->reserved + 16)) = bias;
    } else {
        pfncpp_nvnSamplerBuilderSetLodBias(this, bias);
    }
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetMaxAnisotropy_fastpath(float maxAniso)
{
    if (nvnPrivate0) {
        *((float *)(this->reserved + 20)) = maxAniso;
    } else {
        pfncpp_nvnSamplerBuilderSetMaxAnisotropy(this, maxAniso);
    }
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetLodSnap_fastpath(float lodSnap)
{
    if (nvnPrivate0) {
        *((float *)(this->reserved + 24)) = lodSnap;
    } else {
        pfncpp_nvnSamplerBuilderSetLodSnap(this, lodSnap);
    }
    return *this;
}

inline const Device * SamplerBuilder::GetDevice_fastpath() const
{
    if (nvnPrivate0) {
        return (*((Device **)(this->reserved)));
    }
    return pfncpp_nvnSamplerBuilderGetDevice(this);
}

inline float SamplerBuilder::GetLodBias_fastpath() const
{
    if (nvnPrivate0) {
        return (*((float *)(this->reserved + 16)));
    }
    return pfncpp_nvnSamplerBuilderGetLodBias(this);
}

inline float SamplerBuilder::GetMaxAnisotropy_fastpath() const
{
    if (nvnPrivate0) {
        return (*((float *)(this->reserved + 20)));
    }
    return pfncpp_nvnSamplerBuilderGetMaxAnisotropy(this);
}

inline float SamplerBuilder::GetLodSnap_fastpath() const
{
    if (nvnPrivate0) {
        return (*((float *)(this->reserved + 24)));
    }
    return pfncpp_nvnSamplerBuilderGetLodSnap(this);
}

inline BlendState & BlendState::SetBlendTarget_fastpath(int target)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~7U)) | ((uint32_t)target));
    } else {
        pfncpp_nvnBlendStateSetBlendTarget(this, target);
    }
    return *this;
}

inline BlendState & BlendState::SetBlendFunc_fastpath(BlendFunc srcFunc, BlendFunc dstFunc, BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[1]) = (((((uint32_t *)((*this).reserved))[1]) & (~127U)) | ((uint32_t)srcFunc));
        (((uint32_t *)((*this).reserved))[1]) = (((((uint32_t *)((*this).reserved))[1]) & (~32512U)) | (((uint32_t)dstFunc) << 8));
        (((uint32_t *)((*this).reserved))[1]) = (((((uint32_t *)((*this).reserved))[1]) & (~8323072U)) | (((uint32_t)srcFuncAlpha) << 16));
        (((uint32_t *)((*this).reserved))[1]) = (((((uint32_t *)((*this).reserved))[1]) & (~2130706432U)) | (((uint32_t)dstFuncAlpha) << 24));
    } else {
        pfncpp_nvnBlendStateSetBlendFunc(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
    }
    return *this;
}

inline BlendState & BlendState::SetBlendEquation_fastpath(BlendEquation modeRGB, BlendEquation modeAlpha)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~117440512U)) | (((uint32_t)modeRGB) << 24));
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~1879048192U)) | (((uint32_t)modeAlpha) << 28));
    } else {
        pfncpp_nvnBlendStateSetBlendEquation(this, modeRGB, modeAlpha);
    }
    return *this;
}

inline BlendState & BlendState::SetAdvancedMode_fastpath(BlendAdvancedMode overlap)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~16128U)) | (((uint32_t)overlap) << 8));
    } else {
        pfncpp_nvnBlendStateSetAdvancedMode(this, overlap);
    }
    return *this;
}

inline BlendState & BlendState::SetAdvancedOverlap_fastpath(BlendAdvancedOverlap overlap)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~196608U)) | (((uint32_t)overlap) << 16));
    } else {
        pfncpp_nvnBlendStateSetAdvancedOverlap(this, overlap);
    }
    return *this;
}

inline BlendState & BlendState::SetAdvancedPremultipliedSrc_fastpath(NVNboolean premultiplied)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~262144U)) | (((uint32_t)premultiplied != 0) << 18));
    } else {
        pfncpp_nvnBlendStateSetAdvancedPremultipliedSrc(this, premultiplied);
    }
    return *this;
}

inline BlendState & BlendState::SetAdvancedNormalizedDst_fastpath(NVNboolean normalized)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~524288U)) | (((uint32_t)normalized != 0) << 19));
    } else {
        pfncpp_nvnBlendStateSetAdvancedNormalizedDst(this, normalized);
    }
    return *this;
}

inline int BlendState::GetBlendTarget_fastpath() const
{
    if (nvnPrivate0) {
        return (int)((((const uint32_t *)((*this).reserved))[0]) & 7U);
    }
    return pfncpp_nvnBlendStateGetBlendTarget(this);
}

inline NVNboolean BlendState::GetAdvancedPremultipliedSrc_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 18) & 1U);
    }
    return pfncpp_nvnBlendStateGetAdvancedPremultipliedSrc(this);
}

inline NVNboolean BlendState::GetAdvancedNormalizedDst_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 19) & 1U);
    }
    return pfncpp_nvnBlendStateGetAdvancedNormalizedDst(this);
}

inline ColorState & ColorState::SetLogicOp_fastpath(LogicOp logicOp)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~16711680U)) | (((uint32_t)logicOp) << 16));
    } else {
        pfncpp_nvnColorStateSetLogicOp(this, logicOp);
    }
    return *this;
}

inline ColorState & ColorState::SetAlphaTest_fastpath(AlphaFunc alphaTest)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~251658240U)) | (((uint32_t)alphaTest) << 24));
    } else {
        pfncpp_nvnColorStateSetAlphaTest(this, alphaTest);
    }
    return *this;
}

inline MultisampleState & MultisampleState::SetMultisampleEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~1U)) | ((uint32_t)enable != 0));
    } else {
        pfncpp_nvnMultisampleStateSetMultisampleEnable(this, enable);
    }
    return *this;
}

inline MultisampleState & MultisampleState::SetSamples_fastpath(int samples)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~7936U)) | (((uint32_t)samples) << 8));
    } else {
        pfncpp_nvnMultisampleStateSetSamples(this, samples);
    }
    return *this;
}

inline MultisampleState & MultisampleState::SetAlphaToCoverageEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~2U)) | (((uint32_t)enable != 0) << 1));
    } else {
        pfncpp_nvnMultisampleStateSetAlphaToCoverageEnable(this, enable);
    }
    return *this;
}

inline MultisampleState & MultisampleState::SetAlphaToCoverageDither_fastpath(NVNboolean dither)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~4U)) | (((uint32_t)dither != 0) << 2));
    } else {
        pfncpp_nvnMultisampleStateSetAlphaToCoverageDither(this, dither);
    }
    return *this;
}

inline NVNboolean MultisampleState::GetMultisampleEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)((((const uint32_t *)((*this).reserved))[0]) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetMultisampleEnable(this);
}

inline int MultisampleState::GetSamples_fastpath() const
{
    if (nvnPrivate0) {
        return (int)(((((const uint32_t *)((*this).reserved))[0]) >> 8) & 31U);
    }
    return pfncpp_nvnMultisampleStateGetSamples(this);
}

inline NVNboolean MultisampleState::GetAlphaToCoverageEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 1) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetAlphaToCoverageEnable(this);
}

inline NVNboolean MultisampleState::GetAlphaToCoverageDither_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 2) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetAlphaToCoverageDither(this);
}

inline MultisampleState & MultisampleState::SetRasterSamples_fastpath(int rasterSamples)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~1015808U)) | (((uint32_t)rasterSamples) << 15));
    } else {
        pfncpp_nvnMultisampleStateSetRasterSamples(this, rasterSamples);
    }
    return *this;
}

inline int MultisampleState::GetRasterSamples_fastpath() const
{
    if (nvnPrivate0) {
        return (int)(((((const uint32_t *)((*this).reserved))[0]) >> 15) & 31U);
    }
    return pfncpp_nvnMultisampleStateGetRasterSamples(this);
}

inline MultisampleState & MultisampleState::SetCoverageModulationMode_fastpath(CoverageModulationMode mode)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~24576U)) | (((uint32_t)mode) << 13));
    } else {
        pfncpp_nvnMultisampleStateSetCoverageModulationMode(this, mode);
    }
    return *this;
}

inline MultisampleState & MultisampleState::SetCoverageToColorEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~1048576U)) | (((uint32_t)enable != 0) << 20));
    } else {
        pfncpp_nvnMultisampleStateSetCoverageToColorEnable(this, enable);
    }
    return *this;
}

inline NVNboolean MultisampleState::GetCoverageToColorEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 20) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetCoverageToColorEnable(this);
}

inline MultisampleState & MultisampleState::SetCoverageToColorOutput_fastpath(int color)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~14680064U)) | (((uint32_t)color) << 21));
    } else {
        pfncpp_nvnMultisampleStateSetCoverageToColorOutput(this, color);
    }
    return *this;
}

inline int MultisampleState::GetCoverageToColorOutput_fastpath() const
{
    if (nvnPrivate0) {
        return (int)(((((const uint32_t *)((*this).reserved))[0]) >> 20) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetCoverageToColorOutput(this);
}

inline MultisampleState & MultisampleState::SetSampleLocationsEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~8U)) | (((uint32_t)enable != 0) << 3));
    } else {
        pfncpp_nvnMultisampleStateSetSampleLocationsEnable(this, enable);
    }
    return *this;
}

inline NVNboolean MultisampleState::GetSampleLocationsEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 3) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetSampleLocationsEnable(this);
}

inline MultisampleState & MultisampleState::SetSampleLocationsGridEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~16U)) | (((uint32_t)enable != 0) << 4));
    } else {
        pfncpp_nvnMultisampleStateSetSampleLocationsGridEnable(this, enable);
    }
    return *this;
}

inline NVNboolean MultisampleState::GetSampleLocationsGridEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 4) & 1U);
    }
    return pfncpp_nvnMultisampleStateGetSampleLocationsGridEnable(this);
}

inline PolygonState & PolygonState::SetCullFace_fastpath(Face face)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~3U)) | ((uint32_t)face));
    } else {
        pfncpp_nvnPolygonStateSetCullFace(this, face);
    }
    return *this;
}

inline PolygonState & PolygonState::SetFrontFace_fastpath(FrontFace face)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~4U)) | (((uint32_t)face) << 2));
    } else {
        pfncpp_nvnPolygonStateSetFrontFace(this, face);
    }
    return *this;
}

inline PolygonState & PolygonState::SetPolygonMode_fastpath(PolygonMode polygonMode)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~24U)) | (((uint32_t)polygonMode) << 3));
    } else {
        pfncpp_nvnPolygonStateSetPolygonMode(this, polygonMode);
    }
    return *this;
}

inline DepthStencilState & DepthStencilState::SetDepthTestEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~1U)) | ((uint32_t)enable != 0));
    } else {
        pfncpp_nvnDepthStencilStateSetDepthTestEnable(this, enable);
    }
    return *this;
}

inline DepthStencilState & DepthStencilState::SetDepthWriteEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~2U)) | (((uint32_t)enable != 0) << 1));
    } else {
        pfncpp_nvnDepthStencilStateSetDepthWriteEnable(this, enable);
    }
    return *this;
}

inline DepthStencilState & DepthStencilState::SetDepthFunc_fastpath(DepthFunc func)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~240U)) | (((uint32_t)func) << 4));
    } else {
        pfncpp_nvnDepthStencilStateSetDepthFunc(this, func);
    }
    return *this;
}

inline DepthStencilState & DepthStencilState::SetStencilTestEnable_fastpath(NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~4U)) | (((uint32_t)enable != 0) << 2));
    } else {
        pfncpp_nvnDepthStencilStateSetStencilTestEnable(this, enable);
    }
    return *this;
}

inline NVNboolean DepthStencilState::GetDepthTestEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)((((const uint32_t *)((*this).reserved))[0]) & 1U);
    }
    return pfncpp_nvnDepthStencilStateGetDepthTestEnable(this);
}

inline NVNboolean DepthStencilState::GetDepthWriteEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 1) & 1U);
    }
    return pfncpp_nvnDepthStencilStateGetDepthWriteEnable(this);
}

inline NVNboolean DepthStencilState::GetStencilTestEnable_fastpath() const
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*this).reserved))[0]) >> 2) & 1U);
    }
    return pfncpp_nvnDepthStencilStateGetStencilTestEnable(this);
}

inline VertexAttribState & VertexAttribState::SetStreamIndex_fastpath(int streamIndex)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~31U)) | ((uint32_t)streamIndex));
    } else {
        pfncpp_nvnVertexAttribStateSetStreamIndex(this, streamIndex);
    }
    return *this;
}

inline int VertexAttribState::GetStreamIndex_fastpath() const
{
    if (nvnPrivate0) {
        return (int)((((const uint32_t *)((*this).reserved))[0]) & 31U);
    }
    return pfncpp_nvnVertexAttribStateGetStreamIndex(this);
}

inline VertexStreamState & VertexStreamState::SetStride_fastpath(ptrdiff_t stride)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[0]) = (((((uint32_t *)((*this).reserved))[0]) & (~4294967295U)) | ((uint32_t)stride));
    } else {
        pfncpp_nvnVertexStreamStateSetStride(this, stride);
    }
    return *this;
}

inline VertexStreamState & VertexStreamState::SetDivisor_fastpath(int divisor)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*this).reserved))[1]) = (((((uint32_t *)((*this).reserved))[1]) & (~4294967295U)) | ((uint32_t)divisor));
    } else {
        pfncpp_nvnVertexStreamStateSetDivisor(this, divisor);
    }
    return *this;
}

inline ptrdiff_t VertexStreamState::GetStride_fastpath() const
{
    if (nvnPrivate0) {
        return (ptrdiff_t)((((const uint32_t *)((*this).reserved))[0]) & 4294967295U);
    }
    return pfncpp_nvnVertexStreamStateGetStride(this);
}

inline int VertexStreamState::GetDivisor_fastpath() const
{
    if (nvnPrivate0) {
        return (int)((((const uint32_t *)((*this).reserved))[1]) & 4294967295U);
    }
    return pfncpp_nvnVertexStreamStateGetDivisor(this);
}

inline void CommandBuffer::SetCommandMemoryCallbackEnabled_fastpath(NVNboolean enabled)
{
    if (nvnPrivate0) {
        *(this->reserved + 22) = enabled;
    } else {
        pfncpp_nvnCommandBufferSetCommandMemoryCallbackEnabled(this, enabled);
    }
}

inline void CommandBuffer::BeginRecording_fastpath()
{
    *(this->reserved + 16) = 1;
    uint32_t * v0 = *((uint32_t **)(this->reserved + 32));
    if (nvnPrivate0 && v0 + 4 <= (*((uint32_t **)(this->reserved + 40)))) {
        *((void **)(this->reserved + 64)) = (*((void **)(this->reserved)));
        *((uint32_t **)(this->reserved + 72)) = v0;
        *((void **)(this->reserved + 80)) = 0;
        *(this->reserved + 17) = 1;
        *(this->reserved + 18) = 0;
        v0[0] = 4294967041U;
        v0[1] = 4294967295U;
        v0[2] = 0;
        v0[3] = 0;
        *((uint32_t **)(this->reserved + 32)) = v0 + 4;
        return;
    }
    pfncpp_nvnCommandBufferBeginRecording(this);
}

inline void CommandBuffer::CallCommands_fastpath(int numCommands, NVN_NOESCAPE const CommandHandle * handles)
{
    *(this->reserved + 16) = 1;
    if (!nvnPrivate0) {
        pfncpp_nvnCommandBufferCallCommands(this, numCommands, handles);
        return;
    }
    uint64_t * v0 = *((uint64_t **)(this->reserved + 80));
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    uint64_t * v3 = *((uint64_t **)(this->reserved + 40));
    uint64_t * v4 = *((uint64_t **)(this->reserved + 32));
    for (int v5 = 0; v5 < numCommands; ++v5) {
        uint64_t * v6 = (uint64_t *)(handles[v5] & 281474976710654ULL);
        uint64_t v7 = handles[v5] >> 48;
        if (!(handles[v5] & 1) || (v6[3 * v7] & 255) != 2 || v4 + 3 * v7 + 4 > v3) {
            *((uint64_t **)(this->reserved + 32)) = v4;
            pfncpp_nvnCommandBufferCallCommands(this, numCommands - v5, handles + v5);
            return;
        }
        if (v5 == 0) {
            if (!v0) {
                *v4 = 3;
                v0 = v4;
                *((uint64_t **)(this->reserved + 80)) = v0;
                v4++;
            }
            if (v1 != v2) {
                *v4++ = (*((uint64_t *)(this->reserved + 88))) + (v1 - (*((uint32_t **)(this->reserved + 48)))) * 4;
                *v4++ = (uint64_t)(uintptr_t)v1;
                *v4++ = (v2 - v1) | 12884901888ULL;
                *v0 += 4294967296ULL;
                *((uint32_t **)(this->reserved + 64)) = v2;
            }
        }
        memcpy(v4, v6, (size_t)(24 * v7));
        v4 += 3 * v7;
        *v0 += v7 << 32ULL;
    }
    *((uint64_t **)(this->reserved + 32)) = v4;
}

inline void CommandBuffer::BindVertexBuffer_fastpath(int index, BufferAddress buffer, size_t size)
{
    *(this->reserved + 16) = 1;
#ifndef _WIN32
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(this->reserved));
    if (nvnPrivate0 && (v1 + 6 <= (*((t0 **)(this->reserved + 8))))) {
        uint64_t v2;
        uint64_t v3;
        if (size) {
            v2 = buffer;
            v3 = v2 + size - 1;
        } else {
            v2 = 4096;
            v3 = 4095;
        }
        v1[0].u = (537001984 | ((7172 + index * 16) >> 2));
        v1[1].u = ((uint32_t)((v2 >> 32) & 4294967295U));
        v1[2].u = ((uint32_t)(v2 & 4294967295U));
        v1 += 3;
        v1[0].u = (537001984 | ((7936 + index * 8) >> 2));
        v1[1].u = ((uint32_t)((v3 >> 32) & 4294967295U));
        v1[2].u = ((uint32_t)(v3 & 4294967295U));
        v1 += 3;
        *((t0 **)(this->reserved)) = v1;
        return;
    }
#endif
    pfncpp_nvnCommandBufferBindVertexBuffer(this, index, buffer, size);
}

inline void CommandBuffer::BindVertexBuffers_fastpath(int first, int count, NVN_NOESCAPE const BufferRange * buffers)
{
    *(this->reserved + 16) = 1;
#ifndef _WIN32
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(this->reserved));
    if (nvnPrivate0 && (v1 + 6 * count <= (*((t0 **)(this->reserved + 8))))) {
        for (int v2 = 0; v2 < count; ++v2) {
            uint64_t v3;
            uint64_t v4;
            if (buffers[v2].size) {
                v3 = (uint64_t)buffers[v2].address;
                v4 = v3 + buffers[v2].size - 1;
            } else {
                v3 = 4096;
                v4 = 4095;
            }
            v1[0].u = (537001984 | ((7172 + (first + v2) * 16) >> 2));
            v1[1].u = ((uint32_t)((v3 >> 32) & 4294967295U));
            v1[2].u = ((uint32_t)(v3 & 4294967295U));
            v1 += 3;
            v1[0].u = (537001984 | ((7936 + (first + v2) * 8) >> 2));
            v1[1].u = ((uint32_t)((v4 >> 32) & 4294967295U));
            v1[2].u = ((uint32_t)(v4 & 4294967295U));
            v1 += 3;
        }
        *((t0 **)(this->reserved)) = v1;
        return;
    }
#endif
    pfncpp_nvnCommandBufferBindVertexBuffers(this, first, count, buffers);
}

inline void CommandBuffer::BindUniformBuffer_fastpath(ShaderStage stage, int index, BufferAddress buffer, size_t size)
{
    *(this->reserved + 16) = 1;
    if (nvnPrivate0 && stage != ShaderStage::COMPUTE) {
        typedef union {
            float f;
            int32_t i;
            uint32_t u;
        } t0;
        t0 * v1 = *((t0 **)(this->reserved));
        if (v1 + 6 <= (*((t0 **)(this->reserved + 8)))) {
            static const uint32_t v2[5] = { 9232, 9360, 9328, 9264, 9296 };
            if (size == 0) {
                const uint32_t v3 = ((3 + index) & 31U) << 4;
                v1[0].u = (2147483648U | (v3 << 16) | ((v2[stage]) >> 2));
                v1 += 1;
            } else {
                size = ((size + 255) & ~255);
                v1[0].u = 537069792;
                v1[1].u = (uint32_t)size;
                v1[2].u = ((uint32_t)((buffer >> 32) & 4294967295U));
                v1[3].u = ((uint32_t)(buffer & 4294967295U));
                v1 += 4;
                const uint32_t v4 = (((3 + index) & 31U) << 4) | 1U;
                v1[0].u = (2147483648U | (v4 << 16) | ((v2[stage]) >> 2));
                v1 += 1;
            }
            *((t0 **)(this->reserved)) = v1;
            return;
        }
    }
    pfncpp_nvnCommandBufferBindUniformBuffer(this, stage, index, buffer, size);
}

inline void CommandBuffer::BindUniformBuffers_fastpath(ShaderStage stage, int first, int count, NVN_NOESCAPE const BufferRange * buffers)
{
    *(this->reserved + 16) = 1;
    if (nvnPrivate0 && stage != ShaderStage::COMPUTE) {
        typedef union {
            float f;
            int32_t i;
            uint32_t u;
        } t0;
        t0 * v1 = *((t0 **)(this->reserved));
        if (v1 + 6 * count <= (*((t0 **)(this->reserved + 8)))) {
            static const uint32_t v2[5] = { 9232, 9360, 9328, 9264, 9296 };
            for (int v3 = 0; v3 < count; ++v3) {
                uint64_t v4 = buffers[v3].size;
                if (v4 == 0) {
                    const uint32_t v5 = ((3 + first + v3) & 31U) << 4;
                    v1[0].u = (2147483648U | (v5 << 16) | ((v2[stage]) >> 2));
                    v1 += 1;
                } else {
                    v4 = ((v4 + 255) & ~255);
                    v1[0].u = 537069792;
                    v1[1].u = (uint32_t)v4;
                    v1[2].u = ((uint32_t)((((uint64_t)(buffers[v3].address)) >> 32) & 4294967295U));
                    v1[3].u = ((uint32_t)(((uint64_t)(buffers[v3].address)) & 4294967295U));
                    v1 += 4;
                    const uint32_t v6 = (((3 + first + v3) & 31U) << 4) | 1U;
                    v1[0].u = (2147483648U | (v6 << 16) | ((v2[stage]) >> 2));
                    v1 += 1;
                }
            }
            *((t0 **)(this->reserved)) = v1;
            return;
        }
    }
    pfncpp_nvnCommandBufferBindUniformBuffers(this, stage, first, count, buffers);
}

inline void CommandBuffer::BindUniformBuffersDeferred_fastpath(ShaderStage stage, int first, int count, const BufferRange * buffers)
{
    *(this->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(this->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(this->reserved + 40))))) {
        pfncpp_nvnCommandBufferBindUniformBuffersDeferred(this, stage, first, count, buffers);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(this->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(this->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(this->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(this->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(this->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)26) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)buffers;
    v0 += 2;
    *((uint64_t **)(this->reserved + 32)) = v0;
    *(this->reserved + 18) = 1;
}

inline void CommandBuffer::BindStorageBuffersDeferred_fastpath(ShaderStage stage, int first, int count, const BufferRange * buffers)
{
    *(this->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(this->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(this->reserved + 40))))) {
        pfncpp_nvnCommandBufferBindStorageBuffersDeferred(this, stage, first, count, buffers);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(this->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(this->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(this->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(this->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(this->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)27) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)buffers;
    v0 += 2;
    *((uint64_t **)(this->reserved + 32)) = v0;
    *(this->reserved + 18) = 1;
}

inline void CommandBuffer::BindTexturesDeferred_fastpath(ShaderStage stage, int first, int count, const TextureHandle * textures)
{
    *(this->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(this->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(this->reserved + 40))))) {
        pfncpp_nvnCommandBufferBindTexturesDeferred(this, stage, first, count, textures);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(this->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(this->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(this->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(this->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(this->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)23) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)textures;
    v0 += 2;
    *((uint64_t **)(this->reserved + 32)) = v0;
    *(this->reserved + 18) = 1;
}

inline void CommandBuffer::BindImagesDeferred_fastpath(ShaderStage stage, int first, int count, const ImageHandle * images)
{
    *(this->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(this->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(this->reserved + 40))))) {
        pfncpp_nvnCommandBufferBindImagesDeferred(this, stage, first, count, images);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(this->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(this->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(this->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(this->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(this->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)28) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)images;
    v0 += 2;
    *((uint64_t **)(this->reserved + 32)) = v0;
    *(this->reserved + 18) = 1;
}

inline void CommandBuffer::DrawElements_fastpath(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer)
{
    *(this->reserved + 16) = 1;
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(this->reserved));
    if (nvnPrivate0 && (v1 + 6 <= (*((t0 **)(this->reserved + 8))))) {
        const uint64_t v2 = indexBuffer;
        v1[0].u = 2684685880U;
        v1[1].u = mode;
        v1[2].u = ((uint32_t)((((uint64_t)v2) >> 32) & 4294967295U));
        v1[3].u = ((uint32_t)(((uint64_t)v2) & 4294967295U));
        v1[4].u = type;
        v1[5].u = count;
        v1 += 6;
        *((t0 **)(this->reserved)) = v1;
        return;
    }
    pfncpp_nvnCommandBufferDrawElements(this, mode, type, count, indexBuffer);
}

inline void CommandBuffer::BindSeparateTexturesDeferred_fastpath(ShaderStage stage, int first, int count, const SeparateTextureHandle * textureHandles)
{
    *(this->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(this->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(this->reserved + 40))))) {
        pfncpp_nvnCommandBufferBindSeparateTexturesDeferred(this, stage, first, count, textureHandles);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(this->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(this->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(this->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(this->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(this->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)24) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)textureHandles;
    v0 += 2;
    *((uint64_t **)(this->reserved + 32)) = v0;
    *(this->reserved + 18) = 1;
}

inline void CommandBuffer::BindSeparateSamplersDeferred_fastpath(ShaderStage stage, int first, int count, const SeparateSamplerHandle * samplerHandles)
{
    *(this->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(this->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(this->reserved + 40))))) {
        pfncpp_nvnCommandBufferBindSeparateSamplersDeferred(this, stage, first, count, samplerHandles);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(this->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(this->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(this->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(this->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(this->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(this->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(this->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)25) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)samplerHandles;
    v0 += 2;
    *((uint64_t **)(this->reserved + 32)) = v0;
    *(this->reserved + 18) = 1;
}

inline void CommandBuffer::UpdateUniformBuffer_fastpath(BufferAddress buffer, size_t bufferSize, ptrdiff_t updateOffset, size_t updateSize, NVN_NOESCAPE const void * data)
{
    *(this->reserved + 16) = 1;
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(this->reserved));
    uint32_t v2 = (uint32_t)updateSize / 4;
    if (nvnPrivate0 && (v2 <= 8191) && (v1 + 9 + v2 <= (*((t0 **)(this->reserved + 8))))) {
        if (bufferSize == 0) {
            return;
        }
        v1[0].u = 2433875970U;
        v1 += 1;
        int v4 = (bufferSize + 255) & ~255;
        v1[0].u = 537135328U;
        v1[1].u = v4;
        v1[2].u = ((uint32_t)((buffer >> 32) & 4294967295U));
        v1[3].u = ((uint32_t)(buffer & 4294967295U));
        v1[4].u = (uint32_t)updateOffset;
        v1 += 5;
        v1[0].u = 2147485323U;
        v1 += 1;
        v1[0].u = (1610612736 | (v2 << 16) | 2276);
        v1 += 1;
        memcpy(v1, data, updateSize);
        v1 += v2;
        v1[0].u = 2432696322U;
        v1 += 1;
        *((t0 **)(this->reserved)) = v1;
        return;
    }
    pfncpp_nvnCommandBufferUpdateUniformBuffer(this, buffer, bufferSize, updateOffset, updateSize, data);
}

inline const MemoryPool * EventBuilder::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved)));
    }
    return pfncpp_nvnEventBuilderGetMemoryPool(this);
}

inline int64_t EventBuilder::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint64_t *)(this->reserved + 8)));
    }
    return pfncpp_nvnEventBuilderGetMemoryOffset(this);
}

inline const MemoryPool * Event::GetMemoryPool_fastpath() const
{
    if (nvnPrivate0) {
        return (*((MemoryPool **)(this->reserved + 16)));
    }
    return pfncpp_nvnEventGetMemoryPool(this);
}

inline int64_t Event::GetMemoryOffset_fastpath() const
{
    if (nvnPrivate0) {
        return (*((uint64_t *)(this->reserved + 24)));
    }
    return pfncpp_nvnEventGetMemoryOffset(this);
}

#ifdef NVN_OVERLOAD_CPP_OBJECTS
} // namespace nvn::objects
#endif
} // namespace nvn

#endif // __nvn_cppfastpath_h_
