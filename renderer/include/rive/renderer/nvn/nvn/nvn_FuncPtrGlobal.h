


#ifndef __nvn_funcptrglobal_h_
#define __nvn_funcptrglobal_h_

#include "nvn.h"
#include "nvn_FuncPtr.h"
#include "nvn_Fastpath.h"

#ifndef NVN_DEPRECATED_PRE_MACRO
  #if defined(_MSC_VER)
    #define NVN_DEPRECATED_PRE_MACRO(x)    __pragma(deprecated(#x))
  #elif defined(__GNUC__) || defined(__clang__)
    #define NVN_DEPRECATED_PRE_MACRO(x)
  #else
    #error "Update NVN deprecation macros for this compiler."
  #endif
#endif
#ifndef NVN_DEPRECATED_MACRO_SUFFIX
  #if defined(_MSC_VER)
    #define NVN_DEPRECATED_MACRO_SUFFIX(x)
  #elif defined(__GNUC__) || defined(__clang__)
    #define NVN_DEPRECATED_MACRO_SUFFIX(x)   _Pragma(#x)
  #else
    #error "Update NVN deprecation macros for this compiler."
  #endif
#endif

#define nvnDeviceBuilderSetDefaults pfnc_nvnDeviceBuilderSetDefaults
#define nvnDeviceBuilderSetFlags pfnc_nvnDeviceBuilderSetFlags
#ifdef NVN_FORCE_FASTPATH
    #define nvnDeviceBuilderGetFlags nvnDeviceBuilderGetFlags_fastpath
#else
    #define nvnDeviceBuilderGetFlags pfnc_nvnDeviceBuilderGetFlags
#endif
#define nvnDeviceInitialize pfnc_nvnDeviceInitialize
#define nvnDeviceFinalize pfnc_nvnDeviceFinalize
#define nvnDeviceSetDebugLabel pfnc_nvnDeviceSetDebugLabel
#define nvnDeviceGetProcAddress pfnc_nvnDeviceGetProcAddress
#define nvnDeviceGetInteger pfnc_nvnDeviceGetInteger
#define nvnDeviceGetCurrentTimestampInNanoseconds pfnc_nvnDeviceGetCurrentTimestampInNanoseconds
#define nvnDeviceSetIntermediateShaderCache pfnc_nvnDeviceSetIntermediateShaderCache
#define nvnDeviceGetTextureHandle pfnc_nvnDeviceGetTextureHandle
#define nvnDeviceGetTexelFetchHandle pfnc_nvnDeviceGetTexelFetchHandle
#define nvnDeviceGetImageHandle pfnc_nvnDeviceGetImageHandle
#define nvnDeviceInstallDebugCallback pfnc_nvnDeviceInstallDebugCallback
#define nvnDeviceGenerateDebugDomainId pfnc_nvnDeviceGenerateDebugDomainId
#ifdef NVN_FORCE_FASTPATH
    #define nvnDeviceSetWindowOriginMode nvnDeviceSetWindowOriginMode_fastpath
#else
    #define nvnDeviceSetWindowOriginMode pfnc_nvnDeviceSetWindowOriginMode
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnDeviceSetDepthMode nvnDeviceSetDepthMode_fastpath
#else
    #define nvnDeviceSetDepthMode pfnc_nvnDeviceSetDepthMode
#endif
#define nvnDeviceRegisterFastClearColor pfnc_nvnDeviceRegisterFastClearColor
#define nvnDeviceRegisterFastClearColori pfnc_nvnDeviceRegisterFastClearColori
#define nvnDeviceRegisterFastClearColorui pfnc_nvnDeviceRegisterFastClearColorui
#define nvnDeviceRegisterFastClearDepth pfnc_nvnDeviceRegisterFastClearDepth
#ifdef NVN_FORCE_FASTPATH
    #define nvnDeviceGetWindowOriginMode nvnDeviceGetWindowOriginMode_fastpath
#else
    #define nvnDeviceGetWindowOriginMode pfnc_nvnDeviceGetWindowOriginMode
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnDeviceGetDepthMode nvnDeviceGetDepthMode_fastpath
#else
    #define nvnDeviceGetDepthMode pfnc_nvnDeviceGetDepthMode
#endif
#define nvnDeviceGetTimestampInNanoseconds pfnc_nvnDeviceGetTimestampInNanoseconds
#define nvnDeviceFinalizeCommandHandle pfnc_nvnDeviceFinalizeCommandHandle
#define nvnDeviceWalkDebugDatabase pfnc_nvnDeviceWalkDebugDatabase
#define nvnDeviceGetSeparateTextureHandle pfnc_nvnDeviceGetSeparateTextureHandle
#define nvnDeviceGetSeparateSamplerHandle pfnc_nvnDeviceGetSeparateSamplerHandle
#define nvnDeviceIsExternalDebuggerAttached pfnc_nvnDeviceIsExternalDebuggerAttached
#define nvnQueueGetError pfnc_nvnQueueGetError
#define nvnQueueGetTotalCommandMemoryUsed pfnc_nvnQueueGetTotalCommandMemoryUsed
#define nvnQueueGetTotalControlMemoryUsed pfnc_nvnQueueGetTotalControlMemoryUsed
#define nvnQueueGetTotalComputeMemoryUsed pfnc_nvnQueueGetTotalComputeMemoryUsed
#define nvnQueueResetMemoryUsageCounts pfnc_nvnQueueResetMemoryUsageCounts
#define nvnQueueBuilderSetDevice pfnc_nvnQueueBuilderSetDevice
#define nvnQueueBuilderSetDefaults pfnc_nvnQueueBuilderSetDefaults
#define nvnQueueBuilderSetFlags pfnc_nvnQueueBuilderSetFlags
#define nvnQueueBuilderSetCommandMemorySize pfnc_nvnQueueBuilderSetCommandMemorySize
#define nvnQueueBuilderSetComputeMemorySize pfnc_nvnQueueBuilderSetComputeMemorySize
#define nvnQueueBuilderSetControlMemorySize pfnc_nvnQueueBuilderSetControlMemorySize
#define nvnQueueBuilderGetQueueMemorySize pfnc_nvnQueueBuilderGetQueueMemorySize
#define nvnQueueBuilderSetQueueMemory pfnc_nvnQueueBuilderSetQueueMemory
#define nvnQueueBuilderSetCommandFlushThreshold pfnc_nvnQueueBuilderSetCommandFlushThreshold
#ifdef NVN_FORCE_FASTPATH
    #define nvnQueueBuilderSetQueuePriority nvnQueueBuilderSetQueuePriority_fastpath
#else
    #define nvnQueueBuilderSetQueuePriority pfnc_nvnQueueBuilderSetQueuePriority
#endif
#define nvnQueueBuilderGetQueuePriority pfnc_nvnQueueBuilderGetQueuePriority
#ifdef NVN_FORCE_FASTPATH
    #define nvnQueueBuilderGetDevice nvnQueueBuilderGetDevice_fastpath
#else
    #define nvnQueueBuilderGetDevice pfnc_nvnQueueBuilderGetDevice
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnQueueBuilderGetFlags nvnQueueBuilderGetFlags_fastpath
#else
    #define nvnQueueBuilderGetFlags pfnc_nvnQueueBuilderGetFlags
#endif
#define nvnQueueBuilderGetCommandMemorySize pfnc_nvnQueueBuilderGetCommandMemorySize
#define nvnQueueBuilderGetComputeMemorySize pfnc_nvnQueueBuilderGetComputeMemorySize
#define nvnQueueBuilderGetControlMemorySize pfnc_nvnQueueBuilderGetControlMemorySize
#define nvnQueueBuilderGetCommandFlushThreshold pfnc_nvnQueueBuilderGetCommandFlushThreshold
#define nvnQueueBuilderGetMemorySize pfnc_nvnQueueBuilderGetMemorySize
#ifdef NVN_FORCE_FASTPATH
    #define nvnQueueBuilderGetMemory nvnQueueBuilderGetMemory_fastpath
#else
    #define nvnQueueBuilderGetMemory pfnc_nvnQueueBuilderGetMemory
#endif
#define nvnQueueInitialize pfnc_nvnQueueInitialize
#define nvnQueueFinalize pfnc_nvnQueueFinalize
#define nvnQueueSetDebugLabel pfnc_nvnQueueSetDebugLabel
#define nvnQueueSubmitCommands pfnc_nvnQueueSubmitCommands
#define nvnQueueFlush pfnc_nvnQueueFlush
#define nvnQueueFinish pfnc_nvnQueueFinish
#define nvnQueuePresentTexture pfnc_nvnQueuePresentTexture
#define nvnWindowBuilderSetDevice pfnc_nvnWindowBuilderSetDevice
#define nvnWindowBuilderSetDefaults pfnc_nvnWindowBuilderSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderSetNativeWindow nvnWindowBuilderSetNativeWindow_fastpath
#else
    #define nvnWindowBuilderSetNativeWindow pfnc_nvnWindowBuilderSetNativeWindow
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderSetTextures nvnWindowBuilderSetTextures_fastpath
#else
    #define nvnWindowBuilderSetTextures pfnc_nvnWindowBuilderSetTextures
