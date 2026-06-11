
/*--------------------------------------------------------------------------------*
  Copyright (C)Nintendo All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/


/// \file nvn_CppMethods.h
///      Implementation of class methods in the NVN C++ interface.

#ifndef __nvn_cppmethods_h_
#define __nvn_cppmethods_h_

#include "nvn_Cpp.h"
#include "nvn_CppFuncPtr.h"
#include "nvn_CppFastpath.h"

namespace nvn {
#ifdef NVN_OVERLOAD_CPP_OBJECTS
namespace objects {
#endif

inline void DeviceBuilder::SetDefaults()
{
    pfncpp_nvnDeviceBuilderSetDefaults(this);
}

inline void DeviceBuilder::SetFlags(DeviceFlagBits flags)
{
    pfncpp_nvnDeviceBuilderSetFlags(this, flags);
}

inline DeviceFlagBits DeviceBuilder::GetFlags() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetFlags_fastpath();
#else
    return pfncpp_nvnDeviceBuilderGetFlags(this);
#endif
}

inline NVNboolean Device::Initialize(const DeviceBuilder *builder)
{
    return pfncpp_nvnDeviceInitialize(this, builder);
}

inline void Device::Finalize()
{
    pfncpp_nvnDeviceFinalize(this);
}

inline void Device::SetDebugLabel(const char * label)
{
    pfncpp_nvnDeviceSetDebugLabel(this, label);
}

inline GenericFuncPtrFunc Device::GetProcAddress(const char * name) const
{
    return pfncpp_nvnDeviceGetProcAddress(this, name);
}

inline void Device::GetInteger(DeviceInfo pname, int *v) const
{
    pfncpp_nvnDeviceGetInteger(this, pname, v);
}

inline uint64_t Device::GetCurrentTimestampInNanoseconds() const
{
    return pfncpp_nvnDeviceGetCurrentTimestampInNanoseconds(this);
}

inline void Device::SetIntermediateShaderCache(int numMaxEntries)
{
    pfncpp_nvnDeviceSetIntermediateShaderCache(this, numMaxEntries);
}

inline TextureHandle Device::GetTextureHandle(int textureID, int samplerID) const
{
    return pfncpp_nvnDeviceGetTextureHandle(this, textureID, samplerID);
}

inline TextureHandle Device::GetTexelFetchHandle(int textureID) const
{
    return pfncpp_nvnDeviceGetTexelFetchHandle(this, textureID);
}

inline ImageHandle Device::GetImageHandle(int imageID) const
{
    return pfncpp_nvnDeviceGetImageHandle(this, imageID);
}

inline void Device::InstallDebugCallback(const DebugCallbackFunc callback, void *callbackData, NVNboolean enable)
{
    pfncpp_nvnDeviceInstallDebugCallback(this, callback, callbackData, enable);
}

inline NVNdebugDomainId Device::GenerateDebugDomainId(const char * name) const
{
    return pfncpp_nvnDeviceGenerateDebugDomainId(this, name);
}

inline void Device::SetWindowOriginMode(WindowOriginMode windowOriginMode)
{
#ifdef NVN_FORCE_FASTPATH
    SetWindowOriginMode_fastpath(windowOriginMode);
#else
    pfncpp_nvnDeviceSetWindowOriginMode(this, windowOriginMode);
#endif
}

inline void Device::SetDepthMode(DepthMode depthMode)
{
#ifdef NVN_FORCE_FASTPATH
    SetDepthMode_fastpath(depthMode);
#else
    pfncpp_nvnDeviceSetDepthMode(this, depthMode);
#endif
}

inline NVNboolean Device::RegisterFastClearColor(const float *color, Format format)
{
    return pfncpp_nvnDeviceRegisterFastClearColor(this, color, format);
}

inline NVNboolean Device::RegisterFastClearColori(const int *color, Format format)
{
    return pfncpp_nvnDeviceRegisterFastClearColori(this, color, format);
}

inline NVNboolean Device::RegisterFastClearColorui(const uint32_t *color, Format format)
{
    return pfncpp_nvnDeviceRegisterFastClearColorui(this, color, format);
}

inline NVNboolean Device::RegisterFastClearDepth(float depth)
{
    return pfncpp_nvnDeviceRegisterFastClearDepth(this, depth);
}

inline WindowOriginMode Device::GetWindowOriginMode() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetWindowOriginMode_fastpath();
#else
    return pfncpp_nvnDeviceGetWindowOriginMode(this);
#endif
}

inline DepthMode Device::GetDepthMode() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDepthMode_fastpath();
#else
    return pfncpp_nvnDeviceGetDepthMode(this);
#endif
}

inline uint64_t Device::GetTimestampInNanoseconds(const CounterData *counterData) const
{
    return pfncpp_nvnDeviceGetTimestampInNanoseconds(this, counterData);
}

inline void Device::FinalizeCommandHandle(CommandHandle handles)
{
    pfncpp_nvnDeviceFinalizeCommandHandle(this, handles);
}

inline void Device::WalkDebugDatabase(DebugObjectType type, WalkDebugDatabaseCallbackFunc callback, void *userParam) const
{
    pfncpp_nvnDeviceWalkDebugDatabase(this, type, callback, userParam);
}

inline SeparateTextureHandle Device::GetSeparateTextureHandle(int textureID) const
{
    return pfncpp_nvnDeviceGetSeparateTextureHandle(this, textureID);
}

inline SeparateTextureHandle Device::getSeparateTextureHandle(int textureID) const
{
    return pfncpp_nvnDeviceGetSeparateTextureHandle(this, textureID);
}

inline SeparateSamplerHandle Device::GetSeparateSamplerHandle(int samplerID) const
{
    return pfncpp_nvnDeviceGetSeparateSamplerHandle(this, samplerID);
}

inline SeparateSamplerHandle Device::getSeparateSamplerHandle(int samplerID) const
{
    return pfncpp_nvnDeviceGetSeparateSamplerHandle(this, samplerID);
}

inline NVNboolean Device::IsExternalDebuggerAttached() const
{
    return pfncpp_nvnDeviceIsExternalDebuggerAttached(this);
}

inline QueueGetErrorResult Queue::GetError(QueueErrorInfo *errorInfo)
{
    return pfncpp_nvnQueueGetError(this, errorInfo);
}

inline size_t Queue::GetTotalCommandMemoryUsed()
{
    return pfncpp_nvnQueueGetTotalCommandMemoryUsed(this);
}

inline size_t Queue::GetTotalControlMemoryUsed()
{
    return pfncpp_nvnQueueGetTotalControlMemoryUsed(this);
}

inline size_t Queue::GetTotalComputeMemoryUsed()
{
    return pfncpp_nvnQueueGetTotalComputeMemoryUsed(this);
}

inline void Queue::ResetMemoryUsageCounts()
{
    pfncpp_nvnQueueResetMemoryUsageCounts(this);
}

inline QueueBuilder & QueueBuilder::SetDevice(Device *device)
{
    pfncpp_nvnQueueBuilderSetDevice(this, device);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetDefaults()
{
    pfncpp_nvnQueueBuilderSetDefaults(this);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetFlags(QueueFlags flags)
{
    pfncpp_nvnQueueBuilderSetFlags(this, flags);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetCommandMemorySize(size_t size)
{
    pfncpp_nvnQueueBuilderSetCommandMemorySize(this, size);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetComputeMemorySize(size_t size)
{
    pfncpp_nvnQueueBuilderSetComputeMemorySize(this, size);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetControlMemorySize(size_t size)
{
    pfncpp_nvnQueueBuilderSetControlMemorySize(this, size);
    return *this;
}

inline size_t QueueBuilder::GetQueueMemorySize() const
{
    return pfncpp_nvnQueueBuilderGetQueueMemorySize(this);
}

inline QueueBuilder & QueueBuilder::SetQueueMemory(void *memory, size_t size)
{
    pfncpp_nvnQueueBuilderSetQueueMemory(this, memory, size);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetCommandFlushThreshold(size_t threshold)
{
    pfncpp_nvnQueueBuilderSetCommandFlushThreshold(this, threshold);
    return *this;
}

inline QueueBuilder & QueueBuilder::SetQueuePriority(const QueuePriority priority)
{
#ifdef NVN_FORCE_FASTPATH
    return SetQueuePriority_fastpath(priority);
#else
    pfncpp_nvnQueueBuilderSetQueuePriority(this, priority);
    return *this;
#endif
}

inline QueuePriority QueueBuilder::GetQueuePriority() const
{
    return pfncpp_nvnQueueBuilderGetQueuePriority(this);
}

inline const Device * QueueBuilder::GetDevice() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDevice_fastpath();
#else
    return pfncpp_nvnQueueBuilderGetDevice(this);
#endif
}

inline int QueueBuilder::GetFlags() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetFlags_fastpath();
#else
    return pfncpp_nvnQueueBuilderGetFlags(this);
#endif
}

inline NVNboolean QueueBuilder::GetCommandMemorySize(int *size) const
{
    return pfncpp_nvnQueueBuilderGetCommandMemorySize(this, size);
}

inline NVNboolean QueueBuilder::GetComputeMemorySize(int *size) const
{
    return pfncpp_nvnQueueBuilderGetComputeMemorySize(this, size);
}

inline NVNboolean QueueBuilder::GetControlMemorySize(int *size) const
{
    return pfncpp_nvnQueueBuilderGetControlMemorySize(this, size);
}

inline NVNboolean QueueBuilder::GetCommandFlushThreshold(int *flushThreshold) const
{
    return pfncpp_nvnQueueBuilderGetCommandFlushThreshold(this, flushThreshold);
}

inline int QueueBuilder::GetMemorySize() const
{
    return pfncpp_nvnQueueBuilderGetMemorySize(this);
}

inline void * QueueBuilder::GetMemory() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemory_fastpath();
#else
    return pfncpp_nvnQueueBuilderGetMemory(this);
#endif
}

inline NVNboolean Queue::Initialize(const QueueBuilder *builder)
{
    return pfncpp_nvnQueueInitialize(this, builder);
}

inline void Queue::Finalize()
{
    pfncpp_nvnQueueFinalize(this);
}

inline void Queue::SetDebugLabel(const char * label)
{
    pfncpp_nvnQueueSetDebugLabel(this, label);
}

inline void Queue::SubmitCommands(int numCommands, const CommandHandle *handles)
{
    pfncpp_nvnQueueSubmitCommands(this, numCommands, handles);
}

inline void Queue::Flush()
{
    pfncpp_nvnQueueFlush(this);
}

inline void Queue::Finish()
{
    pfncpp_nvnQueueFinish(this);
}

inline void Queue::PresentTexture(Window *window, int textureIndex)
{
    pfncpp_nvnQueuePresentTexture(this, window, textureIndex);
}

inline WindowBuilder & WindowBuilder::SetDevice(Device *device)
{
    pfncpp_nvnWindowBuilderSetDevice(this, device);
    return *this;
}

inline WindowBuilder & WindowBuilder::SetDefaults()
{
    pfncpp_nvnWindowBuilderSetDefaults(this);
    return *this;
}

inline WindowBuilder & WindowBuilder::SetNativeWindow(NVNnativeWindow nativeWindow)
{
#ifdef NVN_FORCE_FASTPATH
    return SetNativeWindow_fastpath(nativeWindow);
#else
    pfncpp_nvnWindowBuilderSetNativeWindow(this, nativeWindow);
    return *this;
#endif
}

inline WindowBuilder & WindowBuilder::SetTextures(int numTextures, Texture * const *textures)
{
#ifdef NVN_FORCE_FASTPATH
    return SetTextures_fastpath(numTextures, textures);
#else
    pfncpp_nvnWindowBuilderSetTextures(this, numTextures, textures);
    return *this;
#endif
}

inline WindowBuilder & WindowBuilder::SetPresentInterval(int presentInterval)
{
    pfncpp_nvnWindowBuilderSetPresentInterval(this, presentInterval);
    return *this;
}

inline WindowBuilder & WindowBuilder::SetNumActiveTextures(int numActiveTextures)
{
#ifdef NVN_FORCE_FASTPATH
    return SetNumActiveTextures_fastpath(numActiveTextures);
#else
    pfncpp_nvnWindowBuilderSetNumActiveTextures(this, numActiveTextures);
    return *this;
#endif
}

inline const Device * WindowBuilder::GetDevice() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDevice_fastpath();
#else
    return pfncpp_nvnWindowBuilderGetDevice(this);
#endif
}

inline int WindowBuilder::GetNumTextures() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetNumTextures_fastpath();
#else
    return pfncpp_nvnWindowBuilderGetNumTextures(this);
#endif
}

inline const Texture * WindowBuilder::GetTexture(int textureId) const
{
    return pfncpp_nvnWindowBuilderGetTexture(this, textureId);
}

inline NVNnativeWindow WindowBuilder::GetNativeWindow() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetNativeWindow_fastpath();
#else
    return pfncpp_nvnWindowBuilderGetNativeWindow(this);
#endif
}

inline int WindowBuilder::GetPresentInterval() const
{
    return pfncpp_nvnWindowBuilderGetPresentInterval(this);
}

inline int WindowBuilder::GetNumActiveTextures() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetNumActiveTextures_fastpath();
#else
    return pfncpp_nvnWindowBuilderGetNumActiveTextures(this);
#endif
}

inline NVNboolean Window::Initialize(const WindowBuilder *builder)
{
    return pfncpp_nvnWindowInitialize(this, builder);
}

inline void Window::Finalize()
{
    pfncpp_nvnWindowFinalize(this);
}

inline void Window::SetDebugLabel(const char * label)
{
    pfncpp_nvnWindowSetDebugLabel(this, label);
}

inline WindowAcquireTextureResult Window::AcquireTexture(Sync *textureAvailableSync, int *textureIndex)
{
    return pfncpp_nvnWindowAcquireTexture(this, textureAvailableSync, textureIndex);
}

inline NVNnativeWindow Window::GetNativeWindow() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetNativeWindow_fastpath();
#else
    return pfncpp_nvnWindowGetNativeWindow(this);
#endif
}

inline int Window::GetPresentInterval() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetPresentInterval_fastpath();
#else
    return pfncpp_nvnWindowGetPresentInterval(this);
#endif
}

inline void Window::SetPresentInterval(int presentInterval)
{
    pfncpp_nvnWindowSetPresentInterval(this, presentInterval);
}

inline void Window::SetCrop(int x, int y, int w, int h)
{
    pfncpp_nvnWindowSetCrop(this, x, y, w, h);
}

inline void Window::GetCrop(Rectangle *crop) const
{
    pfncpp_nvnWindowGetCrop(this, crop);
}

inline void Window::SetNumActiveTextures(int numActiveTextures)
{
    pfncpp_nvnWindowSetNumActiveTextures(this, numActiveTextures);
}

inline int Window::GetNumActiveTextures() const
{
    return pfncpp_nvnWindowGetNumActiveTextures(this);
}

inline int Window::GetNumTextures() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetNumTextures_fastpath();
#else
    return pfncpp_nvnWindowGetNumTextures(this);
#endif
}

inline NVNboolean Program::Initialize(Device *device)
{
    return pfncpp_nvnProgramInitialize(this, device);
}

inline void Program::Finalize()
{
    pfncpp_nvnProgramFinalize(this);
}

inline void Program::SetDebugLabel(const char * label)
{
    pfncpp_nvnProgramSetDebugLabel(this, label);
}

inline NVNboolean Program::SetShaders(int count, const ShaderData *stageData)
{
    return pfncpp_nvnProgramSetShaders(this, count, stageData);
}

inline NVNboolean Program::SetShadersExt(int count, const ShaderDataExt *stageDataExt)
{
    return pfncpp_nvnProgramSetShadersExt(this, count, stageDataExt);
}

inline void Program::SetSampleShading(SampleShadingMode shadingMode)
{
    pfncpp_nvnProgramSetSampleShading(this, shadingMode);
}

inline int Program::GetSubtileSize() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSubtileSize_fastpath();
#else
    return pfncpp_nvnProgramGetSubtileSize(this);
#endif
}

inline MemoryPoolBuilder & MemoryPoolBuilder::SetDevice(Device *device)
{
    pfncpp_nvnMemoryPoolBuilderSetDevice(this, device);
    return *this;
}

inline MemoryPoolBuilder & MemoryPoolBuilder::SetDefaults()
{
    pfncpp_nvnMemoryPoolBuilderSetDefaults(this);
    return *this;
}

inline MemoryPoolBuilder & MemoryPoolBuilder::SetStorage(void *memory, size_t size)
{
    pfncpp_nvnMemoryPoolBuilderSetStorage(this, memory, size);
    return *this;
}

inline MemoryPoolBuilder & MemoryPoolBuilder::SetFlags(MemoryPoolFlags flags)
{
    pfncpp_nvnMemoryPoolBuilderSetFlags(this, flags);
    return *this;
}

inline const Device * MemoryPoolBuilder::GetDevice() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDevice_fastpath();
#else
    return pfncpp_nvnMemoryPoolBuilderGetDevice(this);
#endif
}

inline void * MemoryPoolBuilder::GetMemory() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemory_fastpath();
#else
    return pfncpp_nvnMemoryPoolBuilderGetMemory(this);
#endif
}

inline size_t MemoryPoolBuilder::GetSize() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSize_fastpath();
#else
    return pfncpp_nvnMemoryPoolBuilderGetSize(this);
#endif
}

inline MemoryPoolFlags MemoryPoolBuilder::GetFlags() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetFlags_fastpath();
#else
    return pfncpp_nvnMemoryPoolBuilderGetFlags(this);
#endif
}

inline NVNboolean MemoryPool::Initialize(const MemoryPoolBuilder *builder)
{
    return pfncpp_nvnMemoryPoolInitialize(this, builder);
}

inline void MemoryPool::SetDebugLabel(const char * label)
{
    pfncpp_nvnMemoryPoolSetDebugLabel(this, label);
}

inline void MemoryPool::Finalize()
{
    pfncpp_nvnMemoryPoolFinalize(this);
}

inline void * MemoryPool::Map() const
{
    return pfncpp_nvnMemoryPoolMap(this);
}

inline void MemoryPool::FlushMappedRange(ptrdiff_t offset, size_t size) const
{
    pfncpp_nvnMemoryPoolFlushMappedRange(this, offset, size);
}

inline void MemoryPool::InvalidateMappedRange(ptrdiff_t offset, size_t size) const
{
    pfncpp_nvnMemoryPoolInvalidateMappedRange(this, offset, size);
}

inline BufferAddress MemoryPool::GetBufferAddress() const
{
    return pfncpp_nvnMemoryPoolGetBufferAddress(this);
}

inline NVNboolean MemoryPool::MapVirtual(int numRequests, const MappingRequest *requests)
{
    return pfncpp_nvnMemoryPoolMapVirtual(this, numRequests, requests);
}

inline size_t MemoryPool::GetSize() const
{
    return pfncpp_nvnMemoryPoolGetSize(this);
}

inline MemoryPoolFlags MemoryPool::GetFlags() const
{
    return pfncpp_nvnMemoryPoolGetFlags(this);
}

inline NVNboolean TexturePool::Initialize(const MemoryPool *memoryPool, ptrdiff_t offset, int numDescriptors)
{
    return pfncpp_nvnTexturePoolInitialize(this, memoryPool, offset, numDescriptors);
}

inline void TexturePool::SetDebugLabel(const char * label)
{
    pfncpp_nvnTexturePoolSetDebugLabel(this, label);
}

inline void TexturePool::Finalize()
{
    pfncpp_nvnTexturePoolFinalize(this);
}

inline void TexturePool::RegisterTexture(int id, const Texture *texture, const TextureView *view) const
{
    pfncpp_nvnTexturePoolRegisterTexture(this, id, texture, view);
}

inline void TexturePool::RegisterImage(int id, const Texture *texture, const TextureView *view) const
{
    pfncpp_nvnTexturePoolRegisterImage(this, id, texture, view);
}

inline const MemoryPool * TexturePool::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnTexturePoolGetMemoryPool(this);
#endif
}

inline ptrdiff_t TexturePool::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnTexturePoolGetMemoryOffset(this);
#endif
}

inline int TexturePool::GetSize() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSize_fastpath();
#else
    return pfncpp_nvnTexturePoolGetSize(this);
#endif
}

inline NVNboolean SamplerPool::Initialize(const MemoryPool *memoryPool, ptrdiff_t offset, int numDescriptors)
{
    return pfncpp_nvnSamplerPoolInitialize(this, memoryPool, offset, numDescriptors);
}

inline void SamplerPool::SetDebugLabel(const char * label)
{
    pfncpp_nvnSamplerPoolSetDebugLabel(this, label);
}

inline void SamplerPool::Finalize()
{
    pfncpp_nvnSamplerPoolFinalize(this);
}

inline void SamplerPool::RegisterSampler(int id, const Sampler *sampler) const
{
    pfncpp_nvnSamplerPoolRegisterSampler(this, id, sampler);
}

inline void SamplerPool::RegisterSamplerBuilder(int id, const SamplerBuilder *builder) const
{
    pfncpp_nvnSamplerPoolRegisterSamplerBuilder(this, id, builder);
}

inline const MemoryPool * SamplerPool::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnSamplerPoolGetMemoryPool(this);
#endif
}

inline ptrdiff_t SamplerPool::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnSamplerPoolGetMemoryOffset(this);
#endif
}

inline int SamplerPool::GetSize() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSize_fastpath();
#else
    return pfncpp_nvnSamplerPoolGetSize(this);
#endif
}

inline BufferBuilder & BufferBuilder::SetDevice(Device *device)
{
    pfncpp_nvnBufferBuilderSetDevice(this, device);
    return *this;
}

inline BufferBuilder & BufferBuilder::SetDefaults()
{
    pfncpp_nvnBufferBuilderSetDefaults(this);
    return *this;
}

inline BufferBuilder & BufferBuilder::SetStorage(MemoryPool *pool, ptrdiff_t offset, size_t size)
{
#ifdef NVN_FORCE_FASTPATH
    return SetStorage_fastpath(pool, offset, size);
#else
    pfncpp_nvnBufferBuilderSetStorage(this, pool, offset, size);
    return *this;
#endif
}

inline const Device * BufferBuilder::GetDevice() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDevice_fastpath();
#else
    return pfncpp_nvnBufferBuilderGetDevice(this);
#endif
}

inline MemoryPool * BufferBuilder::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnBufferBuilderGetMemoryPool(this);
#endif
}

inline ptrdiff_t BufferBuilder::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnBufferBuilderGetMemoryOffset(this);
#endif
}

inline size_t BufferBuilder::GetSize() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSize_fastpath();
#else
    return pfncpp_nvnBufferBuilderGetSize(this);
#endif
}

inline NVNboolean Buffer::Initialize(const BufferBuilder *builder)
{
    return pfncpp_nvnBufferInitialize(this, builder);
}

inline void Buffer::SetDebugLabel(const char * label)
{
    pfncpp_nvnBufferSetDebugLabel(this, label);
}

inline void Buffer::Finalize()
{
    pfncpp_nvnBufferFinalize(this);
}

inline void * Buffer::Map() const
{
    return pfncpp_nvnBufferMap(this);
}

inline BufferAddress Buffer::GetAddress() const
{
    return pfncpp_nvnBufferGetAddress(this);
}

inline void Buffer::FlushMappedRange(ptrdiff_t offset, size_t size) const
{
    pfncpp_nvnBufferFlushMappedRange(this, offset, size);
}

inline void Buffer::InvalidateMappedRange(ptrdiff_t offset, size_t size) const
{
    pfncpp_nvnBufferInvalidateMappedRange(this, offset, size);
}

inline MemoryPool * Buffer::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnBufferGetMemoryPool(this);
#endif
}

inline ptrdiff_t Buffer::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnBufferGetMemoryOffset(this);
#endif
}

inline size_t Buffer::GetSize() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSize_fastpath();
#else
    return pfncpp_nvnBufferGetSize(this);
#endif
}

inline uint64_t Buffer::GetDebugID() const
{
    return pfncpp_nvnBufferGetDebugID(this);
}

inline TextureBuilder & TextureBuilder::SetDevice(Device *device)
{
    pfncpp_nvnTextureBuilderSetDevice(this, device);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetDefaults()
{
    pfncpp_nvnTextureBuilderSetDefaults(this);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetFlags(TextureFlags flags)
{
    pfncpp_nvnTextureBuilderSetFlags(this, flags);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetTarget(TextureTarget target)
{
#ifdef NVN_FORCE_FASTPATH
    return SetTarget_fastpath(target);
#else
    pfncpp_nvnTextureBuilderSetTarget(this, target);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetWidth(int width)
{
#ifdef NVN_FORCE_FASTPATH
    return SetWidth_fastpath(width);
#else
    pfncpp_nvnTextureBuilderSetWidth(this, width);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetHeight(int height)
{
#ifdef NVN_FORCE_FASTPATH
    return SetHeight_fastpath(height);
#else
    pfncpp_nvnTextureBuilderSetHeight(this, height);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetDepth(int depth)
{
#ifdef NVN_FORCE_FASTPATH
    return SetDepth_fastpath(depth);
#else
    pfncpp_nvnTextureBuilderSetDepth(this, depth);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetSize1D(int width)
{
    pfncpp_nvnTextureBuilderSetSize1D(this, width);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetSize2D(int width, int height)
{
    pfncpp_nvnTextureBuilderSetSize2D(this, width, height);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetSize3D(int width, int height, int depth)
{
#ifdef NVN_FORCE_FASTPATH
    return SetSize3D_fastpath(width, height, depth);
#else
    pfncpp_nvnTextureBuilderSetSize3D(this, width, height, depth);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetLevels(int numLevels)
{
#ifdef NVN_FORCE_FASTPATH
    return SetLevels_fastpath(numLevels);
#else
    pfncpp_nvnTextureBuilderSetLevels(this, numLevels);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetFormat(Format format)
{
#ifdef NVN_FORCE_FASTPATH
    return SetFormat_fastpath(format);
#else
    pfncpp_nvnTextureBuilderSetFormat(this, format);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetSamples(int samples)
{
#ifdef NVN_FORCE_FASTPATH
    return SetSamples_fastpath(samples);
#else
    pfncpp_nvnTextureBuilderSetSamples(this, samples);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b, TextureSwizzle a)
{
    pfncpp_nvnTextureBuilderSetSwizzle(this, r, g, b, a);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetDepthStencilMode(TextureDepthStencilMode mode)
{
#ifdef NVN_FORCE_FASTPATH
    return SetDepthStencilMode_fastpath(mode);
#else
    pfncpp_nvnTextureBuilderSetDepthStencilMode(this, mode);
    return *this;
#endif
}

inline size_t TextureBuilder::GetStorageSize() const
{
    return pfncpp_nvnTextureBuilderGetStorageSize(this);
}

inline size_t TextureBuilder::GetStorageAlignment() const
{
    return pfncpp_nvnTextureBuilderGetStorageAlignment(this);
}

inline ptrdiff_t TextureBuilder::GetViewOffset(const TextureView *textureView) const
{
    return pfncpp_nvnTextureBuilderGetViewOffset(this, textureView);
}

inline TextureBuilder & TextureBuilder::SetStorage(MemoryPool *pool, ptrdiff_t offset)
{
#ifdef NVN_FORCE_FASTPATH
    return SetStorage_fastpath(pool, offset);
#else
    pfncpp_nvnTextureBuilderSetStorage(this, pool, offset);
    return *this;
#endif
}

inline TextureBuilder & TextureBuilder::SetPackagedTextureData(const void *data)
{
    pfncpp_nvnTextureBuilderSetPackagedTextureData(this, data);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetPackagedTextureLayout(const PackagedTextureLayout *layout)
{
    pfncpp_nvnTextureBuilderSetPackagedTextureLayout(this, layout);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetStride(ptrdiff_t stride)
{
    pfncpp_nvnTextureBuilderSetStride(this, stride);
    return *this;
}

inline TextureBuilder & TextureBuilder::SetGLTextureName(uint32_t name)
{
    pfncpp_nvnTextureBuilderSetGLTextureName(this, name);
    return *this;
}

inline NVNstorageClass TextureBuilder::GetStorageClass() const
{
    return pfncpp_nvnTextureBuilderGetStorageClass(this);
}

inline const Device * TextureBuilder::GetDevice() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDevice_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetDevice(this);
#endif
}

inline TextureFlags TextureBuilder::GetFlags() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetFlags_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetFlags(this);
#endif
}

inline TextureTarget TextureBuilder::GetTarget() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetTarget_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetTarget(this);
#endif
}

inline int TextureBuilder::GetWidth() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetWidth_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetWidth(this);
#endif
}

inline int TextureBuilder::GetHeight() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetHeight_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetHeight(this);
#endif
}

inline int TextureBuilder::GetDepth() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDepth_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetDepth(this);
#endif
}

inline int TextureBuilder::GetLevels() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetLevels_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetLevels(this);
#endif
}

inline Format TextureBuilder::GetFormat() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetFormat_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetFormat(this);
#endif
}

inline int TextureBuilder::GetSamples() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSamples_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetSamples(this);
#endif
}

inline void TextureBuilder::GetSwizzle(TextureSwizzle *r, TextureSwizzle *g, TextureSwizzle *b, TextureSwizzle *a) const
{
    pfncpp_nvnTextureBuilderGetSwizzle(this, r, g, b, a);
}

inline TextureDepthStencilMode TextureBuilder::GetDepthStencilMode() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDepthStencilMode_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetDepthStencilMode(this);
#endif
}

inline const void * TextureBuilder::GetPackagedTextureData() const
{
    return pfncpp_nvnTextureBuilderGetPackagedTextureData(this);
}

inline NVNboolean TextureBuilder::GetPackagedTextureLayout(PackagedTextureLayout *data) const
{
    return pfncpp_nvnTextureBuilderGetPackagedTextureLayout(this, data);
}

inline ptrdiff_t TextureBuilder::GetStride() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetStride_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetStride(this);
#endif
}

inline void TextureBuilder::GetSparseTileLayout(TextureSparseTileLayout *layout) const
{
    pfncpp_nvnTextureBuilderGetSparseTileLayout(this, layout);
}

inline uint32_t TextureBuilder::GetGLTextureName() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetGLTextureName_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetGLTextureName(this);
#endif
}

inline size_t TextureBuilder::GetZCullStorageSize() const
{
    return pfncpp_nvnTextureBuilderGetZCullStorageSize(this);
}

inline MemoryPool * TextureBuilder::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetMemoryPool(this);
#endif
}

inline ptrdiff_t TextureBuilder::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnTextureBuilderGetMemoryOffset(this);
#endif
}

inline RawStorageClass TextureBuilder::GetRawStorageClass() const
{
    return pfncpp_nvnTextureBuilderGetRawStorageClass(this);
}

inline TextureView & TextureView::SetDefaults()
{
    pfncpp_nvnTextureViewSetDefaults(this);
    return *this;
}

inline TextureView & TextureView::SetLevels(int baseLevel, int numLevels)
{
    pfncpp_nvnTextureViewSetLevels(this, baseLevel, numLevels);
    return *this;
}

inline TextureView & TextureView::SetLayers(int minLayer, int numLayers)
{
    pfncpp_nvnTextureViewSetLayers(this, minLayer, numLayers);
    return *this;
}

inline TextureView & TextureView::SetFormat(Format format)
{
    pfncpp_nvnTextureViewSetFormat(this, format);
    return *this;
}

inline TextureView & TextureView::SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b, TextureSwizzle a)
{
    pfncpp_nvnTextureViewSetSwizzle(this, r, g, b, a);
    return *this;
}

inline TextureView & TextureView::SetDepthStencilMode(TextureDepthStencilMode mode)
{
    pfncpp_nvnTextureViewSetDepthStencilMode(this, mode);
    return *this;
}

inline TextureView & TextureView::SetTarget(TextureTarget target)
{
    pfncpp_nvnTextureViewSetTarget(this, target);
    return *this;
}

inline NVNboolean TextureView::GetLevels(int *baseLevel, int *numLevels) const
{
    return pfncpp_nvnTextureViewGetLevels(this, baseLevel, numLevels);
}

inline NVNboolean TextureView::GetLayers(int *minLayer, int *numLayers) const
{
    return pfncpp_nvnTextureViewGetLayers(this, minLayer, numLayers);
}

inline NVNboolean TextureView::GetFormat(Format *format) const
{
    return pfncpp_nvnTextureViewGetFormat(this, format);
}

inline NVNboolean TextureView::GetSwizzle(TextureSwizzle *r, TextureSwizzle *g, TextureSwizzle *b, TextureSwizzle *a) const
{
    return pfncpp_nvnTextureViewGetSwizzle(this, r, g, b, a);
}

inline NVNboolean TextureView::GetDepthStencilMode(TextureDepthStencilMode *mode) const
{
    return pfncpp_nvnTextureViewGetDepthStencilMode(this, mode);
}

inline NVNboolean TextureView::GetTarget(TextureTarget *target) const
{
    return pfncpp_nvnTextureViewGetTarget(this, target);
}

inline NVNboolean TextureView::Compare(const TextureView *otherView) const
{
    return pfncpp_nvnTextureViewCompare(this, otherView);
}

inline NVNboolean Texture::Initialize(const TextureBuilder *builder)
{
    return pfncpp_nvnTextureInitialize(this, builder);
}

inline size_t Texture::GetZCullStorageSize() const
{
    return pfncpp_nvnTextureGetZCullStorageSize(this);
}

inline void Texture::Finalize()
{
    pfncpp_nvnTextureFinalize(this);
}

inline void Texture::SetDebugLabel(const char * label)
{
    pfncpp_nvnTextureSetDebugLabel(this, label);
}

inline NVNstorageClass Texture::GetStorageClass() const
{
    return pfncpp_nvnTextureGetStorageClass(this);
}

inline ptrdiff_t Texture::GetViewOffset(const TextureView *textureView) const
{
    return pfncpp_nvnTextureGetViewOffset(this, textureView);
}

inline TextureFlags Texture::GetFlags() const
{
    return pfncpp_nvnTextureGetFlags(this);
}

inline TextureTarget Texture::GetTarget() const
{
    return pfncpp_nvnTextureGetTarget(this);
}

inline int Texture::GetWidth() const
{
    return pfncpp_nvnTextureGetWidth(this);
}

inline int Texture::GetHeight() const
{
    return pfncpp_nvnTextureGetHeight(this);
}

inline int Texture::GetDepth() const
{
    return pfncpp_nvnTextureGetDepth(this);
}

inline int Texture::GetLevels() const
{
    return pfncpp_nvnTextureGetLevels(this);
}

inline Format Texture::GetFormat() const
{
    return pfncpp_nvnTextureGetFormat(this);
}

inline int Texture::GetSamples() const
{
    return pfncpp_nvnTextureGetSamples(this);
}

inline void Texture::GetSwizzle(TextureSwizzle *r, TextureSwizzle *g, TextureSwizzle *b, TextureSwizzle *a) const
{
    pfncpp_nvnTextureGetSwizzle(this, r, g, b, a);
}

inline TextureDepthStencilMode Texture::GetDepthStencilMode() const
{
    return pfncpp_nvnTextureGetDepthStencilMode(this);
}

inline ptrdiff_t Texture::GetStride() const
{
    return pfncpp_nvnTextureGetStride(this);
}

inline TextureAddress Texture::GetTextureAddress() const
{
    return pfncpp_nvnTextureGetTextureAddress(this);
}

inline void Texture::GetSparseTileLayout(TextureSparseTileLayout *layout) const
{
    pfncpp_nvnTextureGetSparseTileLayout(this, layout);
}

inline void Texture::WriteTexels(const TextureView *textureView, const CopyRegion *region, const void *data) const
{
    pfncpp_nvnTextureWriteTexels(this, textureView, region, data);
}

inline void Texture::WriteTexelsStrided(const TextureView *textureView, const CopyRegion *region, const void *data, ptrdiff_t rowStride, ptrdiff_t imageStride) const
{
    pfncpp_nvnTextureWriteTexelsStrided(this, textureView, region, data, rowStride, imageStride);
}

inline void Texture::ReadTexels(const TextureView *textureView, const CopyRegion *region, void *data) const
{
    pfncpp_nvnTextureReadTexels(this, textureView, region, data);
}

inline void Texture::ReadTexelsStrided(const TextureView *textureView, const CopyRegion *region, void *data, ptrdiff_t rowStride, ptrdiff_t imageStride) const
{
    pfncpp_nvnTextureReadTexelsStrided(this, textureView, region, data, rowStride, imageStride);
}

inline void Texture::FlushTexels(const TextureView *textureView, const CopyRegion *region) const
{
    pfncpp_nvnTextureFlushTexels(this, textureView, region);
}

inline void Texture::InvalidateTexels(const TextureView *textureView, const CopyRegion *region) const
{
    pfncpp_nvnTextureInvalidateTexels(this, textureView, region);
}

inline MemoryPool * Texture::GetMemoryPool() const
{
    return pfncpp_nvnTextureGetMemoryPool(this);
}

inline ptrdiff_t Texture::GetMemoryOffset() const
{
    return pfncpp_nvnTextureGetMemoryOffset(this);
}

inline int Texture::GetStorageSize() const
{
    return pfncpp_nvnTextureGetStorageSize(this);
}

inline NVNboolean Texture::Compare(const Texture *otherTexture) const
{
    return pfncpp_nvnTextureCompare(this, otherTexture);
}

inline uint64_t Texture::GetDebugID() const
{
    return pfncpp_nvnTextureGetDebugID(this);
}

inline RawStorageClass Texture::GetRawStorageClass() const
{
    return pfncpp_nvnTextureGetRawStorageClass(this);
}

inline SamplerBuilder & SamplerBuilder::SetDevice(Device *device)
{
    pfncpp_nvnSamplerBuilderSetDevice(this, device);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetDefaults()
{
    pfncpp_nvnSamplerBuilderSetDefaults(this);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetMinMagFilter(MinFilter min, MagFilter mag)
{
    pfncpp_nvnSamplerBuilderSetMinMagFilter(this, min, mag);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetWrapMode(WrapMode s, WrapMode t, WrapMode r)
{
    pfncpp_nvnSamplerBuilderSetWrapMode(this, s, t, r);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetLodClamp(float min, float max)
{
#ifdef NVN_FORCE_FASTPATH
    return SetLodClamp_fastpath(min, max);
#else
    pfncpp_nvnSamplerBuilderSetLodClamp(this, min, max);
    return *this;
#endif
}

inline SamplerBuilder & SamplerBuilder::SetLodBias(float bias)
{
#ifdef NVN_FORCE_FASTPATH
    return SetLodBias_fastpath(bias);
#else
    pfncpp_nvnSamplerBuilderSetLodBias(this, bias);
    return *this;
#endif
}

inline SamplerBuilder & SamplerBuilder::SetCompare(CompareMode mode, CompareFunc func)
{
    pfncpp_nvnSamplerBuilderSetCompare(this, mode, func);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetBorderColor(const float *borderColor)
{
    pfncpp_nvnSamplerBuilderSetBorderColor(this, borderColor);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetBorderColori(const int *borderColor)
{
    pfncpp_nvnSamplerBuilderSetBorderColori(this, borderColor);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetBorderColorui(const uint32_t *borderColor)
{
    pfncpp_nvnSamplerBuilderSetBorderColorui(this, borderColor);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetMaxAnisotropy(float maxAniso)
{
#ifdef NVN_FORCE_FASTPATH
    return SetMaxAnisotropy_fastpath(maxAniso);
#else
    pfncpp_nvnSamplerBuilderSetMaxAnisotropy(this, maxAniso);
    return *this;
#endif
}

inline SamplerBuilder & SamplerBuilder::SetReductionFilter(SamplerReduction filter)
{
    pfncpp_nvnSamplerBuilderSetReductionFilter(this, filter);
    return *this;
}

inline SamplerBuilder & SamplerBuilder::SetLodSnap(float lodSnap)
{
#ifdef NVN_FORCE_FASTPATH
    return SetLodSnap_fastpath(lodSnap);
#else
    pfncpp_nvnSamplerBuilderSetLodSnap(this, lodSnap);
    return *this;
#endif
}

inline const Device * SamplerBuilder::GetDevice() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDevice_fastpath();
#else
    return pfncpp_nvnSamplerBuilderGetDevice(this);
#endif
}

inline void SamplerBuilder::GetMinMagFilter(MinFilter *min, MagFilter *mag) const
{
    pfncpp_nvnSamplerBuilderGetMinMagFilter(this, min, mag);
}

inline void SamplerBuilder::GetWrapMode(WrapMode *s, WrapMode *t, WrapMode *r) const
{
    pfncpp_nvnSamplerBuilderGetWrapMode(this, s, t, r);
}

inline void SamplerBuilder::GetLodClamp(float *min, float *max) const
{
    pfncpp_nvnSamplerBuilderGetLodClamp(this, min, max);
}

inline float SamplerBuilder::GetLodBias() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetLodBias_fastpath();
#else
    return pfncpp_nvnSamplerBuilderGetLodBias(this);
#endif
}

inline void SamplerBuilder::GetCompare(CompareMode *mode, CompareFunc *func) const
{
    pfncpp_nvnSamplerBuilderGetCompare(this, mode, func);
}

inline void SamplerBuilder::GetBorderColor(float *borderColor) const
{
    pfncpp_nvnSamplerBuilderGetBorderColor(this, borderColor);
}

inline void SamplerBuilder::GetBorderColori(int *borderColor) const
{
    pfncpp_nvnSamplerBuilderGetBorderColori(this, borderColor);
}

inline void SamplerBuilder::GetBorderColorui(uint32_t *borderColor) const
{
    pfncpp_nvnSamplerBuilderGetBorderColorui(this, borderColor);
}

inline float SamplerBuilder::GetMaxAnisotropy() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMaxAnisotropy_fastpath();
#else
    return pfncpp_nvnSamplerBuilderGetMaxAnisotropy(this);
#endif
}

inline SamplerReduction SamplerBuilder::GetReductionFilter() const
{
    return pfncpp_nvnSamplerBuilderGetReductionFilter(this);
}

inline float SamplerBuilder::GetLodSnap() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetLodSnap_fastpath();
#else
    return pfncpp_nvnSamplerBuilderGetLodSnap(this);
#endif
}

inline NVNboolean Sampler::Initialize(const SamplerBuilder *builder)
{
    return pfncpp_nvnSamplerInitialize(this, builder);
}

inline void Sampler::Finalize()
{
    pfncpp_nvnSamplerFinalize(this);
}

inline void Sampler::SetDebugLabel(const char * label)
{
    pfncpp_nvnSamplerSetDebugLabel(this, label);
}

inline void Sampler::GetMinMagFilter(MinFilter *min, MagFilter *mag) const
{
    pfncpp_nvnSamplerGetMinMagFilter(this, min, mag);
}

inline void Sampler::GetWrapMode(WrapMode *s, WrapMode *t, WrapMode *r) const
{
    pfncpp_nvnSamplerGetWrapMode(this, s, t, r);
}

inline void Sampler::GetLodClamp(float *min, float *max) const
{
    pfncpp_nvnSamplerGetLodClamp(this, min, max);
}

inline float Sampler::GetLodBias() const
{
    return pfncpp_nvnSamplerGetLodBias(this);
}

inline void Sampler::GetCompare(CompareMode *mode, CompareFunc *func) const
{
    pfncpp_nvnSamplerGetCompare(this, mode, func);
}

inline void Sampler::GetBorderColor(float *borderColor) const
{
    pfncpp_nvnSamplerGetBorderColor(this, borderColor);
}

inline void Sampler::GetBorderColori(int *borderColor) const
{
    pfncpp_nvnSamplerGetBorderColori(this, borderColor);
}

inline void Sampler::GetBorderColorui(uint32_t *borderColor) const
{
    pfncpp_nvnSamplerGetBorderColorui(this, borderColor);
}

inline float Sampler::GetMaxAnisotropy() const
{
    return pfncpp_nvnSamplerGetMaxAnisotropy(this);
}

inline SamplerReduction Sampler::GetReductionFilter() const
{
    return pfncpp_nvnSamplerGetReductionFilter(this);
}

inline NVNboolean Sampler::Compare(const Sampler *otherSampler) const
{
    return pfncpp_nvnSamplerCompare(this, otherSampler);
}

inline uint64_t Sampler::GetDebugID() const
{
    return pfncpp_nvnSamplerGetDebugID(this);
}

inline BlendState & BlendState::SetDefaults()
{
    pfncpp_nvnBlendStateSetDefaults(this);
    return *this;
}

inline BlendState & BlendState::SetBlendTarget(int target)
{
#ifdef NVN_FORCE_FASTPATH
    return SetBlendTarget_fastpath(target);
#else
    pfncpp_nvnBlendStateSetBlendTarget(this, target);
    return *this;
#endif
}

inline BlendState & BlendState::SetBlendFunc(BlendFunc srcFunc, BlendFunc dstFunc, BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha)
{
#ifdef NVN_FORCE_FASTPATH
    return SetBlendFunc_fastpath(srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
#else
    pfncpp_nvnBlendStateSetBlendFunc(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
    return *this;
#endif
}

inline BlendState & BlendState::SetBlendEquation(BlendEquation modeRGB, BlendEquation modeAlpha)
{
#ifdef NVN_FORCE_FASTPATH
    return SetBlendEquation_fastpath(modeRGB, modeAlpha);
#else
    pfncpp_nvnBlendStateSetBlendEquation(this, modeRGB, modeAlpha);
    return *this;
#endif
}

inline BlendState & BlendState::SetAdvancedMode(BlendAdvancedMode overlap)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAdvancedMode_fastpath(overlap);
#else
    pfncpp_nvnBlendStateSetAdvancedMode(this, overlap);
    return *this;
#endif
}

inline BlendState & BlendState::SetAdvancedOverlap(BlendAdvancedOverlap overlap)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAdvancedOverlap_fastpath(overlap);
#else
    pfncpp_nvnBlendStateSetAdvancedOverlap(this, overlap);
    return *this;
#endif
}

inline BlendState & BlendState::SetAdvancedPremultipliedSrc(NVNboolean premultiplied)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAdvancedPremultipliedSrc_fastpath(premultiplied);
#else
    pfncpp_nvnBlendStateSetAdvancedPremultipliedSrc(this, premultiplied);
    return *this;
#endif
}

inline BlendState & BlendState::SetAdvancedNormalizedDst(NVNboolean normalized)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAdvancedNormalizedDst_fastpath(normalized);
#else
    pfncpp_nvnBlendStateSetAdvancedNormalizedDst(this, normalized);
    return *this;
#endif
}

inline int BlendState::GetBlendTarget() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetBlendTarget_fastpath();
#else
    return pfncpp_nvnBlendStateGetBlendTarget(this);
#endif
}

inline void BlendState::GetBlendFunc(BlendFunc *srcFunc, BlendFunc *dstFunc, BlendFunc *srcFuncAlpha, BlendFunc *dstFuncAlpha) const
{
    pfncpp_nvnBlendStateGetBlendFunc(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
}

inline void BlendState::GetBlendEquation(BlendEquation *modeRGB, BlendEquation *modeAlpha) const
{
    pfncpp_nvnBlendStateGetBlendEquation(this, modeRGB, modeAlpha);
}

inline BlendAdvancedMode BlendState::GetAdvancedMode() const
{
    return pfncpp_nvnBlendStateGetAdvancedMode(this);
}

inline BlendAdvancedOverlap BlendState::GetAdvancedOverlap() const
{
    return pfncpp_nvnBlendStateGetAdvancedOverlap(this);
}

inline NVNboolean BlendState::GetAdvancedPremultipliedSrc() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetAdvancedPremultipliedSrc_fastpath();
#else
    return pfncpp_nvnBlendStateGetAdvancedPremultipliedSrc(this);
#endif
}

inline NVNboolean BlendState::GetAdvancedNormalizedDst() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetAdvancedNormalizedDst_fastpath();
#else
    return pfncpp_nvnBlendStateGetAdvancedNormalizedDst(this);
#endif
}

inline ColorState & ColorState::SetDefaults()
{
    pfncpp_nvnColorStateSetDefaults(this);
    return *this;
}

inline ColorState & ColorState::SetBlendEnable(int index, NVNboolean enable)
{
    pfncpp_nvnColorStateSetBlendEnable(this, index, enable);
    return *this;
}

inline ColorState & ColorState::SetLogicOp(LogicOp logicOp)
{
#ifdef NVN_FORCE_FASTPATH
    return SetLogicOp_fastpath(logicOp);
#else
    pfncpp_nvnColorStateSetLogicOp(this, logicOp);
    return *this;
#endif
}

inline ColorState & ColorState::SetAlphaTest(AlphaFunc alphaTest)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAlphaTest_fastpath(alphaTest);
#else
    pfncpp_nvnColorStateSetAlphaTest(this, alphaTest);
    return *this;
#endif
}

inline NVNboolean ColorState::GetBlendEnable(int index) const
{
    return pfncpp_nvnColorStateGetBlendEnable(this, index);
}

inline LogicOp ColorState::GetLogicOp() const
{
    return pfncpp_nvnColorStateGetLogicOp(this);
}

inline AlphaFunc ColorState::GetAlphaTest() const
{
    return pfncpp_nvnColorStateGetAlphaTest(this);
}

inline ChannelMaskState & ChannelMaskState::SetDefaults()
{
    pfncpp_nvnChannelMaskStateSetDefaults(this);
    return *this;
}

inline ChannelMaskState & ChannelMaskState::SetChannelMask(int index, NVNboolean r, NVNboolean g, NVNboolean b, NVNboolean a)
{
    pfncpp_nvnChannelMaskStateSetChannelMask(this, index, r, g, b, a);
    return *this;
}

inline void ChannelMaskState::GetChannelMask(int index, NVNboolean *r, NVNboolean *g, NVNboolean *b, NVNboolean *a) const
{
    pfncpp_nvnChannelMaskStateGetChannelMask(this, index, r, g, b, a);
}

inline MultisampleState & MultisampleState::SetDefaults()
{
    pfncpp_nvnMultisampleStateSetDefaults(this);
    return *this;
}

inline MultisampleState & MultisampleState::SetMultisampleEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetMultisampleEnable_fastpath(enable);
#else
    pfncpp_nvnMultisampleStateSetMultisampleEnable(this, enable);
    return *this;
#endif
}

inline MultisampleState & MultisampleState::SetSamples(int samples)
{
#ifdef NVN_FORCE_FASTPATH
    return SetSamples_fastpath(samples);
#else
    pfncpp_nvnMultisampleStateSetSamples(this, samples);
    return *this;
#endif
}

inline MultisampleState & MultisampleState::SetAlphaToCoverageEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAlphaToCoverageEnable_fastpath(enable);
#else
    pfncpp_nvnMultisampleStateSetAlphaToCoverageEnable(this, enable);
    return *this;
#endif
}

inline MultisampleState & MultisampleState::SetAlphaToCoverageDither(NVNboolean dither)
{
#ifdef NVN_FORCE_FASTPATH
    return SetAlphaToCoverageDither_fastpath(dither);
#else
    pfncpp_nvnMultisampleStateSetAlphaToCoverageDither(this, dither);
    return *this;
#endif
}

inline NVNboolean MultisampleState::GetMultisampleEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMultisampleEnable_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetMultisampleEnable(this);
#endif
}

inline int MultisampleState::GetSamples() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSamples_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetSamples(this);
#endif
}

inline NVNboolean MultisampleState::GetAlphaToCoverageEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetAlphaToCoverageEnable_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetAlphaToCoverageEnable(this);
#endif
}

inline NVNboolean MultisampleState::GetAlphaToCoverageDither() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetAlphaToCoverageDither_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetAlphaToCoverageDither(this);
#endif
}

inline MultisampleState & MultisampleState::SetRasterSamples(int rasterSamples)
{
#ifdef NVN_FORCE_FASTPATH
    return SetRasterSamples_fastpath(rasterSamples);
#else
    pfncpp_nvnMultisampleStateSetRasterSamples(this, rasterSamples);
    return *this;
#endif
}

inline int MultisampleState::GetRasterSamples() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetRasterSamples_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetRasterSamples(this);
#endif
}

inline MultisampleState & MultisampleState::SetCoverageModulationMode(CoverageModulationMode mode)
{
#ifdef NVN_FORCE_FASTPATH
    return SetCoverageModulationMode_fastpath(mode);
#else
    pfncpp_nvnMultisampleStateSetCoverageModulationMode(this, mode);
    return *this;
#endif
}

inline CoverageModulationMode MultisampleState::GetCoverageModulationMode() const
{
    return pfncpp_nvnMultisampleStateGetCoverageModulationMode(this);
}

inline MultisampleState & MultisampleState::SetCoverageToColorEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetCoverageToColorEnable_fastpath(enable);
#else
    pfncpp_nvnMultisampleStateSetCoverageToColorEnable(this, enable);
    return *this;
#endif
}

inline NVNboolean MultisampleState::GetCoverageToColorEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetCoverageToColorEnable_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetCoverageToColorEnable(this);
#endif
}

inline MultisampleState & MultisampleState::SetCoverageToColorOutput(int color)
{
#ifdef NVN_FORCE_FASTPATH
    return SetCoverageToColorOutput_fastpath(color);
#else
    pfncpp_nvnMultisampleStateSetCoverageToColorOutput(this, color);
    return *this;
#endif
}

inline int MultisampleState::GetCoverageToColorOutput() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetCoverageToColorOutput_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetCoverageToColorOutput(this);
#endif
}

inline MultisampleState & MultisampleState::SetSampleLocationsEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetSampleLocationsEnable_fastpath(enable);
#else
    pfncpp_nvnMultisampleStateSetSampleLocationsEnable(this, enable);
    return *this;
#endif
}

inline NVNboolean MultisampleState::GetSampleLocationsEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSampleLocationsEnable_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetSampleLocationsEnable(this);
#endif
}

inline void MultisampleState::GetSampleLocationsGrid(int *width, int *height)
{
    pfncpp_nvnMultisampleStateGetSampleLocationsGrid(this, width, height);
}

inline MultisampleState & MultisampleState::SetSampleLocationsGridEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetSampleLocationsGridEnable_fastpath(enable);
#else
    pfncpp_nvnMultisampleStateSetSampleLocationsGridEnable(this, enable);
    return *this;
#endif
}

inline NVNboolean MultisampleState::GetSampleLocationsGridEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetSampleLocationsGridEnable_fastpath();
#else
    return pfncpp_nvnMultisampleStateGetSampleLocationsGridEnable(this);
#endif
}

inline MultisampleState & MultisampleState::SetSampleLocations(int start, int count, const float *values)
{
    pfncpp_nvnMultisampleStateSetSampleLocations(this, start, count, values);
    return *this;
}

inline PolygonState & PolygonState::SetDefaults()
{
    pfncpp_nvnPolygonStateSetDefaults(this);
    return *this;
}

inline PolygonState & PolygonState::SetCullFace(Face face)
{
#ifdef NVN_FORCE_FASTPATH
    return SetCullFace_fastpath(face);
#else
    pfncpp_nvnPolygonStateSetCullFace(this, face);
    return *this;
#endif
}

inline PolygonState & PolygonState::SetFrontFace(FrontFace face)
{
#ifdef NVN_FORCE_FASTPATH
    return SetFrontFace_fastpath(face);
#else
    pfncpp_nvnPolygonStateSetFrontFace(this, face);
    return *this;
#endif
}

inline PolygonState & PolygonState::SetPolygonMode(PolygonMode polygonMode)
{
#ifdef NVN_FORCE_FASTPATH
    return SetPolygonMode_fastpath(polygonMode);
#else
    pfncpp_nvnPolygonStateSetPolygonMode(this, polygonMode);
    return *this;
#endif
}

inline PolygonState & PolygonState::SetPolygonOffsetEnables(PolygonOffsetEnable enables)
{
    pfncpp_nvnPolygonStateSetPolygonOffsetEnables(this, enables);
    return *this;
}

inline Face PolygonState::GetCullFace() const
{
    return pfncpp_nvnPolygonStateGetCullFace(this);
}

inline FrontFace PolygonState::GetFrontFace() const
{
    return pfncpp_nvnPolygonStateGetFrontFace(this);
}

inline PolygonMode PolygonState::GetPolygonMode() const
{
    return pfncpp_nvnPolygonStateGetPolygonMode(this);
}

inline PolygonOffsetEnable PolygonState::GetPolygonOffsetEnables() const
{
    return pfncpp_nvnPolygonStateGetPolygonOffsetEnables(this);
}

inline DepthStencilState & DepthStencilState::SetDefaults()
{
    pfncpp_nvnDepthStencilStateSetDefaults(this);
    return *this;
}

inline DepthStencilState & DepthStencilState::SetDepthTestEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetDepthTestEnable_fastpath(enable);
#else
    pfncpp_nvnDepthStencilStateSetDepthTestEnable(this, enable);
    return *this;
#endif
}

inline DepthStencilState & DepthStencilState::SetDepthWriteEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetDepthWriteEnable_fastpath(enable);
#else
    pfncpp_nvnDepthStencilStateSetDepthWriteEnable(this, enable);
    return *this;
#endif
}

inline DepthStencilState & DepthStencilState::SetDepthFunc(DepthFunc func)
{
#ifdef NVN_FORCE_FASTPATH
    return SetDepthFunc_fastpath(func);
#else
    pfncpp_nvnDepthStencilStateSetDepthFunc(this, func);
    return *this;
#endif
}

inline DepthStencilState & DepthStencilState::SetStencilTestEnable(NVNboolean enable)
{
#ifdef NVN_FORCE_FASTPATH
    return SetStencilTestEnable_fastpath(enable);
#else
    pfncpp_nvnDepthStencilStateSetStencilTestEnable(this, enable);
    return *this;
#endif
}

inline DepthStencilState & DepthStencilState::SetStencilFunc(Face faces, StencilFunc func)
{
    pfncpp_nvnDepthStencilStateSetStencilFunc(this, faces, func);
    return *this;
}

inline DepthStencilState & DepthStencilState::SetStencilOp(Face faces, StencilOp fail, StencilOp depthFail, StencilOp depthPass)
{
    pfncpp_nvnDepthStencilStateSetStencilOp(this, faces, fail, depthFail, depthPass);
    return *this;
}

inline NVNboolean DepthStencilState::GetDepthTestEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDepthTestEnable_fastpath();
#else
    return pfncpp_nvnDepthStencilStateGetDepthTestEnable(this);
#endif
}

inline NVNboolean DepthStencilState::GetDepthWriteEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDepthWriteEnable_fastpath();
#else
    return pfncpp_nvnDepthStencilStateGetDepthWriteEnable(this);
#endif
}

inline DepthFunc DepthStencilState::GetDepthFunc() const
{
    return pfncpp_nvnDepthStencilStateGetDepthFunc(this);
}

inline NVNboolean DepthStencilState::GetStencilTestEnable() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetStencilTestEnable_fastpath();
#else
    return pfncpp_nvnDepthStencilStateGetStencilTestEnable(this);
#endif
}

inline StencilFunc DepthStencilState::GetStencilFunc(Face face) const
{
    return pfncpp_nvnDepthStencilStateGetStencilFunc(this, face);
}

inline void DepthStencilState::GetStencilOp(Face face, StencilOp *fail, StencilOp *depthFail, StencilOp *depthPass) const
{
    pfncpp_nvnDepthStencilStateGetStencilOp(this, face, fail, depthFail, depthPass);
}

inline VertexAttribState & VertexAttribState::SetDefaults()
{
    pfncpp_nvnVertexAttribStateSetDefaults(this);
    return *this;
}

inline VertexAttribState & VertexAttribState::SetFormat(Format format, ptrdiff_t relativeOffset)
{
    pfncpp_nvnVertexAttribStateSetFormat(this, format, relativeOffset);
    return *this;
}

inline VertexAttribState & VertexAttribState::SetStreamIndex(int streamIndex)
{
#ifdef NVN_FORCE_FASTPATH
    return SetStreamIndex_fastpath(streamIndex);
#else
    pfncpp_nvnVertexAttribStateSetStreamIndex(this, streamIndex);
    return *this;
#endif
}

inline void VertexAttribState::GetFormat(Format *format, ptrdiff_t *relativeOffset) const
{
    pfncpp_nvnVertexAttribStateGetFormat(this, format, relativeOffset);
}

inline int VertexAttribState::GetStreamIndex() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetStreamIndex_fastpath();
#else
    return pfncpp_nvnVertexAttribStateGetStreamIndex(this);
#endif
}

inline VertexStreamState & VertexStreamState::SetDefaults()
{
    pfncpp_nvnVertexStreamStateSetDefaults(this);
    return *this;
}

inline VertexStreamState & VertexStreamState::SetStride(ptrdiff_t stride)
{
#ifdef NVN_FORCE_FASTPATH
    return SetStride_fastpath(stride);
#else
    pfncpp_nvnVertexStreamStateSetStride(this, stride);
    return *this;
#endif
}

inline VertexStreamState & VertexStreamState::SetDivisor(int divisor)
{
#ifdef NVN_FORCE_FASTPATH
    return SetDivisor_fastpath(divisor);
#else
    pfncpp_nvnVertexStreamStateSetDivisor(this, divisor);
    return *this;
#endif
}

inline ptrdiff_t VertexStreamState::GetStride() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetStride_fastpath();
#else
    return pfncpp_nvnVertexStreamStateGetStride(this);
#endif
}

inline int VertexStreamState::GetDivisor() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetDivisor_fastpath();
#else
    return pfncpp_nvnVertexStreamStateGetDivisor(this);
#endif
}

inline NVNboolean CommandBuffer::Initialize(Device *device)
{
    return pfncpp_nvnCommandBufferInitialize(this, device);
}

inline void CommandBuffer::Finalize()
{
    pfncpp_nvnCommandBufferFinalize(this);
}

inline void CommandBuffer::SetDebugLabel(const char * label)
{
    pfncpp_nvnCommandBufferSetDebugLabel(this, label);
}

inline void CommandBuffer::SetMemoryCallback(CommandBufferMemoryCallbackFunc callback)
{
    pfncpp_nvnCommandBufferSetMemoryCallback(this, callback);
}

inline void CommandBuffer::SetMemoryCallbackData(void *callbackData)
{
    pfncpp_nvnCommandBufferSetMemoryCallbackData(this, callbackData);
}

inline void CommandBuffer::SetCommandMemoryCallbackEnabled(NVNboolean enabled)
{
#ifdef NVN_FORCE_FASTPATH
    SetCommandMemoryCallbackEnabled_fastpath(enabled);
#else
    pfncpp_nvnCommandBufferSetCommandMemoryCallbackEnabled(this, enabled);
#endif
}

inline void CommandBuffer::AddCommandMemory(const MemoryPool *pool, ptrdiff_t offset, size_t size)
{
    pfncpp_nvnCommandBufferAddCommandMemory(this, pool, offset, size);
}

inline void CommandBuffer::AddControlMemory(void *memory, size_t size)
{
    pfncpp_nvnCommandBufferAddControlMemory(this, memory, size);
}

inline size_t CommandBuffer::GetCommandMemorySize() const
{
    return pfncpp_nvnCommandBufferGetCommandMemorySize(this);
}

inline size_t CommandBuffer::GetCommandMemoryUsed() const
{
    return pfncpp_nvnCommandBufferGetCommandMemoryUsed(this);
}

inline size_t CommandBuffer::GetCommandMemoryFree() const
{
    return pfncpp_nvnCommandBufferGetCommandMemoryFree(this);
}

inline size_t CommandBuffer::GetControlMemorySize() const
{
    return pfncpp_nvnCommandBufferGetControlMemorySize(this);
}

inline size_t CommandBuffer::GetControlMemoryUsed() const
{
    return pfncpp_nvnCommandBufferGetControlMemoryUsed(this);
}

inline size_t CommandBuffer::GetControlMemoryFree() const
{
    return pfncpp_nvnCommandBufferGetControlMemoryFree(this);
}

inline void CommandBuffer::BeginRecording()
{
#ifdef NVN_FORCE_FASTPATH
    BeginRecording_fastpath();
#else
    pfncpp_nvnCommandBufferBeginRecording(this);
#endif
}

inline CommandHandle CommandBuffer::EndRecording()
{
    return pfncpp_nvnCommandBufferEndRecording(this);
}

inline void CommandBuffer::CallCommands(int numCommands, NVN_NOESCAPE const CommandHandle *handles)
{
#ifdef NVN_FORCE_FASTPATH
    CallCommands_fastpath(numCommands, handles);
#else
    pfncpp_nvnCommandBufferCallCommands(this, numCommands, handles);
#endif
}

inline void CommandBuffer::CopyCommands(int numCommands, NVN_NOESCAPE const CommandHandle *handles)
{
    pfncpp_nvnCommandBufferCopyCommands(this, numCommands, handles);
}

inline void CommandBuffer::BindBlendState(NVN_NOESCAPE const BlendState *blend)
{
    pfncpp_nvnCommandBufferBindBlendState(this, blend);
}

inline void CommandBuffer::BindChannelMaskState(NVN_NOESCAPE const ChannelMaskState *channelMask)
{
    pfncpp_nvnCommandBufferBindChannelMaskState(this, channelMask);
}

inline void CommandBuffer::BindColorState(NVN_NOESCAPE const ColorState *color)
{
    pfncpp_nvnCommandBufferBindColorState(this, color);
}

inline void CommandBuffer::BindMultisampleState(NVN_NOESCAPE const MultisampleState *multisample)
{
    pfncpp_nvnCommandBufferBindMultisampleState(this, multisample);
}

inline void CommandBuffer::BindPolygonState(NVN_NOESCAPE const PolygonState *polygon)
{
    pfncpp_nvnCommandBufferBindPolygonState(this, polygon);
}

inline void CommandBuffer::BindDepthStencilState(NVN_NOESCAPE const DepthStencilState *depthStencil)
{
    pfncpp_nvnCommandBufferBindDepthStencilState(this, depthStencil);
}

inline void CommandBuffer::BindVertexAttribState(int numAttribs, NVN_NOESCAPE const VertexAttribState *attribs)
{
    pfncpp_nvnCommandBufferBindVertexAttribState(this, numAttribs, attribs);
}

inline void CommandBuffer::BindVertexStreamState(int numStreams, NVN_NOESCAPE const VertexStreamState *streams)
{
    pfncpp_nvnCommandBufferBindVertexStreamState(this, numStreams, streams);
}

inline void CommandBuffer::BindProgram(const Program *program, ShaderStageBits stages)
{
    pfncpp_nvnCommandBufferBindProgram(this, program, stages);
}

inline void CommandBuffer::BindVertexBuffer(int index, BufferAddress buffer, size_t size)
{
#ifdef NVN_FORCE_FASTPATH
    BindVertexBuffer_fastpath(index, buffer, size);
#else
    pfncpp_nvnCommandBufferBindVertexBuffer(this, index, buffer, size);
#endif
}

inline void CommandBuffer::BindVertexBuffers(int first, int count, NVN_NOESCAPE const BufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    BindVertexBuffers_fastpath(first, count, buffers);
#else
    pfncpp_nvnCommandBufferBindVertexBuffers(this, first, count, buffers);
#endif
}

inline void CommandBuffer::BindUniformBuffer(ShaderStage stage, int index, BufferAddress buffer, size_t size)
{
#ifdef NVN_FORCE_FASTPATH
    BindUniformBuffer_fastpath(stage, index, buffer, size);
#else
    pfncpp_nvnCommandBufferBindUniformBuffer(this, stage, index, buffer, size);
#endif
}

inline void CommandBuffer::BindUniformBuffers(ShaderStage stage, int first, int count, NVN_NOESCAPE const BufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    BindUniformBuffers_fastpath(stage, first, count, buffers);
#else
    pfncpp_nvnCommandBufferBindUniformBuffers(this, stage, first, count, buffers);
#endif
}

inline void CommandBuffer::BindUniformBuffersDeferred(ShaderStage stage, int first, int count, const BufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    BindUniformBuffersDeferred_fastpath(stage, first, count, buffers);
#else
    pfncpp_nvnCommandBufferBindUniformBuffersDeferred(this, stage, first, count, buffers);
#endif
}

inline void CommandBuffer::BindTransformFeedbackBuffer(int index, BufferAddress buffer, size_t size)
{
    pfncpp_nvnCommandBufferBindTransformFeedbackBuffer(this, index, buffer, size);
}

inline void CommandBuffer::BindTransformFeedbackBuffers(int first, int count, NVN_NOESCAPE const BufferRange *buffers)
{
    pfncpp_nvnCommandBufferBindTransformFeedbackBuffers(this, first, count, buffers);
}

inline void CommandBuffer::BindStorageBuffer(ShaderStage stage, int index, BufferAddress buffer, size_t size)
{
    pfncpp_nvnCommandBufferBindStorageBuffer(this, stage, index, buffer, size);
}

inline void CommandBuffer::BindStorageBuffers(ShaderStage stage, int first, int count, NVN_NOESCAPE const BufferRange *buffers)
{
    pfncpp_nvnCommandBufferBindStorageBuffers(this, stage, first, count, buffers);
}

inline void CommandBuffer::BindStorageBuffersDeferred(ShaderStage stage, int first, int count, const BufferRange *buffers)
{
#ifdef NVN_FORCE_FASTPATH
    BindStorageBuffersDeferred_fastpath(stage, first, count, buffers);
#else
    pfncpp_nvnCommandBufferBindStorageBuffersDeferred(this, stage, first, count, buffers);
#endif
}

inline void CommandBuffer::BindTexture(ShaderStage stage, int index, TextureHandle texture)
{
    pfncpp_nvnCommandBufferBindTexture(this, stage, index, texture);
}

inline void CommandBuffer::BindTextures(ShaderStage stage, int first, int count, NVN_NOESCAPE const TextureHandle *textures)
{
    pfncpp_nvnCommandBufferBindTextures(this, stage, first, count, textures);
}

inline void CommandBuffer::BindTexturesDeferred(ShaderStage stage, int first, int count, const TextureHandle *textures)
{
#ifdef NVN_FORCE_FASTPATH
    BindTexturesDeferred_fastpath(stage, first, count, textures);
#else
    pfncpp_nvnCommandBufferBindTexturesDeferred(this, stage, first, count, textures);
#endif
}

inline void CommandBuffer::BindImage(ShaderStage stage, int index, ImageHandle image)
{
    pfncpp_nvnCommandBufferBindImage(this, stage, index, image);
}

inline void CommandBuffer::BindImages(ShaderStage stage, int first, int count, NVN_NOESCAPE const ImageHandle *images)
{
    pfncpp_nvnCommandBufferBindImages(this, stage, first, count, images);
}

inline void CommandBuffer::BindImagesDeferred(ShaderStage stage, int first, int count, const ImageHandle *images)
{
#ifdef NVN_FORCE_FASTPATH
    BindImagesDeferred_fastpath(stage, first, count, images);
#else
    pfncpp_nvnCommandBufferBindImagesDeferred(this, stage, first, count, images);
#endif
}

inline void CommandBuffer::SetPatchSize(int size)
{
    pfncpp_nvnCommandBufferSetPatchSize(this, size);
}

inline void CommandBuffer::SetInnerTessellationLevels(NVN_NOESCAPE const float *levels)
{
    pfncpp_nvnCommandBufferSetInnerTessellationLevels(this, levels);
}

inline void CommandBuffer::SetOuterTessellationLevels(NVN_NOESCAPE const float *levels)
{
    pfncpp_nvnCommandBufferSetOuterTessellationLevels(this, levels);
}

inline void CommandBuffer::SetPrimitiveRestart(NVNboolean enable, int index)
{
    pfncpp_nvnCommandBufferSetPrimitiveRestart(this, enable, index);
}

inline void CommandBuffer::BeginTransformFeedback(BufferAddress buffer)
{
    pfncpp_nvnCommandBufferBeginTransformFeedback(this, buffer);
}

inline void CommandBuffer::EndTransformFeedback(BufferAddress buffer)
{
    pfncpp_nvnCommandBufferEndTransformFeedback(this, buffer);
}

inline void CommandBuffer::PauseTransformFeedback(BufferAddress buffer)
{
    pfncpp_nvnCommandBufferPauseTransformFeedback(this, buffer);
}

inline void CommandBuffer::ResumeTransformFeedback(BufferAddress buffer)
{
    pfncpp_nvnCommandBufferResumeTransformFeedback(this, buffer);
}

inline void CommandBuffer::DrawTransformFeedback(DrawPrimitive mode, BufferAddress buffer)
{
    pfncpp_nvnCommandBufferDrawTransformFeedback(this, mode, buffer);
}

inline void CommandBuffer::DrawArrays(DrawPrimitive mode, int first, int count)
{
    pfncpp_nvnCommandBufferDrawArrays(this, mode, first, count);
}

inline void CommandBuffer::DrawElements(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer)
{
#ifdef NVN_FORCE_FASTPATH
    DrawElements_fastpath(mode, type, count, indexBuffer);
#else
    pfncpp_nvnCommandBufferDrawElements(this, mode, type, count, indexBuffer);
#endif
}

inline void CommandBuffer::DrawElementsBaseVertex(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer, int baseVertex)
{
    pfncpp_nvnCommandBufferDrawElementsBaseVertex(this, mode, type, count, indexBuffer, baseVertex);
}

inline void CommandBuffer::DrawArraysInstanced(DrawPrimitive mode, int first, int count, int baseInstance, int instanceCount)
{
    pfncpp_nvnCommandBufferDrawArraysInstanced(this, mode, first, count, baseInstance, instanceCount);
}

inline void CommandBuffer::DrawElementsInstanced(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer, int baseVertex, int baseInstance, int instanceCount)
{
    pfncpp_nvnCommandBufferDrawElementsInstanced(this, mode, type, count, indexBuffer, baseVertex, baseInstance, instanceCount);
}

inline void CommandBuffer::DrawArraysIndirect(DrawPrimitive mode, BufferAddress indirectBuffer)
{
    pfncpp_nvnCommandBufferDrawArraysIndirect(this, mode, indirectBuffer);
}

inline void CommandBuffer::DrawElementsIndirect(DrawPrimitive mode, IndexType type, BufferAddress indexBuffer, BufferAddress indirectBuffer)
{
    pfncpp_nvnCommandBufferDrawElementsIndirect(this, mode, type, indexBuffer, indirectBuffer);
}

inline void CommandBuffer::MultiDrawArraysIndirectCount(DrawPrimitive mode, BufferAddress indirectBuffer, BufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride)
{
    pfncpp_nvnCommandBufferMultiDrawArraysIndirectCount(this, mode, indirectBuffer, parameterBuffer, maxDrawCount, stride);
}

inline void CommandBuffer::MultiDrawElementsIndirectCount(DrawPrimitive mode, IndexType type, BufferAddress indexBuffer, BufferAddress indirectBuffer, BufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride)
{
    pfncpp_nvnCommandBufferMultiDrawElementsIndirectCount(this, mode, type, indexBuffer, indirectBuffer, parameterBuffer, maxDrawCount, stride);
}

inline void CommandBuffer::ClearColor(int index, NVN_NOESCAPE const float *color, ClearColorMask mask)
{
    pfncpp_nvnCommandBufferClearColor(this, index, color, mask);
}

inline void CommandBuffer::ClearColori(int index, NVN_NOESCAPE const int *color, ClearColorMask mask)
{
    pfncpp_nvnCommandBufferClearColori(this, index, color, mask);
}

inline void CommandBuffer::ClearColorui(int index, NVN_NOESCAPE const uint32_t *color, ClearColorMask mask)
{
    pfncpp_nvnCommandBufferClearColorui(this, index, color, mask);
}

inline void CommandBuffer::ClearDepthStencil(float depthValue, NVNboolean depthMask, int stencilValue, int stencilMask)
{
    pfncpp_nvnCommandBufferClearDepthStencil(this, depthValue, depthMask, stencilValue, stencilMask);
}

inline void CommandBuffer::DispatchCompute(int groupsX, int groupsY, int groupsZ)
{
    pfncpp_nvnCommandBufferDispatchCompute(this, groupsX, groupsY, groupsZ);
}

inline void CommandBuffer::DispatchComputeIndirect(BufferAddress indirectBuffer)
{
    pfncpp_nvnCommandBufferDispatchComputeIndirect(this, indirectBuffer);
}

inline void CommandBuffer::SetViewport(int x, int y, int w, int h)
{
    pfncpp_nvnCommandBufferSetViewport(this, x, y, w, h);
}

inline void CommandBuffer::SetViewports(int first, int count, NVN_NOESCAPE const float *ranges)
{
    pfncpp_nvnCommandBufferSetViewports(this, first, count, ranges);
}

inline void CommandBuffer::SetViewportSwizzles(int first, int count, NVN_NOESCAPE const ViewportSwizzle *swizzles)
{
    pfncpp_nvnCommandBufferSetViewportSwizzles(this, first, count, swizzles);
}

inline void CommandBuffer::SetScissor(int x, int y, int w, int h)
{
    pfncpp_nvnCommandBufferSetScissor(this, x, y, w, h);
}

inline void CommandBuffer::SetScissors(int first, int count, NVN_NOESCAPE const int *rects)
{
    pfncpp_nvnCommandBufferSetScissors(this, first, count, rects);
}

inline void CommandBuffer::SetDepthRange(float n, float f)
{
    pfncpp_nvnCommandBufferSetDepthRange(this, n, f);
}

inline void CommandBuffer::SetDepthBounds(NVNboolean enable, float n, float f)
{
    pfncpp_nvnCommandBufferSetDepthBounds(this, enable, n, f);
}

inline void CommandBuffer::SetDepthRanges(int first, int count, NVN_NOESCAPE const float *ranges)
{
    pfncpp_nvnCommandBufferSetDepthRanges(this, first, count, ranges);
}

inline void CommandBuffer::SetTiledCacheAction(TiledCacheAction action)
{
    pfncpp_nvnCommandBufferSetTiledCacheAction(this, action);
}

inline void CommandBuffer::SetTiledCacheTileSize(int tileWidth, int tileHeight)
{
    pfncpp_nvnCommandBufferSetTiledCacheTileSize(this, tileWidth, tileHeight);
}

inline void CommandBuffer::BindSeparateTexture(ShaderStage stage, int index, SeparateTextureHandle textureHandle)
{
    pfncpp_nvnCommandBufferBindSeparateTexture(this, stage, index, textureHandle);
}

inline void CommandBuffer::bindSeparateTexture(ShaderStage stage, int index, SeparateTextureHandle textureHandle)
{
    pfncpp_nvnCommandBufferBindSeparateTexture(this, stage, index, textureHandle);
}

inline void CommandBuffer::BindSeparateSampler(ShaderStage stage, int index, SeparateSamplerHandle samplerHandle)
{
    pfncpp_nvnCommandBufferBindSeparateSampler(this, stage, index, samplerHandle);
}

inline void CommandBuffer::bindSeparateSampler(ShaderStage stage, int index, SeparateSamplerHandle samplerHandle)
{
    pfncpp_nvnCommandBufferBindSeparateSampler(this, stage, index, samplerHandle);
}

inline void CommandBuffer::BindSeparateTextures(ShaderStage stage, int first, int count, NVN_NOESCAPE const SeparateTextureHandle *textureHandles)
{
    pfncpp_nvnCommandBufferBindSeparateTextures(this, stage, first, count, textureHandles);
}

inline void CommandBuffer::BindSeparateSamplers(ShaderStage stage, int first, int count, NVN_NOESCAPE const SeparateSamplerHandle *samplerHandles)
{
    pfncpp_nvnCommandBufferBindSeparateSamplers(this, stage, first, count, samplerHandles);
}

inline void CommandBuffer::BindSeparateTexturesDeferred(ShaderStage stage, int first, int count, const SeparateTextureHandle *textureHandles)
{
#ifdef NVN_FORCE_FASTPATH
    BindSeparateTexturesDeferred_fastpath(stage, first, count, textureHandles);
#else
    pfncpp_nvnCommandBufferBindSeparateTexturesDeferred(this, stage, first, count, textureHandles);
#endif
}

inline void CommandBuffer::BindSeparateSamplersDeferred(ShaderStage stage, int first, int count, const SeparateSamplerHandle *samplerHandles)
{
#ifdef NVN_FORCE_FASTPATH
    BindSeparateSamplersDeferred_fastpath(stage, first, count, samplerHandles);
#else
    pfncpp_nvnCommandBufferBindSeparateSamplersDeferred(this, stage, first, count, samplerHandles);
#endif
}

inline void CommandBuffer::SetStencilValueMask(Face faces, int mask)
{
    pfncpp_nvnCommandBufferSetStencilValueMask(this, faces, mask);
}

inline void CommandBuffer::SetStencilMask(Face faces, int mask)
{
    pfncpp_nvnCommandBufferSetStencilMask(this, faces, mask);
}

inline void CommandBuffer::SetStencilRef(Face faces, int ref)
{
    pfncpp_nvnCommandBufferSetStencilRef(this, faces, ref);
}

inline void CommandBuffer::SetBlendColor(NVN_NOESCAPE const float *blendColor)
{
    pfncpp_nvnCommandBufferSetBlendColor(this, blendColor);
}

inline void CommandBuffer::SetPointSize(float pointSize)
{
    pfncpp_nvnCommandBufferSetPointSize(this, pointSize);
}

inline void CommandBuffer::SetLineWidth(float lineWidth)
{
    pfncpp_nvnCommandBufferSetLineWidth(this, lineWidth);
}

inline void CommandBuffer::SetPolygonOffsetClamp(float factor, float units, float clamp)
{
    pfncpp_nvnCommandBufferSetPolygonOffsetClamp(this, factor, units, clamp);
}

inline void CommandBuffer::SetAlphaRef(float ref)
{
    pfncpp_nvnCommandBufferSetAlphaRef(this, ref);
}

inline void CommandBuffer::SetSampleMask(int mask)
{
    pfncpp_nvnCommandBufferSetSampleMask(this, mask);
}

inline void CommandBuffer::SetRasterizerDiscard(NVNboolean discard)
{
    pfncpp_nvnCommandBufferSetRasterizerDiscard(this, discard);
}

inline void CommandBuffer::SetDepthClamp(NVNboolean clamp)
{
    pfncpp_nvnCommandBufferSetDepthClamp(this, clamp);
}

inline void CommandBuffer::SetConservativeRasterEnable(NVNboolean enable)
{
    pfncpp_nvnCommandBufferSetConservativeRasterEnable(this, enable);
}

inline void CommandBuffer::SetConservativeRasterDilate(float dilate)
{
    pfncpp_nvnCommandBufferSetConservativeRasterDilate(this, dilate);
}

inline void CommandBuffer::SetSubpixelPrecisionBias(int xBits, int yBits)
{
    pfncpp_nvnCommandBufferSetSubpixelPrecisionBias(this, xBits, yBits);
}

inline void CommandBuffer::CopyBufferToTexture(BufferAddress src, const Texture *dstTexture, NVN_NOESCAPE const TextureView *dstView, NVN_NOESCAPE const CopyRegion *dstRegion, CopyFlags flags)
{
    pfncpp_nvnCommandBufferCopyBufferToTexture(this, src, dstTexture, dstView, dstRegion, flags);
}

inline void CommandBuffer::CopyTextureToBuffer(const Texture *srcTexture, NVN_NOESCAPE const TextureView *srcView, NVN_NOESCAPE const CopyRegion *srcRegion, BufferAddress dst, CopyFlags flags)
{
    pfncpp_nvnCommandBufferCopyTextureToBuffer(this, srcTexture, srcView, srcRegion, dst, flags);
}

inline void CommandBuffer::CopyTextureToTexture(const Texture *srcTexture, NVN_NOESCAPE const TextureView *srcView, NVN_NOESCAPE const CopyRegion *srcRegion, const Texture *dstTexture, NVN_NOESCAPE const TextureView *dstView, NVN_NOESCAPE const CopyRegion *dstRegion, CopyFlags flags)
{
    pfncpp_nvnCommandBufferCopyTextureToTexture(this, srcTexture, srcView, srcRegion, dstTexture, dstView, dstRegion, flags);
}

inline void CommandBuffer::CopyBufferToBuffer(BufferAddress src, BufferAddress dst, size_t size, CopyFlags flags)
{
    pfncpp_nvnCommandBufferCopyBufferToBuffer(this, src, dst, size, flags);
}

inline void CommandBuffer::ClearBuffer(BufferAddress dst, size_t size, uint32_t value)
{
    pfncpp_nvnCommandBufferClearBuffer(this, dst, size, value);
}

inline void CommandBuffer::ClearTexture(const Texture *dstTexture, NVN_NOESCAPE const TextureView *dstView, NVN_NOESCAPE const CopyRegion *dstRegion, NVN_NOESCAPE const float *color, ClearColorMask mask)
{
    pfncpp_nvnCommandBufferClearTexture(this, dstTexture, dstView, dstRegion, color, mask);
}

inline void CommandBuffer::ClearTexturei(const Texture *dstTexture, NVN_NOESCAPE const TextureView *dstView, NVN_NOESCAPE const CopyRegion *dstRegion, NVN_NOESCAPE const int *color, ClearColorMask mask)
{
    pfncpp_nvnCommandBufferClearTexturei(this, dstTexture, dstView, dstRegion, color, mask);
}

inline void CommandBuffer::ClearTextureui(const Texture *dstTexture, NVN_NOESCAPE const TextureView *dstView, NVN_NOESCAPE const CopyRegion *dstRegion, NVN_NOESCAPE const uint32_t *color, ClearColorMask mask)
{
    pfncpp_nvnCommandBufferClearTextureui(this, dstTexture, dstView, dstRegion, color, mask);
}

inline void CommandBuffer::UpdateUniformBuffer(BufferAddress buffer, size_t bufferSize, ptrdiff_t updateOffset, size_t updateSize, NVN_NOESCAPE const void *data)
{
#ifdef NVN_FORCE_FASTPATH
    UpdateUniformBuffer_fastpath(buffer, bufferSize, updateOffset, updateSize, data);
#else
    pfncpp_nvnCommandBufferUpdateUniformBuffer(this, buffer, bufferSize, updateOffset, updateSize, data);
#endif
}

inline void CommandBuffer::ReportCounter(CounterType counter, BufferAddress buffer)
{
    pfncpp_nvnCommandBufferReportCounter(this, counter, buffer);
}

inline void CommandBuffer::ResetCounter(CounterType counter)
{
    pfncpp_nvnCommandBufferResetCounter(this, counter);
}

inline void CommandBuffer::ReportValue(uint32_t value, BufferAddress buffer)
{
    pfncpp_nvnCommandBufferReportValue(this, value, buffer);
}

inline void CommandBuffer::SetRenderEnable(NVNboolean enable)
{
    pfncpp_nvnCommandBufferSetRenderEnable(this, enable);
}

inline void CommandBuffer::SetRenderEnableConditional(ConditionalRenderMode mode, BufferAddress counters)
{
    pfncpp_nvnCommandBufferSetRenderEnableConditional(this, mode, counters);
}

inline void CommandBuffer::SetRenderTargets(int numColors, NVN_NOESCAPE const Texture * const *colors, NVN_NOESCAPE const TextureView * const *colorViews, const Texture *depthStencil, NVN_NOESCAPE const TextureView *depthStencilView)
{
    pfncpp_nvnCommandBufferSetRenderTargets(this, numColors, colors, colorViews, depthStencil, depthStencilView);
}

inline void CommandBuffer::DiscardColor(int index)
{
    pfncpp_nvnCommandBufferDiscardColor(this, index);
}

inline void CommandBuffer::DiscardDepthStencil()
{
    pfncpp_nvnCommandBufferDiscardDepthStencil(this);
}

inline void CommandBuffer::Downsample(const Texture *src, const Texture *dst)
{
    pfncpp_nvnCommandBufferDownsample(this, src, dst);
}

inline void CommandBuffer::TiledDownsample(const Texture *src, const Texture *dst)
{
    pfncpp_nvnCommandBufferTiledDownsample(this, src, dst);
}

inline void CommandBuffer::DownsampleTextureView(const Texture *src, NVN_NOESCAPE const TextureView *srcView, const Texture *dst, NVN_NOESCAPE const TextureView *dstView)
{
    pfncpp_nvnCommandBufferDownsampleTextureView(this, src, srcView, dst, dstView);
}

inline void CommandBuffer::TiledDownsampleTextureView(const Texture *src, NVN_NOESCAPE const TextureView *srcView, const Texture *dst, NVN_NOESCAPE const TextureView *dstView)
{
    pfncpp_nvnCommandBufferTiledDownsampleTextureView(this, src, srcView, dst, dstView);
}

inline void CommandBuffer::Barrier(BarrierBits barrier)
{
    pfncpp_nvnCommandBufferBarrier(this, barrier);
}

inline void CommandBuffer::WaitSync(const Sync *sync)
{
    pfncpp_nvnCommandBufferWaitSync(this, sync);
}

inline void CommandBuffer::FenceSync(Sync *sync, SyncCondition condition, SyncFlagBits flags)
{
    pfncpp_nvnCommandBufferFenceSync(this, sync, condition, flags);
}

inline void CommandBuffer::SetTexturePool(const TexturePool *texturePool)
{
    pfncpp_nvnCommandBufferSetTexturePool(this, texturePool);
}

inline void CommandBuffer::SetSamplerPool(const SamplerPool *samplerPool)
{
    pfncpp_nvnCommandBufferSetSamplerPool(this, samplerPool);
}

inline void CommandBuffer::SetShaderScratchMemory(const MemoryPool *pool, ptrdiff_t offset, size_t size)
{
    pfncpp_nvnCommandBufferSetShaderScratchMemory(this, pool, offset, size);
}

inline void CommandBuffer::SaveZCullData(BufferAddress dst, size_t size)
{
    pfncpp_nvnCommandBufferSaveZCullData(this, dst, size);
}

inline void CommandBuffer::RestoreZCullData(BufferAddress src, size_t size)
{
    pfncpp_nvnCommandBufferRestoreZCullData(this, src, size);
}

inline void CommandBuffer::SetCopyRowStride(ptrdiff_t stride)
{
    pfncpp_nvnCommandBufferSetCopyRowStride(this, stride);
}

inline void CommandBuffer::SetCopyImageStride(ptrdiff_t stride)
{
    pfncpp_nvnCommandBufferSetCopyImageStride(this, stride);
}

inline ptrdiff_t CommandBuffer::GetCopyRowStride() const
{
    return pfncpp_nvnCommandBufferGetCopyRowStride(this);
}

inline ptrdiff_t CommandBuffer::GetCopyImageStride() const
{
    return pfncpp_nvnCommandBufferGetCopyImageStride(this);
}

inline void CommandBuffer::DrawTexture(TextureHandle texture, NVN_NOESCAPE const DrawTextureRegion *dstRegion, NVN_NOESCAPE const DrawTextureRegion *srcRegion)
{
    pfncpp_nvnCommandBufferDrawTexture(this, texture, dstRegion, srcRegion);
}

inline NVNboolean Program::SetSubroutineLinkage(int count, const NVNsubroutineLinkageMapPtr *linkageMapPtrs)
{
    return pfncpp_nvnProgramSetSubroutineLinkage(this, count, linkageMapPtrs);
}

inline void CommandBuffer::SetProgramSubroutines(Program *program, ShaderStage stage, const int first, const int count, NVN_NOESCAPE const int *values)
{
    pfncpp_nvnCommandBufferSetProgramSubroutines(this, program, stage, first, count, values);
}

inline void CommandBuffer::BindCoverageModulationTable(NVN_NOESCAPE const float *entries)
{
    pfncpp_nvnCommandBufferBindCoverageModulationTable(this, entries);
}

inline void CommandBuffer::ResolveDepthBuffer()
{
    pfncpp_nvnCommandBufferResolveDepthBuffer(this);
}

inline void CommandBuffer::SetColorReductionEnable(NVNboolean enable)
{
    pfncpp_nvnCommandBufferSetColorReductionEnable(this, enable);
}

inline void CommandBuffer::SetColorReductionThresholds(FormatClass formatClass, int thresholdConservative, int thresholdAggressive)
{
    pfncpp_nvnCommandBufferSetColorReductionThresholds(this, formatClass, thresholdConservative, thresholdAggressive);
}

inline void CommandBuffer::PushDebugGroupStatic(uint32_t domainId, const char * description)
{
    pfncpp_nvnCommandBufferPushDebugGroupStatic(this, domainId, description);
}

inline void CommandBuffer::PushDebugGroupDynamic(uint32_t domainId, NVN_NOESCAPE const char * description)
{
    pfncpp_nvnCommandBufferPushDebugGroupDynamic(this, domainId, description);
}

inline void CommandBuffer::PushDebugGroup(const char * description)
{
    pfncpp_nvnCommandBufferPushDebugGroup(this, description);
}

inline void CommandBuffer::PopDebugGroup()
{
    pfncpp_nvnCommandBufferPopDebugGroup(this);
}

inline void CommandBuffer::PopDebugGroupId(uint32_t domainId)
{
    pfncpp_nvnCommandBufferPopDebugGroupId(this, domainId);
}

inline void CommandBuffer::InsertDebugMarkerStatic(uint32_t domainId, const char * description)
{
    pfncpp_nvnCommandBufferInsertDebugMarkerStatic(this, domainId, description);
}

inline void CommandBuffer::InsertDebugMarkerDynamic(uint32_t domainId, NVN_NOESCAPE const char * description)
{
    pfncpp_nvnCommandBufferInsertDebugMarkerDynamic(this, domainId, description);
}

inline void CommandBuffer::InsertDebugMarker(const char * description)
{
    pfncpp_nvnCommandBufferInsertDebugMarker(this, description);
}

inline CommandBufferMemoryCallbackFunc CommandBuffer::GetMemoryCallback() const
{
    return pfncpp_nvnCommandBufferGetMemoryCallback(this);
}

inline void * CommandBuffer::GetMemoryCallbackData() const
{
    return pfncpp_nvnCommandBufferGetMemoryCallbackData(this);
}

inline NVNboolean CommandBuffer::IsRecording() const
{
    return pfncpp_nvnCommandBufferIsRecording(this);
}

inline NVNboolean Sync::Initialize(Device *device)
{
    return pfncpp_nvnSyncInitialize(this, device);
}

inline void Sync::Finalize()
{
    pfncpp_nvnSyncFinalize(this);
}

inline void Sync::SetDebugLabel(const char * label)
{
    pfncpp_nvnSyncSetDebugLabel(this, label);
}

inline void Queue::FenceSync(Sync *sync, SyncCondition condition, SyncFlagBits flags)
{
    pfncpp_nvnQueueFenceSync(this, sync, condition, flags);
}

inline SyncWaitResult Sync::Wait(uint64_t timeoutNs) const
{
    return pfncpp_nvnSyncWait(this, timeoutNs);
}

inline NVNboolean Queue::WaitSync(const Sync *sync)
{
    return pfncpp_nvnQueueWaitSync(this, sync);
}

inline NVNboolean Sync::InitializeFromFencedGLSync(Device *device, const void *glSync, SyncInteropStatus *status)
{
    return pfncpp_nvnSyncInitializeFromFencedGLSync(this, device, glSync, status);
}

inline SyncInteropStatus Sync::CreateGLSync(uint64_t *glSync) const
{
    return pfncpp_nvnSyncCreateGLSync(this, glSync);
}

inline EventBuilder & EventBuilder::SetDefaults()
{
    pfncpp_nvnEventBuilderSetDefaults(this);
    return *this;
}

inline EventBuilder & EventBuilder::SetStorage(const MemoryPool *pool, int64_t offset)
{
    pfncpp_nvnEventBuilderSetStorage(this, pool, offset);
    return *this;
}

inline const MemoryPool * EventBuilder::GetStorage(int64_t *offset) const
{
    return pfncpp_nvnEventBuilderGetStorage(this, offset);
}

inline const MemoryPool * EventBuilder::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnEventBuilderGetMemoryPool(this);
#endif
}

inline int64_t EventBuilder::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnEventBuilderGetMemoryOffset(this);
#endif
}

inline NVNboolean Event::Initialize(const EventBuilder *builder)
{
    return pfncpp_nvnEventInitialize(this, builder);
}

inline void Event::Finalize()
{
    pfncpp_nvnEventFinalize(this);
}

inline uint32_t Event::GetValue() const
{
    return pfncpp_nvnEventGetValue(this);
}

inline void Event::Signal(EventSignalMode mode, uint32_t value)
{
    pfncpp_nvnEventSignal(this, mode, value);
}

inline const MemoryPool * Event::GetMemoryPool() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryPool_fastpath();
#else
    return pfncpp_nvnEventGetMemoryPool(this);
#endif
}

inline int64_t Event::GetMemoryOffset() const
{
#ifdef NVN_FORCE_FASTPATH
    return GetMemoryOffset_fastpath();
#else
    return pfncpp_nvnEventGetMemoryOffset(this);
#endif
}

inline void CommandBuffer::WaitEvent(const Event *event, EventWaitMode waitMode, uint32_t value)
{
    pfncpp_nvnCommandBufferWaitEvent(this, event, waitMode, value);
}

inline void CommandBuffer::SignalEvent(const Event *event, EventSignalMode mode, EventSignalLocation location, EventSignalFlags flags, uint32_t value)
{
    pfncpp_nvnCommandBufferSignalEvent(this, event, mode, location, flags, value);
}

inline void CommandBuffer::SetStencilCullCriteria(StencilFunc func, int ref, int mask)
{
    pfncpp_nvnCommandBufferSetStencilCullCriteria(this, func, ref, mask);
}

inline void CommandBuffer::OverrideSubtileSize(NVNboolean override, int subtileSize)
{
    pfncpp_nvnCommandBufferOverrideSubtileSize(this, override, subtileSize);
}

inline NVNboolean CommandBuffer::InsertCheckpointStatic(const void *markerData, size_t markerDataSize)
{
    return pfncpp_nvnCommandBufferInsertCheckpointStatic(this, markerData, markerDataSize);
}

inline NVNboolean CommandBuffer::InsertCheckpointDynamic(NVN_NOESCAPE const void *markerData, size_t markerDataSize)
{
    return pfncpp_nvnCommandBufferInsertCheckpointDynamic(this, markerData, markerDataSize);
}

inline void CommandBuffer::SetZCullZF32CompressionEnable(NVNboolean enable)
{
    pfncpp_nvnCommandBufferSetZCullZF32CompressionEnable(this, enable);
}

inline NVNboolean Device::SetAutomaticCheckpointsEnable(NVNboolean enable)
{
    return pfncpp_nvnDeviceSetAutomaticCheckpointsEnable(this, enable);
}

inline NVNboolean Device::SetAutomaticCheckpointsMask(AutomaticCheckpointsMask mask)
{
    return pfncpp_nvnDeviceSetAutomaticCheckpointsMask(this, mask);
}

inline NVNboolean Device::SetAutomaticCheckpointsSamplingInterval(int interval)
{
    return pfncpp_nvnDeviceSetAutomaticCheckpointsSamplingInterval(this, interval);
}

inline NVNboolean Device::SetAutomaticCheckpointsByDebugGroup(uint32_t domainId, const char * debugGroupName)
{
    return pfncpp_nvnDeviceSetAutomaticCheckpointsByDebugGroup(this, domainId, debugGroupName);
}

inline NVNboolean Device::SetCheckpointCallStacksEnable(NVNboolean enable)
{
    return pfncpp_nvnDeviceSetCheckpointCallStacksEnable(this, enable);
}

inline NVNboolean Device::SetCheckpointMaxCallStacksDepth(int depth)
{
    return pfncpp_nvnDeviceSetCheckpointMaxCallStacksDepth(this, depth);
}


#ifdef NVN_OVERLOAD_CPP_OBJECTS
} /* namespace objects */
#endif
} /* namespace nvn */

#endif // __nvn_cppmethods_h_
