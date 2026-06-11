
/*--------------------------------------------------------------------------------*
  Copyright (C)Nintendo All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/



/// \file nvn_Fastpath.h
///      Implementation of NVN C interface fastpath functions for API version 55.13.

#ifndef __nvn_fastpath_h_
#define __nvn_fastpath_h_

#ifdef NVN_PROTOTYPES
#error To use NVN fastpath functions, please be sure to not define NVN_PROTOTYPES before including "nvn_Fastpath.h".
#endif

#include "nvn.h"
#include "nvn_FuncPtr.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
__declspec(dllimport) uint32_t nvnPrivate0;
#else
extern uint32_t nvnPrivate0;
#endif

static NVNINLINE NVNdeviceFlagBits NVNAPIENTRY nvnDeviceBuilderGetFlags_fastpath(const NVNdeviceBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdeviceFlagBits *)(builder->reserved + 4)));
    }
    return pfnc_nvnDeviceBuilderGetFlags(builder);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceSetWindowOriginMode_fastpath(NVNdevice * device, NVNwindowOriginMode windowOriginMode)
{
    if (nvnPrivate0) {
        *((NVNwindowOriginMode *)(device->reserved)) = windowOriginMode;
    } else {
        pfnc_nvnDeviceSetWindowOriginMode(device, windowOriginMode);
    }
}

static NVNINLINE void NVNAPIENTRY nvnDeviceSetDepthMode_fastpath(NVNdevice * device, NVNdepthMode depthMode)
{
    if (nvnPrivate0) {
        *((NVNdepthMode *)(device->reserved + 4)) = depthMode;
    } else {
        pfnc_nvnDeviceSetDepthMode(device, depthMode);
    }
}

static NVNINLINE NVNwindowOriginMode NVNAPIENTRY nvnDeviceGetWindowOriginMode_fastpath(const NVNdevice * device)
{
    if (nvnPrivate0) {
        return (*((NVNwindowOriginMode *)(device->reserved)));
    }
    return pfnc_nvnDeviceGetWindowOriginMode(device);
}

static NVNINLINE NVNdepthMode NVNAPIENTRY nvnDeviceGetDepthMode_fastpath(const NVNdevice * device)
{
    if (nvnPrivate0) {
        return (*((NVNdepthMode *)(device->reserved + 4)));
    }
    return pfnc_nvnDeviceGetDepthMode(device);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetQueuePriority_fastpath(NVNqueueBuilder * builder, NVNqueuePriority priority)
{
    if (nvnPrivate0) {
        *((NVNqueuePriority *)(builder->reserved + 56)) = priority;
    } else {
        pfnc_nvnQueueBuilderSetQueuePriority(builder, priority);
    }
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnQueueBuilderGetDevice_fastpath(const NVNqueueBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdevice **)(builder->reserved + 8)));
    }
    return pfnc_nvnQueueBuilderGetDevice(builder);
}

static NVNINLINE int NVNAPIENTRY nvnQueueBuilderGetFlags_fastpath(const NVNqueueBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((int *)(builder->reserved + 16)));
    }
    return pfnc_nvnQueueBuilderGetFlags(builder);
}

static NVNINLINE void * NVNAPIENTRY nvnQueueBuilderGetMemory_fastpath(const NVNqueueBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((void **)(builder->reserved + 48)));
    }
    return pfnc_nvnQueueBuilderGetMemory(builder);
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetNativeWindow_fastpath(NVNwindowBuilder * builder, NVNnativeWindow nativeWindow)
{
    if (nvnPrivate0) {
        *((NVNnativeWindow *)(builder->reserved + 24)) = nativeWindow;
    } else {
        pfnc_nvnWindowBuilderSetNativeWindow(builder, nativeWindow);
    }
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetTextures_fastpath(NVNwindowBuilder * builder, int numTextures, NVNtexture *const * textures)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 16)) = numTextures;
        *((NVNtexture *const **)(builder->reserved + 40)) = textures;
    } else {
        pfnc_nvnWindowBuilderSetTextures(builder, numTextures, textures);
    }
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetNumActiveTextures_fastpath(NVNwindowBuilder * builder, int numActiveTextures)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 20)) = numActiveTextures;
    } else {
        pfnc_nvnWindowBuilderSetNumActiveTextures(builder, numActiveTextures);
    }
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnWindowBuilderGetDevice_fastpath(const NVNwindowBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdevice **)(builder->reserved + 8)));
    }
    return pfnc_nvnWindowBuilderGetDevice(builder);
}

static NVNINLINE int NVNAPIENTRY nvnWindowBuilderGetNumTextures_fastpath(const NVNwindowBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 16)));
    }
    return pfnc_nvnWindowBuilderGetNumTextures(builder);
}

static NVNINLINE NVNnativeWindow NVNAPIENTRY nvnWindowBuilderGetNativeWindow_fastpath(const NVNwindowBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNnativeWindow *)(builder->reserved + 24)));
    }
    return pfnc_nvnWindowBuilderGetNativeWindow(builder);
}

static NVNINLINE int NVNAPIENTRY nvnWindowBuilderGetNumActiveTextures_fastpath(const NVNwindowBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 20)));
    }
    return pfnc_nvnWindowBuilderGetNumActiveTextures(builder);
}

static NVNINLINE NVNnativeWindow NVNAPIENTRY nvnWindowGetNativeWindow_fastpath(const NVNwindow * window)
{
    if (nvnPrivate0) {
        return (*((NVNnativeWindow *)(window->reserved + 8)));
    }
    return pfnc_nvnWindowGetNativeWindow(window);
}

static NVNINLINE int NVNAPIENTRY nvnWindowGetPresentInterval_fastpath(const NVNwindow * window)
{
    if (nvnPrivate0) {
        return (*((int *)(window->reserved + 40)));
    }
    return pfnc_nvnWindowGetPresentInterval(window);
}

static NVNINLINE int NVNAPIENTRY nvnWindowGetNumTextures_fastpath(const NVNwindow * window)
{
    if (nvnPrivate0) {
        return (*((int *)(window->reserved + 32)));
    }
    return pfnc_nvnWindowGetNumTextures(window);
}

static NVNINLINE int NVNAPIENTRY nvnProgramGetSubtileSize_fastpath(const NVNprogram * program)
{
    if (nvnPrivate0) {
        return (*((uint8_t *)(program->reserved)));
    }
    return pfnc_nvnProgramGetSubtileSize(program);
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnMemoryPoolBuilderGetDevice_fastpath(const NVNmemoryPoolBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdevice **)(builder->reserved + 8)));
    }
    return pfnc_nvnMemoryPoolBuilderGetDevice(builder);
}

static NVNINLINE void * NVNAPIENTRY nvnMemoryPoolBuilderGetMemory_fastpath(const NVNmemoryPoolBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((void **)(builder->reserved + 16)));
    }
    return pfnc_nvnMemoryPoolBuilderGetMemory(builder);
}

static NVNINLINE size_t NVNAPIENTRY nvnMemoryPoolBuilderGetSize_fastpath(const NVNmemoryPoolBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((intptr_t *)(builder->reserved + 24)));
    }
    return pfnc_nvnMemoryPoolBuilderGetSize(builder);
}

static NVNINLINE NVNmemoryPoolFlags NVNAPIENTRY nvnMemoryPoolBuilderGetFlags_fastpath(const NVNmemoryPoolBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPoolFlags *)(builder->reserved + 4)));
    }
    return pfnc_nvnMemoryPoolBuilderGetFlags(builder);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnTexturePoolGetMemoryPool_fastpath(const NVNtexturePool * pool)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(pool->reserved)));
    }
    return pfnc_nvnTexturePoolGetMemoryPool(pool);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTexturePoolGetMemoryOffset_fastpath(const NVNtexturePool * pool)
{
    if (nvnPrivate0) {
        return (*((ptrdiff_t *)(pool->reserved + 8)));
    }
    return pfnc_nvnTexturePoolGetMemoryOffset(pool);
}

static NVNINLINE int NVNAPIENTRY nvnTexturePoolGetSize_fastpath(const NVNtexturePool * pool)
{
    if (nvnPrivate0) {
        return (*((int *)(pool->reserved + 16)));
    }
    return pfnc_nvnTexturePoolGetSize(pool);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnSamplerPoolGetMemoryPool_fastpath(const NVNsamplerPool * pool)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(pool->reserved)));
    }
    return pfnc_nvnSamplerPoolGetMemoryPool(pool);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnSamplerPoolGetMemoryOffset_fastpath(const NVNsamplerPool * pool)
{
    if (nvnPrivate0) {
        return (*((ptrdiff_t *)(pool->reserved + 8)));
    }
    return pfnc_nvnSamplerPoolGetMemoryOffset(pool);
}

static NVNINLINE int NVNAPIENTRY nvnSamplerPoolGetSize_fastpath(const NVNsamplerPool * pool)
{
    if (nvnPrivate0) {
        return (*((int *)(pool->reserved + 16)));
    }
    return pfnc_nvnSamplerPoolGetSize(pool);
}

static NVNINLINE void NVNAPIENTRY nvnBufferBuilderSetStorage_fastpath(NVNbufferBuilder * builder, NVNmemoryPool * pool, ptrdiff_t offset, size_t size)
{
    if (nvnPrivate0) {
        *((NVNmemoryPool **)(builder->reserved + 16)) = pool;
        *((uintptr_t *)(builder->reserved + 24)) = offset;
        *((intptr_t *)(builder->reserved + 32)) = size;
    } else {
        pfnc_nvnBufferBuilderSetStorage(builder, pool, offset, size);
    }
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnBufferBuilderGetDevice_fastpath(const NVNbufferBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdevice **)(builder->reserved + 8)));
    }
    return pfnc_nvnBufferBuilderGetDevice(builder);
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnBufferBuilderGetMemoryPool_fastpath(const NVNbufferBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(builder->reserved + 16)));
    }
    return pfnc_nvnBufferBuilderGetMemoryPool(builder);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnBufferBuilderGetMemoryOffset_fastpath(const NVNbufferBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uintptr_t *)(builder->reserved + 24)));
    }
    return pfnc_nvnBufferBuilderGetMemoryOffset(builder);
}

static NVNINLINE size_t NVNAPIENTRY nvnBufferBuilderGetSize_fastpath(const NVNbufferBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((intptr_t *)(builder->reserved + 32)));
    }
    return pfnc_nvnBufferBuilderGetSize(builder);
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnBufferGetMemoryPool_fastpath(const NVNbuffer * buffer)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(buffer->reserved + 16)));
    }
    return pfnc_nvnBufferGetMemoryPool(buffer);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnBufferGetMemoryOffset_fastpath(const NVNbuffer * buffer)
{
    if (nvnPrivate0) {
        return (*((uintptr_t *)(buffer->reserved + 24)));
    }
    return pfnc_nvnBufferGetMemoryOffset(buffer);
}

static NVNINLINE size_t NVNAPIENTRY nvnBufferGetSize_fastpath(const NVNbuffer * buffer)
{
    if (nvnPrivate0) {
        return (*((intptr_t *)(buffer->reserved + 32)));
    }
    return pfnc_nvnBufferGetSize(buffer);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetTarget_fastpath(NVNtextureBuilder * builder, NVNtextureTarget target)
{
    if (nvnPrivate0) {
        *((NVNtextureTarget *)(builder->reserved + 36)) = target;
    } else {
        pfnc_nvnTextureBuilderSetTarget(builder, target);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetWidth_fastpath(NVNtextureBuilder * builder, int width)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 40)) = width;
    } else {
        pfnc_nvnTextureBuilderSetWidth(builder, width);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetHeight_fastpath(NVNtextureBuilder * builder, int height)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 44)) = height;
    } else {
        pfnc_nvnTextureBuilderSetHeight(builder, height);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetDepth_fastpath(NVNtextureBuilder * builder, int depth)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 48)) = depth;
    } else {
        pfnc_nvnTextureBuilderSetDepth(builder, depth);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSize3D_fastpath(NVNtextureBuilder * builder, int width, int height, int depth)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 40)) = width;
        *((uint32_t *)(builder->reserved + 44)) = height;
        *((uint32_t *)(builder->reserved + 48)) = depth;
    } else {
        pfnc_nvnTextureBuilderSetSize3D(builder, width, height, depth);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetLevels_fastpath(NVNtextureBuilder * builder, int numLevels)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 52)) = numLevels;
    } else {
        pfnc_nvnTextureBuilderSetLevels(builder, numLevels);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetFormat_fastpath(NVNtextureBuilder * builder, NVNformat format)
{
    if (nvnPrivate0) {
        *((NVNformat *)(builder->reserved + 56)) = format;
    } else {
        pfnc_nvnTextureBuilderSetFormat(builder, format);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSamples_fastpath(NVNtextureBuilder * builder, int samples)
{
    if (nvnPrivate0) {
        *((uint32_t *)(builder->reserved + 60)) = samples;
    } else {
        pfnc_nvnTextureBuilderSetSamples(builder, samples);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetDepthStencilMode_fastpath(NVNtextureBuilder * builder, NVNtextureDepthStencilMode mode)
{
    if (nvnPrivate0) {
        *((NVNtextureDepthStencilMode *)(builder->reserved + 80)) = mode;
    } else {
        pfnc_nvnTextureBuilderSetDepthStencilMode(builder, mode);
    }
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetStorage_fastpath(NVNtextureBuilder * builder, NVNmemoryPool * pool, ptrdiff_t offset)
{
    if (nvnPrivate0) {
        *((NVNmemoryPool **)(builder->reserved + 16)) = pool;
        *((ptrdiff_t *)(builder->reserved + 24)) = offset;
    } else {
        pfnc_nvnTextureBuilderSetStorage(builder, pool, offset);
    }
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnTextureBuilderGetDevice_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdevice **)(builder->reserved + 8)));
    }
    return pfnc_nvnTextureBuilderGetDevice(builder);
}

static NVNINLINE NVNtextureFlags NVNAPIENTRY nvnTextureBuilderGetFlags_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNtextureFlags *)(builder->reserved + 32)));
    }
    return pfnc_nvnTextureBuilderGetFlags(builder);
}

static NVNINLINE NVNtextureTarget NVNAPIENTRY nvnTextureBuilderGetTarget_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNtextureTarget *)(builder->reserved + 36)));
    }
    return pfnc_nvnTextureBuilderGetTarget(builder);
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetWidth_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 40)));
    }
    return pfnc_nvnTextureBuilderGetWidth(builder);
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetHeight_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 44)));
    }
    return pfnc_nvnTextureBuilderGetHeight(builder);
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetDepth_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 48)));
    }
    return pfnc_nvnTextureBuilderGetDepth(builder);
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetLevels_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 52)));
    }
    return pfnc_nvnTextureBuilderGetLevels(builder);
}

static NVNINLINE NVNformat NVNAPIENTRY nvnTextureBuilderGetFormat_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNformat *)(builder->reserved + 56)));
    }
    return pfnc_nvnTextureBuilderGetFormat(builder);
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetSamples_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 60)));
    }
    return pfnc_nvnTextureBuilderGetSamples(builder);
}

static NVNINLINE NVNtextureDepthStencilMode NVNAPIENTRY nvnTextureBuilderGetDepthStencilMode_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNtextureDepthStencilMode *)(builder->reserved + 80)));
    }
    return pfnc_nvnTextureBuilderGetDepthStencilMode(builder);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureBuilderGetStride_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 88)));
    }
    return pfnc_nvnTextureBuilderGetStride(builder);
}

static NVNINLINE uint32_t NVNAPIENTRY nvnTextureBuilderGetGLTextureName_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint32_t *)(builder->reserved + 92)));
    }
    return pfnc_nvnTextureBuilderGetGLTextureName(builder);
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnTextureBuilderGetMemoryPool_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(builder->reserved + 16)));
    }
    return pfnc_nvnTextureBuilderGetMemoryPool(builder);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureBuilderGetMemoryOffset_fastpath(const NVNtextureBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((ptrdiff_t *)(builder->reserved + 24)));
    }
    return pfnc_nvnTextureBuilderGetMemoryOffset(builder);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetLodClamp_fastpath(NVNsamplerBuilder * builder, float min, float max)
{
    if (nvnPrivate0) {
        *((float *)(builder->reserved + 8)) = min;
        *((float *)(builder->reserved + 12)) = max;
    } else {
        pfnc_nvnSamplerBuilderSetLodClamp(builder, min, max);
    }
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetLodBias_fastpath(NVNsamplerBuilder * builder, float bias)
{
    if (nvnPrivate0) {
        *((float *)(builder->reserved + 16)) = bias;
    } else {
        pfnc_nvnSamplerBuilderSetLodBias(builder, bias);
    }
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetMaxAnisotropy_fastpath(NVNsamplerBuilder * builder, float maxAniso)
{
    if (nvnPrivate0) {
        *((float *)(builder->reserved + 20)) = maxAniso;
    } else {
        pfnc_nvnSamplerBuilderSetMaxAnisotropy(builder, maxAniso);
    }
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetLodSnap_fastpath(NVNsamplerBuilder * builder, float lodSnap)
{
    if (nvnPrivate0) {
        *((float *)(builder->reserved + 24)) = lodSnap;
    } else {
        pfnc_nvnSamplerBuilderSetLodSnap(builder, lodSnap);
    }
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnSamplerBuilderGetDevice_fastpath(const NVNsamplerBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNdevice **)(builder->reserved)));
    }
    return pfnc_nvnSamplerBuilderGetDevice(builder);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerBuilderGetLodBias_fastpath(const NVNsamplerBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((float *)(builder->reserved + 16)));
    }
    return pfnc_nvnSamplerBuilderGetLodBias(builder);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerBuilderGetMaxAnisotropy_fastpath(const NVNsamplerBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((float *)(builder->reserved + 20)));
    }
    return pfnc_nvnSamplerBuilderGetMaxAnisotropy(builder);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerBuilderGetLodSnap_fastpath(const NVNsamplerBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((float *)(builder->reserved + 24)));
    }
    return pfnc_nvnSamplerBuilderGetLodSnap(builder);
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetBlendTarget_fastpath(NVNblendState * blend, int target)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~7U)) | ((uint32_t)target));
    } else {
        pfnc_nvnBlendStateSetBlendTarget(blend, target);
    }
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetBlendFunc_fastpath(NVNblendState * blend, NVNblendFunc srcFunc, NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha, NVNblendFunc dstFuncAlpha)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[1]) = (((((uint32_t *)((*blend).reserved))[1]) & (~127U)) | ((uint32_t)srcFunc));
        (((uint32_t *)((*blend).reserved))[1]) = (((((uint32_t *)((*blend).reserved))[1]) & (~32512U)) | (((uint32_t)dstFunc) << 8));
        (((uint32_t *)((*blend).reserved))[1]) = (((((uint32_t *)((*blend).reserved))[1]) & (~8323072U)) | (((uint32_t)srcFuncAlpha) << 16));
        (((uint32_t *)((*blend).reserved))[1]) = (((((uint32_t *)((*blend).reserved))[1]) & (~2130706432U)) | (((uint32_t)dstFuncAlpha) << 24));
    } else {
        pfnc_nvnBlendStateSetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
    }
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetBlendEquation_fastpath(NVNblendState * blend, NVNblendEquation modeRGB, NVNblendEquation modeAlpha)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~117440512U)) | (((uint32_t)modeRGB) << 24));
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~1879048192U)) | (((uint32_t)modeAlpha) << 28));
    } else {
        pfnc_nvnBlendStateSetBlendEquation(blend, modeRGB, modeAlpha);
    }
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedMode_fastpath(NVNblendState * blend, NVNblendAdvancedMode overlap)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~16128U)) | (((uint32_t)overlap) << 8));
    } else {
        pfnc_nvnBlendStateSetAdvancedMode(blend, overlap);
    }
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedOverlap_fastpath(NVNblendState * blend, NVNblendAdvancedOverlap overlap)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~196608U)) | (((uint32_t)overlap) << 16));
    } else {
        pfnc_nvnBlendStateSetAdvancedOverlap(blend, overlap);
    }
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedPremultipliedSrc_fastpath(NVNblendState * blend, NVNboolean premultiplied)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~262144U)) | (((uint32_t)premultiplied != 0) << 18));
    } else {
        pfnc_nvnBlendStateSetAdvancedPremultipliedSrc(blend, premultiplied);
    }
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedNormalizedDst_fastpath(NVNblendState * blend, NVNboolean normalized)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*blend).reserved))[0]) = (((((uint32_t *)((*blend).reserved))[0]) & (~524288U)) | (((uint32_t)normalized != 0) << 19));
    } else {
        pfnc_nvnBlendStateSetAdvancedNormalizedDst(blend, normalized);
    }
}

static NVNINLINE int NVNAPIENTRY nvnBlendStateGetBlendTarget_fastpath(const NVNblendState * blend)
{
    if (nvnPrivate0) {
        return (int)((((const uint32_t *)((*blend).reserved))[0]) & 7U);
    }
    return pfnc_nvnBlendStateGetBlendTarget(blend);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnBlendStateGetAdvancedPremultipliedSrc_fastpath(const NVNblendState * blend)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*blend).reserved))[0]) >> 18) & 1U);
    }
    return pfnc_nvnBlendStateGetAdvancedPremultipliedSrc(blend);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnBlendStateGetAdvancedNormalizedDst_fastpath(const NVNblendState * blend)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*blend).reserved))[0]) >> 19) & 1U);
    }
    return pfnc_nvnBlendStateGetAdvancedNormalizedDst(blend);
}

static NVNINLINE void NVNAPIENTRY nvnColorStateSetLogicOp_fastpath(NVNcolorState * color, NVNlogicOp logicOp)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*color).reserved))[0]) = (((((uint32_t *)((*color).reserved))[0]) & (~16711680U)) | (((uint32_t)logicOp) << 16));
    } else {
        pfnc_nvnColorStateSetLogicOp(color, logicOp);
    }
}

static NVNINLINE void NVNAPIENTRY nvnColorStateSetAlphaTest_fastpath(NVNcolorState * color, NVNalphaFunc alphaTest)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*color).reserved))[0]) = (((((uint32_t *)((*color).reserved))[0]) & (~251658240U)) | (((uint32_t)alphaTest) << 24));
    } else {
        pfnc_nvnColorStateSetAlphaTest(color, alphaTest);
    }
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetMultisampleEnable_fastpath(NVNmultisampleState * multisample, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~1U)) | ((uint32_t)enable != 0));
    } else {
        pfnc_nvnMultisampleStateSetMultisampleEnable(multisample, enable);
    }
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSamples_fastpath(NVNmultisampleState * multisample, int samples)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~7936U)) | (((uint32_t)samples) << 8));
    } else {
        pfnc_nvnMultisampleStateSetSamples(multisample, samples);
    }
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetAlphaToCoverageEnable_fastpath(NVNmultisampleState * multisample, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~2U)) | (((uint32_t)enable != 0) << 1));
    } else {
        pfnc_nvnMultisampleStateSetAlphaToCoverageEnable(multisample, enable);
    }
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetAlphaToCoverageDither_fastpath(NVNmultisampleState * multisample, NVNboolean dither)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~4U)) | (((uint32_t)dither != 0) << 2));
    } else {
        pfnc_nvnMultisampleStateSetAlphaToCoverageDither(multisample, dither);
    }
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetMultisampleEnable_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (NVNboolean)((((const uint32_t *)((*multisample).reserved))[0]) & 1U);
    }
    return pfnc_nvnMultisampleStateGetMultisampleEnable(multisample);
}

static NVNINLINE int NVNAPIENTRY nvnMultisampleStateGetSamples_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (int)(((((const uint32_t *)((*multisample).reserved))[0]) >> 8) & 31U);
    }
    return pfnc_nvnMultisampleStateGetSamples(multisample);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetAlphaToCoverageEnable_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*multisample).reserved))[0]) >> 1) & 1U);
    }
    return pfnc_nvnMultisampleStateGetAlphaToCoverageEnable(multisample);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetAlphaToCoverageDither_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*multisample).reserved))[0]) >> 2) & 1U);
    }
    return pfnc_nvnMultisampleStateGetAlphaToCoverageDither(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetRasterSamples_fastpath(NVNmultisampleState * multisample, int rasterSamples)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~1015808U)) | (((uint32_t)rasterSamples) << 15));
    } else {
        pfnc_nvnMultisampleStateSetRasterSamples(multisample, rasterSamples);
    }
}

static NVNINLINE int NVNAPIENTRY nvnMultisampleStateGetRasterSamples_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (int)(((((const uint32_t *)((*multisample).reserved))[0]) >> 15) & 31U);
    }
    return pfnc_nvnMultisampleStateGetRasterSamples(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetCoverageModulationMode_fastpath(NVNmultisampleState * multisample, NVNcoverageModulationMode mode)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~24576U)) | (((uint32_t)mode) << 13));
    } else {
        pfnc_nvnMultisampleStateSetCoverageModulationMode(multisample, mode);
    }
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetCoverageToColorEnable_fastpath(NVNmultisampleState * multisample, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~1048576U)) | (((uint32_t)enable != 0) << 20));
    } else {
        pfnc_nvnMultisampleStateSetCoverageToColorEnable(multisample, enable);
    }
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetCoverageToColorEnable_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*multisample).reserved))[0]) >> 20) & 1U);
    }
    return pfnc_nvnMultisampleStateGetCoverageToColorEnable(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetCoverageToColorOutput_fastpath(NVNmultisampleState * multisample, int color)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~14680064U)) | (((uint32_t)color) << 21));
    } else {
        pfnc_nvnMultisampleStateSetCoverageToColorOutput(multisample, color);
    }
}

static NVNINLINE int NVNAPIENTRY nvnMultisampleStateGetCoverageToColorOutput_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (int)(((((const uint32_t *)((*multisample).reserved))[0]) >> 20) & 1U);
    }
    return pfnc_nvnMultisampleStateGetCoverageToColorOutput(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSampleLocationsEnable_fastpath(NVNmultisampleState * multisample, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~8U)) | (((uint32_t)enable != 0) << 3));
    } else {
        pfnc_nvnMultisampleStateSetSampleLocationsEnable(multisample, enable);
    }
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetSampleLocationsEnable_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*multisample).reserved))[0]) >> 3) & 1U);
    }
    return pfnc_nvnMultisampleStateGetSampleLocationsEnable(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSampleLocationsGridEnable_fastpath(NVNmultisampleState * multisample, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*multisample).reserved))[0]) = (((((uint32_t *)((*multisample).reserved))[0]) & (~16U)) | (((uint32_t)enable != 0) << 4));
    } else {
        pfnc_nvnMultisampleStateSetSampleLocationsGridEnable(multisample, enable);
    }
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetSampleLocationsGridEnable_fastpath(const NVNmultisampleState * multisample)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*multisample).reserved))[0]) >> 4) & 1U);
    }
    return pfnc_nvnMultisampleStateGetSampleLocationsGridEnable(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetCullFace_fastpath(NVNpolygonState * polygon, NVNface face)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*polygon).reserved))[0]) = (((((uint32_t *)((*polygon).reserved))[0]) & (~3U)) | ((uint32_t)face));
    } else {
        pfnc_nvnPolygonStateSetCullFace(polygon, face);
    }
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetFrontFace_fastpath(NVNpolygonState * polygon, NVNfrontFace face)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*polygon).reserved))[0]) = (((((uint32_t *)((*polygon).reserved))[0]) & (~4U)) | (((uint32_t)face) << 2));
    } else {
        pfnc_nvnPolygonStateSetFrontFace(polygon, face);
    }
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetPolygonMode_fastpath(NVNpolygonState * polygon, NVNpolygonMode polygonMode)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*polygon).reserved))[0]) = (((((uint32_t *)((*polygon).reserved))[0]) & (~24U)) | (((uint32_t)polygonMode) << 3));
    } else {
        pfnc_nvnPolygonStateSetPolygonMode(polygon, polygonMode);
    }
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDepthTestEnable_fastpath(NVNdepthStencilState * depthStencil, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*depthStencil).reserved))[0]) = (((((uint32_t *)((*depthStencil).reserved))[0]) & (~1U)) | ((uint32_t)enable != 0));
    } else {
        pfnc_nvnDepthStencilStateSetDepthTestEnable(depthStencil, enable);
    }
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDepthWriteEnable_fastpath(NVNdepthStencilState * depthStencil, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*depthStencil).reserved))[0]) = (((((uint32_t *)((*depthStencil).reserved))[0]) & (~2U)) | (((uint32_t)enable != 0) << 1));
    } else {
        pfnc_nvnDepthStencilStateSetDepthWriteEnable(depthStencil, enable);
    }
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDepthFunc_fastpath(NVNdepthStencilState * depthStencil, NVNdepthFunc func)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*depthStencil).reserved))[0]) = (((((uint32_t *)((*depthStencil).reserved))[0]) & (~240U)) | (((uint32_t)func) << 4));
    } else {
        pfnc_nvnDepthStencilStateSetDepthFunc(depthStencil, func);
    }
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetStencilTestEnable_fastpath(NVNdepthStencilState * depthStencil, NVNboolean enable)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*depthStencil).reserved))[0]) = (((((uint32_t *)((*depthStencil).reserved))[0]) & (~4U)) | (((uint32_t)enable != 0) << 2));
    } else {
        pfnc_nvnDepthStencilStateSetStencilTestEnable(depthStencil, enable);
    }
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDepthStencilStateGetDepthTestEnable_fastpath(const NVNdepthStencilState * depthStencil)
{
    if (nvnPrivate0) {
        return (NVNboolean)((((const uint32_t *)((*depthStencil).reserved))[0]) & 1U);
    }
    return pfnc_nvnDepthStencilStateGetDepthTestEnable(depthStencil);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDepthStencilStateGetDepthWriteEnable_fastpath(const NVNdepthStencilState * depthStencil)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*depthStencil).reserved))[0]) >> 1) & 1U);
    }
    return pfnc_nvnDepthStencilStateGetDepthWriteEnable(depthStencil);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDepthStencilStateGetStencilTestEnable_fastpath(const NVNdepthStencilState * depthStencil)
{
    if (nvnPrivate0) {
        return (NVNboolean)(((((const uint32_t *)((*depthStencil).reserved))[0]) >> 2) & 1U);
    }
    return pfnc_nvnDepthStencilStateGetStencilTestEnable(depthStencil);
}

static NVNINLINE void NVNAPIENTRY nvnVertexAttribStateSetStreamIndex_fastpath(NVNvertexAttribState * attrib, int streamIndex)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*attrib).reserved))[0]) = (((((uint32_t *)((*attrib).reserved))[0]) & (~31U)) | ((uint32_t)streamIndex));
    } else {
        pfnc_nvnVertexAttribStateSetStreamIndex(attrib, streamIndex);
    }
}

static NVNINLINE int NVNAPIENTRY nvnVertexAttribStateGetStreamIndex_fastpath(const NVNvertexAttribState * attrib)
{
    if (nvnPrivate0) {
        return (int)((((const uint32_t *)((*attrib).reserved))[0]) & 31U);
    }
    return pfnc_nvnVertexAttribStateGetStreamIndex(attrib);
}

static NVNINLINE void NVNAPIENTRY nvnVertexStreamStateSetStride_fastpath(NVNvertexStreamState * stream, ptrdiff_t stride)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*stream).reserved))[0]) = (((((uint32_t *)((*stream).reserved))[0]) & (~4294967295U)) | ((uint32_t)stride));
    } else {
        pfnc_nvnVertexStreamStateSetStride(stream, stride);
    }
}

static NVNINLINE void NVNAPIENTRY nvnVertexStreamStateSetDivisor_fastpath(NVNvertexStreamState * stream, int divisor)
{
    if (nvnPrivate0) {
        (((uint32_t *)((*stream).reserved))[1]) = (((((uint32_t *)((*stream).reserved))[1]) & (~4294967295U)) | ((uint32_t)divisor));
    } else {
        pfnc_nvnVertexStreamStateSetDivisor(stream, divisor);
    }
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnVertexStreamStateGetStride_fastpath(const NVNvertexStreamState * stream)
{
    if (nvnPrivate0) {
        return (ptrdiff_t)((((const uint32_t *)((*stream).reserved))[0]) & 4294967295U);
    }
    return pfnc_nvnVertexStreamStateGetStride(stream);
}

static NVNINLINE int NVNAPIENTRY nvnVertexStreamStateGetDivisor_fastpath(const NVNvertexStreamState * stream)
{
    if (nvnPrivate0) {
        return (int)((((const uint32_t *)((*stream).reserved))[1]) & 4294967295U);
    }
    return pfnc_nvnVertexStreamStateGetDivisor(stream);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetCommandMemoryCallbackEnabled_fastpath(NVNcommandBuffer * cmdBuf, NVNboolean enabled)
{
    if (nvnPrivate0) {
        *(cmdBuf->reserved + 22) = enabled;
    } else {
        pfnc_nvnCommandBufferSetCommandMemoryCallbackEnabled(cmdBuf, enabled);
    }
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBeginRecording_fastpath(NVNcommandBuffer * cmdBuf)
{
    *(cmdBuf->reserved + 16) = 1;
    uint32_t * v0 = *((uint32_t **)(cmdBuf->reserved + 32));
    if (nvnPrivate0 && v0 + 4 <= (*((uint32_t **)(cmdBuf->reserved + 40)))) {
        *((void **)(cmdBuf->reserved + 64)) = (*((void **)(cmdBuf->reserved)));
        *((uint32_t **)(cmdBuf->reserved + 72)) = v0;
        *((void **)(cmdBuf->reserved + 80)) = 0;
        *(cmdBuf->reserved + 17) = 1;
        *(cmdBuf->reserved + 18) = 0;
        v0[0] = 4294967041U;
        v0[1] = 4294967295U;
        v0[2] = 0;
        v0[3] = 0;
        *((uint32_t **)(cmdBuf->reserved + 32)) = v0 + 4;
        return;
    }
    pfnc_nvnCommandBufferBeginRecording(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCallCommands_fastpath(NVNcommandBuffer * cmdBuf, int numCommands, NVN_NOESCAPE const NVNcommandHandle * handles)
{
    *(cmdBuf->reserved + 16) = 1;
    if (!nvnPrivate0) {
        pfnc_nvnCommandBufferCallCommands(cmdBuf, numCommands, handles);
        return;
    }
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 80));
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 40));
    uint64_t * v4 = *((uint64_t **)(cmdBuf->reserved + 32));
    for (int v5 = 0; v5 < numCommands; ++v5) {
        uint64_t * v6 = (uint64_t *)(handles[v5] & 281474976710654ULL);
        uint64_t v7 = handles[v5] >> 48;
        if (!(handles[v5] & 1) || (v6[3 * v7] & 255) != 2 || v4 + 3 * v7 + 4 > v3) {
            *((uint64_t **)(cmdBuf->reserved + 32)) = v4;
            pfnc_nvnCommandBufferCallCommands(cmdBuf, numCommands - v5, handles + v5);
            return;
        }
        if (v5 == 0) {
            if (!v0) {
                *v4 = 3;
                v0 = v4;
                *((uint64_t **)(cmdBuf->reserved + 80)) = v0;
                v4++;
            }
            if (v1 != v2) {
                *v4++ = (*((uint64_t *)(cmdBuf->reserved + 88))) + (v1 - (*((uint32_t **)(cmdBuf->reserved + 48)))) * 4;
                *v4++ = (uint64_t)(uintptr_t)v1;
                *v4++ = (v2 - v1) | 12884901888ULL;
                *v0 += 4294967296ULL;
                *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
            }
        }
        memcpy(v4, v6, (size_t)(24 * v7));
        v4 += 3 * v7;
        *v0 += v7 << 32ULL;
    }
    *((uint64_t **)(cmdBuf->reserved + 32)) = v4;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindVertexBuffer_fastpath(NVNcommandBuffer * cmdBuf, int index, NVNbufferAddress buffer, size_t size)
{
    *(cmdBuf->reserved + 16) = 1;
#ifndef _WIN32
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(cmdBuf->reserved));
    if (nvnPrivate0 && (v1 + 6 <= (*((t0 **)(cmdBuf->reserved + 8))))) {
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
        *((t0 **)(cmdBuf->reserved)) = v1;
        return;
    }
#endif
    pfnc_nvnCommandBufferBindVertexBuffer(cmdBuf, index, buffer, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindVertexBuffers_fastpath(NVNcommandBuffer * cmdBuf, int first, int count, NVN_NOESCAPE const NVNbufferRange * buffers)
{
    *(cmdBuf->reserved + 16) = 1;
#ifndef _WIN32
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(cmdBuf->reserved));
    if (nvnPrivate0 && (v1 + 6 * count <= (*((t0 **)(cmdBuf->reserved + 8))))) {
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
        *((t0 **)(cmdBuf->reserved)) = v1;
        return;
    }
#endif
    pfnc_nvnCommandBufferBindVertexBuffers(cmdBuf, first, count, buffers);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindUniformBuffer_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size)
{
    *(cmdBuf->reserved + 16) = 1;
    if (nvnPrivate0 && stage != NVN_SHADER_STAGE_COMPUTE) {
        typedef union {
            float f;
            int32_t i;
            uint32_t u;
        } t0;
        t0 * v1 = *((t0 **)(cmdBuf->reserved));
        if (v1 + 6 <= (*((t0 **)(cmdBuf->reserved + 8)))) {
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
            *((t0 **)(cmdBuf->reserved)) = v1;
            return;
        }
    }
    pfnc_nvnCommandBufferBindUniformBuffer(cmdBuf, stage, index, buffer, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindUniformBuffers_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNbufferRange * buffers)
{
    *(cmdBuf->reserved + 16) = 1;
    if (nvnPrivate0 && stage != NVN_SHADER_STAGE_COMPUTE) {
        typedef union {
            float f;
            int32_t i;
            uint32_t u;
        } t0;
        t0 * v1 = *((t0 **)(cmdBuf->reserved));
        if (v1 + 6 * count <= (*((t0 **)(cmdBuf->reserved + 8)))) {
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
            *((t0 **)(cmdBuf->reserved)) = v1;
            return;
        }
    }
    pfnc_nvnCommandBufferBindUniformBuffers(cmdBuf, stage, first, count, buffers);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindUniformBuffersDeferred_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, const NVNbufferRange * buffers)
{
    *(cmdBuf->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(cmdBuf->reserved + 40))))) {
        pfnc_nvnCommandBufferBindUniformBuffersDeferred(cmdBuf, stage, first, count, buffers);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(cmdBuf->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(cmdBuf->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(cmdBuf->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)26) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)buffers;
    v0 += 2;
    *((uint64_t **)(cmdBuf->reserved + 32)) = v0;
    *(cmdBuf->reserved + 18) = 1;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindStorageBuffersDeferred_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, const NVNbufferRange * buffers)
{
    *(cmdBuf->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(cmdBuf->reserved + 40))))) {
        pfnc_nvnCommandBufferBindStorageBuffersDeferred(cmdBuf, stage, first, count, buffers);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(cmdBuf->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(cmdBuf->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(cmdBuf->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)27) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)buffers;
    v0 += 2;
    *((uint64_t **)(cmdBuf->reserved + 32)) = v0;
    *(cmdBuf->reserved + 18) = 1;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindTexturesDeferred_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, const NVNtextureHandle * textures)
{
    *(cmdBuf->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(cmdBuf->reserved + 40))))) {
        pfnc_nvnCommandBufferBindTexturesDeferred(cmdBuf, stage, first, count, textures);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(cmdBuf->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(cmdBuf->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(cmdBuf->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)23) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)textures;
    v0 += 2;
    *((uint64_t **)(cmdBuf->reserved + 32)) = v0;
    *(cmdBuf->reserved + 18) = 1;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindImagesDeferred_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, const NVNimageHandle * images)
{
    *(cmdBuf->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(cmdBuf->reserved + 40))))) {
        pfnc_nvnCommandBufferBindImagesDeferred(cmdBuf, stage, first, count, images);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(cmdBuf->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(cmdBuf->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(cmdBuf->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)28) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)images;
    v0 += 2;
    *((uint64_t **)(cmdBuf->reserved + 32)) = v0;
    *(cmdBuf->reserved + 18) = 1;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawElements_fastpath(NVNcommandBuffer * cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer)
{
    *(cmdBuf->reserved + 16) = 1;
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(cmdBuf->reserved));
    if (nvnPrivate0 && (v1 + 6 <= (*((t0 **)(cmdBuf->reserved + 8))))) {
        const uint64_t v2 = indexBuffer;
        v1[0].u = 2684685880U;
        v1[1].u = mode;
        v1[2].u = ((uint32_t)((((uint64_t)v2) >> 32) & 4294967295U));
        v1[3].u = ((uint32_t)(((uint64_t)v2) & 4294967295U));
        v1[4].u = type;
        v1[5].u = count;
        v1 += 6;
        *((t0 **)(cmdBuf->reserved)) = v1;
        return;
    }
    pfnc_nvnCommandBufferDrawElements(cmdBuf, mode, type, count, indexBuffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateTexturesDeferred_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, const NVNseparateTextureHandle * textureHandles)
{
    *(cmdBuf->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(cmdBuf->reserved + 40))))) {
        pfnc_nvnCommandBufferBindSeparateTexturesDeferred(cmdBuf, stage, first, count, textureHandles);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(cmdBuf->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(cmdBuf->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(cmdBuf->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)24) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)textureHandles;
    v0 += 2;
    *((uint64_t **)(cmdBuf->reserved + 32)) = v0;
    *(cmdBuf->reserved + 18) = 1;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateSamplersDeferred_fastpath(NVNcommandBuffer * cmdBuf, NVNshaderStage stage, int first, int count, const NVNseparateSamplerHandle * samplerHandles)
{
    *(cmdBuf->reserved + 16) = 1;
    uint64_t * v0 = *((uint64_t **)(cmdBuf->reserved + 32));
    if (!nvnPrivate0 || !(v0 + 6 <= (*((uint64_t **)(cmdBuf->reserved + 40))))) {
        pfnc_nvnCommandBufferBindSeparateSamplersDeferred(cmdBuf, stage, first, count, samplerHandles);
        return;
    }
    uint32_t * v1 = *((uint32_t **)(cmdBuf->reserved + 64));
    uint32_t * v2 = *((uint32_t **)(cmdBuf->reserved));
    if (v2 != v1) {
        uint64_t * v3 = *((uint64_t **)(cmdBuf->reserved + 80));
        if (v3) {
            *v3 += 4294967296ULL;
        } else {
            *v0++ = 4294967299ULL;
        }
        v0[0] = ((*((uint64_t *)(cmdBuf->reserved + 88))) + ((char *)v1 - (char *)(*((uint32_t **)(cmdBuf->reserved + 48)))));
        v0[1] = (uint64_t)(uintptr_t)v1;
        v0[2] = (v2 - v1) | 12884901888ULL;
        v0 += 3;
        *((uint64_t **)(cmdBuf->reserved + 80)) = (uint64_t *)0;
        *((uint32_t **)(cmdBuf->reserved + 64)) = v2;
    }
    v0[0] = (((uint64_t)25) | ((uint64_t)stage << 8) | ((uint64_t)first << 16) | ((uint64_t)count << 24));
    v0[1] = (uint64_t)(uintptr_t)samplerHandles;
    v0 += 2;
    *((uint64_t **)(cmdBuf->reserved + 32)) = v0;
    *(cmdBuf->reserved + 18) = 1;
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferUpdateUniformBuffer_fastpath(NVNcommandBuffer * cmdBuf, NVNbufferAddress buffer, size_t bufferSize, ptrdiff_t updateOffset, size_t updateSize, NVN_NOESCAPE const void * data)
{
    *(cmdBuf->reserved + 16) = 1;
    typedef union {
        float f;
        int32_t i;
        uint32_t u;
    } t0;
    t0 * v1 = *((t0 **)(cmdBuf->reserved));
    uint32_t v2 = (uint32_t)updateSize / 4;
    if (nvnPrivate0 && (v2 <= 8191) && (v1 + 9 + v2 <= (*((t0 **)(cmdBuf->reserved + 8))))) {
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
        *((t0 **)(cmdBuf->reserved)) = v1;
        return;
    }
    pfnc_nvnCommandBufferUpdateUniformBuffer(cmdBuf, buffer, bufferSize, updateOffset, updateSize, data);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnEventBuilderGetMemoryPool_fastpath(const NVNeventBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(builder->reserved)));
    }
    return pfnc_nvnEventBuilderGetMemoryPool(builder);
}

static NVNINLINE int64_t NVNAPIENTRY nvnEventBuilderGetMemoryOffset_fastpath(const NVNeventBuilder * builder)
{
    if (nvnPrivate0) {
        return (*((uint64_t *)(builder->reserved + 8)));
    }
    return pfnc_nvnEventBuilderGetMemoryOffset(builder);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnEventGetMemoryPool_fastpath(const NVNevent * event)
{
    if (nvnPrivate0) {
        return (*((NVNmemoryPool **)(event->reserved + 16)));
    }
    return pfnc_nvnEventGetMemoryPool(event);
}

static NVNINLINE int64_t NVNAPIENTRY nvnEventGetMemoryOffset_fastpath(const NVNevent * event)
{
    if (nvnPrivate0) {
        return (*((uint64_t *)(event->reserved + 24)));
    }
    return pfnc_nvnEventGetMemoryOffset(event);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __nvn_fastpath_h_