#endif
#define nvnWindowBuilderSetPresentInterval pfnc_nvnWindowBuilderSetPresentInterval
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderSetNumActiveTextures nvnWindowBuilderSetNumActiveTextures_fastpath
#else
    #define nvnWindowBuilderSetNumActiveTextures pfnc_nvnWindowBuilderSetNumActiveTextures
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderGetDevice nvnWindowBuilderGetDevice_fastpath
#else
    #define nvnWindowBuilderGetDevice pfnc_nvnWindowBuilderGetDevice
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderGetNumTextures nvnWindowBuilderGetNumTextures_fastpath
#else
    #define nvnWindowBuilderGetNumTextures pfnc_nvnWindowBuilderGetNumTextures
#endif
#define nvnWindowBuilderGetTexture pfnc_nvnWindowBuilderGetTexture
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderGetNativeWindow nvnWindowBuilderGetNativeWindow_fastpath
#else
    #define nvnWindowBuilderGetNativeWindow pfnc_nvnWindowBuilderGetNativeWindow
#endif
#define nvnWindowBuilderGetPresentInterval pfnc_nvnWindowBuilderGetPresentInterval
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowBuilderGetNumActiveTextures nvnWindowBuilderGetNumActiveTextures_fastpath
#else
    #define nvnWindowBuilderGetNumActiveTextures pfnc_nvnWindowBuilderGetNumActiveTextures
#endif
#define nvnWindowInitialize pfnc_nvnWindowInitialize
#define nvnWindowFinalize pfnc_nvnWindowFinalize
#define nvnWindowSetDebugLabel pfnc_nvnWindowSetDebugLabel
#define nvnWindowAcquireTexture pfnc_nvnWindowAcquireTexture
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowGetNativeWindow nvnWindowGetNativeWindow_fastpath
#else
    #define nvnWindowGetNativeWindow pfnc_nvnWindowGetNativeWindow
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowGetPresentInterval nvnWindowGetPresentInterval_fastpath
#else
    #define nvnWindowGetPresentInterval pfnc_nvnWindowGetPresentInterval
#endif
#define nvnWindowSetPresentInterval pfnc_nvnWindowSetPresentInterval
#define nvnWindowSetCrop pfnc_nvnWindowSetCrop
#define nvnWindowGetCrop pfnc_nvnWindowGetCrop
#define nvnWindowSetNumActiveTextures pfnc_nvnWindowSetNumActiveTextures
#define nvnWindowGetNumActiveTextures pfnc_nvnWindowGetNumActiveTextures
#ifdef NVN_FORCE_FASTPATH
    #define nvnWindowGetNumTextures nvnWindowGetNumTextures_fastpath
#else
    #define nvnWindowGetNumTextures pfnc_nvnWindowGetNumTextures
#endif
#define nvnProgramInitialize pfnc_nvnProgramInitialize
#define nvnProgramFinalize pfnc_nvnProgramFinalize
#define nvnProgramSetDebugLabel pfnc_nvnProgramSetDebugLabel
#define nvnProgramSetShaders pfnc_nvnProgramSetShaders
#define nvnProgramSetShadersExt pfnc_nvnProgramSetShadersExt
#define nvnProgramSetSampleShading pfnc_nvnProgramSetSampleShading
#ifdef NVN_FORCE_FASTPATH
    #define nvnProgramGetSubtileSize nvnProgramGetSubtileSize_fastpath
#else
    #define nvnProgramGetSubtileSize pfnc_nvnProgramGetSubtileSize
#endif
#define nvnMemoryPoolBuilderSetDevice pfnc_nvnMemoryPoolBuilderSetDevice
#define nvnMemoryPoolBuilderSetDefaults pfnc_nvnMemoryPoolBuilderSetDefaults
#define nvnMemoryPoolBuilderSetStorage pfnc_nvnMemoryPoolBuilderSetStorage
#define nvnMemoryPoolBuilderSetFlags pfnc_nvnMemoryPoolBuilderSetFlags
#ifdef NVN_FORCE_FASTPATH
    #define nvnMemoryPoolBuilderGetDevice nvnMemoryPoolBuilderGetDevice_fastpath
#else
    #define nvnMemoryPoolBuilderGetDevice pfnc_nvnMemoryPoolBuilderGetDevice
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMemoryPoolBuilderGetMemory nvnMemoryPoolBuilderGetMemory_fastpath
#else
    #define nvnMemoryPoolBuilderGetMemory pfnc_nvnMemoryPoolBuilderGetMemory
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMemoryPoolBuilderGetSize nvnMemoryPoolBuilderGetSize_fastpath
#else
    #define nvnMemoryPoolBuilderGetSize pfnc_nvnMemoryPoolBuilderGetSize
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMemoryPoolBuilderGetFlags nvnMemoryPoolBuilderGetFlags_fastpath
#else
    #define nvnMemoryPoolBuilderGetFlags pfnc_nvnMemoryPoolBuilderGetFlags
#endif
#define nvnMemoryPoolInitialize pfnc_nvnMemoryPoolInitialize
#define nvnMemoryPoolSetDebugLabel pfnc_nvnMemoryPoolSetDebugLabel
#define nvnMemoryPoolFinalize pfnc_nvnMemoryPoolFinalize
#define nvnMemoryPoolMap pfnc_nvnMemoryPoolMap
#define nvnMemoryPoolFlushMappedRange pfnc_nvnMemoryPoolFlushMappedRange
#define nvnMemoryPoolInvalidateMappedRange pfnc_nvnMemoryPoolInvalidateMappedRange
#define nvnMemoryPoolGetBufferAddress pfnc_nvnMemoryPoolGetBufferAddress
#define nvnMemoryPoolMapVirtual pfnc_nvnMemoryPoolMapVirtual
#define nvnMemoryPoolGetSize pfnc_nvnMemoryPoolGetSize
#define nvnMemoryPoolGetFlags pfnc_nvnMemoryPoolGetFlags
#define nvnTexturePoolInitialize pfnc_nvnTexturePoolInitialize
#define nvnTexturePoolSetDebugLabel pfnc_nvnTexturePoolSetDebugLabel
#define nvnTexturePoolFinalize pfnc_nvnTexturePoolFinalize
#define nvnTexturePoolRegisterTexture pfnc_nvnTexturePoolRegisterTexture
#define nvnTexturePoolRegisterImage pfnc_nvnTexturePoolRegisterImage
#ifdef NVN_FORCE_FASTPATH
    #define nvnTexturePoolGetMemoryPool nvnTexturePoolGetMemoryPool_fastpath
#else
    #define nvnTexturePoolGetMemoryPool pfnc_nvnTexturePoolGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTexturePoolGetMemoryOffset nvnTexturePoolGetMemoryOffset_fastpath
#else
    #define nvnTexturePoolGetMemoryOffset pfnc_nvnTexturePoolGetMemoryOffset
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTexturePoolGetSize nvnTexturePoolGetSize_fastpath
#else
    #define nvnTexturePoolGetSize pfnc_nvnTexturePoolGetSize
#endif
#define nvnSamplerPoolInitialize pfnc_nvnSamplerPoolInitialize
#define nvnSamplerPoolSetDebugLabel pfnc_nvnSamplerPoolSetDebugLabel
#define nvnSamplerPoolFinalize pfnc_nvnSamplerPoolFinalize
#define nvnSamplerPoolRegisterSampler pfnc_nvnSamplerPoolRegisterSampler
#define nvnSamplerPoolRegisterSamplerBuilder pfnc_nvnSamplerPoolRegisterSamplerBuilder
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerPoolGetMemoryPool nvnSamplerPoolGetMemoryPool_fastpath
#else
    #define nvnSamplerPoolGetMemoryPool pfnc_nvnSamplerPoolGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerPoolGetMemoryOffset nvnSamplerPoolGetMemoryOffset_fastpath
#else
    #define nvnSamplerPoolGetMemoryOffset pfnc_nvnSamplerPoolGetMemoryOffset
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerPoolGetSize nvnSamplerPoolGetSize_fastpath
#else
    #define nvnSamplerPoolGetSize pfnc_nvnSamplerPoolGetSize
