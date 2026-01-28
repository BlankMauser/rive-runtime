
/*--------------------------------------------------------------------------------*
  Copyright (C)Nintendo All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/


/// \file nvn_FuncPtrInline.h
///      Implementation of the NVN C interface entry points as inline
///      functions that call through global function pointer variables.

#ifndef __nvn_funcptrinline_h_
#define __nvn_funcptrinline_h_

#ifdef NVN_PROTOTYPES
#error To use NVN inline functions, please be sure to not define NVN_PROTOTYPES before including "nvn_FuncPtrInline.h".
#endif

#include "nvn.h"
#include "nvn_FuncPtr.h"
#include "nvn_Fastpath.h"

#ifdef __cplusplus
extern "C" {
#endif

static NVNINLINE void NVNAPIENTRY nvnDeviceBuilderSetDefaults(NVNdeviceBuilder *builder)
{
    pfnc_nvnDeviceBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceBuilderSetFlags(NVNdeviceBuilder *builder, int flags)
{
    pfnc_nvnDeviceBuilderSetFlags(builder, flags);
}

static NVNINLINE NVNdeviceFlagBits NVNAPIENTRY nvnDeviceBuilderGetFlags(const NVNdeviceBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnDeviceBuilderGetFlags_fastpath(builder);
#else
    return pfnc_nvnDeviceBuilderGetFlags(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceInitialize(NVNdevice *device, const NVNdeviceBuilder *builder)
{
    return pfnc_nvnDeviceInitialize(device, builder);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceFinalize(NVNdevice *device)
{
    pfnc_nvnDeviceFinalize(device);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceSetDebugLabel(NVNdevice *device, const char * label)
{
    pfnc_nvnDeviceSetDebugLabel(device, label);
}

static NVNINLINE PFNNVNGENERICFUNCPTRPROC NVNAPIENTRY nvnDeviceGetProcAddress(const NVNdevice *device, const char * name)
{
    return pfnc_nvnDeviceGetProcAddress(device, name);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceGetInteger(const NVNdevice *device, NVNdeviceInfo pname, int *v)
{
    pfnc_nvnDeviceGetInteger(device, pname, v);
}

static NVNINLINE uint64_t NVNAPIENTRY nvnDeviceGetCurrentTimestampInNanoseconds(const NVNdevice *device)
{
    return pfnc_nvnDeviceGetCurrentTimestampInNanoseconds(device);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceSetIntermediateShaderCache(NVNdevice *device, int numMaxEntries)
{
    pfnc_nvnDeviceSetIntermediateShaderCache(device, numMaxEntries);
}

static NVNINLINE NVNtextureHandle NVNAPIENTRY nvnDeviceGetTextureHandle(const NVNdevice *device, int textureID, int samplerID)
{
    return pfnc_nvnDeviceGetTextureHandle(device, textureID, samplerID);
}

static NVNINLINE NVNtextureHandle NVNAPIENTRY nvnDeviceGetTexelFetchHandle(const NVNdevice *device, int textureID)
{
    return pfnc_nvnDeviceGetTexelFetchHandle(device, textureID);
}

static NVNINLINE NVNimageHandle NVNAPIENTRY nvnDeviceGetImageHandle(const NVNdevice *device, int imageID)
{
    return pfnc_nvnDeviceGetImageHandle(device, imageID);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceInstallDebugCallback(NVNdevice *device, const PFNNVNDEBUGCALLBACKPROC callback, void *callbackData, NVNboolean enable)
{
    pfnc_nvnDeviceInstallDebugCallback(device, callback, callbackData, enable);
}

static NVNINLINE NVNdebugDomainId NVNAPIENTRY nvnDeviceGenerateDebugDomainId(const NVNdevice *device, const char * name)
{
    return pfnc_nvnDeviceGenerateDebugDomainId(device, name);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceSetWindowOriginMode(NVNdevice *device, NVNwindowOriginMode windowOriginMode)
{
#ifdef NVN_FORCE_FASTPATH
    nvnDeviceSetWindowOriginMode_fastpath(device, windowOriginMode);
#else
    pfnc_nvnDeviceSetWindowOriginMode(device, windowOriginMode);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnDeviceSetDepthMode(NVNdevice *device, NVNdepthMode depthMode)
{
#ifdef NVN_FORCE_FASTPATH
    nvnDeviceSetDepthMode_fastpath(device, depthMode);
#else
    pfnc_nvnDeviceSetDepthMode(device, depthMode);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceRegisterFastClearColor(NVNdevice *device, const float *color, NVNformat format)
{
    return pfnc_nvnDeviceRegisterFastClearColor(device, color, format);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceRegisterFastClearColori(NVNdevice *device, const int *color, NVNformat format)
{
    return pfnc_nvnDeviceRegisterFastClearColori(device, color, format);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceRegisterFastClearColorui(NVNdevice *device, const uint32_t *color, NVNformat format)
{
    return pfnc_nvnDeviceRegisterFastClearColorui(device, color, format);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceRegisterFastClearDepth(NVNdevice *device, float depth)
{
    return pfnc_nvnDeviceRegisterFastClearDepth(device, depth);
}

static NVNINLINE NVNwindowOriginMode NVNAPIENTRY nvnDeviceGetWindowOriginMode(const NVNdevice *device)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnDeviceGetWindowOriginMode_fastpath(device);
#else
    return pfnc_nvnDeviceGetWindowOriginMode(device);
#endif
}

static NVNINLINE NVNdepthMode NVNAPIENTRY nvnDeviceGetDepthMode(const NVNdevice *device)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnDeviceGetDepthMode_fastpath(device);
#else
    return pfnc_nvnDeviceGetDepthMode(device);
#endif
}

static NVNINLINE uint64_t NVNAPIENTRY nvnDeviceGetTimestampInNanoseconds(const NVNdevice *device, const NVNcounterData *counterData)
{
    return pfnc_nvnDeviceGetTimestampInNanoseconds(device, counterData);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceFinalizeCommandHandle(NVNdevice *device, NVNcommandHandle handles)
{
    pfnc_nvnDeviceFinalizeCommandHandle(device, handles);
}

static NVNINLINE void NVNAPIENTRY nvnDeviceWalkDebugDatabase(const NVNdevice *device, NVNdebugObjectType type, PFNNVNWALKDEBUGDATABASECALLBACKPROC callback, void *userParam)
{
    pfnc_nvnDeviceWalkDebugDatabase(device, type, callback, userParam);
}

static NVNINLINE NVNseparateTextureHandle NVNAPIENTRY nvnDeviceGetSeparateTextureHandle(const NVNdevice *device, int textureID)
{
    return pfnc_nvnDeviceGetSeparateTextureHandle(device, textureID);
}

static NVNINLINE NVNseparateSamplerHandle NVNAPIENTRY nvnDeviceGetSeparateSamplerHandle(const NVNdevice *device, int samplerID)
{
    return pfnc_nvnDeviceGetSeparateSamplerHandle(device, samplerID);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceIsExternalDebuggerAttached(const NVNdevice *device)
{
    return pfnc_nvnDeviceIsExternalDebuggerAttached(device);
}

static NVNINLINE NVNqueueGetErrorResult NVNAPIENTRY nvnQueueGetError(NVNqueue *queue, NVNqueueErrorInfo *errorInfo)
{
    return pfnc_nvnQueueGetError(queue, errorInfo);
}

static NVNINLINE size_t NVNAPIENTRY nvnQueueGetTotalCommandMemoryUsed(NVNqueue *queue)
{
    return pfnc_nvnQueueGetTotalCommandMemoryUsed(queue);
}

static NVNINLINE size_t NVNAPIENTRY nvnQueueGetTotalControlMemoryUsed(NVNqueue *queue)
{
    return pfnc_nvnQueueGetTotalControlMemoryUsed(queue);
}

static NVNINLINE size_t NVNAPIENTRY nvnQueueGetTotalComputeMemoryUsed(NVNqueue *queue)
{
    return pfnc_nvnQueueGetTotalComputeMemoryUsed(queue);
}

static NVNINLINE void NVNAPIENTRY nvnQueueResetMemoryUsageCounts(NVNqueue *queue)
{
    pfnc_nvnQueueResetMemoryUsageCounts(queue);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetDevice(NVNqueueBuilder *builder, NVNdevice *device)
{
    pfnc_nvnQueueBuilderSetDevice(builder, device);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetDefaults(NVNqueueBuilder *builder)
{
    pfnc_nvnQueueBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetFlags(NVNqueueBuilder *builder, int flags)
{
    pfnc_nvnQueueBuilderSetFlags(builder, flags);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetCommandMemorySize(NVNqueueBuilder *builder, size_t size)
{
    pfnc_nvnQueueBuilderSetCommandMemorySize(builder, size);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetComputeMemorySize(NVNqueueBuilder *builder, size_t size)
{
    pfnc_nvnQueueBuilderSetComputeMemorySize(builder, size);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetControlMemorySize(NVNqueueBuilder *builder, size_t size)
{
    pfnc_nvnQueueBuilderSetControlMemorySize(builder, size);
}

static NVNINLINE size_t NVNAPIENTRY nvnQueueBuilderGetQueueMemorySize(const NVNqueueBuilder *builder)
{
    return pfnc_nvnQueueBuilderGetQueueMemorySize(builder);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetQueueMemory(NVNqueueBuilder *builder, void *memory, size_t size)
{
    pfnc_nvnQueueBuilderSetQueueMemory(builder, memory, size);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetCommandFlushThreshold(NVNqueueBuilder *builder, size_t threshold)
{
    pfnc_nvnQueueBuilderSetCommandFlushThreshold(builder, threshold);
}

static NVNINLINE void NVNAPIENTRY nvnQueueBuilderSetQueuePriority(NVNqueueBuilder *builder, const NVNqueuePriority priority)
{
#ifdef NVN_FORCE_FASTPATH
    nvnQueueBuilderSetQueuePriority_fastpath(builder, priority);
#else
    pfnc_nvnQueueBuilderSetQueuePriority(builder, priority);
#endif
}

static NVNINLINE NVNqueuePriority NVNAPIENTRY nvnQueueBuilderGetQueuePriority(const NVNqueueBuilder *builder)
{
    return pfnc_nvnQueueBuilderGetQueuePriority(builder);
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnQueueBuilderGetDevice(const NVNqueueBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnQueueBuilderGetDevice_fastpath(builder);
#else
    return pfnc_nvnQueueBuilderGetDevice(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnQueueBuilderGetFlags(const NVNqueueBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnQueueBuilderGetFlags_fastpath(builder);
#else
    return pfnc_nvnQueueBuilderGetFlags(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnQueueBuilderGetCommandMemorySize(const NVNqueueBuilder *builder, int *size)
{
    return pfnc_nvnQueueBuilderGetCommandMemorySize(builder, size);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnQueueBuilderGetComputeMemorySize(const NVNqueueBuilder *builder, int *size)
{
    return pfnc_nvnQueueBuilderGetComputeMemorySize(builder, size);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnQueueBuilderGetControlMemorySize(const NVNqueueBuilder *builder, int *size)
{
    return pfnc_nvnQueueBuilderGetControlMemorySize(builder, size);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnQueueBuilderGetCommandFlushThreshold(const NVNqueueBuilder *builder, int *flushThreshold)
{
    return pfnc_nvnQueueBuilderGetCommandFlushThreshold(builder, flushThreshold);
}

static NVNINLINE int NVNAPIENTRY nvnQueueBuilderGetMemorySize(const NVNqueueBuilder *builder)
{
    return pfnc_nvnQueueBuilderGetMemorySize(builder);
}

static NVNINLINE void * NVNAPIENTRY nvnQueueBuilderGetMemory(const NVNqueueBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnQueueBuilderGetMemory_fastpath(builder);
#else
    return pfnc_nvnQueueBuilderGetMemory(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnQueueInitialize(NVNqueue *queue, const NVNqueueBuilder *builder)
{
    return pfnc_nvnQueueInitialize(queue, builder);
}

static NVNINLINE void NVNAPIENTRY nvnQueueFinalize(NVNqueue *queue)
{
    pfnc_nvnQueueFinalize(queue);
}

static NVNINLINE void NVNAPIENTRY nvnQueueSetDebugLabel(NVNqueue *queue, const char * label)
{
    pfnc_nvnQueueSetDebugLabel(queue, label);
}

static NVNINLINE void NVNAPIENTRY nvnQueueSubmitCommands(NVNqueue *queue, int numCommands, const NVNcommandHandle *handles)
{
    pfnc_nvnQueueSubmitCommands(queue, numCommands, handles);
}

static NVNINLINE void NVNAPIENTRY nvnQueueFlush(NVNqueue *queue)
{
    pfnc_nvnQueueFlush(queue);
}

static NVNINLINE void NVNAPIENTRY nvnQueueFinish(NVNqueue *queue)
{
    pfnc_nvnQueueFinish(queue);
}

static NVNINLINE void NVNAPIENTRY nvnQueuePresentTexture(NVNqueue *queue, NVNwindow *window, int textureIndex)
{
    pfnc_nvnQueuePresentTexture(queue, window, textureIndex);
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetDevice(NVNwindowBuilder *builder, NVNdevice *device)
{
    pfnc_nvnWindowBuilderSetDevice(builder, device);
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetDefaults(NVNwindowBuilder *builder)
{
    pfnc_nvnWindowBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetNativeWindow(NVNwindowBuilder *builder, NVNnativeWindow nativeWindow)
{
#ifdef NVN_FORCE_FASTPATH
    nvnWindowBuilderSetNativeWindow_fastpath(builder, nativeWindow);
#else
    pfnc_nvnWindowBuilderSetNativeWindow(builder, nativeWindow);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetTextures(NVNwindowBuilder *builder, int numTextures, NVNtexture * const *textures)
{
#ifdef NVN_FORCE_FASTPATH
    nvnWindowBuilderSetTextures_fastpath(builder, numTextures, textures);
#else
    pfnc_nvnWindowBuilderSetTextures(builder, numTextures, textures);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetPresentInterval(NVNwindowBuilder *builder, int presentInterval)
{
    pfnc_nvnWindowBuilderSetPresentInterval(builder, presentInterval);
}

static NVNINLINE void NVNAPIENTRY nvnWindowBuilderSetNumActiveTextures(NVNwindowBuilder *builder, int numActiveTextures)
{
#ifdef NVN_FORCE_FASTPATH
    nvnWindowBuilderSetNumActiveTextures_fastpath(builder, numActiveTextures);
#else
    pfnc_nvnWindowBuilderSetNumActiveTextures(builder, numActiveTextures);
#endif
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnWindowBuilderGetDevice(const NVNwindowBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowBuilderGetDevice_fastpath(builder);
#else
    return pfnc_nvnWindowBuilderGetDevice(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnWindowBuilderGetNumTextures(const NVNwindowBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowBuilderGetNumTextures_fastpath(builder);
#else
    return pfnc_nvnWindowBuilderGetNumTextures(builder);
#endif
}

static NVNINLINE const NVNtexture * NVNAPIENTRY nvnWindowBuilderGetTexture(const NVNwindowBuilder *builder, int textureId)
{
    return pfnc_nvnWindowBuilderGetTexture(builder, textureId);
}

static NVNINLINE NVNnativeWindow NVNAPIENTRY nvnWindowBuilderGetNativeWindow(const NVNwindowBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowBuilderGetNativeWindow_fastpath(builder);
#else
    return pfnc_nvnWindowBuilderGetNativeWindow(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnWindowBuilderGetPresentInterval(const NVNwindowBuilder *builder)
{
    return pfnc_nvnWindowBuilderGetPresentInterval(builder);
}

static NVNINLINE int NVNAPIENTRY nvnWindowBuilderGetNumActiveTextures(const NVNwindowBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowBuilderGetNumActiveTextures_fastpath(builder);
#else
    return pfnc_nvnWindowBuilderGetNumActiveTextures(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnWindowInitialize(NVNwindow *window, const NVNwindowBuilder *builder)
{
    return pfnc_nvnWindowInitialize(window, builder);
}

static NVNINLINE void NVNAPIENTRY nvnWindowFinalize(NVNwindow *window)
{
    pfnc_nvnWindowFinalize(window);
}

static NVNINLINE void NVNAPIENTRY nvnWindowSetDebugLabel(NVNwindow *window, const char * label)
{
    pfnc_nvnWindowSetDebugLabel(window, label);
}

static NVNINLINE NVNwindowAcquireTextureResult NVNAPIENTRY nvnWindowAcquireTexture(NVNwindow *window, NVNsync *textureAvailableSync, int *textureIndex)
{
    return pfnc_nvnWindowAcquireTexture(window, textureAvailableSync, textureIndex);
}

static NVNINLINE NVNnativeWindow NVNAPIENTRY nvnWindowGetNativeWindow(const NVNwindow *window)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowGetNativeWindow_fastpath(window);
#else
    return pfnc_nvnWindowGetNativeWindow(window);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnWindowGetPresentInterval(const NVNwindow *window)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowGetPresentInterval_fastpath(window);
#else
    return pfnc_nvnWindowGetPresentInterval(window);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnWindowSetPresentInterval(NVNwindow *window, int presentInterval)
{
    pfnc_nvnWindowSetPresentInterval(window, presentInterval);
}

static NVNINLINE void NVNAPIENTRY nvnWindowSetCrop(NVNwindow *window, int x, int y, int w, int h)
{
    pfnc_nvnWindowSetCrop(window, x, y, w, h);
}

static NVNINLINE void NVNAPIENTRY nvnWindowGetCrop(const NVNwindow *window, NVNrectangle *crop)
{
    pfnc_nvnWindowGetCrop(window, crop);
}

static NVNINLINE void NVNAPIENTRY nvnWindowSetNumActiveTextures(NVNwindow *window, int numActiveTextures)
{
    pfnc_nvnWindowSetNumActiveTextures(window, numActiveTextures);
}

static NVNINLINE int NVNAPIENTRY nvnWindowGetNumActiveTextures(const NVNwindow *window)
{
    return pfnc_nvnWindowGetNumActiveTextures(window);
}

static NVNINLINE int NVNAPIENTRY nvnWindowGetNumTextures(const NVNwindow *window)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnWindowGetNumTextures_fastpath(window);
#else
    return pfnc_nvnWindowGetNumTextures(window);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnProgramInitialize(NVNprogram *program, NVNdevice *device)
{
    return pfnc_nvnProgramInitialize(program, device);
}

static NVNINLINE void NVNAPIENTRY nvnProgramFinalize(NVNprogram *program)
{
    pfnc_nvnProgramFinalize(program);
}

static NVNINLINE void NVNAPIENTRY nvnProgramSetDebugLabel(NVNprogram *program, const char * label)
{
    pfnc_nvnProgramSetDebugLabel(program, label);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnProgramSetShaders(NVNprogram *program, int count, const NVNshaderData *stageData)
{
    return pfnc_nvnProgramSetShaders(program, count, stageData);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnProgramSetShadersExt(NVNprogram *program, int count, const NVNshaderDataExt *stageDataExt)
{
    return pfnc_nvnProgramSetShadersExt(program, count, stageDataExt);
}

static NVNINLINE void NVNAPIENTRY nvnProgramSetSampleShading(NVNprogram *program, NVNsampleShadingMode shadingMode)
{
    pfnc_nvnProgramSetSampleShading(program, shadingMode);
}

static NVNINLINE int NVNAPIENTRY nvnProgramGetSubtileSize(const NVNprogram *program)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnProgramGetSubtileSize_fastpath(program);
#else
    return pfnc_nvnProgramGetSubtileSize(program);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolBuilderSetDevice(NVNmemoryPoolBuilder *builder, NVNdevice *device)
{
    pfnc_nvnMemoryPoolBuilderSetDevice(builder, device);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolBuilderSetDefaults(NVNmemoryPoolBuilder *builder)
{
    pfnc_nvnMemoryPoolBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolBuilderSetStorage(NVNmemoryPoolBuilder *builder, void *memory, size_t size)
{
    pfnc_nvnMemoryPoolBuilderSetStorage(builder, memory, size);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolBuilderSetFlags(NVNmemoryPoolBuilder *builder, int flags)
{
    pfnc_nvnMemoryPoolBuilderSetFlags(builder, flags);
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnMemoryPoolBuilderGetDevice(const NVNmemoryPoolBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMemoryPoolBuilderGetDevice_fastpath(builder);
#else
    return pfnc_nvnMemoryPoolBuilderGetDevice(builder);
#endif
}

static NVNINLINE void * NVNAPIENTRY nvnMemoryPoolBuilderGetMemory(const NVNmemoryPoolBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMemoryPoolBuilderGetMemory_fastpath(builder);
#else
    return pfnc_nvnMemoryPoolBuilderGetMemory(builder);
#endif
}

static NVNINLINE size_t NVNAPIENTRY nvnMemoryPoolBuilderGetSize(const NVNmemoryPoolBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMemoryPoolBuilderGetSize_fastpath(builder);
#else
    return pfnc_nvnMemoryPoolBuilderGetSize(builder);
#endif
}

static NVNINLINE NVNmemoryPoolFlags NVNAPIENTRY nvnMemoryPoolBuilderGetFlags(const NVNmemoryPoolBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMemoryPoolBuilderGetFlags_fastpath(builder);
#else
    return pfnc_nvnMemoryPoolBuilderGetFlags(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMemoryPoolInitialize(NVNmemoryPool *pool, const NVNmemoryPoolBuilder *builder)
{
    return pfnc_nvnMemoryPoolInitialize(pool, builder);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolSetDebugLabel(NVNmemoryPool *pool, const char * label)
{
    pfnc_nvnMemoryPoolSetDebugLabel(pool, label);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolFinalize(NVNmemoryPool *pool)
{
    pfnc_nvnMemoryPoolFinalize(pool);
}

static NVNINLINE void * NVNAPIENTRY nvnMemoryPoolMap(const NVNmemoryPool *pool)
{
    return pfnc_nvnMemoryPoolMap(pool);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolFlushMappedRange(const NVNmemoryPool *pool, ptrdiff_t offset, size_t size)
{
    pfnc_nvnMemoryPoolFlushMappedRange(pool, offset, size);
}

static NVNINLINE void NVNAPIENTRY nvnMemoryPoolInvalidateMappedRange(const NVNmemoryPool *pool, ptrdiff_t offset, size_t size)
{
    pfnc_nvnMemoryPoolInvalidateMappedRange(pool, offset, size);
}

static NVNINLINE NVNbufferAddress NVNAPIENTRY nvnMemoryPoolGetBufferAddress(const NVNmemoryPool *pool)
{
    return pfnc_nvnMemoryPoolGetBufferAddress(pool);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMemoryPoolMapVirtual(NVNmemoryPool *virtualPool, int numRequests, const NVNmappingRequest *requests)
{
    return pfnc_nvnMemoryPoolMapVirtual(virtualPool, numRequests, requests);
}

static NVNINLINE size_t NVNAPIENTRY nvnMemoryPoolGetSize(const NVNmemoryPool *pool)
{
    return pfnc_nvnMemoryPoolGetSize(pool);
}

static NVNINLINE NVNmemoryPoolFlags NVNAPIENTRY nvnMemoryPoolGetFlags(const NVNmemoryPool *pool)
{
    return pfnc_nvnMemoryPoolGetFlags(pool);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTexturePoolInitialize(NVNtexturePool *texturePool, const NVNmemoryPool *memoryPool, ptrdiff_t offset, int numDescriptors)
{
    return pfnc_nvnTexturePoolInitialize(texturePool, memoryPool, offset, numDescriptors);
}

static NVNINLINE void NVNAPIENTRY nvnTexturePoolSetDebugLabel(NVNtexturePool *pool, const char * label)
{
    pfnc_nvnTexturePoolSetDebugLabel(pool, label);
}

static NVNINLINE void NVNAPIENTRY nvnTexturePoolFinalize(NVNtexturePool *pool)
{
    pfnc_nvnTexturePoolFinalize(pool);
}

static NVNINLINE void NVNAPIENTRY nvnTexturePoolRegisterTexture(const NVNtexturePool *texturePool, int id, const NVNtexture *texture, const NVNtextureView *view)
{
    pfnc_nvnTexturePoolRegisterTexture(texturePool, id, texture, view);
}

static NVNINLINE void NVNAPIENTRY nvnTexturePoolRegisterImage(const NVNtexturePool *texturePool, int id, const NVNtexture *texture, const NVNtextureView *view)
{
    pfnc_nvnTexturePoolRegisterImage(texturePool, id, texture, view);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnTexturePoolGetMemoryPool(const NVNtexturePool *pool)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTexturePoolGetMemoryPool_fastpath(pool);
#else
    return pfnc_nvnTexturePoolGetMemoryPool(pool);
#endif
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTexturePoolGetMemoryOffset(const NVNtexturePool *pool)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTexturePoolGetMemoryOffset_fastpath(pool);
#else
    return pfnc_nvnTexturePoolGetMemoryOffset(pool);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnTexturePoolGetSize(const NVNtexturePool *pool)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTexturePoolGetSize_fastpath(pool);
#else
    return pfnc_nvnTexturePoolGetSize(pool);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnSamplerPoolInitialize(NVNsamplerPool *samplerPool, const NVNmemoryPool *memoryPool, ptrdiff_t offset, int numDescriptors)
{
    return pfnc_nvnSamplerPoolInitialize(samplerPool, memoryPool, offset, numDescriptors);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerPoolSetDebugLabel(NVNsamplerPool *pool, const char * label)
{
    pfnc_nvnSamplerPoolSetDebugLabel(pool, label);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerPoolFinalize(NVNsamplerPool *pool)
{
    pfnc_nvnSamplerPoolFinalize(pool);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerPoolRegisterSampler(const NVNsamplerPool *samplerPool, int id, const NVNsampler *sampler)
{
    pfnc_nvnSamplerPoolRegisterSampler(samplerPool, id, sampler);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerPoolRegisterSamplerBuilder(const NVNsamplerPool *samplerPool, int id, const NVNsamplerBuilder *builder)
{
    pfnc_nvnSamplerPoolRegisterSamplerBuilder(samplerPool, id, builder);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnSamplerPoolGetMemoryPool(const NVNsamplerPool *pool)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerPoolGetMemoryPool_fastpath(pool);
#else
    return pfnc_nvnSamplerPoolGetMemoryPool(pool);
#endif
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnSamplerPoolGetMemoryOffset(const NVNsamplerPool *pool)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerPoolGetMemoryOffset_fastpath(pool);
#else
    return pfnc_nvnSamplerPoolGetMemoryOffset(pool);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnSamplerPoolGetSize(const NVNsamplerPool *pool)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerPoolGetSize_fastpath(pool);
#else
    return pfnc_nvnSamplerPoolGetSize(pool);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBufferBuilderSetDevice(NVNbufferBuilder *builder, NVNdevice *device)
{
    pfnc_nvnBufferBuilderSetDevice(builder, device);
}

static NVNINLINE void NVNAPIENTRY nvnBufferBuilderSetDefaults(NVNbufferBuilder *builder)
{
    pfnc_nvnBufferBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnBufferBuilderSetStorage(NVNbufferBuilder *builder, NVNmemoryPool *pool, ptrdiff_t offset, size_t size)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBufferBuilderSetStorage_fastpath(builder, pool, offset, size);
#else
    pfnc_nvnBufferBuilderSetStorage(builder, pool, offset, size);
#endif
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnBufferBuilderGetDevice(const NVNbufferBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferBuilderGetDevice_fastpath(builder);
#else
    return pfnc_nvnBufferBuilderGetDevice(builder);
#endif
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnBufferBuilderGetMemoryPool(const NVNbufferBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferBuilderGetMemoryPool_fastpath(builder);
#else
    return pfnc_nvnBufferBuilderGetMemoryPool(builder);
#endif
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnBufferBuilderGetMemoryOffset(const NVNbufferBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferBuilderGetMemoryOffset_fastpath(builder);
#else
    return pfnc_nvnBufferBuilderGetMemoryOffset(builder);
#endif
}

static NVNINLINE size_t NVNAPIENTRY nvnBufferBuilderGetSize(const NVNbufferBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferBuilderGetSize_fastpath(builder);
#else
    return pfnc_nvnBufferBuilderGetSize(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnBufferInitialize(NVNbuffer *buffer, const NVNbufferBuilder *builder)
{
    return pfnc_nvnBufferInitialize(buffer, builder);
}

static NVNINLINE void NVNAPIENTRY nvnBufferSetDebugLabel(NVNbuffer *buffer, const char * label)
{
    pfnc_nvnBufferSetDebugLabel(buffer, label);
}

static NVNINLINE void NVNAPIENTRY nvnBufferFinalize(NVNbuffer *buffer)
{
    pfnc_nvnBufferFinalize(buffer);
}

static NVNINLINE void * NVNAPIENTRY nvnBufferMap(const NVNbuffer *buffer)
{
    return pfnc_nvnBufferMap(buffer);
}

static NVNINLINE NVNbufferAddress NVNAPIENTRY nvnBufferGetAddress(const NVNbuffer *buffer)
{
    return pfnc_nvnBufferGetAddress(buffer);
}

static NVNINLINE void NVNAPIENTRY nvnBufferFlushMappedRange(const NVNbuffer *buffer, ptrdiff_t offset, size_t size)
{
    pfnc_nvnBufferFlushMappedRange(buffer, offset, size);
}

static NVNINLINE void NVNAPIENTRY nvnBufferInvalidateMappedRange(const NVNbuffer *buffer, ptrdiff_t offset, size_t size)
{
    pfnc_nvnBufferInvalidateMappedRange(buffer, offset, size);
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnBufferGetMemoryPool(const NVNbuffer *buffer)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferGetMemoryPool_fastpath(buffer);
#else
    return pfnc_nvnBufferGetMemoryPool(buffer);
#endif
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnBufferGetMemoryOffset(const NVNbuffer *buffer)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferGetMemoryOffset_fastpath(buffer);
#else
    return pfnc_nvnBufferGetMemoryOffset(buffer);
#endif
}

static NVNINLINE size_t NVNAPIENTRY nvnBufferGetSize(const NVNbuffer *buffer)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBufferGetSize_fastpath(buffer);
#else
    return pfnc_nvnBufferGetSize(buffer);
#endif
}

static NVNINLINE uint64_t NVNAPIENTRY nvnBufferGetDebugID(const NVNbuffer *buffer)
{
    return pfnc_nvnBufferGetDebugID(buffer);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetDevice(NVNtextureBuilder *builder, NVNdevice *device)
{
    pfnc_nvnTextureBuilderSetDevice(builder, device);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetDefaults(NVNtextureBuilder *builder)
{
    pfnc_nvnTextureBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetFlags(NVNtextureBuilder *builder, int flags)
{
    pfnc_nvnTextureBuilderSetFlags(builder, flags);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetTarget(NVNtextureBuilder *builder, NVNtextureTarget target)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetTarget_fastpath(builder, target);
#else
    pfnc_nvnTextureBuilderSetTarget(builder, target);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetWidth(NVNtextureBuilder *builder, int width)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetWidth_fastpath(builder, width);
#else
    pfnc_nvnTextureBuilderSetWidth(builder, width);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetHeight(NVNtextureBuilder *builder, int height)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetHeight_fastpath(builder, height);
#else
    pfnc_nvnTextureBuilderSetHeight(builder, height);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetDepth(NVNtextureBuilder *builder, int depth)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetDepth_fastpath(builder, depth);
#else
    pfnc_nvnTextureBuilderSetDepth(builder, depth);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSize1D(NVNtextureBuilder *builder, int width)
{
    pfnc_nvnTextureBuilderSetSize1D(builder, width);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSize2D(NVNtextureBuilder *builder, int width, int height)
{
    pfnc_nvnTextureBuilderSetSize2D(builder, width, height);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSize3D(NVNtextureBuilder *builder, int width, int height, int depth)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetSize3D_fastpath(builder, width, height, depth);
#else
    pfnc_nvnTextureBuilderSetSize3D(builder, width, height, depth);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetLevels(NVNtextureBuilder *builder, int numLevels)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetLevels_fastpath(builder, numLevels);
#else
    pfnc_nvnTextureBuilderSetLevels(builder, numLevels);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetFormat(NVNtextureBuilder *builder, NVNformat format)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetFormat_fastpath(builder, format);
#else
    pfnc_nvnTextureBuilderSetFormat(builder, format);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSamples(NVNtextureBuilder *builder, int samples)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetSamples_fastpath(builder, samples);
#else
    pfnc_nvnTextureBuilderSetSamples(builder, samples);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetSwizzle(NVNtextureBuilder *builder, NVNtextureSwizzle r, NVNtextureSwizzle g, NVNtextureSwizzle b, NVNtextureSwizzle a)
{
    pfnc_nvnTextureBuilderSetSwizzle(builder, r, g, b, a);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetDepthStencilMode(NVNtextureBuilder *builder, NVNtextureDepthStencilMode mode)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetDepthStencilMode_fastpath(builder, mode);
#else
    pfnc_nvnTextureBuilderSetDepthStencilMode(builder, mode);
#endif
}

static NVNINLINE size_t NVNAPIENTRY nvnTextureBuilderGetStorageSize(const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureBuilderGetStorageSize(builder);
}

static NVNINLINE size_t NVNAPIENTRY nvnTextureBuilderGetStorageAlignment(const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureBuilderGetStorageAlignment(builder);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureBuilderGetViewOffset(const NVNtextureBuilder *builder, const NVNtextureView *textureView)
{
    return pfnc_nvnTextureBuilderGetViewOffset(builder, textureView);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetStorage(NVNtextureBuilder *builder, NVNmemoryPool *pool, ptrdiff_t offset)
{
#ifdef NVN_FORCE_FASTPATH
    nvnTextureBuilderSetStorage_fastpath(builder, pool, offset);
#else
    pfnc_nvnTextureBuilderSetStorage(builder, pool, offset);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetPackagedTextureData(NVNtextureBuilder *builder, const void *data)
{
    pfnc_nvnTextureBuilderSetPackagedTextureData(builder, data);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetPackagedTextureLayout(NVNtextureBuilder *builder, const NVNpackagedTextureLayout *layout)
{
    pfnc_nvnTextureBuilderSetPackagedTextureLayout(builder, layout);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetStride(NVNtextureBuilder *builder, ptrdiff_t stride)
{
    pfnc_nvnTextureBuilderSetStride(builder, stride);
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderSetGLTextureName(NVNtextureBuilder *builder, uint32_t name)
{
    pfnc_nvnTextureBuilderSetGLTextureName(builder, name);
}

static NVNINLINE NVNstorageClass NVNAPIENTRY nvnTextureBuilderGetStorageClass(const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureBuilderGetStorageClass(builder);
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnTextureBuilderGetDevice(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetDevice_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetDevice(builder);
#endif
}

static NVNINLINE NVNtextureFlags NVNAPIENTRY nvnTextureBuilderGetFlags(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetFlags_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetFlags(builder);
#endif
}

static NVNINLINE NVNtextureTarget NVNAPIENTRY nvnTextureBuilderGetTarget(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetTarget_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetTarget(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetWidth(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetWidth_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetWidth(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetHeight(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetHeight_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetHeight(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetDepth(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetDepth_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetDepth(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetLevels(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetLevels_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetLevels(builder);
#endif
}

static NVNINLINE NVNformat NVNAPIENTRY nvnTextureBuilderGetFormat(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetFormat_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetFormat(builder);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnTextureBuilderGetSamples(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetSamples_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetSamples(builder);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderGetSwizzle(const NVNtextureBuilder *builder, NVNtextureSwizzle *r, NVNtextureSwizzle *g, NVNtextureSwizzle *b, NVNtextureSwizzle *a)
{
    pfnc_nvnTextureBuilderGetSwizzle(builder, r, g, b, a);
}

static NVNINLINE NVNtextureDepthStencilMode NVNAPIENTRY nvnTextureBuilderGetDepthStencilMode(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetDepthStencilMode_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetDepthStencilMode(builder);
#endif
}

static NVNINLINE const void * NVNAPIENTRY nvnTextureBuilderGetPackagedTextureData(const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureBuilderGetPackagedTextureData(builder);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureBuilderGetPackagedTextureLayout(const NVNtextureBuilder *builder, NVNpackagedTextureLayout *data)
{
    return pfnc_nvnTextureBuilderGetPackagedTextureLayout(builder, data);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureBuilderGetStride(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetStride_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetStride(builder);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnTextureBuilderGetSparseTileLayout(const NVNtextureBuilder *builder, NVNtextureSparseTileLayout *layout)
{
    pfnc_nvnTextureBuilderGetSparseTileLayout(builder, layout);
}

static NVNINLINE uint32_t NVNAPIENTRY nvnTextureBuilderGetGLTextureName(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetGLTextureName_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetGLTextureName(builder);
#endif
}

static NVNINLINE size_t NVNAPIENTRY nvnTextureBuilderGetZCullStorageSize(const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureBuilderGetZCullStorageSize(builder);
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnTextureBuilderGetMemoryPool(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetMemoryPool_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetMemoryPool(builder);
#endif
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureBuilderGetMemoryOffset(const NVNtextureBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnTextureBuilderGetMemoryOffset_fastpath(builder);
#else
    return pfnc_nvnTextureBuilderGetMemoryOffset(builder);
#endif
}

static NVNINLINE NVNrawStorageClass NVNAPIENTRY nvnTextureBuilderGetRawStorageClass(const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureBuilderGetRawStorageClass(builder);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetDefaults(NVNtextureView *view)
{
    pfnc_nvnTextureViewSetDefaults(view);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetLevels(NVNtextureView *view, int baseLevel, int numLevels)
{
    pfnc_nvnTextureViewSetLevels(view, baseLevel, numLevels);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetLayers(NVNtextureView *view, int minLayer, int numLayers)
{
    pfnc_nvnTextureViewSetLayers(view, minLayer, numLayers);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetFormat(NVNtextureView *view, NVNformat format)
{
    pfnc_nvnTextureViewSetFormat(view, format);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetSwizzle(NVNtextureView *view, NVNtextureSwizzle r, NVNtextureSwizzle g, NVNtextureSwizzle b, NVNtextureSwizzle a)
{
    pfnc_nvnTextureViewSetSwizzle(view, r, g, b, a);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetDepthStencilMode(NVNtextureView *view, NVNtextureDepthStencilMode mode)
{
    pfnc_nvnTextureViewSetDepthStencilMode(view, mode);
}

static NVNINLINE void NVNAPIENTRY nvnTextureViewSetTarget(NVNtextureView *view, NVNtextureTarget target)
{
    pfnc_nvnTextureViewSetTarget(view, target);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewGetLevels(const NVNtextureView *view, int *baseLevel, int *numLevels)
{
    return pfnc_nvnTextureViewGetLevels(view, baseLevel, numLevels);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewGetLayers(const NVNtextureView *view, int *minLayer, int *numLayers)
{
    return pfnc_nvnTextureViewGetLayers(view, minLayer, numLayers);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewGetFormat(const NVNtextureView *view, NVNformat *format)
{
    return pfnc_nvnTextureViewGetFormat(view, format);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewGetSwizzle(const NVNtextureView *view, NVNtextureSwizzle *r, NVNtextureSwizzle *g, NVNtextureSwizzle *b, NVNtextureSwizzle *a)
{
    return pfnc_nvnTextureViewGetSwizzle(view, r, g, b, a);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewGetDepthStencilMode(const NVNtextureView *view, NVNtextureDepthStencilMode *mode)
{
    return pfnc_nvnTextureViewGetDepthStencilMode(view, mode);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewGetTarget(const NVNtextureView *view, NVNtextureTarget *target)
{
    return pfnc_nvnTextureViewGetTarget(view, target);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureViewCompare(const NVNtextureView *view, const NVNtextureView *otherView)
{
    return pfnc_nvnTextureViewCompare(view, otherView);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureInitialize(NVNtexture *texture, const NVNtextureBuilder *builder)
{
    return pfnc_nvnTextureInitialize(texture, builder);
}

static NVNINLINE size_t NVNAPIENTRY nvnTextureGetZCullStorageSize(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetZCullStorageSize(texture);
}

static NVNINLINE void NVNAPIENTRY nvnTextureFinalize(NVNtexture *texture)
{
    pfnc_nvnTextureFinalize(texture);
}

static NVNINLINE void NVNAPIENTRY nvnTextureSetDebugLabel(NVNtexture *texture, const char * label)
{
    pfnc_nvnTextureSetDebugLabel(texture, label);
}

static NVNINLINE NVNstorageClass NVNAPIENTRY nvnTextureGetStorageClass(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetStorageClass(texture);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureGetViewOffset(const NVNtexture *texture, const NVNtextureView *textureView)
{
    return pfnc_nvnTextureGetViewOffset(texture, textureView);
}

static NVNINLINE NVNtextureFlags NVNAPIENTRY nvnTextureGetFlags(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetFlags(texture);
}

static NVNINLINE NVNtextureTarget NVNAPIENTRY nvnTextureGetTarget(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetTarget(texture);
}

static NVNINLINE int NVNAPIENTRY nvnTextureGetWidth(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetWidth(texture);
}

static NVNINLINE int NVNAPIENTRY nvnTextureGetHeight(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetHeight(texture);
}

static NVNINLINE int NVNAPIENTRY nvnTextureGetDepth(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetDepth(texture);
}

static NVNINLINE int NVNAPIENTRY nvnTextureGetLevels(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetLevels(texture);
}

static NVNINLINE NVNformat NVNAPIENTRY nvnTextureGetFormat(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetFormat(texture);
}

static NVNINLINE int NVNAPIENTRY nvnTextureGetSamples(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetSamples(texture);
}

static NVNINLINE void NVNAPIENTRY nvnTextureGetSwizzle(const NVNtexture *texture, NVNtextureSwizzle *r, NVNtextureSwizzle *g, NVNtextureSwizzle *b, NVNtextureSwizzle *a)
{
    pfnc_nvnTextureGetSwizzle(texture, r, g, b, a);
}

static NVNINLINE NVNtextureDepthStencilMode NVNAPIENTRY nvnTextureGetDepthStencilMode(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetDepthStencilMode(texture);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureGetStride(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetStride(texture);
}

static NVNINLINE NVNtextureAddress NVNAPIENTRY nvnTextureGetTextureAddress(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetTextureAddress(texture);
}

static NVNINLINE void NVNAPIENTRY nvnTextureGetSparseTileLayout(const NVNtexture *texture, NVNtextureSparseTileLayout *layout)
{
    pfnc_nvnTextureGetSparseTileLayout(texture, layout);
}

static NVNINLINE void NVNAPIENTRY nvnTextureWriteTexels(const NVNtexture *texture, const NVNtextureView *textureView, const NVNcopyRegion *region, const void *data)
{
    pfnc_nvnTextureWriteTexels(texture, textureView, region, data);
}

static NVNINLINE void NVNAPIENTRY nvnTextureWriteTexelsStrided(const NVNtexture *texture, const NVNtextureView *textureView, const NVNcopyRegion *region, const void *data, ptrdiff_t rowStride, ptrdiff_t imageStride)
{
    pfnc_nvnTextureWriteTexelsStrided(texture, textureView, region, data, rowStride, imageStride);
}

static NVNINLINE void NVNAPIENTRY nvnTextureReadTexels(const NVNtexture *texture, const NVNtextureView *textureView, const NVNcopyRegion *region, void *data)
{
    pfnc_nvnTextureReadTexels(texture, textureView, region, data);
}

static NVNINLINE void NVNAPIENTRY nvnTextureReadTexelsStrided(const NVNtexture *texture, const NVNtextureView *textureView, const NVNcopyRegion *region, void *data, ptrdiff_t rowStride, ptrdiff_t imageStride)
{
    pfnc_nvnTextureReadTexelsStrided(texture, textureView, region, data, rowStride, imageStride);
}

static NVNINLINE void NVNAPIENTRY nvnTextureFlushTexels(const NVNtexture *texture, const NVNtextureView *textureView, const NVNcopyRegion *region)
{
    pfnc_nvnTextureFlushTexels(texture, textureView, region);
}

static NVNINLINE void NVNAPIENTRY nvnTextureInvalidateTexels(const NVNtexture *texture, const NVNtextureView *textureView, const NVNcopyRegion *region)
{
    pfnc_nvnTextureInvalidateTexels(texture, textureView, region);
}

static NVNINLINE NVNmemoryPool * NVNAPIENTRY nvnTextureGetMemoryPool(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetMemoryPool(texture);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnTextureGetMemoryOffset(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetMemoryOffset(texture);
}

static NVNINLINE int NVNAPIENTRY nvnTextureGetStorageSize(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetStorageSize(texture);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnTextureCompare(const NVNtexture *texture, const NVNtexture *otherTexture)
{
    return pfnc_nvnTextureCompare(texture, otherTexture);
}

static NVNINLINE uint64_t NVNAPIENTRY nvnTextureGetDebugID(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetDebugID(texture);
}

static NVNINLINE NVNrawStorageClass NVNAPIENTRY nvnTextureGetRawStorageClass(const NVNtexture *texture)
{
    return pfnc_nvnTextureGetRawStorageClass(texture);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetDevice(NVNsamplerBuilder *builder, NVNdevice *device)
{
    pfnc_nvnSamplerBuilderSetDevice(builder, device);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetDefaults(NVNsamplerBuilder *builder)
{
    pfnc_nvnSamplerBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetMinMagFilter(NVNsamplerBuilder *builder, NVNminFilter min, NVNmagFilter mag)
{
    pfnc_nvnSamplerBuilderSetMinMagFilter(builder, min, mag);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetWrapMode(NVNsamplerBuilder *builder, NVNwrapMode s, NVNwrapMode t, NVNwrapMode r)
{
    pfnc_nvnSamplerBuilderSetWrapMode(builder, s, t, r);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetLodClamp(NVNsamplerBuilder *builder, float min, float max)
{
#ifdef NVN_FORCE_FASTPATH
    nvnSamplerBuilderSetLodClamp_fastpath(builder, min, max);
#else
    pfnc_nvnSamplerBuilderSetLodClamp(builder, min, max);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetLodBias(NVNsamplerBuilder *builder, float bias)
{
#ifdef NVN_FORCE_FASTPATH
    nvnSamplerBuilderSetLodBias_fastpath(builder, bias);
#else
    pfnc_nvnSamplerBuilderSetLodBias(builder, bias);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetCompare(NVNsamplerBuilder *builder, NVNcompareMode mode, NVNcompareFunc func)
{
    pfnc_nvnSamplerBuilderSetCompare(builder, mode, func);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetBorderColor(NVNsamplerBuilder *builder, const float *borderColor)
{
    pfnc_nvnSamplerBuilderSetBorderColor(builder, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetBorderColori(NVNsamplerBuilder *builder, const int *borderColor)
{
    pfnc_nvnSamplerBuilderSetBorderColori(builder, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetBorderColorui(NVNsamplerBuilder *builder, const uint32_t *borderColor)
{
    pfnc_nvnSamplerBuilderSetBorderColorui(builder, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetMaxAnisotropy(NVNsamplerBuilder *builder, float maxAniso)
{
#ifdef NVN_FORCE_FASTPATH
    nvnSamplerBuilderSetMaxAnisotropy_fastpath(builder, maxAniso);
#else
    pfnc_nvnSamplerBuilderSetMaxAnisotropy(builder, maxAniso);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetReductionFilter(NVNsamplerBuilder *builder, NVNsamplerReduction filter)
{
    pfnc_nvnSamplerBuilderSetReductionFilter(builder, filter);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderSetLodSnap(NVNsamplerBuilder *builder, float lodSnap)
{
#ifdef NVN_FORCE_FASTPATH
    nvnSamplerBuilderSetLodSnap_fastpath(builder, lodSnap);
#else
    pfnc_nvnSamplerBuilderSetLodSnap(builder, lodSnap);
#endif
}

static NVNINLINE const NVNdevice * NVNAPIENTRY nvnSamplerBuilderGetDevice(const NVNsamplerBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerBuilderGetDevice_fastpath(builder);
#else
    return pfnc_nvnSamplerBuilderGetDevice(builder);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetMinMagFilter(const NVNsamplerBuilder *builder, NVNminFilter *min, NVNmagFilter *mag)
{
    pfnc_nvnSamplerBuilderGetMinMagFilter(builder, min, mag);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetWrapMode(const NVNsamplerBuilder *builder, NVNwrapMode *s, NVNwrapMode *t, NVNwrapMode *r)
{
    pfnc_nvnSamplerBuilderGetWrapMode(builder, s, t, r);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetLodClamp(const NVNsamplerBuilder *builder, float *min, float *max)
{
    pfnc_nvnSamplerBuilderGetLodClamp(builder, min, max);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerBuilderGetLodBias(const NVNsamplerBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerBuilderGetLodBias_fastpath(builder);
#else
    return pfnc_nvnSamplerBuilderGetLodBias(builder);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetCompare(const NVNsamplerBuilder *builder, NVNcompareMode *mode, NVNcompareFunc *func)
{
    pfnc_nvnSamplerBuilderGetCompare(builder, mode, func);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetBorderColor(const NVNsamplerBuilder *builder, float *borderColor)
{
    pfnc_nvnSamplerBuilderGetBorderColor(builder, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetBorderColori(const NVNsamplerBuilder *builder, int *borderColor)
{
    pfnc_nvnSamplerBuilderGetBorderColori(builder, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerBuilderGetBorderColorui(const NVNsamplerBuilder *builder, uint32_t *borderColor)
{
    pfnc_nvnSamplerBuilderGetBorderColorui(builder, borderColor);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerBuilderGetMaxAnisotropy(const NVNsamplerBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerBuilderGetMaxAnisotropy_fastpath(builder);
#else
    return pfnc_nvnSamplerBuilderGetMaxAnisotropy(builder);
#endif
}

static NVNINLINE NVNsamplerReduction NVNAPIENTRY nvnSamplerBuilderGetReductionFilter(const NVNsamplerBuilder *builder)
{
    return pfnc_nvnSamplerBuilderGetReductionFilter(builder);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerBuilderGetLodSnap(const NVNsamplerBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnSamplerBuilderGetLodSnap_fastpath(builder);
#else
    return pfnc_nvnSamplerBuilderGetLodSnap(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnSamplerInitialize(NVNsampler *sampler, const NVNsamplerBuilder *builder)
{
    return pfnc_nvnSamplerInitialize(sampler, builder);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerFinalize(NVNsampler *sampler)
{
    pfnc_nvnSamplerFinalize(sampler);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerSetDebugLabel(NVNsampler *sampler, const char * label)
{
    pfnc_nvnSamplerSetDebugLabel(sampler, label);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetMinMagFilter(const NVNsampler *sampler, NVNminFilter *min, NVNmagFilter *mag)
{
    pfnc_nvnSamplerGetMinMagFilter(sampler, min, mag);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetWrapMode(const NVNsampler *sampler, NVNwrapMode *s, NVNwrapMode *t, NVNwrapMode *r)
{
    pfnc_nvnSamplerGetWrapMode(sampler, s, t, r);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetLodClamp(const NVNsampler *sampler, float *min, float *max)
{
    pfnc_nvnSamplerGetLodClamp(sampler, min, max);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerGetLodBias(const NVNsampler *sampler)
{
    return pfnc_nvnSamplerGetLodBias(sampler);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetCompare(const NVNsampler *sampler, NVNcompareMode *mode, NVNcompareFunc *func)
{
    pfnc_nvnSamplerGetCompare(sampler, mode, func);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetBorderColor(const NVNsampler *sampler, float *borderColor)
{
    pfnc_nvnSamplerGetBorderColor(sampler, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetBorderColori(const NVNsampler *sampler, int *borderColor)
{
    pfnc_nvnSamplerGetBorderColori(sampler, borderColor);
}

static NVNINLINE void NVNAPIENTRY nvnSamplerGetBorderColorui(const NVNsampler *sampler, uint32_t *borderColor)
{
    pfnc_nvnSamplerGetBorderColorui(sampler, borderColor);
}

static NVNINLINE float NVNAPIENTRY nvnSamplerGetMaxAnisotropy(const NVNsampler *sampler)
{
    return pfnc_nvnSamplerGetMaxAnisotropy(sampler);
}

static NVNINLINE NVNsamplerReduction NVNAPIENTRY nvnSamplerGetReductionFilter(const NVNsampler *sampler)
{
    return pfnc_nvnSamplerGetReductionFilter(sampler);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnSamplerCompare(const NVNsampler *sampler, const NVNsampler *otherSampler)
{
    return pfnc_nvnSamplerCompare(sampler, otherSampler);
}

static NVNINLINE uint64_t NVNAPIENTRY nvnSamplerGetDebugID(const NVNsampler *sampler)
{
    return pfnc_nvnSamplerGetDebugID(sampler);
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetDefaults(NVNblendState *blend)
{
    pfnc_nvnBlendStateSetDefaults(blend);
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetBlendTarget(NVNblendState *blend, int target)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetBlendTarget_fastpath(blend, target);
#else
    pfnc_nvnBlendStateSetBlendTarget(blend, target);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetBlendFunc(NVNblendState *blend, NVNblendFunc srcFunc, NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha, NVNblendFunc dstFuncAlpha)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetBlendFunc_fastpath(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
#else
    pfnc_nvnBlendStateSetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetBlendEquation(NVNblendState *blend, NVNblendEquation modeRGB, NVNblendEquation modeAlpha)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetBlendEquation_fastpath(blend, modeRGB, modeAlpha);
#else
    pfnc_nvnBlendStateSetBlendEquation(blend, modeRGB, modeAlpha);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedMode(NVNblendState *blend, NVNblendAdvancedMode overlap)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetAdvancedMode_fastpath(blend, overlap);
#else
    pfnc_nvnBlendStateSetAdvancedMode(blend, overlap);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedOverlap(NVNblendState *blend, NVNblendAdvancedOverlap overlap)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetAdvancedOverlap_fastpath(blend, overlap);
#else
    pfnc_nvnBlendStateSetAdvancedOverlap(blend, overlap);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedPremultipliedSrc(NVNblendState *blend, NVNboolean premultiplied)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetAdvancedPremultipliedSrc_fastpath(blend, premultiplied);
#else
    pfnc_nvnBlendStateSetAdvancedPremultipliedSrc(blend, premultiplied);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateSetAdvancedNormalizedDst(NVNblendState *blend, NVNboolean normalized)
{
#ifdef NVN_FORCE_FASTPATH
    nvnBlendStateSetAdvancedNormalizedDst_fastpath(blend, normalized);
#else
    pfnc_nvnBlendStateSetAdvancedNormalizedDst(blend, normalized);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnBlendStateGetBlendTarget(const NVNblendState *blend)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBlendStateGetBlendTarget_fastpath(blend);
#else
    return pfnc_nvnBlendStateGetBlendTarget(blend);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateGetBlendFunc(const NVNblendState *blend, NVNblendFunc *srcFunc, NVNblendFunc *dstFunc, NVNblendFunc *srcFuncAlpha, NVNblendFunc *dstFuncAlpha)
{
    pfnc_nvnBlendStateGetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
}

static NVNINLINE void NVNAPIENTRY nvnBlendStateGetBlendEquation(const NVNblendState *blend, NVNblendEquation *modeRGB, NVNblendEquation *modeAlpha)
{
    pfnc_nvnBlendStateGetBlendEquation(blend, modeRGB, modeAlpha);
}

static NVNINLINE NVNblendAdvancedMode NVNAPIENTRY nvnBlendStateGetAdvancedMode(const NVNblendState *blend)
{
    return pfnc_nvnBlendStateGetAdvancedMode(blend);
}

static NVNINLINE NVNblendAdvancedOverlap NVNAPIENTRY nvnBlendStateGetAdvancedOverlap(const NVNblendState *blend)
{
    return pfnc_nvnBlendStateGetAdvancedOverlap(blend);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnBlendStateGetAdvancedPremultipliedSrc(const NVNblendState *blend)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBlendStateGetAdvancedPremultipliedSrc_fastpath(blend);
#else
    return pfnc_nvnBlendStateGetAdvancedPremultipliedSrc(blend);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnBlendStateGetAdvancedNormalizedDst(const NVNblendState *blend)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnBlendStateGetAdvancedNormalizedDst_fastpath(blend);
#else
    return pfnc_nvnBlendStateGetAdvancedNormalizedDst(blend);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnColorStateSetDefaults(NVNcolorState *color)
{
    pfnc_nvnColorStateSetDefaults(color);
}

static NVNINLINE void NVNAPIENTRY nvnColorStateSetBlendEnable(NVNcolorState *color, int index, NVNboolean enable)
{
    pfnc_nvnColorStateSetBlendEnable(color, index, enable);
}

static NVNINLINE void NVNAPIENTRY nvnColorStateSetLogicOp(NVNcolorState *color, NVNlogicOp logicOp)
{
#ifdef NVN_FORCE_FASTPATH
    nvnColorStateSetLogicOp_fastpath(color, logicOp);
#else
    pfnc_nvnColorStateSetLogicOp(color, logicOp);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnColorStateSetAlphaTest(NVNcolorState *color, NVNalphaFunc alphaTest)
{
#ifdef NVN_FORCE_FASTPATH
    nvnColorStateSetAlphaTest_fastpath(color, alphaTest);
#else
    pfnc_nvnColorStateSetAlphaTest(color, alphaTest);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnColorStateGetBlendEnable(const NVNcolorState *color, int index)
{
    return pfnc_nvnColorStateGetBlendEnable(color, index);
}

static NVNINLINE NVNlogicOp NVNAPIENTRY nvnColorStateGetLogicOp(const NVNcolorState *color)
{
    return pfnc_nvnColorStateGetLogicOp(color);
}

static NVNINLINE NVNalphaFunc NVNAPIENTRY nvnColorStateGetAlphaTest(const NVNcolorState *color)
{
    return pfnc_nvnColorStateGetAlphaTest(color);
}

static NVNINLINE void NVNAPIENTRY nvnChannelMaskStateSetDefaults(NVNchannelMaskState *channelMask)
{
    pfnc_nvnChannelMaskStateSetDefaults(channelMask);
}

static NVNINLINE void NVNAPIENTRY nvnChannelMaskStateSetChannelMask(NVNchannelMaskState *channelMask, int index, NVNboolean r, NVNboolean g, NVNboolean b, NVNboolean a)
{
    pfnc_nvnChannelMaskStateSetChannelMask(channelMask, index, r, g, b, a);
}

static NVNINLINE void NVNAPIENTRY nvnChannelMaskStateGetChannelMask(const NVNchannelMaskState *channelMask, int index, NVNboolean *r, NVNboolean *g, NVNboolean *b, NVNboolean *a)
{
    pfnc_nvnChannelMaskStateGetChannelMask(channelMask, index, r, g, b, a);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetDefaults(NVNmultisampleState *multisample)
{
    pfnc_nvnMultisampleStateSetDefaults(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetMultisampleEnable(NVNmultisampleState *multisample, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetMultisampleEnable_fastpath(multisample, enable);
#else
    pfnc_nvnMultisampleStateSetMultisampleEnable(multisample, enable);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSamples(NVNmultisampleState *multisample, int samples)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetSamples_fastpath(multisample, samples);
#else
    pfnc_nvnMultisampleStateSetSamples(multisample, samples);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetAlphaToCoverageEnable(NVNmultisampleState *multisample, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetAlphaToCoverageEnable_fastpath(multisample, enable);
#else
    pfnc_nvnMultisampleStateSetAlphaToCoverageEnable(multisample, enable);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetAlphaToCoverageDither(NVNmultisampleState *multisample, NVNboolean dither)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetAlphaToCoverageDither_fastpath(multisample, dither);
#else
    pfnc_nvnMultisampleStateSetAlphaToCoverageDither(multisample, dither);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetMultisampleEnable(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetMultisampleEnable_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetMultisampleEnable(multisample);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnMultisampleStateGetSamples(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetSamples_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetSamples(multisample);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetAlphaToCoverageEnable(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetAlphaToCoverageEnable_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetAlphaToCoverageEnable(multisample);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetAlphaToCoverageDither(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetAlphaToCoverageDither_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetAlphaToCoverageDither(multisample);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetRasterSamples(NVNmultisampleState *multisample, int rasterSamples)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetRasterSamples_fastpath(multisample, rasterSamples);
#else
    pfnc_nvnMultisampleStateSetRasterSamples(multisample, rasterSamples);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnMultisampleStateGetRasterSamples(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetRasterSamples_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetRasterSamples(multisample);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetCoverageModulationMode(NVNmultisampleState *multisample, NVNcoverageModulationMode mode)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetCoverageModulationMode_fastpath(multisample, mode);
#else
    pfnc_nvnMultisampleStateSetCoverageModulationMode(multisample, mode);
#endif
}

static NVNINLINE NVNcoverageModulationMode NVNAPIENTRY nvnMultisampleStateGetCoverageModulationMode(const NVNmultisampleState *multisample)
{
    return pfnc_nvnMultisampleStateGetCoverageModulationMode(multisample);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetCoverageToColorEnable(NVNmultisampleState *multisample, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetCoverageToColorEnable_fastpath(multisample, enable);
#else
    pfnc_nvnMultisampleStateSetCoverageToColorEnable(multisample, enable);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetCoverageToColorEnable(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetCoverageToColorEnable_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetCoverageToColorEnable(multisample);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetCoverageToColorOutput(NVNmultisampleState *multisample, int color)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetCoverageToColorOutput_fastpath(multisample, color);
#else
    pfnc_nvnMultisampleStateSetCoverageToColorOutput(multisample, color);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnMultisampleStateGetCoverageToColorOutput(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetCoverageToColorOutput_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetCoverageToColorOutput(multisample);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSampleLocationsEnable(NVNmultisampleState *multisample, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetSampleLocationsEnable_fastpath(multisample, enable);
#else
    pfnc_nvnMultisampleStateSetSampleLocationsEnable(multisample, enable);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetSampleLocationsEnable(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetSampleLocationsEnable_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetSampleLocationsEnable(multisample);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateGetSampleLocationsGrid(NVNmultisampleState *multisample, int *width, int *height)
{
    pfnc_nvnMultisampleStateGetSampleLocationsGrid(multisample, width, height);
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSampleLocationsGridEnable(NVNmultisampleState *multisample, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnMultisampleStateSetSampleLocationsGridEnable_fastpath(multisample, enable);
#else
    pfnc_nvnMultisampleStateSetSampleLocationsGridEnable(multisample, enable);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnMultisampleStateGetSampleLocationsGridEnable(const NVNmultisampleState *multisample)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnMultisampleStateGetSampleLocationsGridEnable_fastpath(multisample);
#else
    return pfnc_nvnMultisampleStateGetSampleLocationsGridEnable(multisample);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnMultisampleStateSetSampleLocations(NVNmultisampleState *multisample, int start, int count, const float *values)
{
    pfnc_nvnMultisampleStateSetSampleLocations(multisample, start, count, values);
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetDefaults(NVNpolygonState *polygon)
{
    pfnc_nvnPolygonStateSetDefaults(polygon);
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetCullFace(NVNpolygonState *polygon, NVNface face)
{
#ifdef NVN_FORCE_FASTPATH
    nvnPolygonStateSetCullFace_fastpath(polygon, face);
#else
    pfnc_nvnPolygonStateSetCullFace(polygon, face);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetFrontFace(NVNpolygonState *polygon, NVNfrontFace face)
{
#ifdef NVN_FORCE_FASTPATH
    nvnPolygonStateSetFrontFace_fastpath(polygon, face);
#else
    pfnc_nvnPolygonStateSetFrontFace(polygon, face);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetPolygonMode(NVNpolygonState *polygon, NVNpolygonMode polygonMode)
{
#ifdef NVN_FORCE_FASTPATH
    nvnPolygonStateSetPolygonMode_fastpath(polygon, polygonMode);
#else
    pfnc_nvnPolygonStateSetPolygonMode(polygon, polygonMode);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnPolygonStateSetPolygonOffsetEnables(NVNpolygonState *polygon, int enables)
{
    pfnc_nvnPolygonStateSetPolygonOffsetEnables(polygon, enables);
}

static NVNINLINE NVNface NVNAPIENTRY nvnPolygonStateGetCullFace(const NVNpolygonState *polygon)
{
    return pfnc_nvnPolygonStateGetCullFace(polygon);
}

static NVNINLINE NVNfrontFace NVNAPIENTRY nvnPolygonStateGetFrontFace(const NVNpolygonState *polygon)
{
    return pfnc_nvnPolygonStateGetFrontFace(polygon);
}

static NVNINLINE NVNpolygonMode NVNAPIENTRY nvnPolygonStateGetPolygonMode(const NVNpolygonState *polygon)
{
    return pfnc_nvnPolygonStateGetPolygonMode(polygon);
}

static NVNINLINE NVNpolygonOffsetEnable NVNAPIENTRY nvnPolygonStateGetPolygonOffsetEnables(const NVNpolygonState *polygon)
{
    return pfnc_nvnPolygonStateGetPolygonOffsetEnables(polygon);
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDefaults(NVNdepthStencilState *depthStencil)
{
    pfnc_nvnDepthStencilStateSetDefaults(depthStencil);
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDepthTestEnable(NVNdepthStencilState *depthStencil, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnDepthStencilStateSetDepthTestEnable_fastpath(depthStencil, enable);
#else
    pfnc_nvnDepthStencilStateSetDepthTestEnable(depthStencil, enable);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDepthWriteEnable(NVNdepthStencilState *depthStencil, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnDepthStencilStateSetDepthWriteEnable_fastpath(depthStencil, enable);
#else
    pfnc_nvnDepthStencilStateSetDepthWriteEnable(depthStencil, enable);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetDepthFunc(NVNdepthStencilState *depthStencil, NVNdepthFunc func)
{
#ifdef NVN_FORCE_FASTPATH
    nvnDepthStencilStateSetDepthFunc_fastpath(depthStencil, func);
#else
    pfnc_nvnDepthStencilStateSetDepthFunc(depthStencil, func);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetStencilTestEnable(NVNdepthStencilState *depthStencil, NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    nvnDepthStencilStateSetStencilTestEnable_fastpath(depthStencil, enable);
#else
    pfnc_nvnDepthStencilStateSetStencilTestEnable(depthStencil, enable);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetStencilFunc(NVNdepthStencilState *depthStencil, NVNface faces, NVNstencilFunc func)
{
    pfnc_nvnDepthStencilStateSetStencilFunc(depthStencil, faces, func);
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateSetStencilOp(NVNdepthStencilState *depthStencil, NVNface faces, NVNstencilOp fail, NVNstencilOp depthFail, NVNstencilOp depthPass)
{
    pfnc_nvnDepthStencilStateSetStencilOp(depthStencil, faces, fail, depthFail, depthPass);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDepthStencilStateGetDepthTestEnable(const NVNdepthStencilState *depthStencil)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnDepthStencilStateGetDepthTestEnable_fastpath(depthStencil);
#else
    return pfnc_nvnDepthStencilStateGetDepthTestEnable(depthStencil);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDepthStencilStateGetDepthWriteEnable(const NVNdepthStencilState *depthStencil)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnDepthStencilStateGetDepthWriteEnable_fastpath(depthStencil);
#else
    return pfnc_nvnDepthStencilStateGetDepthWriteEnable(depthStencil);
#endif
}

static NVNINLINE NVNdepthFunc NVNAPIENTRY nvnDepthStencilStateGetDepthFunc(const NVNdepthStencilState *depthStencil)
{
    return pfnc_nvnDepthStencilStateGetDepthFunc(depthStencil);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDepthStencilStateGetStencilTestEnable(const NVNdepthStencilState *depthStencil)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnDepthStencilStateGetStencilTestEnable_fastpath(depthStencil);
#else
    return pfnc_nvnDepthStencilStateGetStencilTestEnable(depthStencil);
#endif
}

static NVNINLINE NVNstencilFunc NVNAPIENTRY nvnDepthStencilStateGetStencilFunc(const NVNdepthStencilState *depthStencil, NVNface face)
{
    return pfnc_nvnDepthStencilStateGetStencilFunc(depthStencil, face);
}

static NVNINLINE void NVNAPIENTRY nvnDepthStencilStateGetStencilOp(const NVNdepthStencilState *depthStencil, NVNface face, NVNstencilOp *fail, NVNstencilOp *depthFail, NVNstencilOp *depthPass)
{
    pfnc_nvnDepthStencilStateGetStencilOp(depthStencil, face, fail, depthFail, depthPass);
}

static NVNINLINE void NVNAPIENTRY nvnVertexAttribStateSetDefaults(NVNvertexAttribState *attrib)
{
    pfnc_nvnVertexAttribStateSetDefaults(attrib);
}

static NVNINLINE void NVNAPIENTRY nvnVertexAttribStateSetFormat(NVNvertexAttribState *attrib, NVNformat format, ptrdiff_t relativeOffset)
{
    pfnc_nvnVertexAttribStateSetFormat(attrib, format, relativeOffset);
}

static NVNINLINE void NVNAPIENTRY nvnVertexAttribStateSetStreamIndex(NVNvertexAttribState *attrib, int streamIndex)
{
#ifdef NVN_FORCE_FASTPATH
    nvnVertexAttribStateSetStreamIndex_fastpath(attrib, streamIndex);
#else
    pfnc_nvnVertexAttribStateSetStreamIndex(attrib, streamIndex);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnVertexAttribStateGetFormat(const NVNvertexAttribState *attrib, NVNformat *format, ptrdiff_t *relativeOffset)
{
    pfnc_nvnVertexAttribStateGetFormat(attrib, format, relativeOffset);
}

static NVNINLINE int NVNAPIENTRY nvnVertexAttribStateGetStreamIndex(const NVNvertexAttribState *attrib)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnVertexAttribStateGetStreamIndex_fastpath(attrib);
#else
    return pfnc_nvnVertexAttribStateGetStreamIndex(attrib);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnVertexStreamStateSetDefaults(NVNvertexStreamState *stream)
{
    pfnc_nvnVertexStreamStateSetDefaults(stream);
}

static NVNINLINE void NVNAPIENTRY nvnVertexStreamStateSetStride(NVNvertexStreamState *stream, ptrdiff_t stride)
{
#ifdef NVN_FORCE_FASTPATH
    nvnVertexStreamStateSetStride_fastpath(stream, stride);
#else
    pfnc_nvnVertexStreamStateSetStride(stream, stride);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnVertexStreamStateSetDivisor(NVNvertexStreamState *stream, int divisor)
{
#ifdef NVN_FORCE_FASTPATH
    nvnVertexStreamStateSetDivisor_fastpath(stream, divisor);
#else
    pfnc_nvnVertexStreamStateSetDivisor(stream, divisor);
#endif
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnVertexStreamStateGetStride(const NVNvertexStreamState *stream)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnVertexStreamStateGetStride_fastpath(stream);
#else
    return pfnc_nvnVertexStreamStateGetStride(stream);
#endif
}

static NVNINLINE int NVNAPIENTRY nvnVertexStreamStateGetDivisor(const NVNvertexStreamState *stream)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnVertexStreamStateGetDivisor_fastpath(stream);
#else
    return pfnc_nvnVertexStreamStateGetDivisor(stream);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnCommandBufferInitialize(NVNcommandBuffer *cmdBuf, NVNdevice *device)
{
    return pfnc_nvnCommandBufferInitialize(cmdBuf, device);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferFinalize(NVNcommandBuffer *cmdBuf)
{
    pfnc_nvnCommandBufferFinalize(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetDebugLabel(NVNcommandBuffer *cmdBuf, const char * label)
{
    pfnc_nvnCommandBufferSetDebugLabel(cmdBuf, label);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetMemoryCallback(NVNcommandBuffer *cmdBuf, PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC callback)
{
    pfnc_nvnCommandBufferSetMemoryCallback(cmdBuf, callback);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetMemoryCallbackData(NVNcommandBuffer *cmdBuf, void *callbackData)
{
    pfnc_nvnCommandBufferSetMemoryCallbackData(cmdBuf, callbackData);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetCommandMemoryCallbackEnabled(NVNcommandBuffer *cmdBuf, NVNboolean enabled)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferSetCommandMemoryCallbackEnabled_fastpath(cmdBuf, enabled);
#else
    pfnc_nvnCommandBufferSetCommandMemoryCallbackEnabled(cmdBuf, enabled);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferAddCommandMemory(NVNcommandBuffer *cmdBuf, const NVNmemoryPool *pool, ptrdiff_t offset, size_t size)
{
    pfnc_nvnCommandBufferAddCommandMemory(cmdBuf, pool, offset, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferAddControlMemory(NVNcommandBuffer *cmdBuf, void *memory, size_t size)
{
    pfnc_nvnCommandBufferAddControlMemory(cmdBuf, memory, size);
}

static NVNINLINE size_t NVNAPIENTRY nvnCommandBufferGetCommandMemorySize(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetCommandMemorySize(cmdBuf);
}

static NVNINLINE size_t NVNAPIENTRY nvnCommandBufferGetCommandMemoryUsed(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetCommandMemoryUsed(cmdBuf);
}

static NVNINLINE size_t NVNAPIENTRY nvnCommandBufferGetCommandMemoryFree(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetCommandMemoryFree(cmdBuf);
}

static NVNINLINE size_t NVNAPIENTRY nvnCommandBufferGetControlMemorySize(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetControlMemorySize(cmdBuf);
}

static NVNINLINE size_t NVNAPIENTRY nvnCommandBufferGetControlMemoryUsed(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetControlMemoryUsed(cmdBuf);
}

static NVNINLINE size_t NVNAPIENTRY nvnCommandBufferGetControlMemoryFree(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetControlMemoryFree(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBeginRecording(NVNcommandBuffer *cmdBuf)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBeginRecording_fastpath(cmdBuf);
#else
    pfnc_nvnCommandBufferBeginRecording(cmdBuf);
#endif
}

static NVNINLINE NVNcommandHandle NVNAPIENTRY nvnCommandBufferEndRecording(NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferEndRecording(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCallCommands(NVNcommandBuffer *cmdBuf, int numCommands, NVN_NOESCAPE const NVNcommandHandle *handles)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferCallCommands_fastpath(cmdBuf, numCommands, handles);
#else
    pfnc_nvnCommandBufferCallCommands(cmdBuf, numCommands, handles);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCopyCommands(NVNcommandBuffer *cmdBuf, int numCommands, NVN_NOESCAPE const NVNcommandHandle *handles)
{
    pfnc_nvnCommandBufferCopyCommands(cmdBuf, numCommands, handles);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindBlendState(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const NVNblendState *blend)
{
    pfnc_nvnCommandBufferBindBlendState(cmdBuf, blend);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindChannelMaskState(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const NVNchannelMaskState *channelMask)
{
    pfnc_nvnCommandBufferBindChannelMaskState(cmdBuf, channelMask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindColorState(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const NVNcolorState *color)
{
    pfnc_nvnCommandBufferBindColorState(cmdBuf, color);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindMultisampleState(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const NVNmultisampleState *multisample)
{
    pfnc_nvnCommandBufferBindMultisampleState(cmdBuf, multisample);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindPolygonState(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const NVNpolygonState *polygon)
{
    pfnc_nvnCommandBufferBindPolygonState(cmdBuf, polygon);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindDepthStencilState(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const NVNdepthStencilState *depthStencil)
{
    pfnc_nvnCommandBufferBindDepthStencilState(cmdBuf, depthStencil);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindVertexAttribState(NVNcommandBuffer *cmdBuf, int numAttribs, NVN_NOESCAPE const NVNvertexAttribState *attribs)
{
    pfnc_nvnCommandBufferBindVertexAttribState(cmdBuf, numAttribs, attribs);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindVertexStreamState(NVNcommandBuffer *cmdBuf, int numStreams, NVN_NOESCAPE const NVNvertexStreamState *streams)
{
    pfnc_nvnCommandBufferBindVertexStreamState(cmdBuf, numStreams, streams);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindProgram(NVNcommandBuffer *cmdBuf, const NVNprogram *program, int stages)
{
    pfnc_nvnCommandBufferBindProgram(cmdBuf, program, stages);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindVertexBuffer(NVNcommandBuffer *cmdBuf, int index, NVNbufferAddress buffer, size_t size)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindVertexBuffer_fastpath(cmdBuf, index, buffer, size);
#else
    pfnc_nvnCommandBufferBindVertexBuffer(cmdBuf, index, buffer, size);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindVertexBuffers(NVNcommandBuffer *cmdBuf, int first, int count, NVN_NOESCAPE const NVNbufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindVertexBuffers_fastpath(cmdBuf, first, count, buffers);
#else
    pfnc_nvnCommandBufferBindVertexBuffers(cmdBuf, first, count, buffers);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindUniformBuffer(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindUniformBuffer_fastpath(cmdBuf, stage, index, buffer, size);
#else
    pfnc_nvnCommandBufferBindUniformBuffer(cmdBuf, stage, index, buffer, size);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindUniformBuffers(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNbufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindUniformBuffers_fastpath(cmdBuf, stage, first, count, buffers);
#else
    pfnc_nvnCommandBufferBindUniformBuffers(cmdBuf, stage, first, count, buffers);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindUniformBuffersDeferred(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, const NVNbufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindUniformBuffersDeferred_fastpath(cmdBuf, stage, first, count, buffers);
#else
    pfnc_nvnCommandBufferBindUniformBuffersDeferred(cmdBuf, stage, first, count, buffers);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindTransformFeedbackBuffer(NVNcommandBuffer *cmdBuf, int index, NVNbufferAddress buffer, size_t size)
{
    pfnc_nvnCommandBufferBindTransformFeedbackBuffer(cmdBuf, index, buffer, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindTransformFeedbackBuffers(NVNcommandBuffer *cmdBuf, int first, int count, NVN_NOESCAPE const NVNbufferRange *buffers)
{
    pfnc_nvnCommandBufferBindTransformFeedbackBuffers(cmdBuf, first, count, buffers);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindStorageBuffer(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size)
{
    pfnc_nvnCommandBufferBindStorageBuffer(cmdBuf, stage, index, buffer, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindStorageBuffers(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNbufferRange *buffers)
{
    pfnc_nvnCommandBufferBindStorageBuffers(cmdBuf, stage, first, count, buffers);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindStorageBuffersDeferred(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, const NVNbufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindStorageBuffersDeferred_fastpath(cmdBuf, stage, first, count, buffers);
#else
    pfnc_nvnCommandBufferBindStorageBuffersDeferred(cmdBuf, stage, first, count, buffers);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindTexture(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNtextureHandle texture)
{
    pfnc_nvnCommandBufferBindTexture(cmdBuf, stage, index, texture);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindTextures(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNtextureHandle *textures)
{
    pfnc_nvnCommandBufferBindTextures(cmdBuf, stage, first, count, textures);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindTexturesDeferred(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, const NVNtextureHandle *textures)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindTexturesDeferred_fastpath(cmdBuf, stage, first, count, textures);
#else
    pfnc_nvnCommandBufferBindTexturesDeferred(cmdBuf, stage, first, count, textures);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindImage(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNimageHandle image)
{
    pfnc_nvnCommandBufferBindImage(cmdBuf, stage, index, image);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindImages(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNimageHandle *images)
{
    pfnc_nvnCommandBufferBindImages(cmdBuf, stage, first, count, images);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindImagesDeferred(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, const NVNimageHandle *images)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindImagesDeferred_fastpath(cmdBuf, stage, first, count, images);
#else
    pfnc_nvnCommandBufferBindImagesDeferred(cmdBuf, stage, first, count, images);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetPatchSize(NVNcommandBuffer *cmdBuf, int size)
{
    pfnc_nvnCommandBufferSetPatchSize(cmdBuf, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetInnerTessellationLevels(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const float *levels)
{
    pfnc_nvnCommandBufferSetInnerTessellationLevels(cmdBuf, levels);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetOuterTessellationLevels(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const float *levels)
{
    pfnc_nvnCommandBufferSetOuterTessellationLevels(cmdBuf, levels);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetPrimitiveRestart(NVNcommandBuffer *cmdBuf, NVNboolean enable, int index)
{
    pfnc_nvnCommandBufferSetPrimitiveRestart(cmdBuf, enable, index);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBeginTransformFeedback(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferBeginTransformFeedback(cmdBuf, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferEndTransformFeedback(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferEndTransformFeedback(cmdBuf, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferPauseTransformFeedback(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferPauseTransformFeedback(cmdBuf, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferResumeTransformFeedback(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferResumeTransformFeedback(cmdBuf, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawTransformFeedback(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferDrawTransformFeedback(cmdBuf, mode, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawArrays(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, int first, int count)
{
    pfnc_nvnCommandBufferDrawArrays(cmdBuf, mode, first, count);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawElements(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferDrawElements_fastpath(cmdBuf, mode, type, count, indexBuffer);
#else
    pfnc_nvnCommandBufferDrawElements(cmdBuf, mode, type, count, indexBuffer);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawElementsBaseVertex(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer, int baseVertex)
{
    pfnc_nvnCommandBufferDrawElementsBaseVertex(cmdBuf, mode, type, count, indexBuffer, baseVertex);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawArraysInstanced(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, int first, int count, int baseInstance, int instanceCount)
{
    pfnc_nvnCommandBufferDrawArraysInstanced(cmdBuf, mode, first, count, baseInstance, instanceCount);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawElementsInstanced(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer, int baseVertex, int baseInstance, int instanceCount)
{
    pfnc_nvnCommandBufferDrawElementsInstanced(cmdBuf, mode, type, count, indexBuffer, baseVertex, baseInstance, instanceCount);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawArraysIndirect(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress indirectBuffer)
{
    pfnc_nvnCommandBufferDrawArraysIndirect(cmdBuf, mode, indirectBuffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawElementsIndirect(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress indexBuffer, NVNbufferAddress indirectBuffer)
{
    pfnc_nvnCommandBufferDrawElementsIndirect(cmdBuf, mode, type, indexBuffer, indirectBuffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferMultiDrawArraysIndirectCount(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress indirectBuffer, NVNbufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride)
{
    pfnc_nvnCommandBufferMultiDrawArraysIndirectCount(cmdBuf, mode, indirectBuffer, parameterBuffer, maxDrawCount, stride);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferMultiDrawElementsIndirectCount(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress indexBuffer, NVNbufferAddress indirectBuffer, NVNbufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride)
{
    pfnc_nvnCommandBufferMultiDrawElementsIndirectCount(cmdBuf, mode, type, indexBuffer, indirectBuffer, parameterBuffer, maxDrawCount, stride);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearColor(NVNcommandBuffer *cmdBuf, int index, NVN_NOESCAPE const float *color, int mask)
{
    pfnc_nvnCommandBufferClearColor(cmdBuf, index, color, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearColori(NVNcommandBuffer *cmdBuf, int index, NVN_NOESCAPE const int *color, int mask)
{
    pfnc_nvnCommandBufferClearColori(cmdBuf, index, color, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearColorui(NVNcommandBuffer *cmdBuf, int index, NVN_NOESCAPE const uint32_t *color, int mask)
{
    pfnc_nvnCommandBufferClearColorui(cmdBuf, index, color, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearDepthStencil(NVNcommandBuffer *cmdBuf, float depthValue, NVNboolean depthMask, int stencilValue, int stencilMask)
{
    pfnc_nvnCommandBufferClearDepthStencil(cmdBuf, depthValue, depthMask, stencilValue, stencilMask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDispatchCompute(NVNcommandBuffer *cmdBuf, int groupsX, int groupsY, int groupsZ)
{
    pfnc_nvnCommandBufferDispatchCompute(cmdBuf, groupsX, groupsY, groupsZ);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDispatchComputeIndirect(NVNcommandBuffer *cmdBuf, NVNbufferAddress indirectBuffer)
{
    pfnc_nvnCommandBufferDispatchComputeIndirect(cmdBuf, indirectBuffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetViewport(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h)
{
    pfnc_nvnCommandBufferSetViewport(cmdBuf, x, y, w, h);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetViewports(NVNcommandBuffer *cmdBuf, int first, int count, NVN_NOESCAPE const float *ranges)
{
    pfnc_nvnCommandBufferSetViewports(cmdBuf, first, count, ranges);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetViewportSwizzles(NVNcommandBuffer *cmdBuf, int first, int count, NVN_NOESCAPE const NVNviewportSwizzle *swizzles)
{
    pfnc_nvnCommandBufferSetViewportSwizzles(cmdBuf, first, count, swizzles);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetScissor(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h)
{
    pfnc_nvnCommandBufferSetScissor(cmdBuf, x, y, w, h);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetScissors(NVNcommandBuffer *cmdBuf, int first, int count, NVN_NOESCAPE const int *rects)
{
    pfnc_nvnCommandBufferSetScissors(cmdBuf, first, count, rects);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetDepthRange(NVNcommandBuffer *cmdBuf, float n, float f)
{
    pfnc_nvnCommandBufferSetDepthRange(cmdBuf, n, f);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetDepthBounds(NVNcommandBuffer *cmdBuf, NVNboolean enable, float n, float f)
{
    pfnc_nvnCommandBufferSetDepthBounds(cmdBuf, enable, n, f);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetDepthRanges(NVNcommandBuffer *cmdBuf, int first, int count, NVN_NOESCAPE const float *ranges)
{
    pfnc_nvnCommandBufferSetDepthRanges(cmdBuf, first, count, ranges);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetTiledCacheAction(NVNcommandBuffer *cmdBuf, NVNtiledCacheAction action)
{
    pfnc_nvnCommandBufferSetTiledCacheAction(cmdBuf, action);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetTiledCacheTileSize(NVNcommandBuffer *cmdBuf, int tileWidth, int tileHeight)
{
    pfnc_nvnCommandBufferSetTiledCacheTileSize(cmdBuf, tileWidth, tileHeight);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateTexture(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNseparateTextureHandle textureHandle)
{
    pfnc_nvnCommandBufferBindSeparateTexture(cmdBuf, stage, index, textureHandle);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateSampler(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNseparateSamplerHandle samplerHandle)
{
    pfnc_nvnCommandBufferBindSeparateSampler(cmdBuf, stage, index, samplerHandle);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateTextures(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNseparateTextureHandle *textureHandles)
{
    pfnc_nvnCommandBufferBindSeparateTextures(cmdBuf, stage, first, count, textureHandles);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateSamplers(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, NVN_NOESCAPE const NVNseparateSamplerHandle *samplerHandles)
{
    pfnc_nvnCommandBufferBindSeparateSamplers(cmdBuf, stage, first, count, samplerHandles);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateTexturesDeferred(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, const NVNseparateTextureHandle *textureHandles)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindSeparateTexturesDeferred_fastpath(cmdBuf, stage, first, count, textureHandles);
#else
    pfnc_nvnCommandBufferBindSeparateTexturesDeferred(cmdBuf, stage, first, count, textureHandles);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindSeparateSamplersDeferred(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int first, int count, const NVNseparateSamplerHandle *samplerHandles)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferBindSeparateSamplersDeferred_fastpath(cmdBuf, stage, first, count, samplerHandles);
#else
    pfnc_nvnCommandBufferBindSeparateSamplersDeferred(cmdBuf, stage, first, count, samplerHandles);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetStencilValueMask(NVNcommandBuffer *cmdBuf, NVNface faces, int mask)
{
    pfnc_nvnCommandBufferSetStencilValueMask(cmdBuf, faces, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetStencilMask(NVNcommandBuffer *cmdBuf, NVNface faces, int mask)
{
    pfnc_nvnCommandBufferSetStencilMask(cmdBuf, faces, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetStencilRef(NVNcommandBuffer *cmdBuf, NVNface faces, int ref)
{
    pfnc_nvnCommandBufferSetStencilRef(cmdBuf, faces, ref);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetBlendColor(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const float *blendColor)
{
    pfnc_nvnCommandBufferSetBlendColor(cmdBuf, blendColor);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetPointSize(NVNcommandBuffer *cmdBuf, float pointSize)
{
    pfnc_nvnCommandBufferSetPointSize(cmdBuf, pointSize);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetLineWidth(NVNcommandBuffer *cmdBuf, float lineWidth)
{
    pfnc_nvnCommandBufferSetLineWidth(cmdBuf, lineWidth);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetPolygonOffsetClamp(NVNcommandBuffer *cmdBuf, float factor, float units, float clamp)
{
    pfnc_nvnCommandBufferSetPolygonOffsetClamp(cmdBuf, factor, units, clamp);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetAlphaRef(NVNcommandBuffer *cmdBuf, float ref)
{
    pfnc_nvnCommandBufferSetAlphaRef(cmdBuf, ref);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetSampleMask(NVNcommandBuffer *cmdBuf, int mask)
{
    pfnc_nvnCommandBufferSetSampleMask(cmdBuf, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetRasterizerDiscard(NVNcommandBuffer *cmdBuf, NVNboolean discard)
{
    pfnc_nvnCommandBufferSetRasterizerDiscard(cmdBuf, discard);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetDepthClamp(NVNcommandBuffer *cmdBuf, NVNboolean clamp)
{
    pfnc_nvnCommandBufferSetDepthClamp(cmdBuf, clamp);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetConservativeRasterEnable(NVNcommandBuffer *cmdBuf, NVNboolean enable)
{
    pfnc_nvnCommandBufferSetConservativeRasterEnable(cmdBuf, enable);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetConservativeRasterDilate(NVNcommandBuffer *cmdBuf, float dilate)
{
    pfnc_nvnCommandBufferSetConservativeRasterDilate(cmdBuf, dilate);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetSubpixelPrecisionBias(NVNcommandBuffer *cmdBuf, int xBits, int yBits)
{
    pfnc_nvnCommandBufferSetSubpixelPrecisionBias(cmdBuf, xBits, yBits);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCopyBufferToTexture(NVNcommandBuffer *cmdBuf, NVNbufferAddress src, const NVNtexture *dstTexture, NVN_NOESCAPE const NVNtextureView *dstView, NVN_NOESCAPE const NVNcopyRegion *dstRegion, int flags)
{
    pfnc_nvnCommandBufferCopyBufferToTexture(cmdBuf, src, dstTexture, dstView, dstRegion, flags);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCopyTextureToBuffer(NVNcommandBuffer *cmdBuf, const NVNtexture *srcTexture, NVN_NOESCAPE const NVNtextureView *srcView, NVN_NOESCAPE const NVNcopyRegion *srcRegion, NVNbufferAddress dst, int flags)
{
    pfnc_nvnCommandBufferCopyTextureToBuffer(cmdBuf, srcTexture, srcView, srcRegion, dst, flags);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCopyTextureToTexture(NVNcommandBuffer *cmdBuf, const NVNtexture *srcTexture, NVN_NOESCAPE const NVNtextureView *srcView, NVN_NOESCAPE const NVNcopyRegion *srcRegion, const NVNtexture *dstTexture, NVN_NOESCAPE const NVNtextureView *dstView, NVN_NOESCAPE const NVNcopyRegion *dstRegion, int flags)
{
    pfnc_nvnCommandBufferCopyTextureToTexture(cmdBuf, srcTexture, srcView, srcRegion, dstTexture, dstView, dstRegion, flags);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferCopyBufferToBuffer(NVNcommandBuffer *cmdBuf, NVNbufferAddress src, NVNbufferAddress dst, size_t size, int flags)
{
    pfnc_nvnCommandBufferCopyBufferToBuffer(cmdBuf, src, dst, size, flags);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearBuffer(NVNcommandBuffer *cmdBuf, NVNbufferAddress dst, size_t size, uint32_t value)
{
    pfnc_nvnCommandBufferClearBuffer(cmdBuf, dst, size, value);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearTexture(NVNcommandBuffer *cmdBuf, const NVNtexture *dstTexture, NVN_NOESCAPE const NVNtextureView *dstView, NVN_NOESCAPE const NVNcopyRegion *dstRegion, NVN_NOESCAPE const float *color, int mask)
{
    pfnc_nvnCommandBufferClearTexture(cmdBuf, dstTexture, dstView, dstRegion, color, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearTexturei(NVNcommandBuffer *cmdBuf, const NVNtexture *dstTexture, NVN_NOESCAPE const NVNtextureView *dstView, NVN_NOESCAPE const NVNcopyRegion *dstRegion, NVN_NOESCAPE const int *color, int mask)
{
    pfnc_nvnCommandBufferClearTexturei(cmdBuf, dstTexture, dstView, dstRegion, color, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferClearTextureui(NVNcommandBuffer *cmdBuf, const NVNtexture *dstTexture, NVN_NOESCAPE const NVNtextureView *dstView, NVN_NOESCAPE const NVNcopyRegion *dstRegion, NVN_NOESCAPE const uint32_t *color, int mask)
{
    pfnc_nvnCommandBufferClearTextureui(cmdBuf, dstTexture, dstView, dstRegion, color, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferUpdateUniformBuffer(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer, size_t bufferSize, ptrdiff_t updateOffset, size_t updateSize, NVN_NOESCAPE const void *data)
{
#ifdef NVN_FORCE_FASTPATH
    nvnCommandBufferUpdateUniformBuffer_fastpath(cmdBuf, buffer, bufferSize, updateOffset, updateSize, data);
#else
    pfnc_nvnCommandBufferUpdateUniformBuffer(cmdBuf, buffer, bufferSize, updateOffset, updateSize, data);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferReportCounter(NVNcommandBuffer *cmdBuf, NVNcounterType counter, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferReportCounter(cmdBuf, counter, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferResetCounter(NVNcommandBuffer *cmdBuf, NVNcounterType counter)
{
    pfnc_nvnCommandBufferResetCounter(cmdBuf, counter);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferReportValue(NVNcommandBuffer *cmdBuf, uint32_t value, NVNbufferAddress buffer)
{
    pfnc_nvnCommandBufferReportValue(cmdBuf, value, buffer);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetRenderEnable(NVNcommandBuffer *cmdBuf, NVNboolean enable)
{
    pfnc_nvnCommandBufferSetRenderEnable(cmdBuf, enable);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetRenderEnableConditional(NVNcommandBuffer *cmdBuf, NVNconditionalRenderMode mode, NVNbufferAddress counters)
{
    pfnc_nvnCommandBufferSetRenderEnableConditional(cmdBuf, mode, counters);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetRenderTargets(NVNcommandBuffer *cmdBuf, int numColors, NVN_NOESCAPE const NVNtexture * const *colors, NVN_NOESCAPE const NVNtextureView * const *colorViews, const NVNtexture *depthStencil, NVN_NOESCAPE const NVNtextureView *depthStencilView)
{
    pfnc_nvnCommandBufferSetRenderTargets(cmdBuf, numColors, colors, colorViews, depthStencil, depthStencilView);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDiscardColor(NVNcommandBuffer *cmdBuf, int index)
{
    pfnc_nvnCommandBufferDiscardColor(cmdBuf, index);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDiscardDepthStencil(NVNcommandBuffer *cmdBuf)
{
    pfnc_nvnCommandBufferDiscardDepthStencil(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDownsample(NVNcommandBuffer *cmdBuf, const NVNtexture *src, const NVNtexture *dst)
{
    pfnc_nvnCommandBufferDownsample(cmdBuf, src, dst);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferTiledDownsample(NVNcommandBuffer *cmdBuf, const NVNtexture *src, const NVNtexture *dst)
{
    pfnc_nvnCommandBufferTiledDownsample(cmdBuf, src, dst);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDownsampleTextureView(NVNcommandBuffer *cmdBuf, const NVNtexture *src, NVN_NOESCAPE const NVNtextureView *srcView, const NVNtexture *dst, NVN_NOESCAPE const NVNtextureView *dstView)
{
    pfnc_nvnCommandBufferDownsampleTextureView(cmdBuf, src, srcView, dst, dstView);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferTiledDownsampleTextureView(NVNcommandBuffer *cmdBuf, const NVNtexture *src, NVN_NOESCAPE const NVNtextureView *srcView, const NVNtexture *dst, NVN_NOESCAPE const NVNtextureView *dstView)
{
    pfnc_nvnCommandBufferTiledDownsampleTextureView(cmdBuf, src, srcView, dst, dstView);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBarrier(NVNcommandBuffer *cmdBuf, int barrier)
{
    pfnc_nvnCommandBufferBarrier(cmdBuf, barrier);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferWaitSync(NVNcommandBuffer *cmdBuf, const NVNsync *sync)
{
    pfnc_nvnCommandBufferWaitSync(cmdBuf, sync);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferFenceSync(NVNcommandBuffer *cmdBuf, NVNsync *sync, NVNsyncCondition condition, int flags)
{
    pfnc_nvnCommandBufferFenceSync(cmdBuf, sync, condition, flags);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetTexturePool(NVNcommandBuffer *cmdBuf, const NVNtexturePool *texturePool)
{
    pfnc_nvnCommandBufferSetTexturePool(cmdBuf, texturePool);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetSamplerPool(NVNcommandBuffer *cmdBuf, const NVNsamplerPool *samplerPool)
{
    pfnc_nvnCommandBufferSetSamplerPool(cmdBuf, samplerPool);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetShaderScratchMemory(NVNcommandBuffer *cmdBuf, const NVNmemoryPool *pool, ptrdiff_t offset, size_t size)
{
    pfnc_nvnCommandBufferSetShaderScratchMemory(cmdBuf, pool, offset, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSaveZCullData(NVNcommandBuffer *cmdBuf, NVNbufferAddress dst, size_t size)
{
    pfnc_nvnCommandBufferSaveZCullData(cmdBuf, dst, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferRestoreZCullData(NVNcommandBuffer *cmdBuf, NVNbufferAddress src, size_t size)
{
    pfnc_nvnCommandBufferRestoreZCullData(cmdBuf, src, size);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetCopyRowStride(NVNcommandBuffer *cmdBuf, ptrdiff_t stride)
{
    pfnc_nvnCommandBufferSetCopyRowStride(cmdBuf, stride);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetCopyImageStride(NVNcommandBuffer *cmdBuf, ptrdiff_t stride)
{
    pfnc_nvnCommandBufferSetCopyImageStride(cmdBuf, stride);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnCommandBufferGetCopyRowStride(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetCopyRowStride(cmdBuf);
}

static NVNINLINE ptrdiff_t NVNAPIENTRY nvnCommandBufferGetCopyImageStride(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetCopyImageStride(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferDrawTexture(NVNcommandBuffer *cmdBuf, NVNtextureHandle texture, NVN_NOESCAPE const NVNdrawTextureRegion *dstRegion, NVN_NOESCAPE const NVNdrawTextureRegion *srcRegion)
{
    pfnc_nvnCommandBufferDrawTexture(cmdBuf, texture, dstRegion, srcRegion);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnProgramSetSubroutineLinkage(NVNprogram *program, int count, const NVNsubroutineLinkageMapPtr *linkageMapPtrs)
{
    return pfnc_nvnProgramSetSubroutineLinkage(program, count, linkageMapPtrs);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetProgramSubroutines(NVNcommandBuffer *cmdBuf, NVNprogram *program, NVNshaderStage stage, const int first, const int count, NVN_NOESCAPE const int *values)
{
    pfnc_nvnCommandBufferSetProgramSubroutines(cmdBuf, program, stage, first, count, values);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferBindCoverageModulationTable(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const float *entries)
{
    pfnc_nvnCommandBufferBindCoverageModulationTable(cmdBuf, entries);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferResolveDepthBuffer(NVNcommandBuffer *cmdBuf)
{
    pfnc_nvnCommandBufferResolveDepthBuffer(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetColorReductionEnable(NVNcommandBuffer *cmdBuf, NVNboolean enable)
{
    pfnc_nvnCommandBufferSetColorReductionEnable(cmdBuf, enable);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetColorReductionThresholds(NVNcommandBuffer *cmdBuf, NVNformatClass formatClass, int thresholdConservative, int thresholdAggressive)
{
    pfnc_nvnCommandBufferSetColorReductionThresholds(cmdBuf, formatClass, thresholdConservative, thresholdAggressive);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferPushDebugGroupStatic(NVNcommandBuffer *cmdBuf, uint32_t domainId, const char * description)
{
    pfnc_nvnCommandBufferPushDebugGroupStatic(cmdBuf, domainId, description);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferPushDebugGroupDynamic(NVNcommandBuffer *cmdBuf, uint32_t domainId, NVN_NOESCAPE const char * description)
{
    pfnc_nvnCommandBufferPushDebugGroupDynamic(cmdBuf, domainId, description);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferPushDebugGroup(NVNcommandBuffer *cmdBuf, const char * description)
{
    pfnc_nvnCommandBufferPushDebugGroup(cmdBuf, description);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferPopDebugGroup(NVNcommandBuffer *cmdBuf)
{
    pfnc_nvnCommandBufferPopDebugGroup(cmdBuf);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferPopDebugGroupId(NVNcommandBuffer *cmdBuf, uint32_t domainId)
{
    pfnc_nvnCommandBufferPopDebugGroupId(cmdBuf, domainId);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferInsertDebugMarkerStatic(NVNcommandBuffer *cmdBuf, uint32_t domainId, const char * description)
{
    pfnc_nvnCommandBufferInsertDebugMarkerStatic(cmdBuf, domainId, description);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferInsertDebugMarkerDynamic(NVNcommandBuffer *cmdBuf, uint32_t domainId, NVN_NOESCAPE const char * description)
{
    pfnc_nvnCommandBufferInsertDebugMarkerDynamic(cmdBuf, domainId, description);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferInsertDebugMarker(NVNcommandBuffer *cmdBuf, const char * description)
{
    pfnc_nvnCommandBufferInsertDebugMarker(cmdBuf, description);
}

static NVNINLINE PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC NVNAPIENTRY nvnCommandBufferGetMemoryCallback(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetMemoryCallback(cmdBuf);
}

static NVNINLINE void * NVNAPIENTRY nvnCommandBufferGetMemoryCallbackData(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferGetMemoryCallbackData(cmdBuf);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnCommandBufferIsRecording(const NVNcommandBuffer *cmdBuf)
{
    return pfnc_nvnCommandBufferIsRecording(cmdBuf);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnSyncInitialize(NVNsync *sync, NVNdevice *device)
{
    return pfnc_nvnSyncInitialize(sync, device);
}

static NVNINLINE void NVNAPIENTRY nvnSyncFinalize(NVNsync *sync)
{
    pfnc_nvnSyncFinalize(sync);
}

static NVNINLINE void NVNAPIENTRY nvnSyncSetDebugLabel(NVNsync *sync, const char * label)
{
    pfnc_nvnSyncSetDebugLabel(sync, label);
}

static NVNINLINE void NVNAPIENTRY nvnQueueFenceSync(NVNqueue *queue, NVNsync *sync, NVNsyncCondition condition, int flags)
{
    pfnc_nvnQueueFenceSync(queue, sync, condition, flags);
}

static NVNINLINE NVNsyncWaitResult NVNAPIENTRY nvnSyncWait(const NVNsync *sync, uint64_t timeoutNs)
{
    return pfnc_nvnSyncWait(sync, timeoutNs);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnQueueWaitSync(NVNqueue *queue, const NVNsync *sync)
{
    return pfnc_nvnQueueWaitSync(queue, sync);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnSyncInitializeFromFencedGLSync(NVNsync *sync, NVNdevice *device, const void *glSync, NVNsyncInteropStatus *status)
{
    return pfnc_nvnSyncInitializeFromFencedGLSync(sync, device, glSync, status);
}

static NVNINLINE NVNsyncInteropStatus NVNAPIENTRY nvnSyncCreateGLSync(const NVNsync *sync, uint64_t *glSync)
{
    return pfnc_nvnSyncCreateGLSync(sync, glSync);
}

static NVNINLINE void NVNAPIENTRY nvnEventBuilderSetDefaults(NVNeventBuilder *builder)
{
    pfnc_nvnEventBuilderSetDefaults(builder);
}

static NVNINLINE void NVNAPIENTRY nvnEventBuilderSetStorage(NVNeventBuilder *builder, const NVNmemoryPool *pool, int64_t offset)
{
    pfnc_nvnEventBuilderSetStorage(builder, pool, offset);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnEventBuilderGetStorage(const NVNeventBuilder *builder, int64_t *offset)
{
    return pfnc_nvnEventBuilderGetStorage(builder, offset);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnEventBuilderGetMemoryPool(const NVNeventBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnEventBuilderGetMemoryPool_fastpath(builder);
#else
    return pfnc_nvnEventBuilderGetMemoryPool(builder);
#endif
}

static NVNINLINE int64_t NVNAPIENTRY nvnEventBuilderGetMemoryOffset(const NVNeventBuilder *builder)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnEventBuilderGetMemoryOffset_fastpath(builder);
#else
    return pfnc_nvnEventBuilderGetMemoryOffset(builder);
#endif
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnEventInitialize(NVNevent *event, const NVNeventBuilder *builder)
{
    return pfnc_nvnEventInitialize(event, builder);
}

static NVNINLINE void NVNAPIENTRY nvnEventFinalize(NVNevent *event)
{
    pfnc_nvnEventFinalize(event);
}

static NVNINLINE uint32_t NVNAPIENTRY nvnEventGetValue(const NVNevent *event)
{
    return pfnc_nvnEventGetValue(event);
}

static NVNINLINE void NVNAPIENTRY nvnEventSignal(NVNevent *event, NVNeventSignalMode mode, uint32_t value)
{
    pfnc_nvnEventSignal(event, mode, value);
}

static NVNINLINE const NVNmemoryPool * NVNAPIENTRY nvnEventGetMemoryPool(const NVNevent *event)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnEventGetMemoryPool_fastpath(event);
#else
    return pfnc_nvnEventGetMemoryPool(event);
#endif
}

static NVNINLINE int64_t NVNAPIENTRY nvnEventGetMemoryOffset(const NVNevent *event)
{
#ifdef NVN_FORCE_FASTPATH
    return nvnEventGetMemoryOffset_fastpath(event);
#else
    return pfnc_nvnEventGetMemoryOffset(event);
#endif
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferWaitEvent(NVNcommandBuffer *cmdBuf, const NVNevent *event, NVNeventWaitMode waitMode, uint32_t value)
{
    pfnc_nvnCommandBufferWaitEvent(cmdBuf, event, waitMode, value);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSignalEvent(NVNcommandBuffer *cmdBuf, const NVNevent *event, NVNeventSignalMode mode, NVNeventSignalLocation location, int flags, uint32_t value)
{
    pfnc_nvnCommandBufferSignalEvent(cmdBuf, event, mode, location, flags, value);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetStencilCullCriteria(NVNcommandBuffer *cmdBuf, NVNstencilFunc func, int ref, int mask)
{
    pfnc_nvnCommandBufferSetStencilCullCriteria(cmdBuf, func, ref, mask);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferOverrideSubtileSize(NVNcommandBuffer *cmdBuf, NVNboolean override, int subtileSize)
{
    pfnc_nvnCommandBufferOverrideSubtileSize(cmdBuf, override, subtileSize);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnCommandBufferInsertCheckpointStatic(NVNcommandBuffer *cmdBuf, const void *markerData, size_t markerDataSize)
{
    return pfnc_nvnCommandBufferInsertCheckpointStatic(cmdBuf, markerData, markerDataSize);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnCommandBufferInsertCheckpointDynamic(NVNcommandBuffer *cmdBuf, NVN_NOESCAPE const void *markerData, size_t markerDataSize)
{
    return pfnc_nvnCommandBufferInsertCheckpointDynamic(cmdBuf, markerData, markerDataSize);
}

static NVNINLINE void NVNAPIENTRY nvnCommandBufferSetZCullZF32CompressionEnable(NVNcommandBuffer *cmdBuf, NVNboolean enable)
{
    pfnc_nvnCommandBufferSetZCullZF32CompressionEnable(cmdBuf, enable);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceSetAutomaticCheckpointsEnable(NVNdevice *device, NVNboolean enable)
{
    return pfnc_nvnDeviceSetAutomaticCheckpointsEnable(device, enable);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceSetAutomaticCheckpointsMask(NVNdevice *device, int mask)
{
    return pfnc_nvnDeviceSetAutomaticCheckpointsMask(device, mask);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceSetAutomaticCheckpointsSamplingInterval(NVNdevice *device, int interval)
{
    return pfnc_nvnDeviceSetAutomaticCheckpointsSamplingInterval(device, interval);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceSetAutomaticCheckpointsByDebugGroup(NVNdevice *device, uint32_t domainId, const char * debugGroupName)
{
    return pfnc_nvnDeviceSetAutomaticCheckpointsByDebugGroup(device, domainId, debugGroupName);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceSetCheckpointCallStacksEnable(NVNdevice *device, NVNboolean enable)
{
    return pfnc_nvnDeviceSetCheckpointCallStacksEnable(device, enable);
}

static NVNINLINE NVNboolean NVNAPIENTRY nvnDeviceSetCheckpointMaxCallStacksDepth(NVNdevice *device, int depth)
{
    return pfnc_nvnDeviceSetCheckpointMaxCallStacksDepth(device, depth);
}


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __nvn_funcptrinline_h_