#endif
#define nvnBufferBuilderSetDevice pfnc_nvnBufferBuilderSetDevice
#define nvnBufferBuilderSetDefaults pfnc_nvnBufferBuilderSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferBuilderSetStorage nvnBufferBuilderSetStorage_fastpath
#else
    #define nvnBufferBuilderSetStorage pfnc_nvnBufferBuilderSetStorage
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferBuilderGetDevice nvnBufferBuilderGetDevice_fastpath
#else
    #define nvnBufferBuilderGetDevice pfnc_nvnBufferBuilderGetDevice
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferBuilderGetMemoryPool nvnBufferBuilderGetMemoryPool_fastpath
#else
    #define nvnBufferBuilderGetMemoryPool pfnc_nvnBufferBuilderGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferBuilderGetMemoryOffset nvnBufferBuilderGetMemoryOffset_fastpath
#else
    #define nvnBufferBuilderGetMemoryOffset pfnc_nvnBufferBuilderGetMemoryOffset
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferBuilderGetSize nvnBufferBuilderGetSize_fastpath
#else
    #define nvnBufferBuilderGetSize pfnc_nvnBufferBuilderGetSize
#endif
#define nvnBufferInitialize pfnc_nvnBufferInitialize
#define nvnBufferSetDebugLabel pfnc_nvnBufferSetDebugLabel
#define nvnBufferFinalize pfnc_nvnBufferFinalize
#define nvnBufferMap pfnc_nvnBufferMap
#define nvnBufferGetAddress pfnc_nvnBufferGetAddress
#define nvnBufferFlushMappedRange pfnc_nvnBufferFlushMappedRange
#define nvnBufferInvalidateMappedRange pfnc_nvnBufferInvalidateMappedRange
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferGetMemoryPool nvnBufferGetMemoryPool_fastpath
#else
    #define nvnBufferGetMemoryPool pfnc_nvnBufferGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferGetMemoryOffset nvnBufferGetMemoryOffset_fastpath
#else
    #define nvnBufferGetMemoryOffset pfnc_nvnBufferGetMemoryOffset
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBufferGetSize nvnBufferGetSize_fastpath
#else
    #define nvnBufferGetSize pfnc_nvnBufferGetSize
#endif
#define nvnBufferGetDebugID pfnc_nvnBufferGetDebugID
#define nvnTextureBuilderSetDevice pfnc_nvnTextureBuilderSetDevice
#define nvnTextureBuilderSetDefaults pfnc_nvnTextureBuilderSetDefaults
#define nvnTextureBuilderSetFlags pfnc_nvnTextureBuilderSetFlags
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetTarget nvnTextureBuilderSetTarget_fastpath
#else
    #define nvnTextureBuilderSetTarget pfnc_nvnTextureBuilderSetTarget
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetWidth nvnTextureBuilderSetWidth_fastpath
#else
    #define nvnTextureBuilderSetWidth pfnc_nvnTextureBuilderSetWidth
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetHeight nvnTextureBuilderSetHeight_fastpath
#else
    #define nvnTextureBuilderSetHeight pfnc_nvnTextureBuilderSetHeight
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetDepth nvnTextureBuilderSetDepth_fastpath
#else
    #define nvnTextureBuilderSetDepth pfnc_nvnTextureBuilderSetDepth
#endif
#define nvnTextureBuilderSetSize1D pfnc_nvnTextureBuilderSetSize1D
#define nvnTextureBuilderSetSize2D pfnc_nvnTextureBuilderSetSize2D
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetSize3D nvnTextureBuilderSetSize3D_fastpath
#else
    #define nvnTextureBuilderSetSize3D pfnc_nvnTextureBuilderSetSize3D
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetLevels nvnTextureBuilderSetLevels_fastpath
#else
    #define nvnTextureBuilderSetLevels pfnc_nvnTextureBuilderSetLevels
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetFormat nvnTextureBuilderSetFormat_fastpath
#else
    #define nvnTextureBuilderSetFormat pfnc_nvnTextureBuilderSetFormat
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetSamples nvnTextureBuilderSetSamples_fastpath
#else
    #define nvnTextureBuilderSetSamples pfnc_nvnTextureBuilderSetSamples
#endif
#define nvnTextureBuilderSetSwizzle pfnc_nvnTextureBuilderSetSwizzle
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetDepthStencilMode nvnTextureBuilderSetDepthStencilMode_fastpath
#else
    #define nvnTextureBuilderSetDepthStencilMode pfnc_nvnTextureBuilderSetDepthStencilMode
#endif
#define nvnTextureBuilderGetStorageSize pfnc_nvnTextureBuilderGetStorageSize
#define nvnTextureBuilderGetStorageAlignment pfnc_nvnTextureBuilderGetStorageAlignment
#define nvnTextureBuilderGetViewOffset pfnc_nvnTextureBuilderGetViewOffset
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderSetStorage nvnTextureBuilderSetStorage_fastpath
#else
    #define nvnTextureBuilderSetStorage pfnc_nvnTextureBuilderSetStorage
#endif
#define nvnTextureBuilderSetPackagedTextureData pfnc_nvnTextureBuilderSetPackagedTextureData
#define nvnTextureBuilderSetPackagedTextureLayout pfnc_nvnTextureBuilderSetPackagedTextureLayout
#define nvnTextureBuilderSetStride pfnc_nvnTextureBuilderSetStride
#define nvnTextureBuilderSetGLTextureName pfnc_nvnTextureBuilderSetGLTextureName
#define nvnTextureBuilderGetStorageClass pfnc_nvnTextureBuilderGetStorageClass
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetDevice nvnTextureBuilderGetDevice_fastpath
#else
    #define nvnTextureBuilderGetDevice pfnc_nvnTextureBuilderGetDevice
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetFlags nvnTextureBuilderGetFlags_fastpath
#else
    #define nvnTextureBuilderGetFlags pfnc_nvnTextureBuilderGetFlags
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetTarget nvnTextureBuilderGetTarget_fastpath
#else
    #define nvnTextureBuilderGetTarget pfnc_nvnTextureBuilderGetTarget
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetWidth nvnTextureBuilderGetWidth_fastpath
#else
    #define nvnTextureBuilderGetWidth pfnc_nvnTextureBuilderGetWidth
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetHeight nvnTextureBuilderGetHeight_fastpath
#else
    #define nvnTextureBuilderGetHeight pfnc_nvnTextureBuilderGetHeight
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetDepth nvnTextureBuilderGetDepth_fastpath
#else
    #define nvnTextureBuilderGetDepth pfnc_nvnTextureBuilderGetDepth
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetLevels nvnTextureBuilderGetLevels_fastpath
#else
    #define nvnTextureBuilderGetLevels pfnc_nvnTextureBuilderGetLevels
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetFormat nvnTextureBuilderGetFormat_fastpath
#else
    #define nvnTextureBuilderGetFormat pfnc_nvnTextureBuilderGetFormat
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetSamples nvnTextureBuilderGetSamples_fastpath
#else
    #define nvnTextureBuilderGetSamples pfnc_nvnTextureBuilderGetSamples
#endif
#define nvnTextureBuilderGetSwizzle pfnc_nvnTextureBuilderGetSwizzle
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetDepthStencilMode nvnTextureBuilderGetDepthStencilMode_fastpath
#else
    #define nvnTextureBuilderGetDepthStencilMode pfnc_nvnTextureBuilderGetDepthStencilMode
#endif
#define nvnTextureBuilderGetPackagedTextureData pfnc_nvnTextureBuilderGetPackagedTextureData
#define nvnTextureBuilderGetPackagedTextureLayout pfnc_nvnTextureBuilderGetPackagedTextureLayout
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetStride nvnTextureBuilderGetStride_fastpath
#else
    #define nvnTextureBuilderGetStride pfnc_nvnTextureBuilderGetStride
#endif
#define nvnTextureBuilderGetSparseTileLayout pfnc_nvnTextureBuilderGetSparseTileLayout
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetGLTextureName nvnTextureBuilderGetGLTextureName_fastpath
#else
    #define nvnTextureBuilderGetGLTextureName pfnc_nvnTextureBuilderGetGLTextureName
#endif
#define nvnTextureBuilderGetZCullStorageSize pfnc_nvnTextureBuilderGetZCullStorageSize
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetMemoryPool nvnTextureBuilderGetMemoryPool_fastpath
#else
    #define nvnTextureBuilderGetMemoryPool pfnc_nvnTextureBuilderGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnTextureBuilderGetMemoryOffset nvnTextureBuilderGetMemoryOffset_fastpath
#else
    #define nvnTextureBuilderGetMemoryOffset pfnc_nvnTextureBuilderGetMemoryOffset
#endif
#define nvnTextureBuilderGetRawStorageClass pfnc_nvnTextureBuilderGetRawStorageClass
#define nvnTextureViewSetDefaults pfnc_nvnTextureViewSetDefaults
#define nvnTextureViewSetLevels pfnc_nvnTextureViewSetLevels
#define nvnTextureViewSetLayers pfnc_nvnTextureViewSetLayers
#define nvnTextureViewSetFormat pfnc_nvnTextureViewSetFormat
#define nvnTextureViewSetSwizzle pfnc_nvnTextureViewSetSwizzle
#define nvnTextureViewSetDepthStencilMode pfnc_nvnTextureViewSetDepthStencilMode
#define nvnTextureViewSetTarget pfnc_nvnTextureViewSetTarget
#define nvnTextureViewGetLevels pfnc_nvnTextureViewGetLevels
#define nvnTextureViewGetLayers pfnc_nvnTextureViewGetLayers
#define nvnTextureViewGetFormat pfnc_nvnTextureViewGetFormat
#define nvnTextureViewGetSwizzle pfnc_nvnTextureViewGetSwizzle
#define nvnTextureViewGetDepthStencilMode pfnc_nvnTextureViewGetDepthStencilMode
#define nvnTextureViewGetTarget pfnc_nvnTextureViewGetTarget
#define nvnTextureViewCompare pfnc_nvnTextureViewCompare
#define nvnTextureInitialize pfnc_nvnTextureInitialize
#define nvnTextureGetZCullStorageSize pfnc_nvnTextureGetZCullStorageSize
#define nvnTextureFinalize pfnc_nvnTextureFinalize
#define nvnTextureSetDebugLabel pfnc_nvnTextureSetDebugLabel
#define nvnTextureGetStorageClass pfnc_nvnTextureGetStorageClass
#define nvnTextureGetViewOffset pfnc_nvnTextureGetViewOffset
#define nvnTextureGetFlags pfnc_nvnTextureGetFlags
#define nvnTextureGetTarget pfnc_nvnTextureGetTarget
#define nvnTextureGetWidth pfnc_nvnTextureGetWidth
#define nvnTextureGetHeight pfnc_nvnTextureGetHeight
#define nvnTextureGetDepth pfnc_nvnTextureGetDepth
#define nvnTextureGetLevels pfnc_nvnTextureGetLevels
#define nvnTextureGetFormat pfnc_nvnTextureGetFormat
#define nvnTextureGetSamples pfnc_nvnTextureGetSamples
#define nvnTextureGetSwizzle pfnc_nvnTextureGetSwizzle
#define nvnTextureGetDepthStencilMode pfnc_nvnTextureGetDepthStencilMode
#define nvnTextureGetStride pfnc_nvnTextureGetStride
#define nvnTextureGetTextureAddress pfnc_nvnTextureGetTextureAddress
#define nvnTextureGetSparseTileLayout pfnc_nvnTextureGetSparseTileLayout
#define nvnTextureWriteTexels pfnc_nvnTextureWriteTexels
#define nvnTextureWriteTexelsStrided pfnc_nvnTextureWriteTexelsStrided
#define nvnTextureReadTexels pfnc_nvnTextureReadTexels
#define nvnTextureReadTexelsStrided pfnc_nvnTextureReadTexelsStrided
#define nvnTextureFlushTexels pfnc_nvnTextureFlushTexels
#define nvnTextureInvalidateTexels pfnc_nvnTextureInvalidateTexels
#define nvnTextureGetMemoryPool pfnc_nvnTextureGetMemoryPool
#define nvnTextureGetMemoryOffset pfnc_nvnTextureGetMemoryOffset
#define nvnTextureGetStorageSize pfnc_nvnTextureGetStorageSize
#define nvnTextureCompare pfnc_nvnTextureCompare
#define nvnTextureGetDebugID pfnc_nvnTextureGetDebugID
#define nvnTextureGetRawStorageClass pfnc_nvnTextureGetRawStorageClass
#define nvnSamplerBuilderSetDevice pfnc_nvnSamplerBuilderSetDevice
#define nvnSamplerBuilderSetDefaults pfnc_nvnSamplerBuilderSetDefaults
#define nvnSamplerBuilderSetMinMagFilter pfnc_nvnSamplerBuilderSetMinMagFilter
#define nvnSamplerBuilderSetWrapMode pfnc_nvnSamplerBuilderSetWrapMode
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderSetLodClamp nvnSamplerBuilderSetLodClamp_fastpath
#else
    #define nvnSamplerBuilderSetLodClamp pfnc_nvnSamplerBuilderSetLodClamp
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderSetLodBias nvnSamplerBuilderSetLodBias_fastpath
#else
    #define nvnSamplerBuilderSetLodBias pfnc_nvnSamplerBuilderSetLodBias
#endif
#define nvnSamplerBuilderSetCompare pfnc_nvnSamplerBuilderSetCompare
#define nvnSamplerBuilderSetBorderColor pfnc_nvnSamplerBuilderSetBorderColor
#define nvnSamplerBuilderSetBorderColori pfnc_nvnSamplerBuilderSetBorderColori
#define nvnSamplerBuilderSetBorderColorui pfnc_nvnSamplerBuilderSetBorderColorui
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderSetMaxAnisotropy nvnSamplerBuilderSetMaxAnisotropy_fastpath
#else
    #define nvnSamplerBuilderSetMaxAnisotropy pfnc_nvnSamplerBuilderSetMaxAnisotropy
#endif
#define nvnSamplerBuilderSetReductionFilter pfnc_nvnSamplerBuilderSetReductionFilter
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderSetLodSnap nvnSamplerBuilderSetLodSnap_fastpath
#else
    #define nvnSamplerBuilderSetLodSnap pfnc_nvnSamplerBuilderSetLodSnap
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderGetDevice nvnSamplerBuilderGetDevice_fastpath
#else
    #define nvnSamplerBuilderGetDevice pfnc_nvnSamplerBuilderGetDevice
#endif
#define nvnSamplerBuilderGetMinMagFilter pfnc_nvnSamplerBuilderGetMinMagFilter
#define nvnSamplerBuilderGetWrapMode pfnc_nvnSamplerBuilderGetWrapMode
#define nvnSamplerBuilderGetLodClamp pfnc_nvnSamplerBuilderGetLodClamp
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderGetLodBias nvnSamplerBuilderGetLodBias_fastpath
#else
    #define nvnSamplerBuilderGetLodBias pfnc_nvnSamplerBuilderGetLodBias
#endif
#define nvnSamplerBuilderGetCompare pfnc_nvnSamplerBuilderGetCompare
#define nvnSamplerBuilderGetBorderColor pfnc_nvnSamplerBuilderGetBorderColor
#define nvnSamplerBuilderGetBorderColori pfnc_nvnSamplerBuilderGetBorderColori
#define nvnSamplerBuilderGetBorderColorui pfnc_nvnSamplerBuilderGetBorderColorui
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderGetMaxAnisotropy nvnSamplerBuilderGetMaxAnisotropy_fastpath
#else
    #define nvnSamplerBuilderGetMaxAnisotropy pfnc_nvnSamplerBuilderGetMaxAnisotropy
#endif
#define nvnSamplerBuilderGetReductionFilter pfnc_nvnSamplerBuilderGetReductionFilter
#ifdef NVN_FORCE_FASTPATH
    #define nvnSamplerBuilderGetLodSnap nvnSamplerBuilderGetLodSnap_fastpath
#else
    #define nvnSamplerBuilderGetLodSnap pfnc_nvnSamplerBuilderGetLodSnap
#endif
#define nvnSamplerInitialize pfnc_nvnSamplerInitialize
#define nvnSamplerFinalize pfnc_nvnSamplerFinalize
#define nvnSamplerSetDebugLabel pfnc_nvnSamplerSetDebugLabel
#define nvnSamplerGetMinMagFilter pfnc_nvnSamplerGetMinMagFilter
#define nvnSamplerGetWrapMode pfnc_nvnSamplerGetWrapMode
#define nvnSamplerGetLodClamp pfnc_nvnSamplerGetLodClamp
#define nvnSamplerGetLodBias pfnc_nvnSamplerGetLodBias
#define nvnSamplerGetCompare pfnc_nvnSamplerGetCompare
#define nvnSamplerGetBorderColor pfnc_nvnSamplerGetBorderColor
#define nvnSamplerGetBorderColori pfnc_nvnSamplerGetBorderColori
#define nvnSamplerGetBorderColorui pfnc_nvnSamplerGetBorderColorui
#define nvnSamplerGetMaxAnisotropy pfnc_nvnSamplerGetMaxAnisotropy
#define nvnSamplerGetReductionFilter pfnc_nvnSamplerGetReductionFilter
#define nvnSamplerCompare pfnc_nvnSamplerCompare
#define nvnSamplerGetDebugID pfnc_nvnSamplerGetDebugID
#define nvnBlendStateSetDefaults pfnc_nvnBlendStateSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetBlendTarget nvnBlendStateSetBlendTarget_fastpath
#else
    #define nvnBlendStateSetBlendTarget pfnc_nvnBlendStateSetBlendTarget
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetBlendFunc nvnBlendStateSetBlendFunc_fastpath
#else
    #define nvnBlendStateSetBlendFunc pfnc_nvnBlendStateSetBlendFunc
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetBlendEquation nvnBlendStateSetBlendEquation_fastpath
#else
    #define nvnBlendStateSetBlendEquation pfnc_nvnBlendStateSetBlendEquation
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetAdvancedMode nvnBlendStateSetAdvancedMode_fastpath
#else
    #define nvnBlendStateSetAdvancedMode pfnc_nvnBlendStateSetAdvancedMode
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetAdvancedOverlap nvnBlendStateSetAdvancedOverlap_fastpath
#else
    #define nvnBlendStateSetAdvancedOverlap pfnc_nvnBlendStateSetAdvancedOverlap
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetAdvancedPremultipliedSrc nvnBlendStateSetAdvancedPremultipliedSrc_fastpath
#else
    #define nvnBlendStateSetAdvancedPremultipliedSrc pfnc_nvnBlendStateSetAdvancedPremultipliedSrc
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateSetAdvancedNormalizedDst nvnBlendStateSetAdvancedNormalizedDst_fastpath
#else
    #define nvnBlendStateSetAdvancedNormalizedDst pfnc_nvnBlendStateSetAdvancedNormalizedDst
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateGetBlendTarget nvnBlendStateGetBlendTarget_fastpath
#else
    #define nvnBlendStateGetBlendTarget pfnc_nvnBlendStateGetBlendTarget
#endif
#define nvnBlendStateGetBlendFunc pfnc_nvnBlendStateGetBlendFunc
#define nvnBlendStateGetBlendEquation pfnc_nvnBlendStateGetBlendEquation
#define nvnBlendStateGetAdvancedMode pfnc_nvnBlendStateGetAdvancedMode
#define nvnBlendStateGetAdvancedOverlap pfnc_nvnBlendStateGetAdvancedOverlap
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateGetAdvancedPremultipliedSrc nvnBlendStateGetAdvancedPremultipliedSrc_fastpath
#else
    #define nvnBlendStateGetAdvancedPremultipliedSrc pfnc_nvnBlendStateGetAdvancedPremultipliedSrc
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnBlendStateGetAdvancedNormalizedDst nvnBlendStateGetAdvancedNormalizedDst_fastpath
#else
    #define nvnBlendStateGetAdvancedNormalizedDst pfnc_nvnBlendStateGetAdvancedNormalizedDst
#endif
#define nvnColorStateSetDefaults pfnc_nvnColorStateSetDefaults
#define nvnColorStateSetBlendEnable pfnc_nvnColorStateSetBlendEnable
#ifdef NVN_FORCE_FASTPATH
    #define nvnColorStateSetLogicOp nvnColorStateSetLogicOp_fastpath
#else
    #define nvnColorStateSetLogicOp pfnc_nvnColorStateSetLogicOp
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnColorStateSetAlphaTest nvnColorStateSetAlphaTest_fastpath
#else
    #define nvnColorStateSetAlphaTest pfnc_nvnColorStateSetAlphaTest
#endif
#define nvnColorStateGetBlendEnable pfnc_nvnColorStateGetBlendEnable
#define nvnColorStateGetLogicOp pfnc_nvnColorStateGetLogicOp
#define nvnColorStateGetAlphaTest pfnc_nvnColorStateGetAlphaTest
#define nvnChannelMaskStateSetDefaults pfnc_nvnChannelMaskStateSetDefaults
#define nvnChannelMaskStateSetChannelMask pfnc_nvnChannelMaskStateSetChannelMask
#define nvnChannelMaskStateGetChannelMask pfnc_nvnChannelMaskStateGetChannelMask
#define nvnMultisampleStateSetDefaults pfnc_nvnMultisampleStateSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetMultisampleEnable nvnMultisampleStateSetMultisampleEnable_fastpath
#else
    #define nvnMultisampleStateSetMultisampleEnable pfnc_nvnMultisampleStateSetMultisampleEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetSamples nvnMultisampleStateSetSamples_fastpath
#else
    #define nvnMultisampleStateSetSamples pfnc_nvnMultisampleStateSetSamples
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetAlphaToCoverageEnable nvnMultisampleStateSetAlphaToCoverageEnable_fastpath
#else
    #define nvnMultisampleStateSetAlphaToCoverageEnable pfnc_nvnMultisampleStateSetAlphaToCoverageEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetAlphaToCoverageDither nvnMultisampleStateSetAlphaToCoverageDither_fastpath
#else
    #define nvnMultisampleStateSetAlphaToCoverageDither pfnc_nvnMultisampleStateSetAlphaToCoverageDither
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetMultisampleEnable nvnMultisampleStateGetMultisampleEnable_fastpath
#else
    #define nvnMultisampleStateGetMultisampleEnable pfnc_nvnMultisampleStateGetMultisampleEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetSamples nvnMultisampleStateGetSamples_fastpath
#else
    #define nvnMultisampleStateGetSamples pfnc_nvnMultisampleStateGetSamples
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetAlphaToCoverageEnable nvnMultisampleStateGetAlphaToCoverageEnable_fastpath
#else
    #define nvnMultisampleStateGetAlphaToCoverageEnable pfnc_nvnMultisampleStateGetAlphaToCoverageEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetAlphaToCoverageDither nvnMultisampleStateGetAlphaToCoverageDither_fastpath
#else
    #define nvnMultisampleStateGetAlphaToCoverageDither pfnc_nvnMultisampleStateGetAlphaToCoverageDither
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetRasterSamples nvnMultisampleStateSetRasterSamples_fastpath
#else
    #define nvnMultisampleStateSetRasterSamples pfnc_nvnMultisampleStateSetRasterSamples
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetRasterSamples nvnMultisampleStateGetRasterSamples_fastpath
#else
    #define nvnMultisampleStateGetRasterSamples pfnc_nvnMultisampleStateGetRasterSamples
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetCoverageModulationMode nvnMultisampleStateSetCoverageModulationMode_fastpath
#else
    #define nvnMultisampleStateSetCoverageModulationMode pfnc_nvnMultisampleStateSetCoverageModulationMode
#endif
#define nvnMultisampleStateGetCoverageModulationMode pfnc_nvnMultisampleStateGetCoverageModulationMode
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetCoverageToColorEnable nvnMultisampleStateSetCoverageToColorEnable_fastpath
#else
    #define nvnMultisampleStateSetCoverageToColorEnable pfnc_nvnMultisampleStateSetCoverageToColorEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetCoverageToColorEnable nvnMultisampleStateGetCoverageToColorEnable_fastpath
#else
    #define nvnMultisampleStateGetCoverageToColorEnable pfnc_nvnMultisampleStateGetCoverageToColorEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetCoverageToColorOutput nvnMultisampleStateSetCoverageToColorOutput_fastpath
#else
    #define nvnMultisampleStateSetCoverageToColorOutput pfnc_nvnMultisampleStateSetCoverageToColorOutput
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetCoverageToColorOutput nvnMultisampleStateGetCoverageToColorOutput_fastpath
#else
    #define nvnMultisampleStateGetCoverageToColorOutput pfnc_nvnMultisampleStateGetCoverageToColorOutput
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetSampleLocationsEnable nvnMultisampleStateSetSampleLocationsEnable_fastpath
#else
    #define nvnMultisampleStateSetSampleLocationsEnable pfnc_nvnMultisampleStateSetSampleLocationsEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetSampleLocationsEnable nvnMultisampleStateGetSampleLocationsEnable_fastpath
#else
    #define nvnMultisampleStateGetSampleLocationsEnable pfnc_nvnMultisampleStateGetSampleLocationsEnable
#endif
#define nvnMultisampleStateGetSampleLocationsGrid pfnc_nvnMultisampleStateGetSampleLocationsGrid
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateSetSampleLocationsGridEnable nvnMultisampleStateSetSampleLocationsGridEnable_fastpath
#else
    #define nvnMultisampleStateSetSampleLocationsGridEnable pfnc_nvnMultisampleStateSetSampleLocationsGridEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnMultisampleStateGetSampleLocationsGridEnable nvnMultisampleStateGetSampleLocationsGridEnable_fastpath
#else
    #define nvnMultisampleStateGetSampleLocationsGridEnable pfnc_nvnMultisampleStateGetSampleLocationsGridEnable
#endif
#define nvnMultisampleStateSetSampleLocations pfnc_nvnMultisampleStateSetSampleLocations
#define nvnPolygonStateSetDefaults pfnc_nvnPolygonStateSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnPolygonStateSetCullFace nvnPolygonStateSetCullFace_fastpath
#else
    #define nvnPolygonStateSetCullFace pfnc_nvnPolygonStateSetCullFace
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnPolygonStateSetFrontFace nvnPolygonStateSetFrontFace_fastpath
#else
    #define nvnPolygonStateSetFrontFace pfnc_nvnPolygonStateSetFrontFace
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnPolygonStateSetPolygonMode nvnPolygonStateSetPolygonMode_fastpath
#else
    #define nvnPolygonStateSetPolygonMode pfnc_nvnPolygonStateSetPolygonMode
#endif
#define nvnPolygonStateSetPolygonOffsetEnables pfnc_nvnPolygonStateSetPolygonOffsetEnables
#define nvnPolygonStateGetCullFace pfnc_nvnPolygonStateGetCullFace
#define nvnPolygonStateGetFrontFace pfnc_nvnPolygonStateGetFrontFace
#define nvnPolygonStateGetPolygonMode pfnc_nvnPolygonStateGetPolygonMode
#define nvnPolygonStateGetPolygonOffsetEnables pfnc_nvnPolygonStateGetPolygonOffsetEnables
#define nvnDepthStencilStateSetDefaults pfnc_nvnDepthStencilStateSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateSetDepthTestEnable nvnDepthStencilStateSetDepthTestEnable_fastpath
#else
    #define nvnDepthStencilStateSetDepthTestEnable pfnc_nvnDepthStencilStateSetDepthTestEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateSetDepthWriteEnable nvnDepthStencilStateSetDepthWriteEnable_fastpath
#else
    #define nvnDepthStencilStateSetDepthWriteEnable pfnc_nvnDepthStencilStateSetDepthWriteEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateSetDepthFunc nvnDepthStencilStateSetDepthFunc_fastpath
#else
    #define nvnDepthStencilStateSetDepthFunc pfnc_nvnDepthStencilStateSetDepthFunc
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateSetStencilTestEnable nvnDepthStencilStateSetStencilTestEnable_fastpath
#else
    #define nvnDepthStencilStateSetStencilTestEnable pfnc_nvnDepthStencilStateSetStencilTestEnable
#endif
#define nvnDepthStencilStateSetStencilFunc pfnc_nvnDepthStencilStateSetStencilFunc
#define nvnDepthStencilStateSetStencilOp pfnc_nvnDepthStencilStateSetStencilOp
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateGetDepthTestEnable nvnDepthStencilStateGetDepthTestEnable_fastpath
#else
    #define nvnDepthStencilStateGetDepthTestEnable pfnc_nvnDepthStencilStateGetDepthTestEnable
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateGetDepthWriteEnable nvnDepthStencilStateGetDepthWriteEnable_fastpath
#else
    #define nvnDepthStencilStateGetDepthWriteEnable pfnc_nvnDepthStencilStateGetDepthWriteEnable
#endif
#define nvnDepthStencilStateGetDepthFunc pfnc_nvnDepthStencilStateGetDepthFunc
#ifdef NVN_FORCE_FASTPATH
    #define nvnDepthStencilStateGetStencilTestEnable nvnDepthStencilStateGetStencilTestEnable_fastpath
#else
    #define nvnDepthStencilStateGetStencilTestEnable pfnc_nvnDepthStencilStateGetStencilTestEnable
#endif
#define nvnDepthStencilStateGetStencilFunc pfnc_nvnDepthStencilStateGetStencilFunc
#define nvnDepthStencilStateGetStencilOp pfnc_nvnDepthStencilStateGetStencilOp
#define nvnVertexAttribStateSetDefaults pfnc_nvnVertexAttribStateSetDefaults
#define nvnVertexAttribStateSetFormat pfnc_nvnVertexAttribStateSetFormat
#ifdef NVN_FORCE_FASTPATH
    #define nvnVertexAttribStateSetStreamIndex nvnVertexAttribStateSetStreamIndex_fastpath
#else
    #define nvnVertexAttribStateSetStreamIndex pfnc_nvnVertexAttribStateSetStreamIndex
#endif
#define nvnVertexAttribStateGetFormat pfnc_nvnVertexAttribStateGetFormat
#ifdef NVN_FORCE_FASTPATH
    #define nvnVertexAttribStateGetStreamIndex nvnVertexAttribStateGetStreamIndex_fastpath
#else
    #define nvnVertexAttribStateGetStreamIndex pfnc_nvnVertexAttribStateGetStreamIndex
#endif
#define nvnVertexStreamStateSetDefaults pfnc_nvnVertexStreamStateSetDefaults
#ifdef NVN_FORCE_FASTPATH
    #define nvnVertexStreamStateSetStride nvnVertexStreamStateSetStride_fastpath
#else
    #define nvnVertexStreamStateSetStride pfnc_nvnVertexStreamStateSetStride
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnVertexStreamStateSetDivisor nvnVertexStreamStateSetDivisor_fastpath
#else
    #define nvnVertexStreamStateSetDivisor pfnc_nvnVertexStreamStateSetDivisor
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnVertexStreamStateGetStride nvnVertexStreamStateGetStride_fastpath
#else
    #define nvnVertexStreamStateGetStride pfnc_nvnVertexStreamStateGetStride
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnVertexStreamStateGetDivisor nvnVertexStreamStateGetDivisor_fastpath
#else
    #define nvnVertexStreamStateGetDivisor pfnc_nvnVertexStreamStateGetDivisor
#endif
#define nvnCommandBufferInitialize pfnc_nvnCommandBufferInitialize
#define nvnCommandBufferFinalize pfnc_nvnCommandBufferFinalize
#define nvnCommandBufferSetDebugLabel pfnc_nvnCommandBufferSetDebugLabel
#define nvnCommandBufferSetMemoryCallback pfnc_nvnCommandBufferSetMemoryCallback
#define nvnCommandBufferSetMemoryCallbackData pfnc_nvnCommandBufferSetMemoryCallbackData
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferSetCommandMemoryCallbackEnabled nvnCommandBufferSetCommandMemoryCallbackEnabled_fastpath
#else
    #define nvnCommandBufferSetCommandMemoryCallbackEnabled pfnc_nvnCommandBufferSetCommandMemoryCallbackEnabled
#endif
#define nvnCommandBufferAddCommandMemory pfnc_nvnCommandBufferAddCommandMemory
#define nvnCommandBufferAddControlMemory pfnc_nvnCommandBufferAddControlMemory
#define nvnCommandBufferGetCommandMemorySize pfnc_nvnCommandBufferGetCommandMemorySize
#define nvnCommandBufferGetCommandMemoryUsed pfnc_nvnCommandBufferGetCommandMemoryUsed
#define nvnCommandBufferGetCommandMemoryFree pfnc_nvnCommandBufferGetCommandMemoryFree
#define nvnCommandBufferGetControlMemorySize pfnc_nvnCommandBufferGetControlMemorySize
#define nvnCommandBufferGetControlMemoryUsed pfnc_nvnCommandBufferGetControlMemoryUsed
#define nvnCommandBufferGetControlMemoryFree pfnc_nvnCommandBufferGetControlMemoryFree
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBeginRecording nvnCommandBufferBeginRecording_fastpath
#else
    #define nvnCommandBufferBeginRecording pfnc_nvnCommandBufferBeginRecording
#endif
#define nvnCommandBufferEndRecording pfnc_nvnCommandBufferEndRecording
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferCallCommands nvnCommandBufferCallCommands_fastpath
#else
    #define nvnCommandBufferCallCommands pfnc_nvnCommandBufferCallCommands
#endif
#define nvnCommandBufferCopyCommands pfnc_nvnCommandBufferCopyCommands
#define nvnCommandBufferBindBlendState pfnc_nvnCommandBufferBindBlendState
#define nvnCommandBufferBindChannelMaskState pfnc_nvnCommandBufferBindChannelMaskState
#define nvnCommandBufferBindColorState pfnc_nvnCommandBufferBindColorState
#define nvnCommandBufferBindMultisampleState pfnc_nvnCommandBufferBindMultisampleState
#define nvnCommandBufferBindPolygonState pfnc_nvnCommandBufferBindPolygonState
#define nvnCommandBufferBindDepthStencilState pfnc_nvnCommandBufferBindDepthStencilState
#define nvnCommandBufferBindVertexAttribState pfnc_nvnCommandBufferBindVertexAttribState
#define nvnCommandBufferBindVertexStreamState pfnc_nvnCommandBufferBindVertexStreamState
#define nvnCommandBufferBindProgram pfnc_nvnCommandBufferBindProgram
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindVertexBuffer nvnCommandBufferBindVertexBuffer_fastpath
#else
    #define nvnCommandBufferBindVertexBuffer pfnc_nvnCommandBufferBindVertexBuffer
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindVertexBuffers nvnCommandBufferBindVertexBuffers_fastpath
#else
    #define nvnCommandBufferBindVertexBuffers pfnc_nvnCommandBufferBindVertexBuffers
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindUniformBuffer nvnCommandBufferBindUniformBuffer_fastpath
#else
    #define nvnCommandBufferBindUniformBuffer pfnc_nvnCommandBufferBindUniformBuffer
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindUniformBuffers nvnCommandBufferBindUniformBuffers_fastpath
#else
    #define nvnCommandBufferBindUniformBuffers pfnc_nvnCommandBufferBindUniformBuffers
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindUniformBuffersDeferred nvnCommandBufferBindUniformBuffersDeferred_fastpath
#else
    #define nvnCommandBufferBindUniformBuffersDeferred pfnc_nvnCommandBufferBindUniformBuffersDeferred
#endif
#define nvnCommandBufferBindTransformFeedbackBuffer pfnc_nvnCommandBufferBindTransformFeedbackBuffer
#define nvnCommandBufferBindTransformFeedbackBuffers pfnc_nvnCommandBufferBindTransformFeedbackBuffers
#define nvnCommandBufferBindStorageBuffer pfnc_nvnCommandBufferBindStorageBuffer
#define nvnCommandBufferBindStorageBuffers pfnc_nvnCommandBufferBindStorageBuffers
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindStorageBuffersDeferred nvnCommandBufferBindStorageBuffersDeferred_fastpath
#else
    #define nvnCommandBufferBindStorageBuffersDeferred pfnc_nvnCommandBufferBindStorageBuffersDeferred
#endif
#define nvnCommandBufferBindTexture pfnc_nvnCommandBufferBindTexture
#define nvnCommandBufferBindTextures pfnc_nvnCommandBufferBindTextures
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindTexturesDeferred nvnCommandBufferBindTexturesDeferred_fastpath
#else
    #define nvnCommandBufferBindTexturesDeferred pfnc_nvnCommandBufferBindTexturesDeferred
#endif
#define nvnCommandBufferBindImage pfnc_nvnCommandBufferBindImage
#define nvnCommandBufferBindImages pfnc_nvnCommandBufferBindImages
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindImagesDeferred nvnCommandBufferBindImagesDeferred_fastpath
#else
    #define nvnCommandBufferBindImagesDeferred pfnc_nvnCommandBufferBindImagesDeferred
#endif
#define nvnCommandBufferSetPatchSize pfnc_nvnCommandBufferSetPatchSize
#define nvnCommandBufferSetInnerTessellationLevels pfnc_nvnCommandBufferSetInnerTessellationLevels
#define nvnCommandBufferSetOuterTessellationLevels pfnc_nvnCommandBufferSetOuterTessellationLevels
#define nvnCommandBufferSetPrimitiveRestart pfnc_nvnCommandBufferSetPrimitiveRestart
#define nvnCommandBufferBeginTransformFeedback pfnc_nvnCommandBufferBeginTransformFeedback
#define nvnCommandBufferEndTransformFeedback pfnc_nvnCommandBufferEndTransformFeedback
#define nvnCommandBufferPauseTransformFeedback pfnc_nvnCommandBufferPauseTransformFeedback
#define nvnCommandBufferResumeTransformFeedback pfnc_nvnCommandBufferResumeTransformFeedback
#define nvnCommandBufferDrawTransformFeedback pfnc_nvnCommandBufferDrawTransformFeedback
#define nvnCommandBufferDrawArrays pfnc_nvnCommandBufferDrawArrays
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferDrawElements nvnCommandBufferDrawElements_fastpath
#else
    #define nvnCommandBufferDrawElements pfnc_nvnCommandBufferDrawElements
#endif
#define nvnCommandBufferDrawElementsBaseVertex pfnc_nvnCommandBufferDrawElementsBaseVertex
#define nvnCommandBufferDrawArraysInstanced pfnc_nvnCommandBufferDrawArraysInstanced
#define nvnCommandBufferDrawElementsInstanced pfnc_nvnCommandBufferDrawElementsInstanced
#define nvnCommandBufferDrawArraysIndirect pfnc_nvnCommandBufferDrawArraysIndirect
#define nvnCommandBufferDrawElementsIndirect pfnc_nvnCommandBufferDrawElementsIndirect
#define nvnCommandBufferMultiDrawArraysIndirectCount pfnc_nvnCommandBufferMultiDrawArraysIndirectCount
#define nvnCommandBufferMultiDrawElementsIndirectCount pfnc_nvnCommandBufferMultiDrawElementsIndirectCount
#define nvnCommandBufferClearColor pfnc_nvnCommandBufferClearColor
#define nvnCommandBufferClearColori pfnc_nvnCommandBufferClearColori
#define nvnCommandBufferClearColorui pfnc_nvnCommandBufferClearColorui
#define nvnCommandBufferClearDepthStencil pfnc_nvnCommandBufferClearDepthStencil
#define nvnCommandBufferDispatchCompute pfnc_nvnCommandBufferDispatchCompute
#define nvnCommandBufferDispatchComputeIndirect pfnc_nvnCommandBufferDispatchComputeIndirect
#define nvnCommandBufferSetViewport pfnc_nvnCommandBufferSetViewport
#define nvnCommandBufferSetViewports pfnc_nvnCommandBufferSetViewports
#define nvnCommandBufferSetViewportSwizzles pfnc_nvnCommandBufferSetViewportSwizzles
#define nvnCommandBufferSetScissor pfnc_nvnCommandBufferSetScissor
#define nvnCommandBufferSetScissors pfnc_nvnCommandBufferSetScissors
#define nvnCommandBufferSetDepthRange pfnc_nvnCommandBufferSetDepthRange
#define nvnCommandBufferSetDepthBounds pfnc_nvnCommandBufferSetDepthBounds
#define nvnCommandBufferSetDepthRanges pfnc_nvnCommandBufferSetDepthRanges
#define nvnCommandBufferSetTiledCacheAction pfnc_nvnCommandBufferSetTiledCacheAction
#define nvnCommandBufferSetTiledCacheTileSize pfnc_nvnCommandBufferSetTiledCacheTileSize
#define nvnCommandBufferBindSeparateTexture pfnc_nvnCommandBufferBindSeparateTexture
#define nvnCommandBufferBindSeparateSampler pfnc_nvnCommandBufferBindSeparateSampler
#define nvnCommandBufferBindSeparateTextures pfnc_nvnCommandBufferBindSeparateTextures
#define nvnCommandBufferBindSeparateSamplers pfnc_nvnCommandBufferBindSeparateSamplers
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindSeparateTexturesDeferred nvnCommandBufferBindSeparateTexturesDeferred_fastpath
#else
    #define nvnCommandBufferBindSeparateTexturesDeferred pfnc_nvnCommandBufferBindSeparateTexturesDeferred
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferBindSeparateSamplersDeferred nvnCommandBufferBindSeparateSamplersDeferred_fastpath
#else
    #define nvnCommandBufferBindSeparateSamplersDeferred pfnc_nvnCommandBufferBindSeparateSamplersDeferred
#endif
#define nvnCommandBufferSetStencilValueMask pfnc_nvnCommandBufferSetStencilValueMask
#define nvnCommandBufferSetStencilMask pfnc_nvnCommandBufferSetStencilMask
#define nvnCommandBufferSetStencilRef pfnc_nvnCommandBufferSetStencilRef
#define nvnCommandBufferSetBlendColor pfnc_nvnCommandBufferSetBlendColor
#define nvnCommandBufferSetPointSize pfnc_nvnCommandBufferSetPointSize
#define nvnCommandBufferSetLineWidth pfnc_nvnCommandBufferSetLineWidth
#define nvnCommandBufferSetPolygonOffsetClamp pfnc_nvnCommandBufferSetPolygonOffsetClamp
#define nvnCommandBufferSetAlphaRef pfnc_nvnCommandBufferSetAlphaRef
#define nvnCommandBufferSetSampleMask pfnc_nvnCommandBufferSetSampleMask
#define nvnCommandBufferSetRasterizerDiscard pfnc_nvnCommandBufferSetRasterizerDiscard
#define nvnCommandBufferSetDepthClamp pfnc_nvnCommandBufferSetDepthClamp
#define nvnCommandBufferSetConservativeRasterEnable pfnc_nvnCommandBufferSetConservativeRasterEnable
#define nvnCommandBufferSetConservativeRasterDilate pfnc_nvnCommandBufferSetConservativeRasterDilate
#define nvnCommandBufferSetSubpixelPrecisionBias pfnc_nvnCommandBufferSetSubpixelPrecisionBias
#define nvnCommandBufferCopyBufferToTexture pfnc_nvnCommandBufferCopyBufferToTexture
#define nvnCommandBufferCopyTextureToBuffer pfnc_nvnCommandBufferCopyTextureToBuffer
#define nvnCommandBufferCopyTextureToTexture pfnc_nvnCommandBufferCopyTextureToTexture
#define nvnCommandBufferCopyBufferToBuffer pfnc_nvnCommandBufferCopyBufferToBuffer
#define nvnCommandBufferClearBuffer pfnc_nvnCommandBufferClearBuffer
#define nvnCommandBufferClearTexture pfnc_nvnCommandBufferClearTexture
#define nvnCommandBufferClearTexturei pfnc_nvnCommandBufferClearTexturei
#define nvnCommandBufferClearTextureui pfnc_nvnCommandBufferClearTextureui
#ifdef NVN_FORCE_FASTPATH
    #define nvnCommandBufferUpdateUniformBuffer nvnCommandBufferUpdateUniformBuffer_fastpath
#else
    #define nvnCommandBufferUpdateUniformBuffer pfnc_nvnCommandBufferUpdateUniformBuffer
#endif
#define nvnCommandBufferReportCounter pfnc_nvnCommandBufferReportCounter
#define nvnCommandBufferResetCounter pfnc_nvnCommandBufferResetCounter
#define nvnCommandBufferReportValue pfnc_nvnCommandBufferReportValue
#define nvnCommandBufferSetRenderEnable pfnc_nvnCommandBufferSetRenderEnable
#define nvnCommandBufferSetRenderEnableConditional pfnc_nvnCommandBufferSetRenderEnableConditional
#define nvnCommandBufferSetRenderTargets pfnc_nvnCommandBufferSetRenderTargets
#define nvnCommandBufferDiscardColor pfnc_nvnCommandBufferDiscardColor
#define nvnCommandBufferDiscardDepthStencil pfnc_nvnCommandBufferDiscardDepthStencil
#define nvnCommandBufferDownsample pfnc_nvnCommandBufferDownsample
#define nvnCommandBufferTiledDownsample pfnc_nvnCommandBufferTiledDownsample
#define nvnCommandBufferDownsampleTextureView pfnc_nvnCommandBufferDownsampleTextureView
#define nvnCommandBufferTiledDownsampleTextureView pfnc_nvnCommandBufferTiledDownsampleTextureView
#define nvnCommandBufferBarrier pfnc_nvnCommandBufferBarrier
#define nvnCommandBufferWaitSync pfnc_nvnCommandBufferWaitSync
#define nvnCommandBufferFenceSync pfnc_nvnCommandBufferFenceSync
#define nvnCommandBufferSetTexturePool pfnc_nvnCommandBufferSetTexturePool
#define nvnCommandBufferSetSamplerPool pfnc_nvnCommandBufferSetSamplerPool
#define nvnCommandBufferSetShaderScratchMemory pfnc_nvnCommandBufferSetShaderScratchMemory
#define nvnCommandBufferSaveZCullData pfnc_nvnCommandBufferSaveZCullData
#define nvnCommandBufferRestoreZCullData pfnc_nvnCommandBufferRestoreZCullData
#define nvnCommandBufferSetCopyRowStride pfnc_nvnCommandBufferSetCopyRowStride
#define nvnCommandBufferSetCopyImageStride pfnc_nvnCommandBufferSetCopyImageStride
#define nvnCommandBufferGetCopyRowStride pfnc_nvnCommandBufferGetCopyRowStride
#define nvnCommandBufferGetCopyImageStride pfnc_nvnCommandBufferGetCopyImageStride
#define nvnCommandBufferDrawTexture pfnc_nvnCommandBufferDrawTexture
#define nvnProgramSetSubroutineLinkage pfnc_nvnProgramSetSubroutineLinkage
#define nvnCommandBufferSetProgramSubroutines pfnc_nvnCommandBufferSetProgramSubroutines
#define nvnCommandBufferBindCoverageModulationTable pfnc_nvnCommandBufferBindCoverageModulationTable
#define nvnCommandBufferResolveDepthBuffer pfnc_nvnCommandBufferResolveDepthBuffer
#define nvnCommandBufferSetColorReductionEnable pfnc_nvnCommandBufferSetColorReductionEnable
#define nvnCommandBufferSetColorReductionThresholds pfnc_nvnCommandBufferSetColorReductionThresholds
#define nvnCommandBufferPushDebugGroupStatic pfnc_nvnCommandBufferPushDebugGroupStatic
#define nvnCommandBufferPushDebugGroupDynamic pfnc_nvnCommandBufferPushDebugGroupDynamic
#define nvnCommandBufferPushDebugGroup pfnc_nvnCommandBufferPushDebugGroup
#define nvnCommandBufferPopDebugGroup pfnc_nvnCommandBufferPopDebugGroup
#define nvnCommandBufferPopDebugGroupId pfnc_nvnCommandBufferPopDebugGroupId
#define nvnCommandBufferInsertDebugMarkerStatic pfnc_nvnCommandBufferInsertDebugMarkerStatic
#define nvnCommandBufferInsertDebugMarkerDynamic pfnc_nvnCommandBufferInsertDebugMarkerDynamic
#define nvnCommandBufferInsertDebugMarker pfnc_nvnCommandBufferInsertDebugMarker
#define nvnCommandBufferGetMemoryCallback pfnc_nvnCommandBufferGetMemoryCallback
#define nvnCommandBufferGetMemoryCallbackData pfnc_nvnCommandBufferGetMemoryCallbackData
#define nvnCommandBufferIsRecording pfnc_nvnCommandBufferIsRecording
#define nvnSyncInitialize pfnc_nvnSyncInitialize
#define nvnSyncFinalize pfnc_nvnSyncFinalize
#define nvnSyncSetDebugLabel pfnc_nvnSyncSetDebugLabel
#define nvnQueueFenceSync pfnc_nvnQueueFenceSync
#define nvnSyncWait pfnc_nvnSyncWait
#define nvnQueueWaitSync pfnc_nvnQueueWaitSync
#define nvnSyncInitializeFromFencedGLSync pfnc_nvnSyncInitializeFromFencedGLSync
#define nvnSyncCreateGLSync pfnc_nvnSyncCreateGLSync
#define nvnEventBuilderSetDefaults pfnc_nvnEventBuilderSetDefaults
#define nvnEventBuilderSetStorage pfnc_nvnEventBuilderSetStorage
#define nvnEventBuilderGetStorage pfnc_nvnEventBuilderGetStorage
#ifdef NVN_FORCE_FASTPATH
    #define nvnEventBuilderGetMemoryPool nvnEventBuilderGetMemoryPool_fastpath
#else
    #define nvnEventBuilderGetMemoryPool pfnc_nvnEventBuilderGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnEventBuilderGetMemoryOffset nvnEventBuilderGetMemoryOffset_fastpath
#else
    #define nvnEventBuilderGetMemoryOffset pfnc_nvnEventBuilderGetMemoryOffset
#endif
#define nvnEventInitialize pfnc_nvnEventInitialize
#define nvnEventFinalize pfnc_nvnEventFinalize
#define nvnEventGetValue pfnc_nvnEventGetValue
#define nvnEventSignal pfnc_nvnEventSignal
#ifdef NVN_FORCE_FASTPATH
    #define nvnEventGetMemoryPool nvnEventGetMemoryPool_fastpath
#else
    #define nvnEventGetMemoryPool pfnc_nvnEventGetMemoryPool
#endif
#ifdef NVN_FORCE_FASTPATH
    #define nvnEventGetMemoryOffset nvnEventGetMemoryOffset_fastpath
#else
    #define nvnEventGetMemoryOffset pfnc_nvnEventGetMemoryOffset
#endif
#define nvnCommandBufferWaitEvent pfnc_nvnCommandBufferWaitEvent
#define nvnCommandBufferSignalEvent pfnc_nvnCommandBufferSignalEvent
#define nvnCommandBufferSetStencilCullCriteria pfnc_nvnCommandBufferSetStencilCullCriteria
#define nvnCommandBufferOverrideSubtileSize pfnc_nvnCommandBufferOverrideSubtileSize
#define nvnCommandBufferInsertCheckpointStatic pfnc_nvnCommandBufferInsertCheckpointStatic
#define nvnCommandBufferInsertCheckpointDynamic pfnc_nvnCommandBufferInsertCheckpointDynamic
#define nvnCommandBufferSetZCullZF32CompressionEnable pfnc_nvnCommandBufferSetZCullZF32CompressionEnable
#define nvnDeviceSetAutomaticCheckpointsEnable pfnc_nvnDeviceSetAutomaticCheckpointsEnable
#define nvnDeviceSetAutomaticCheckpointsMask pfnc_nvnDeviceSetAutomaticCheckpointsMask
#define nvnDeviceSetAutomaticCheckpointsSamplingInterval pfnc_nvnDeviceSetAutomaticCheckpointsSamplingInterval
#define nvnDeviceSetAutomaticCheckpointsByDebugGroup pfnc_nvnDeviceSetAutomaticCheckpointsByDebugGroup
#define nvnDeviceSetCheckpointCallStacksEnable pfnc_nvnDeviceSetCheckpointCallStacksEnable
#define nvnDeviceSetCheckpointMaxCallStacksDepth pfnc_nvnDeviceSetCheckpointMaxCallStacksDepth

#endif // __nvn_funcptrglobal_h_
