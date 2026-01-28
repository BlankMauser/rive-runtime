#include "nvn/nvn.hpp"

// nvnDeviceWaitForError always returns zero when we try to get its address

namespace nvn {
    NVN_GLOBAL(DeviceBuilderSetDefaults);
    NVN_GLOBAL(DeviceBuilderSetFlags);
    NVN_GLOBAL(DeviceInitialize);
    NVN_GLOBAL(DeviceFinalize);
    NVN_GLOBAL(DeviceSetDebugLabel);
    NVN_GLOBAL(DeviceGetProcAddress);
    NVN_GLOBAL(DeviceGetInteger);
    NVN_GLOBAL(DeviceGetCurrentTimestampInNanoseconds);
    NVN_GLOBAL(DeviceGetTextureHandle);
    NVN_GLOBAL(DeviceGetTexelFetchHandle);
    NVN_GLOBAL(DeviceGetImageHandle);
    NVN_GLOBAL(DeviceInstallDebugCallback);
    NVN_GLOBAL(DeviceSetWindowOriginMode);
    NVN_GLOBAL(DeviceSetDepthMode);
    NVN_GLOBAL(DeviceRegisterFastClearColor);
    NVN_GLOBAL(DeviceRegisterFastClearColori);
    NVN_GLOBAL(DeviceRegisterFastClearColorui);
    NVN_GLOBAL(DeviceRegisterFastClearDepth);
    NVN_GLOBAL(DeviceGetWindowOriginMode);
    NVN_GLOBAL(DeviceGetDepthMode);
    NVN_GLOBAL(DeviceGetTimestampInNanoseconds);
    NVN_GLOBAL(DeviceApplyDeferredFinalizes);
    NVN_GLOBAL(DeviceFinalizeCommandHandle);
    NVN_GLOBAL(DeviceWaitForError);
    NVN_GLOBAL(QueueGetError);
    NVN_GLOBAL(QueueBuilderSetDevice);
    NVN_GLOBAL(QueueBuilderSetDefaults);
    NVN_GLOBAL(QueueBuilderSetFlags);
    NVN_GLOBAL(QueueBuilderSetCommandMemorySize);
    NVN_GLOBAL(QueueBuilderSetComputeMemorySize);
    NVN_GLOBAL(QueueBuilderGetQueueMemorySize);
    NVN_GLOBAL(QueueBuilderSetQueueMemory);
    NVN_GLOBAL(QueueBuilderSetCommandFlushThreshold);
    NVN_GLOBAL(QueueInitialize);
    NVN_GLOBAL(QueueFinalize);
    NVN_GLOBAL(QueueSetDebugLabel);
    NVN_GLOBAL(QueueSubmitCommands);
    NVN_GLOBAL(QueueFlush);
    NVN_GLOBAL(QueueFinish);
    NVN_GLOBAL(QueuePresentTexture);
    NVN_GLOBAL(QueueAcquireTexture);
    NVN_GLOBAL(WindowBuilderSetDevice);
    NVN_GLOBAL(WindowBuilderSetDefaults);
    NVN_GLOBAL(WindowBuilderSetNativeWindow);
    NVN_GLOBAL(WindowBuilderSetTextures);
    NVN_GLOBAL(WindowBuilderSetPresentInterval);
    NVN_GLOBAL(WindowBuilderGetNativeWindow);
    NVN_GLOBAL(WindowBuilderGetPresentInterval);
    NVN_GLOBAL(WindowInitialize);
    NVN_GLOBAL(WindowFinalize);
    NVN_GLOBAL(WindowSetDebugLabel);
    NVN_GLOBAL(WindowAcquireTexture);
    NVN_GLOBAL(WindowGetNativeWindow);
    NVN_GLOBAL(WindowGetPresentInterval);
    NVN_GLOBAL(WindowSetPresentInterval);
    NVN_GLOBAL(WindowSetCrop);
    NVN_GLOBAL(ProgramInitialize);
    NVN_GLOBAL(ProgramFinalize);
    NVN_GLOBAL(ProgramSetDebugLabel);
    NVN_GLOBAL(ProgramSetShaders);
    NVN_GLOBAL(MemoryPoolBuilderSetDevice);
    NVN_GLOBAL(MemoryPoolBuilderSetDefaults);
    NVN_GLOBAL(MemoryPoolBuilderSetStorage);
    NVN_GLOBAL(MemoryPoolBuilderSetFlags);
    NVN_GLOBAL(MemoryPoolBuilderGetMemory);
    NVN_GLOBAL(MemoryPoolBuilderGetSize);
    NVN_GLOBAL(MemoryPoolBuilderGetFlags);
    NVN_GLOBAL(MemoryPoolInitialize);
    NVN_GLOBAL(MemoryPoolSetDebugLabel);
    NVN_GLOBAL(MemoryPoolFinalize);
    NVN_GLOBAL(MemoryPoolMap);
    NVN_GLOBAL(MemoryPoolFlushMappedRange);
    NVN_GLOBAL(MemoryPoolInvalidateMappedRange);
    NVN_GLOBAL(MemoryPoolGetBufferAddress);
    NVN_GLOBAL(MemoryPoolMapVirtual);
    NVN_GLOBAL(MemoryPoolGetSize);
    NVN_GLOBAL(MemoryPoolGetFlags);
    NVN_GLOBAL(TexturePoolInitialize);
    NVN_GLOBAL(TexturePoolSetDebugLabel);
    NVN_GLOBAL(TexturePoolFinalize);
    NVN_GLOBAL(TexturePoolRegisterTexture);
    NVN_GLOBAL(TexturePoolRegisterImage);
    NVN_GLOBAL(TexturePoolGetMemoryPool);
    NVN_GLOBAL(TexturePoolGetMemoryOffset);
    NVN_GLOBAL(TexturePoolGetSize);
    NVN_GLOBAL(SamplerPoolInitialize);
    NVN_GLOBAL(SamplerPoolSetDebugLabel);
    NVN_GLOBAL(SamplerPoolFinalize);
    NVN_GLOBAL(SamplerPoolRegisterSampler);
    NVN_GLOBAL(SamplerPoolGetMemoryPool);
    NVN_GLOBAL(SamplerPoolGetMemoryOffset);
    NVN_GLOBAL(SamplerPoolGetSize);
    NVN_GLOBAL(BufferBuilderSetDevice);
    NVN_GLOBAL(BufferBuilderSetDefaults);
    NVN_GLOBAL(BufferBuilderSetStorage);
    NVN_GLOBAL(BufferBuilderGetMemoryPool);
    NVN_GLOBAL(BufferBuilderGetMemoryOffset);
    NVN_GLOBAL(BufferBuilderGetSize);
    NVN_GLOBAL(BufferInitialize);
    NVN_GLOBAL(BufferSetDebugLabel);
    NVN_GLOBAL(BufferFinalize);
    NVN_GLOBAL(BufferMap);
    NVN_GLOBAL(BufferGetAddress);
    NVN_GLOBAL(BufferFlushMappedRange);
    NVN_GLOBAL(BufferInvalidateMappedRange);
    NVN_GLOBAL(BufferGetMemoryPool);
    NVN_GLOBAL(BufferGetMemoryOffset);
    NVN_GLOBAL(BufferGetSize);
    NVN_GLOBAL(BufferGetDebugID);
    NVN_GLOBAL(TextureBuilderSetDevice);
    NVN_GLOBAL(TextureBuilderSetDefaults);
    NVN_GLOBAL(TextureBuilderSetFlags);
    NVN_GLOBAL(TextureBuilderSetTarget);
    NVN_GLOBAL(TextureBuilderSetWidth);
    NVN_GLOBAL(TextureBuilderSetHeight);
    NVN_GLOBAL(TextureBuilderSetDepth);
    NVN_GLOBAL(TextureBuilderSetSize1D);
    NVN_GLOBAL(TextureBuilderSetSize2D);
    NVN_GLOBAL(TextureBuilderSetSize3D);
    NVN_GLOBAL(TextureBuilderSetLevels);
    NVN_GLOBAL(TextureBuilderSetFormat);
    NVN_GLOBAL(TextureBuilderSetSamples);
    NVN_GLOBAL(TextureBuilderSetSwizzle);
    NVN_GLOBAL(TextureBuilderSetDepthStencilMode);
    NVN_GLOBAL(TextureBuilderGetStorageSize);
    NVN_GLOBAL(TextureBuilderGetStorageAlignment);
    NVN_GLOBAL(TextureBuilderSetStorage);
    NVN_GLOBAL(TextureBuilderSetPackagedTextureData);
    NVN_GLOBAL(TextureBuilderSetPackagedTextureLayout);
    NVN_GLOBAL(TextureBuilderSetStride);
    NVN_GLOBAL(TextureBuilderSetGLTextureName);
    NVN_GLOBAL(TextureBuilderGetStorageClass);
    NVN_GLOBAL(TextureBuilderGetFlags);
    NVN_GLOBAL(TextureBuilderGetTarget);
    NVN_GLOBAL(TextureBuilderGetWidth);
    NVN_GLOBAL(TextureBuilderGetHeight);
    NVN_GLOBAL(TextureBuilderGetDepth);
    NVN_GLOBAL(TextureBuilderGetLevels);
    NVN_GLOBAL(TextureBuilderGetFormat);
    NVN_GLOBAL(TextureBuilderGetSamples);
    NVN_GLOBAL(TextureBuilderGetSwizzle);
    NVN_GLOBAL(TextureBuilderGetDepthStencilMode);
    NVN_GLOBAL(TextureBuilderGetPackagedTextureData);
    NVN_GLOBAL(TextureBuilderGetStride);
    NVN_GLOBAL(TextureBuilderGetSparseTileLayout);
    NVN_GLOBAL(TextureBuilderGetGLTextureName);
    NVN_GLOBAL(TextureBuilderGetZCullStorageSize);
    NVN_GLOBAL(TextureBuilderGetMemoryPool);
    NVN_GLOBAL(TextureBuilderGetMemoryOffset);
    NVN_GLOBAL(TextureViewSetDefaults);
    NVN_GLOBAL(TextureViewSetLevels);
    NVN_GLOBAL(TextureViewSetLayers);
    NVN_GLOBAL(TextureViewSetFormat);
    NVN_GLOBAL(TextureViewSetSwizzle);
    NVN_GLOBAL(TextureViewSetDepthStencilMode);
    NVN_GLOBAL(TextureViewSetTarget);
    NVN_GLOBAL(TextureViewGetLevels);
    NVN_GLOBAL(TextureViewGetLayers);
    NVN_GLOBAL(TextureViewGetFormat);
    NVN_GLOBAL(TextureViewGetSwizzle);
    NVN_GLOBAL(TextureViewGetDepthStencilMode);
    NVN_GLOBAL(TextureViewGetTarget);
    NVN_GLOBAL(TextureViewCompare);
    NVN_GLOBAL(TextureInitialize);
    NVN_GLOBAL(TextureGetZCullStorageSize);
    NVN_GLOBAL(TextureFinalize);
    NVN_GLOBAL(TextureSetDebugLabel);
    NVN_GLOBAL(TextureGetStorageClass);
    NVN_GLOBAL(TextureGetViewOffset);
    NVN_GLOBAL(TextureGetFlags);
    NVN_GLOBAL(TextureGetTarget);
    NVN_GLOBAL(TextureGetWidth);
    NVN_GLOBAL(TextureGetHeight);
    NVN_GLOBAL(TextureGetDepth);
    NVN_GLOBAL(TextureGetLevels);
    NVN_GLOBAL(TextureGetFormat);
    NVN_GLOBAL(TextureGetSamples);
    NVN_GLOBAL(TextureGetSwizzle);
    NVN_GLOBAL(TextureGetDepthStencilMode);
    NVN_GLOBAL(TextureGetStride);
    NVN_GLOBAL(TextureGetTextureAddress);
    NVN_GLOBAL(TextureGetSparseTileLayout);
    NVN_GLOBAL(TextureWriteTexels);
    NVN_GLOBAL(TextureReadTexels);
    NVN_GLOBAL(TextureFlushTexels);
    NVN_GLOBAL(TextureInvalidateTexels);
    NVN_GLOBAL(TextureGetMemoryPool);
    NVN_GLOBAL(TextureGetMemoryOffset);
    NVN_GLOBAL(TextureGetStorageSize);
    NVN_GLOBAL(TextureCompare);
    NVN_GLOBAL(TextureGetDebugID);
    NVN_GLOBAL(SamplerBuilderSetDevice);
    NVN_GLOBAL(SamplerBuilderSetDefaults);
    NVN_GLOBAL(SamplerBuilderSetMinMagFilter);
    NVN_GLOBAL(SamplerBuilderSetWrapMode);
    NVN_GLOBAL(SamplerBuilderSetLodClamp);
    NVN_GLOBAL(SamplerBuilderSetLodBias);
    NVN_GLOBAL(SamplerBuilderSetCompare);
    NVN_GLOBAL(SamplerBuilderSetBorderColor);
    NVN_GLOBAL(SamplerBuilderSetBorderColori);
    NVN_GLOBAL(SamplerBuilderSetBorderColorui);
    NVN_GLOBAL(SamplerBuilderSetMaxAnisotropy);
    NVN_GLOBAL(SamplerBuilderSetReductionFilter);
    NVN_GLOBAL(SamplerBuilderGetMinMagFilter);
    NVN_GLOBAL(SamplerBuilderGetWrapMode);
    NVN_GLOBAL(SamplerBuilderGetLodClamp);
    NVN_GLOBAL(SamplerBuilderGetLodBias);
    NVN_GLOBAL(SamplerBuilderGetCompare);
    NVN_GLOBAL(SamplerBuilderGetBorderColor);
    NVN_GLOBAL(SamplerBuilderGetBorderColori);
    NVN_GLOBAL(SamplerBuilderGetBorderColorui);
    NVN_GLOBAL(SamplerBuilderGetMaxAnisotropy);
    NVN_GLOBAL(SamplerBuilderGetReductionFilter);
    NVN_GLOBAL(SamplerInitialize);
    NVN_GLOBAL(SamplerFinalize);
    NVN_GLOBAL(SamplerSetDebugLabel);
    NVN_GLOBAL(SamplerGetMinMagFilter);
    NVN_GLOBAL(SamplerGetWrapMode);
    NVN_GLOBAL(SamplerGetLodClamp);
    NVN_GLOBAL(SamplerGetLodBias);
    NVN_GLOBAL(SamplerGetCompare);
    NVN_GLOBAL(SamplerGetBorderColor);
    NVN_GLOBAL(SamplerGetBorderColori);
    NVN_GLOBAL(SamplerGetBorderColorui);
    NVN_GLOBAL(SamplerGetMaxAnisotropy);
    NVN_GLOBAL(SamplerGetReductionFilter);
    NVN_GLOBAL(SamplerCompare);
    NVN_GLOBAL(SamplerGetDebugID);
    NVN_GLOBAL(BlendStateSetDefaults);
    NVN_GLOBAL(BlendStateSetBlendTarget);
    NVN_GLOBAL(BlendStateSetBlendFunc);
    NVN_GLOBAL(BlendStateSetBlendEquation);
    NVN_GLOBAL(BlendStateSetAdvancedMode);
    NVN_GLOBAL(BlendStateSetAdvancedOverlap);
    NVN_GLOBAL(BlendStateSetAdvancedPremultipliedSrc);
    NVN_GLOBAL(BlendStateSetAdvancedNormalizedDst);
    NVN_GLOBAL(BlendStateGetBlendTarget);
    NVN_GLOBAL(BlendStateGetBlendFunc);
    NVN_GLOBAL(BlendStateGetBlendEquation);
    NVN_GLOBAL(BlendStateGetAdvancedMode);
    NVN_GLOBAL(BlendStateGetAdvancedOverlap);
    NVN_GLOBAL(BlendStateGetAdvancedPremultipliedSrc);
    NVN_GLOBAL(BlendStateGetAdvancedNormalizedDst);
    NVN_GLOBAL(ColorStateSetDefaults);
    NVN_GLOBAL(ColorStateSetBlendEnable);
    NVN_GLOBAL(ColorStateSetLogicOp);
    NVN_GLOBAL(ColorStateSetAlphaTest);
    NVN_GLOBAL(ColorStateGetBlendEnable);
    NVN_GLOBAL(ColorStateGetLogicOp);
    NVN_GLOBAL(ColorStateGetAlphaTest);
    NVN_GLOBAL(ChannelMaskStateSetDefaults);
    NVN_GLOBAL(ChannelMaskStateSetChannelMask);
    NVN_GLOBAL(ChannelMaskStateGetChannelMask);
    NVN_GLOBAL(MultisampleStateSetDefaults);
    NVN_GLOBAL(MultisampleStateSetMultisampleEnable);
    NVN_GLOBAL(MultisampleStateSetSamples);
    NVN_GLOBAL(MultisampleStateSetAlphaToCoverageEnable);
    NVN_GLOBAL(MultisampleStateSetAlphaToCoverageDither);
    NVN_GLOBAL(MultisampleStateGetMultisampleEnable);
    NVN_GLOBAL(MultisampleStateGetSamples);
    NVN_GLOBAL(MultisampleStateGetAlphaToCoverageEnable);
    NVN_GLOBAL(MultisampleStateGetAlphaToCoverageDither);
    NVN_GLOBAL(MultisampleStateSetRasterSamples);
    NVN_GLOBAL(MultisampleStateGetRasterSamples);
    NVN_GLOBAL(MultisampleStateSetCoverageModulationMode);
    NVN_GLOBAL(MultisampleStateGetCoverageModulationMode);
    NVN_GLOBAL(MultisampleStateSetCoverageToColorEnable);
    NVN_GLOBAL(MultisampleStateGetCoverageToColorEnable);
    NVN_GLOBAL(MultisampleStateSetCoverageToColorOutput);
    NVN_GLOBAL(MultisampleStateGetCoverageToColorOutput);
    NVN_GLOBAL(MultisampleStateSetSampleLocationsEnable);
    NVN_GLOBAL(MultisampleStateGetSampleLocationsEnable);
    NVN_GLOBAL(MultisampleStateGetSampleLocationsGrid);
    NVN_GLOBAL(MultisampleStateSetSampleLocationsGridEnable);
    NVN_GLOBAL(MultisampleStateGetSampleLocationsGridEnable);
    NVN_GLOBAL(MultisampleStateSetSampleLocations);
    NVN_GLOBAL(PolygonStateSetDefaults);
    NVN_GLOBAL(PolygonStateSetCullFace);
    NVN_GLOBAL(PolygonStateSetFrontFace);
    NVN_GLOBAL(PolygonStateSetPolygonMode);
    NVN_GLOBAL(PolygonStateSetPolygonOffsetEnables);
    NVN_GLOBAL(PolygonStateGetCullFace);
    NVN_GLOBAL(PolygonStateGetFrontFace);
    NVN_GLOBAL(PolygonStateGetPolygonMode);
    NVN_GLOBAL(PolygonStateGetPolygonOffsetEnables);
    NVN_GLOBAL(DepthStencilStateSetDefaults);
    NVN_GLOBAL(DepthStencilStateSetDepthTestEnable);
    NVN_GLOBAL(DepthStencilStateSetDepthWriteEnable);
    NVN_GLOBAL(DepthStencilStateSetDepthFunc);
    NVN_GLOBAL(DepthStencilStateSetStencilTestEnable);
    NVN_GLOBAL(DepthStencilStateSetStencilFunc);
    NVN_GLOBAL(DepthStencilStateSetStencilOp);
    NVN_GLOBAL(DepthStencilStateGetDepthTestEnable);
    NVN_GLOBAL(DepthStencilStateGetDepthWriteEnable);
    NVN_GLOBAL(DepthStencilStateGetDepthFunc);
    NVN_GLOBAL(DepthStencilStateGetStencilTestEnable);
    NVN_GLOBAL(DepthStencilStateGetStencilFunc);
    NVN_GLOBAL(DepthStencilStateGetStencilOp);
    NVN_GLOBAL(VertexAttribStateSetDefaults);
    NVN_GLOBAL(VertexAttribStateSetFormat);
    NVN_GLOBAL(VertexAttribStateSetStreamIndex);
    NVN_GLOBAL(VertexAttribStateGetFormat);
    NVN_GLOBAL(VertexAttribStateGetStreamIndex);
    NVN_GLOBAL(VertexStreamStateSetDefaults);
    NVN_GLOBAL(VertexStreamStateSetStride);
    NVN_GLOBAL(VertexStreamStateSetDivisor);
    NVN_GLOBAL(VertexStreamStateGetStride);
    NVN_GLOBAL(VertexStreamStateGetDivisor);
    NVN_GLOBAL(CommandBufferInitialize);
    NVN_GLOBAL(CommandBufferFinalize);
    NVN_GLOBAL(CommandBufferSetDebugLabel);
    NVN_GLOBAL(CommandBufferSetMemoryCallback);
    NVN_GLOBAL(CommandBufferSetMemoryCallbackData);
    NVN_GLOBAL(CommandBufferAddCommandMemory);
    NVN_GLOBAL(CommandBufferAddControlMemory);
    NVN_GLOBAL(CommandBufferGetCommandMemorySize);
    NVN_GLOBAL(CommandBufferGetCommandMemoryUsed);
    NVN_GLOBAL(CommandBufferGetCommandMemoryFree);
    NVN_GLOBAL(CommandBufferGetControlMemorySize);
    NVN_GLOBAL(CommandBufferGetControlMemoryUsed);
    NVN_GLOBAL(CommandBufferGetControlMemoryFree);
    NVN_GLOBAL(CommandBufferBeginRecording);
    NVN_GLOBAL(CommandBufferEndRecording);
    NVN_GLOBAL(CommandBufferCallCommands);
    NVN_GLOBAL(CommandBufferCopyCommands);
    NVN_GLOBAL(CommandBufferBindBlendState);
    NVN_GLOBAL(CommandBufferBindChannelMaskState);
    NVN_GLOBAL(CommandBufferBindColorState);
    NVN_GLOBAL(CommandBufferBindMultisampleState);
    NVN_GLOBAL(CommandBufferBindPolygonState);
    NVN_GLOBAL(CommandBufferBindDepthStencilState);
    NVN_GLOBAL(CommandBufferBindVertexAttribState);
    NVN_GLOBAL(CommandBufferBindVertexStreamState);
    NVN_GLOBAL(CommandBufferBindProgram);
    NVN_GLOBAL(CommandBufferBindVertexBuffer);
    NVN_GLOBAL(CommandBufferBindVertexBuffers);
    NVN_GLOBAL(CommandBufferBindUniformBuffer);
    NVN_GLOBAL(CommandBufferBindUniformBuffers);
    NVN_GLOBAL(CommandBufferBindTransformFeedbackBuffer);
    NVN_GLOBAL(CommandBufferBindTransformFeedbackBuffers);
    NVN_GLOBAL(CommandBufferBindStorageBuffer);
    NVN_GLOBAL(CommandBufferBindStorageBuffers);
    NVN_GLOBAL(CommandBufferBindTexture);
    NVN_GLOBAL(CommandBufferBindTextures);
    NVN_GLOBAL(CommandBufferBindImage);
    NVN_GLOBAL(CommandBufferBindImages);
    NVN_GLOBAL(CommandBufferSetPatchSize);
    NVN_GLOBAL(CommandBufferSetInnerTessellationLevels);
    NVN_GLOBAL(CommandBufferSetOuterTessellationLevels);
    NVN_GLOBAL(CommandBufferSetPrimitiveRestart);
    NVN_GLOBAL(CommandBufferBeginTransformFeedback);
    NVN_GLOBAL(CommandBufferEndTransformFeedback);
    NVN_GLOBAL(CommandBufferPauseTransformFeedback);
    NVN_GLOBAL(CommandBufferResumeTransformFeedback);
    NVN_GLOBAL(CommandBufferDrawTransformFeedback);
    NVN_GLOBAL(CommandBufferDrawArrays);
    NVN_GLOBAL(CommandBufferDrawElements);
    NVN_GLOBAL(CommandBufferDrawElementsBaseVertex);
    NVN_GLOBAL(CommandBufferDrawArraysInstanced);
    NVN_GLOBAL(CommandBufferDrawElementsInstanced);
    NVN_GLOBAL(CommandBufferDrawArraysIndirect);
    NVN_GLOBAL(CommandBufferDrawElementsIndirect);
    NVN_GLOBAL(CommandBufferMultiDrawArraysIndirectCount);
    NVN_GLOBAL(CommandBufferMultiDrawElementsIndirectCount);
    NVN_GLOBAL(CommandBufferClearColor);
    NVN_GLOBAL(CommandBufferClearColori);
    NVN_GLOBAL(CommandBufferClearColorui);
    NVN_GLOBAL(CommandBufferClearDepthStencil);
    NVN_GLOBAL(CommandBufferDispatchCompute);
    NVN_GLOBAL(CommandBufferDispatchComputeIndirect);
    NVN_GLOBAL(CommandBufferSetViewport);
    NVN_GLOBAL(CommandBufferSetViewports);
    NVN_GLOBAL(CommandBufferSetViewportSwizzles);
    NVN_GLOBAL(CommandBufferSetScissor);
    NVN_GLOBAL(CommandBufferSetScissors);
    NVN_GLOBAL(CommandBufferSetDepthRange);
    NVN_GLOBAL(CommandBufferSetDepthBounds);
    NVN_GLOBAL(CommandBufferSetDepthRanges);
    NVN_GLOBAL(CommandBufferSetTiledCacheAction);
    NVN_GLOBAL(CommandBufferSetTiledCacheTileSize);
    NVN_GLOBAL(CommandBufferSetStencilValueMask);
    NVN_GLOBAL(CommandBufferSetStencilMask);
    NVN_GLOBAL(CommandBufferSetStencilRef);
    NVN_GLOBAL(CommandBufferSetBlendColor);
    NVN_GLOBAL(CommandBufferSetPointSize);
    NVN_GLOBAL(CommandBufferSetLineWidth);
    NVN_GLOBAL(CommandBufferSetPolygonOffsetClamp);
    NVN_GLOBAL(CommandBufferSetAlphaRef);
    NVN_GLOBAL(CommandBufferSetSampleMask);
    NVN_GLOBAL(CommandBufferSetRasterizerDiscard);
    NVN_GLOBAL(CommandBufferSetDepthClamp);
    NVN_GLOBAL(CommandBufferSetConservativeRasterEnable);
    NVN_GLOBAL(CommandBufferSetConservativeRasterDilate);
    NVN_GLOBAL(CommandBufferSetSubpixelPrecisionBias);
    NVN_GLOBAL(CommandBufferCopyBufferToTexture);
    NVN_GLOBAL(CommandBufferCopyTextureToBuffer);
    NVN_GLOBAL(CommandBufferCopyTextureToTexture);
    NVN_GLOBAL(CommandBufferCopyBufferToBuffer);
    NVN_GLOBAL(CommandBufferClearBuffer);
    NVN_GLOBAL(CommandBufferClearTexture);
    NVN_GLOBAL(CommandBufferClearTexturei);
    NVN_GLOBAL(CommandBufferClearTextureui);
    NVN_GLOBAL(CommandBufferUpdateUniformBuffer);
    NVN_GLOBAL(CommandBufferReportCounter);
    NVN_GLOBAL(CommandBufferResetCounter);
    NVN_GLOBAL(CommandBufferReportValue);
    NVN_GLOBAL(CommandBufferSetRenderEnable);
    NVN_GLOBAL(CommandBufferSetRenderEnableConditional);
    NVN_GLOBAL(CommandBufferSetRenderTargets);
    NVN_GLOBAL(CommandBufferDiscardColor);
    NVN_GLOBAL(CommandBufferDiscardDepthStencil);
    NVN_GLOBAL(CommandBufferDownsample);
    NVN_GLOBAL(CommandBufferTiledDownsample);
    NVN_GLOBAL(CommandBufferBarrier);
    NVN_GLOBAL(CommandBufferWaitSync);
    NVN_GLOBAL(CommandBufferFenceSync);
    NVN_GLOBAL(CommandBufferSetTexturePool);
    NVN_GLOBAL(CommandBufferSetSamplerPool);
    NVN_GLOBAL(CommandBufferSetShaderScratchMemory);
    NVN_GLOBAL(CommandBufferSaveZCullData);
    NVN_GLOBAL(CommandBufferRestoreZCullData);
    NVN_GLOBAL(CommandBufferSetCopyRowStride);
    NVN_GLOBAL(CommandBufferSetCopyImageStride);
    NVN_GLOBAL(CommandBufferGetCopyRowStride);
    NVN_GLOBAL(CommandBufferGetCopyImageStride);
    NVN_GLOBAL(CommandBufferDrawTexture);
    NVN_GLOBAL(ProgramSetSubroutineLinkage);
    NVN_GLOBAL(CommandBufferSetProgramSubroutines);
    NVN_GLOBAL(CommandBufferBindCoverageModulationTable);
    NVN_GLOBAL(CommandBufferResolveDepthBuffer);
    NVN_GLOBAL(CommandBufferPushDebugGroup);
    NVN_GLOBAL(CommandBufferPopDebugGroup);
    NVN_GLOBAL(CommandBufferInsertDebugMarker);
    NVN_GLOBAL(CommandBufferGetMemoryCallback);
    NVN_GLOBAL(CommandBufferGetMemoryCallbackData);
    NVN_GLOBAL(CommandBufferIsRecording);
    NVN_GLOBAL(SyncInitialize);
    NVN_GLOBAL(SyncFinalize);
    NVN_GLOBAL(SyncSetDebugLabel);
    NVN_GLOBAL(QueueFenceSync);
    NVN_GLOBAL(SyncWait);
    NVN_GLOBAL(QueueWaitSync);
    void initialize(nvn::Device* pDevice, GetProcAddressPtr getProc) {
        NVN_LOAD_FUNC(DeviceBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceBuilderSetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetProcAddress, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetInteger, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetCurrentTimestampInNanoseconds, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetTextureHandle, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetTexelFetchHandle, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetImageHandle, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceInstallDebugCallback, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceSetWindowOriginMode, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceSetDepthMode, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceRegisterFastClearColor, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceRegisterFastClearColori, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceRegisterFastClearColorui, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceRegisterFastClearDepth, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetWindowOriginMode, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetDepthMode, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceGetTimestampInNanoseconds, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceApplyDeferredFinalizes, pDevice, getProc);
        NVN_LOAD_FUNC(DeviceFinalizeCommandHandle, pDevice, getProc);
        // NVN_LOAD_FUNC(DeviceWaitForError, pDevice, getProc);
        NVN_LOAD_FUNC(QueueGetError, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetDevice, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetCommandMemorySize, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetComputeMemorySize, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderGetQueueMemorySize, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetQueueMemory, pDevice, getProc);
        NVN_LOAD_FUNC(QueueBuilderSetCommandFlushThreshold, pDevice, getProc);
        NVN_LOAD_FUNC(QueueInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(QueueFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(QueueSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(QueueSubmitCommands, pDevice, getProc);
        NVN_LOAD_FUNC(QueueFlush, pDevice, getProc);
        NVN_LOAD_FUNC(QueueFinish, pDevice, getProc);
        NVN_LOAD_FUNC(QueuePresentTexture, pDevice, getProc);
        NVN_LOAD_FUNC(QueueAcquireTexture, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderSetDevice, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderSetNativeWindow, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderSetTextures, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderSetPresentInterval, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderGetNativeWindow, pDevice, getProc);
        NVN_LOAD_FUNC(WindowBuilderGetPresentInterval, pDevice, getProc);
        NVN_LOAD_FUNC(WindowInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(WindowFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(WindowSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(WindowAcquireTexture, pDevice, getProc);
        NVN_LOAD_FUNC(WindowGetNativeWindow, pDevice, getProc);
        NVN_LOAD_FUNC(WindowGetPresentInterval, pDevice, getProc);
        NVN_LOAD_FUNC(WindowSetPresentInterval, pDevice, getProc);
        NVN_LOAD_FUNC(WindowSetCrop, pDevice, getProc);
        NVN_LOAD_FUNC(ProgramInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(ProgramFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(ProgramSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(ProgramSetShaders, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderSetDevice, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderSetStorage, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderSetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderGetMemory, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderGetSize, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolBuilderGetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolMap, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolFlushMappedRange, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolInvalidateMappedRange, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolGetBufferAddress, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolMapVirtual, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolGetSize, pDevice, getProc);
        NVN_LOAD_FUNC(MemoryPoolGetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolRegisterTexture, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolRegisterImage, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolGetMemoryPool, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolGetMemoryOffset, pDevice, getProc);
        NVN_LOAD_FUNC(TexturePoolGetSize, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolRegisterSampler, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolGetMemoryPool, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolGetMemoryOffset, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerPoolGetSize, pDevice, getProc);
        NVN_LOAD_FUNC(BufferBuilderSetDevice, pDevice, getProc);
        NVN_LOAD_FUNC(BufferBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(BufferBuilderSetStorage, pDevice, getProc);
        NVN_LOAD_FUNC(BufferBuilderGetMemoryPool, pDevice, getProc);
        NVN_LOAD_FUNC(BufferBuilderGetMemoryOffset, pDevice, getProc);
        NVN_LOAD_FUNC(BufferBuilderGetSize, pDevice, getProc);
        NVN_LOAD_FUNC(BufferInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(BufferSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(BufferFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(BufferMap, pDevice, getProc);
        NVN_LOAD_FUNC(BufferGetAddress, pDevice, getProc);
        NVN_LOAD_FUNC(BufferFlushMappedRange, pDevice, getProc);
        NVN_LOAD_FUNC(BufferInvalidateMappedRange, pDevice, getProc);
        NVN_LOAD_FUNC(BufferGetMemoryPool, pDevice, getProc);
        NVN_LOAD_FUNC(BufferGetMemoryOffset, pDevice, getProc);
        NVN_LOAD_FUNC(BufferGetSize, pDevice, getProc);
        NVN_LOAD_FUNC(BufferGetDebugID, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetDevice, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetTarget, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetWidth, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetHeight, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetDepth, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetSize1D, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetSize2D, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetSize3D, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetLevels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetSamples, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetSwizzle, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetDepthStencilMode, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetStorageSize, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetStorageAlignment, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetStorage, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetPackagedTextureData, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetPackagedTextureLayout, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetStride, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderSetGLTextureName, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetStorageClass, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetTarget, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetWidth, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetHeight, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetDepth, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetLevels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetSamples, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetSwizzle, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetDepthStencilMode, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetPackagedTextureData, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetStride, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetSparseTileLayout, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetGLTextureName, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetZCullStorageSize, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetMemoryPool, pDevice, getProc);
        NVN_LOAD_FUNC(TextureBuilderGetMemoryOffset, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetLevels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetLayers, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetSwizzle, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetDepthStencilMode, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewSetTarget, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewGetLevels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewGetLayers, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewGetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewGetSwizzle, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewGetDepthStencilMode, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewGetTarget, pDevice, getProc);
        NVN_LOAD_FUNC(TextureViewCompare, pDevice, getProc);
        NVN_LOAD_FUNC(TextureInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetZCullStorageSize, pDevice, getProc);
        NVN_LOAD_FUNC(TextureFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(TextureSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetStorageClass, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetViewOffset, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetFlags, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetTarget, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetWidth, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetHeight, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetDepth, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetLevels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetSamples, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetSwizzle, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetDepthStencilMode, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetStride, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetTextureAddress, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetSparseTileLayout, pDevice, getProc);
        NVN_LOAD_FUNC(TextureWriteTexels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureReadTexels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureFlushTexels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureInvalidateTexels, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetMemoryPool, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetMemoryOffset, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetStorageSize, pDevice, getProc);
        NVN_LOAD_FUNC(TextureCompare, pDevice, getProc);
        NVN_LOAD_FUNC(TextureGetDebugID, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetDevice, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetMinMagFilter, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetWrapMode, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetLodClamp, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetLodBias, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetCompare, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetBorderColor, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetBorderColori, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetBorderColorui, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetMaxAnisotropy, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderSetReductionFilter, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetMinMagFilter, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetWrapMode, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetLodClamp, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetLodBias, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetCompare, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetBorderColor, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetBorderColori, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetBorderColorui, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetMaxAnisotropy, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerBuilderGetReductionFilter, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetMinMagFilter, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetWrapMode, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetLodClamp, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetLodBias, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetCompare, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetBorderColor, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetBorderColori, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetBorderColorui, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetMaxAnisotropy, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetReductionFilter, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerCompare, pDevice, getProc);
        NVN_LOAD_FUNC(SamplerGetDebugID, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetBlendTarget, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetBlendFunc, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetBlendEquation, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetAdvancedMode, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetAdvancedOverlap, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetAdvancedPremultipliedSrc, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateSetAdvancedNormalizedDst, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetBlendTarget, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetBlendFunc, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetBlendEquation, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetAdvancedMode, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetAdvancedOverlap, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetAdvancedPremultipliedSrc, pDevice, getProc);
        NVN_LOAD_FUNC(BlendStateGetAdvancedNormalizedDst, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateSetBlendEnable, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateSetLogicOp, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateSetAlphaTest, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateGetBlendEnable, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateGetLogicOp, pDevice, getProc);
        NVN_LOAD_FUNC(ColorStateGetAlphaTest, pDevice, getProc);
        NVN_LOAD_FUNC(ChannelMaskStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(ChannelMaskStateSetChannelMask, pDevice, getProc);
        NVN_LOAD_FUNC(ChannelMaskStateGetChannelMask, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetMultisampleEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetSamples, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetAlphaToCoverageEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetAlphaToCoverageDither, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetMultisampleEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetSamples, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetAlphaToCoverageEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetAlphaToCoverageDither, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetRasterSamples, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetRasterSamples, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetCoverageModulationMode, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetCoverageModulationMode, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetCoverageToColorEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetCoverageToColorEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetCoverageToColorOutput, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetCoverageToColorOutput, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetSampleLocationsEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetSampleLocationsEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetSampleLocationsGrid, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetSampleLocationsGridEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateGetSampleLocationsGridEnable, pDevice, getProc);
        NVN_LOAD_FUNC(MultisampleStateSetSampleLocations, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateSetCullFace, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateSetFrontFace, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateSetPolygonMode, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateSetPolygonOffsetEnables, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateGetCullFace, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateGetFrontFace, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateGetPolygonMode, pDevice, getProc);
        NVN_LOAD_FUNC(PolygonStateGetPolygonOffsetEnables, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetDepthTestEnable, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetDepthWriteEnable, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetDepthFunc, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetStencilTestEnable, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetStencilFunc, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateSetStencilOp, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateGetDepthTestEnable, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateGetDepthWriteEnable, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateGetDepthFunc, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateGetStencilTestEnable, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateGetStencilFunc, pDevice, getProc);
        NVN_LOAD_FUNC(DepthStencilStateGetStencilOp, pDevice, getProc);
        NVN_LOAD_FUNC(VertexAttribStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(VertexAttribStateSetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(VertexAttribStateSetStreamIndex, pDevice, getProc);
        NVN_LOAD_FUNC(VertexAttribStateGetFormat, pDevice, getProc);
        NVN_LOAD_FUNC(VertexAttribStateGetStreamIndex, pDevice, getProc);
        NVN_LOAD_FUNC(VertexStreamStateSetDefaults, pDevice, getProc);
        NVN_LOAD_FUNC(VertexStreamStateSetStride, pDevice, getProc);
        NVN_LOAD_FUNC(VertexStreamStateSetDivisor, pDevice, getProc);
        NVN_LOAD_FUNC(VertexStreamStateGetStride, pDevice, getProc);
        NVN_LOAD_FUNC(VertexStreamStateGetDivisor, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetMemoryCallback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetMemoryCallbackData, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferAddCommandMemory, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferAddControlMemory, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetCommandMemorySize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetCommandMemoryUsed, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetCommandMemoryFree, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetControlMemorySize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetControlMemoryUsed, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetControlMemoryFree, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBeginRecording, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferEndRecording, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferCallCommands, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferCopyCommands, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindBlendState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindChannelMaskState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindColorState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindMultisampleState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindPolygonState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindDepthStencilState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindVertexAttribState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindVertexStreamState, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindProgram, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindVertexBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindVertexBuffers, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindUniformBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindUniformBuffers, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindTransformFeedbackBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindTransformFeedbackBuffers, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindStorageBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindStorageBuffers, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindTexture, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindTextures, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindImage, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindImages, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetPatchSize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetInnerTessellationLevels, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetOuterTessellationLevels, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetPrimitiveRestart, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBeginTransformFeedback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferEndTransformFeedback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferPauseTransformFeedback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferResumeTransformFeedback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawTransformFeedback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawArrays, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawElements, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawElementsBaseVertex, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawArraysInstanced, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawElementsInstanced, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawArraysIndirect, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawElementsIndirect, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferMultiDrawArraysIndirectCount, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferMultiDrawElementsIndirectCount, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearColor, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearColori, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearColorui, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearDepthStencil, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDispatchCompute, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDispatchComputeIndirect, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetViewport, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetViewports, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetViewportSwizzles, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetScissor, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetScissors, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetDepthRange, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetDepthBounds, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetDepthRanges, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetTiledCacheAction, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetTiledCacheTileSize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetStencilValueMask, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetStencilMask, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetStencilRef, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetBlendColor, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetPointSize, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetLineWidth, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetPolygonOffsetClamp, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetAlphaRef, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetSampleMask, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetRasterizerDiscard, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetDepthClamp, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetConservativeRasterEnable, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetConservativeRasterDilate, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetSubpixelPrecisionBias, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferCopyBufferToTexture, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferCopyTextureToBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferCopyTextureToTexture, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferCopyBufferToBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearTexture, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearTexturei, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferClearTextureui, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferUpdateUniformBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferReportCounter, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferResetCounter, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferReportValue, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetRenderEnable, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetRenderEnableConditional, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetRenderTargets, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDiscardColor, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDiscardDepthStencil, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDownsample, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferTiledDownsample, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBarrier, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferWaitSync, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferFenceSync, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetTexturePool, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetSamplerPool, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetShaderScratchMemory, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSaveZCullData, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferRestoreZCullData, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetCopyRowStride, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetCopyImageStride, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetCopyRowStride, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetCopyImageStride, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferDrawTexture, pDevice, getProc);
        NVN_LOAD_FUNC(ProgramSetSubroutineLinkage, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferSetProgramSubroutines, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferBindCoverageModulationTable, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferResolveDepthBuffer, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferPushDebugGroup, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferPopDebugGroup, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferInsertDebugMarker, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetMemoryCallback, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferGetMemoryCallbackData, pDevice, getProc);
        NVN_LOAD_FUNC(CommandBufferIsRecording, pDevice, getProc);
        NVN_LOAD_FUNC(SyncInitialize, pDevice, getProc);
        NVN_LOAD_FUNC(SyncFinalize, pDevice, getProc);
        NVN_LOAD_FUNC(SyncSetDebugLabel, pDevice, getProc);
        NVN_LOAD_FUNC(QueueFenceSync, pDevice, getProc);
        NVN_LOAD_FUNC(SyncWait, pDevice, getProc);
        NVN_LOAD_FUNC(QueueWaitSync, pDevice, getProc);

#ifdef OCEAN_CONFIRM_ON_INIT

        NVN_CONFIRM(DeviceBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(DeviceBuilderSetFlags, "nvn::initialize");
        NVN_CONFIRM(DeviceInitialize, "nvn::initialize");
        NVN_CONFIRM(DeviceFinalize, "nvn::initialize");
        NVN_CONFIRM(DeviceSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(DeviceGetProcAddress, "nvn::initialize");
        NVN_CONFIRM(DeviceGetInteger, "nvn::initialize");
        NVN_CONFIRM(DeviceGetCurrentTimestampInNanoseconds, "nvn::initialize");
        NVN_CONFIRM(DeviceGetTextureHandle, "nvn::initialize");
        NVN_CONFIRM(DeviceGetTexelFetchHandle, "nvn::initialize");
        NVN_CONFIRM(DeviceGetImageHandle, "nvn::initialize");
        NVN_CONFIRM(DeviceInstallDebugCallback, "nvn::initialize");
        NVN_CONFIRM(DeviceSetWindowOriginMode, "nvn::initialize");
        NVN_CONFIRM(DeviceSetDepthMode, "nvn::initialize");
        NVN_CONFIRM(DeviceRegisterFastClearColor, "nvn::initialize");
        NVN_CONFIRM(DeviceRegisterFastClearColori, "nvn::initialize");
        NVN_CONFIRM(DeviceRegisterFastClearColorui, "nvn::initialize");
        NVN_CONFIRM(DeviceRegisterFastClearDepth, "nvn::initialize");
        NVN_CONFIRM(DeviceGetWindowOriginMode, "nvn::initialize");
        NVN_CONFIRM(DeviceGetDepthMode, "nvn::initialize");
        NVN_CONFIRM(DeviceGetTimestampInNanoseconds, "nvn::initialize");
        NVN_CONFIRM(DeviceApplyDeferredFinalizes, "nvn::initialize");
        NVN_CONFIRM(DeviceFinalizeCommandHandle, "nvn::initialize");
        // NVN_CONFIRM(DeviceWaitForError, "nvn::initialize");
        NVN_CONFIRM(QueueGetError, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetDevice, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetFlags, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetCommandMemorySize, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetComputeMemorySize, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderGetQueueMemorySize, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetQueueMemory, "nvn::initialize");
        NVN_CONFIRM(QueueBuilderSetCommandFlushThreshold, "nvn::initialize");
        NVN_CONFIRM(QueueInitialize, "nvn::initialize");
        NVN_CONFIRM(QueueFinalize, "nvn::initialize");
        NVN_CONFIRM(QueueSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(QueueSubmitCommands, "nvn::initialize");
        NVN_CONFIRM(QueueFlush, "nvn::initialize");
        NVN_CONFIRM(QueueFinish, "nvn::initialize");
        NVN_CONFIRM(QueuePresentTexture, "nvn::initialize");
        NVN_CONFIRM(QueueAcquireTexture, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderSetDevice, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderSetNativeWindow, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderSetTextures, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderSetPresentInterval, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderGetNativeWindow, "nvn::initialize");
        NVN_CONFIRM(WindowBuilderGetPresentInterval, "nvn::initialize");
        NVN_CONFIRM(WindowInitialize, "nvn::initialize");
        NVN_CONFIRM(WindowFinalize, "nvn::initialize");
        NVN_CONFIRM(WindowSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(WindowAcquireTexture, "nvn::initialize");
        NVN_CONFIRM(WindowGetNativeWindow, "nvn::initialize");
        NVN_CONFIRM(WindowGetPresentInterval, "nvn::initialize");
        NVN_CONFIRM(WindowSetPresentInterval, "nvn::initialize");
        NVN_CONFIRM(WindowSetCrop, "nvn::initialize");
        NVN_CONFIRM(ProgramInitialize, "nvn::initialize");
        NVN_CONFIRM(ProgramFinalize, "nvn::initialize");
        NVN_CONFIRM(ProgramSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(ProgramSetShaders, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderSetDevice, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderSetStorage, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderSetFlags, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderGetMemory, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderGetSize, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolBuilderGetFlags, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolInitialize, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolFinalize, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolMap, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolFlushMappedRange, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolInvalidateMappedRange, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolGetBufferAddress, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolMapVirtual, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolGetSize, "nvn::initialize");
        NVN_CONFIRM(MemoryPoolGetFlags, "nvn::initialize");
        NVN_CONFIRM(TexturePoolInitialize, "nvn::initialize");
        NVN_CONFIRM(TexturePoolSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(TexturePoolFinalize, "nvn::initialize");
        NVN_CONFIRM(TexturePoolRegisterTexture, "nvn::initialize");
        NVN_CONFIRM(TexturePoolRegisterImage, "nvn::initialize");
        NVN_CONFIRM(TexturePoolGetMemoryPool, "nvn::initialize");
        NVN_CONFIRM(TexturePoolGetMemoryOffset, "nvn::initialize");
        NVN_CONFIRM(TexturePoolGetSize, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolInitialize, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolFinalize, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolRegisterSampler, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolGetMemoryPool, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolGetMemoryOffset, "nvn::initialize");
        NVN_CONFIRM(SamplerPoolGetSize, "nvn::initialize");
        NVN_CONFIRM(BufferBuilderSetDevice, "nvn::initialize");
        NVN_CONFIRM(BufferBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(BufferBuilderSetStorage, "nvn::initialize");
        NVN_CONFIRM(BufferBuilderGetMemoryPool, "nvn::initialize");
        NVN_CONFIRM(BufferBuilderGetMemoryOffset, "nvn::initialize");
        NVN_CONFIRM(BufferBuilderGetSize, "nvn::initialize");
        NVN_CONFIRM(BufferInitialize, "nvn::initialize");
        NVN_CONFIRM(BufferSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(BufferFinalize, "nvn::initialize");
        NVN_CONFIRM(BufferMap, "nvn::initialize");
        NVN_CONFIRM(BufferGetAddress, "nvn::initialize");
        NVN_CONFIRM(BufferFlushMappedRange, "nvn::initialize");
        NVN_CONFIRM(BufferInvalidateMappedRange, "nvn::initialize");
        NVN_CONFIRM(BufferGetMemoryPool, "nvn::initialize");
        NVN_CONFIRM(BufferGetMemoryOffset, "nvn::initialize");
        NVN_CONFIRM(BufferGetSize, "nvn::initialize");
        NVN_CONFIRM(BufferGetDebugID, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetDevice, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetFlags, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetTarget, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetWidth, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetHeight, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetDepth, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetSize1D, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetSize2D, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetSize3D, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetLevels, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetFormat, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetSamples, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetSwizzle, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetDepthStencilMode, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetStorageSize, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetStorageAlignment, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetStorage, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetPackagedTextureData, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetPackagedTextureLayout, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetStride, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderSetGLTextureName, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetStorageClass, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetFlags, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetTarget, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetWidth, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetHeight, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetDepth, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetLevels, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetFormat, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetSamples, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetSwizzle, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetDepthStencilMode, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetPackagedTextureData, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetStride, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetSparseTileLayout, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetGLTextureName, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetZCullStorageSize, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetMemoryPool, "nvn::initialize");
        NVN_CONFIRM(TextureBuilderGetMemoryOffset, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetDefaults, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetLevels, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetLayers, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetFormat, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetSwizzle, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetDepthStencilMode, "nvn::initialize");
        NVN_CONFIRM(TextureViewSetTarget, "nvn::initialize");
        NVN_CONFIRM(TextureViewGetLevels, "nvn::initialize");
        NVN_CONFIRM(TextureViewGetLayers, "nvn::initialize");
        NVN_CONFIRM(TextureViewGetFormat, "nvn::initialize");
        NVN_CONFIRM(TextureViewGetSwizzle, "nvn::initialize");
        NVN_CONFIRM(TextureViewGetDepthStencilMode, "nvn::initialize");
        NVN_CONFIRM(TextureViewGetTarget, "nvn::initialize");
        NVN_CONFIRM(TextureViewCompare, "nvn::initialize");
        NVN_CONFIRM(TextureInitialize, "nvn::initialize");
        NVN_CONFIRM(TextureGetZCullStorageSize, "nvn::initialize");
        NVN_CONFIRM(TextureFinalize, "nvn::initialize");
        NVN_CONFIRM(TextureSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(TextureGetStorageClass, "nvn::initialize");
        NVN_CONFIRM(TextureGetViewOffset, "nvn::initialize");
        NVN_CONFIRM(TextureGetFlags, "nvn::initialize");
        NVN_CONFIRM(TextureGetTarget, "nvn::initialize");
        NVN_CONFIRM(TextureGetWidth, "nvn::initialize");
        NVN_CONFIRM(TextureGetHeight, "nvn::initialize");
        NVN_CONFIRM(TextureGetDepth, "nvn::initialize");
        NVN_CONFIRM(TextureGetLevels, "nvn::initialize");
        NVN_CONFIRM(TextureGetFormat, "nvn::initialize");
        NVN_CONFIRM(TextureGetSamples, "nvn::initialize");
        NVN_CONFIRM(TextureGetSwizzle, "nvn::initialize");
        NVN_CONFIRM(TextureGetDepthStencilMode, "nvn::initialize");
        NVN_CONFIRM(TextureGetStride, "nvn::initialize");
        NVN_CONFIRM(TextureGetTextureAddress, "nvn::initialize");
        NVN_CONFIRM(TextureGetSparseTileLayout, "nvn::initialize");
        NVN_CONFIRM(TextureWriteTexels, "nvn::initialize");
        NVN_CONFIRM(TextureReadTexels, "nvn::initialize");
        NVN_CONFIRM(TextureFlushTexels, "nvn::initialize");
        NVN_CONFIRM(TextureInvalidateTexels, "nvn::initialize");
        NVN_CONFIRM(TextureGetMemoryPool, "nvn::initialize");
        NVN_CONFIRM(TextureGetMemoryOffset, "nvn::initialize");
        NVN_CONFIRM(TextureGetStorageSize, "nvn::initialize");
        NVN_CONFIRM(TextureCompare, "nvn::initialize");
        NVN_CONFIRM(TextureGetDebugID, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetDevice, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetDefaults, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetMinMagFilter, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetWrapMode, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetLodClamp, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetLodBias, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetCompare, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetBorderColor, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetBorderColori, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetBorderColorui, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetMaxAnisotropy, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderSetReductionFilter, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetMinMagFilter, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetWrapMode, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetLodClamp, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetLodBias, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetCompare, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetBorderColor, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetBorderColori, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetBorderColorui, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetMaxAnisotropy, "nvn::initialize");
        NVN_CONFIRM(SamplerBuilderGetReductionFilter, "nvn::initialize");
        NVN_CONFIRM(SamplerInitialize, "nvn::initialize");
        NVN_CONFIRM(SamplerFinalize, "nvn::initialize");
        NVN_CONFIRM(SamplerSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(SamplerGetMinMagFilter, "nvn::initialize");
        NVN_CONFIRM(SamplerGetWrapMode, "nvn::initialize");
        NVN_CONFIRM(SamplerGetLodClamp, "nvn::initialize");
        NVN_CONFIRM(SamplerGetLodBias, "nvn::initialize");
        NVN_CONFIRM(SamplerGetCompare, "nvn::initialize");
        NVN_CONFIRM(SamplerGetBorderColor, "nvn::initialize");
        NVN_CONFIRM(SamplerGetBorderColori, "nvn::initialize");
        NVN_CONFIRM(SamplerGetBorderColorui, "nvn::initialize");
        NVN_CONFIRM(SamplerGetMaxAnisotropy, "nvn::initialize");
        NVN_CONFIRM(SamplerGetReductionFilter, "nvn::initialize");
        NVN_CONFIRM(SamplerCompare, "nvn::initialize");
        NVN_CONFIRM(SamplerGetDebugID, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetBlendTarget, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetBlendFunc, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetBlendEquation, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetAdvancedMode, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetAdvancedOverlap, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetAdvancedPremultipliedSrc, "nvn::initialize");
        NVN_CONFIRM(BlendStateSetAdvancedNormalizedDst, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetBlendTarget, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetBlendFunc, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetBlendEquation, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetAdvancedMode, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetAdvancedOverlap, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetAdvancedPremultipliedSrc, "nvn::initialize");
        NVN_CONFIRM(BlendStateGetAdvancedNormalizedDst, "nvn::initialize");
        NVN_CONFIRM(ColorStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(ColorStateSetBlendEnable, "nvn::initialize");
        NVN_CONFIRM(ColorStateSetLogicOp, "nvn::initialize");
        NVN_CONFIRM(ColorStateSetAlphaTest, "nvn::initialize");
        NVN_CONFIRM(ColorStateGetBlendEnable, "nvn::initialize");
        NVN_CONFIRM(ColorStateGetLogicOp, "nvn::initialize");
        NVN_CONFIRM(ColorStateGetAlphaTest, "nvn::initialize");
        NVN_CONFIRM(ChannelMaskStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(ChannelMaskStateSetChannelMask, "nvn::initialize");
        NVN_CONFIRM(ChannelMaskStateGetChannelMask, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetMultisampleEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetSamples, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetAlphaToCoverageEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetAlphaToCoverageDither, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetMultisampleEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetSamples, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetAlphaToCoverageEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetAlphaToCoverageDither, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetRasterSamples, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetRasterSamples, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetCoverageModulationMode, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetCoverageModulationMode, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetCoverageToColorEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetCoverageToColorEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetCoverageToColorOutput, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetCoverageToColorOutput, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetSampleLocationsEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetSampleLocationsEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetSampleLocationsGrid, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetSampleLocationsGridEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateGetSampleLocationsGridEnable, "nvn::initialize");
        NVN_CONFIRM(MultisampleStateSetSampleLocations, "nvn::initialize");
        NVN_CONFIRM(PolygonStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(PolygonStateSetCullFace, "nvn::initialize");
        NVN_CONFIRM(PolygonStateSetFrontFace, "nvn::initialize");
        NVN_CONFIRM(PolygonStateSetPolygonMode, "nvn::initialize");
        NVN_CONFIRM(PolygonStateSetPolygonOffsetEnables, "nvn::initialize");
        NVN_CONFIRM(PolygonStateGetCullFace, "nvn::initialize");
        NVN_CONFIRM(PolygonStateGetFrontFace, "nvn::initialize");
        NVN_CONFIRM(PolygonStateGetPolygonMode, "nvn::initialize");
        NVN_CONFIRM(PolygonStateGetPolygonOffsetEnables, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetDepthTestEnable, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetDepthWriteEnable, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetDepthFunc, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetStencilTestEnable, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetStencilFunc, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateSetStencilOp, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateGetDepthTestEnable, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateGetDepthWriteEnable, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateGetDepthFunc, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateGetStencilTestEnable, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateGetStencilFunc, "nvn::initialize");
        NVN_CONFIRM(DepthStencilStateGetStencilOp, "nvn::initialize");
        NVN_CONFIRM(VertexAttribStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(VertexAttribStateSetFormat, "nvn::initialize");
        NVN_CONFIRM(VertexAttribStateSetStreamIndex, "nvn::initialize");
        NVN_CONFIRM(VertexAttribStateGetFormat, "nvn::initialize");
        NVN_CONFIRM(VertexAttribStateGetStreamIndex, "nvn::initialize");
        NVN_CONFIRM(VertexStreamStateSetDefaults, "nvn::initialize");
        NVN_CONFIRM(VertexStreamStateSetStride, "nvn::initialize");
        NVN_CONFIRM(VertexStreamStateSetDivisor, "nvn::initialize");
        NVN_CONFIRM(VertexStreamStateGetStride, "nvn::initialize");
        NVN_CONFIRM(VertexStreamStateGetDivisor, "nvn::initialize");
        NVN_CONFIRM(CommandBufferInitialize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferFinalize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetMemoryCallback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetMemoryCallbackData, "nvn::initialize");
        NVN_CONFIRM(CommandBufferAddCommandMemory, "nvn::initialize");
        NVN_CONFIRM(CommandBufferAddControlMemory, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetCommandMemorySize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetCommandMemoryUsed, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetCommandMemoryFree, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetControlMemorySize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetControlMemoryUsed, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetControlMemoryFree, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBeginRecording, "nvn::initialize");
        NVN_CONFIRM(CommandBufferEndRecording, "nvn::initialize");
        NVN_CONFIRM(CommandBufferCallCommands, "nvn::initialize");
        NVN_CONFIRM(CommandBufferCopyCommands, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindBlendState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindChannelMaskState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindColorState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindMultisampleState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindPolygonState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindDepthStencilState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindVertexAttribState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindVertexStreamState, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindProgram, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindVertexBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindVertexBuffers, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindUniformBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindUniformBuffers, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindTransformFeedbackBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindTransformFeedbackBuffers, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindStorageBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindStorageBuffers, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindTexture, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindTextures, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindImage, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindImages, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetPatchSize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetInnerTessellationLevels, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetOuterTessellationLevels, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetPrimitiveRestart, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBeginTransformFeedback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferEndTransformFeedback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferPauseTransformFeedback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferResumeTransformFeedback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawTransformFeedback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawArrays, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawElements, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawElementsBaseVertex, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawArraysInstanced, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawElementsInstanced, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawArraysIndirect, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawElementsIndirect, "nvn::initialize");
        NVN_CONFIRM(CommandBufferMultiDrawArraysIndirectCount, "nvn::initialize");
        NVN_CONFIRM(CommandBufferMultiDrawElementsIndirectCount, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearColor, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearColori, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearColorui, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearDepthStencil, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDispatchCompute, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDispatchComputeIndirect, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetViewport, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetViewports, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetViewportSwizzles, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetScissor, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetScissors, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetDepthRange, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetDepthBounds, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetDepthRanges, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetTiledCacheAction, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetTiledCacheTileSize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetStencilValueMask, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetStencilMask, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetStencilRef, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetBlendColor, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetPointSize, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetLineWidth, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetPolygonOffsetClamp, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetAlphaRef, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetSampleMask, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetRasterizerDiscard, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetDepthClamp, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetConservativeRasterEnable, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetConservativeRasterDilate, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetSubpixelPrecisionBias, "nvn::initialize");
        NVN_CONFIRM(CommandBufferCopyBufferToTexture, "nvn::initialize");
        NVN_CONFIRM(CommandBufferCopyTextureToBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferCopyTextureToTexture, "nvn::initialize");
        NVN_CONFIRM(CommandBufferCopyBufferToBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearTexture, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearTexturei, "nvn::initialize");
        NVN_CONFIRM(CommandBufferClearTextureui, "nvn::initialize");
        NVN_CONFIRM(CommandBufferUpdateUniformBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferReportCounter, "nvn::initialize");
        NVN_CONFIRM(CommandBufferResetCounter, "nvn::initialize");
        NVN_CONFIRM(CommandBufferReportValue, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetRenderEnable, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetRenderEnableConditional, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetRenderTargets, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDiscardColor, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDiscardDepthStencil, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDownsample, "nvn::initialize");
        NVN_CONFIRM(CommandBufferTiledDownsample, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBarrier, "nvn::initialize");
        NVN_CONFIRM(CommandBufferWaitSync, "nvn::initialize");
        NVN_CONFIRM(CommandBufferFenceSync, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetTexturePool, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetSamplerPool, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetShaderScratchMemory, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSaveZCullData, "nvn::initialize");
        NVN_CONFIRM(CommandBufferRestoreZCullData, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetCopyRowStride, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetCopyImageStride, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetCopyRowStride, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetCopyImageStride, "nvn::initialize");
        NVN_CONFIRM(CommandBufferDrawTexture, "nvn::initialize");
        NVN_CONFIRM(ProgramSetSubroutineLinkage, "nvn::initialize");
        NVN_CONFIRM(CommandBufferSetProgramSubroutines, "nvn::initialize");
        NVN_CONFIRM(CommandBufferBindCoverageModulationTable, "nvn::initialize");
        NVN_CONFIRM(CommandBufferResolveDepthBuffer, "nvn::initialize");
        NVN_CONFIRM(CommandBufferPushDebugGroup, "nvn::initialize");
        NVN_CONFIRM(CommandBufferPopDebugGroup, "nvn::initialize");
        NVN_CONFIRM(CommandBufferInsertDebugMarker, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetMemoryCallback, "nvn::initialize");
        NVN_CONFIRM(CommandBufferGetMemoryCallbackData, "nvn::initialize");
        NVN_CONFIRM(CommandBufferIsRecording, "nvn::initialize");
        NVN_CONFIRM(SyncInitialize, "nvn::initialize");
        NVN_CONFIRM(SyncFinalize, "nvn::initialize");
        NVN_CONFIRM(SyncSetDebugLabel, "nvn::initialize");
        NVN_CONFIRM(QueueFenceSync, "nvn::initialize");
        NVN_CONFIRM(SyncWait, "nvn::initialize");
        NVN_CONFIRM(QueueWaitSync, "nvn::initialize");
#endif
    }

    void DeviceBuilder::SetDefaults() {
        NVN_VAR(DeviceBuilderSetDefaults)(this);
    }
    
    void DeviceBuilder::SetFlags(DeviceFlagBits flags) {
        NVN_VAR(DeviceBuilderSetFlags)(this, flags);
    }
    
    bool Device::Initialize(const DeviceBuilder* builder) {
        return NVN_VAR(DeviceInitialize)(this, builder);
    }
    
    void Device::Finalize() {
        NVN_VAR(DeviceFinalize)(this);
    }
    
    void Device::SetDebugLabel(const char* label) {
        NVN_VAR(DeviceSetDebugLabel)(this, label);
    }
    
    GenericFuncPtr Device::GetProcAddress(const char* name) const {
        return NVN_VAR(DeviceGetProcAddress)(this, name);
    }
    
    void Device::GetInteger(DeviceInfo pname, int* v) const {
        NVN_VAR(DeviceGetInteger)(this, pname, v);
    }
    
    uint64_t Device::GetCurrentTimestampInNanoseconds() const {
        return NVN_VAR(DeviceGetCurrentTimestampInNanoseconds)(this);
    }
    
    TextureHandle Device::GetTextureHandle(int textureID, int samplerID) const {
        return NVN_VAR(DeviceGetTextureHandle)(this, textureID, samplerID);
    }
    
    TextureHandle Device::GetTexelFetchHandle(int textureID) const {
        return NVN_VAR(DeviceGetTexelFetchHandle)(this, textureID);
    }
    
    ImageHandle Device::GetImageHandle(int imageID) const {
        return NVN_VAR(DeviceGetImageHandle)(this, imageID);
    }
    
    void Device::InstallDebugCallback(const DebugCallback callback, void* callbackData, bool enable) {
        NVN_VAR(DeviceInstallDebugCallback)(this, callback, callbackData, enable);
    }
    
    void Device::SetWindowOriginMode(WindowOriginMode windowOriginMode) {
        NVN_VAR(DeviceSetWindowOriginMode)(this, windowOriginMode);
    }
    
    void Device::SetDepthMode(DepthMode depthMode) {
        NVN_VAR(DeviceSetDepthMode)(this, depthMode);
    }
    
    bool Device::RegisterFastClearColor(const float* color, Format format) {
        return NVN_VAR(DeviceRegisterFastClearColor)(this, color, format);
    }
    
    bool Device::RegisterFastClearColori(const int* color, Format format) {
        return NVN_VAR(DeviceRegisterFastClearColori)(this, color, format);
    }
    
    bool Device::RegisterFastClearColorui(const uint32_t* color, Format format) {
        return NVN_VAR(DeviceRegisterFastClearColorui)(this, color, format);
    }
    
    bool Device::RegisterFastClearDepth(float depth) {
        return NVN_VAR(DeviceRegisterFastClearDepth)(depth, this);
    }
    
    WindowOriginMode Device::GetWindowOriginMode() const {
        return NVN_VAR(DeviceGetWindowOriginMode)(this);
    }
    
    DepthMode Device::GetDepthMode() const {
        return NVN_VAR(DeviceGetDepthMode)(this);
    }
    
    uint64_t Device::GetTimestampInNanoseconds(const CounterData* counterData) const {
        return NVN_VAR(DeviceGetTimestampInNanoseconds)(this, counterData);
    }
    
    void Device::ApplyDeferredFinalizes(int age) {
        NVN_VAR(DeviceApplyDeferredFinalizes)(this, age);
    }
    
    void Device::FinalizeCommandHandle(CommandHandle handles) {
        NVN_VAR(DeviceFinalizeCommandHandle)(this, handles);
    }
    
    DeviceWaitForErrorResult Device::WaitForError(uint64_t timeoutNs, DeviceErrorData* errorData) const {
        return NVN_VAR(DeviceWaitForError)(this, timeoutNs, errorData);
    }
    
    QueueGetErrorResult Queue::GetError(QueueErrorInfo* errorInfo) {
        return NVN_VAR(QueueGetError)(this, errorInfo);
    }
    
    QueueBuilder& QueueBuilder::SetDevice(Device* device) {
        NVN_VAR(QueueBuilderSetDevice)(this, device);
        return *this;
    }
    
    QueueBuilder& QueueBuilder::SetDefaults() {
        NVN_VAR(QueueBuilderSetDefaults)(this);
        return *this;
    }
    
    QueueBuilder& QueueBuilder::SetFlags(QueueFlags flags) {
        NVN_VAR(QueueBuilderSetFlags)(this, flags);
        return *this;
    }
    
    QueueBuilder& QueueBuilder::SetCommandMemorySize(size_t size) {
        NVN_VAR(QueueBuilderSetCommandMemorySize)(this, size);
        return *this;
    }
    
    QueueBuilder& QueueBuilder::SetComputeMemorySize(size_t size) {
        NVN_VAR(QueueBuilderSetComputeMemorySize)(this, size);
        return *this;
    }
    
    size_t QueueBuilder::GetQueueMemorySize() const {
        return NVN_VAR(QueueBuilderGetQueueMemorySize)(this);
    }
    
    QueueBuilder& QueueBuilder::SetQueueMemory(void* memory, size_t size) {
        NVN_VAR(QueueBuilderSetQueueMemory)(this, memory, size);
        return *this;
    }
    
    QueueBuilder& QueueBuilder::SetCommandFlushThreshold(size_t threshold) {
        NVN_VAR(QueueBuilderSetCommandFlushThreshold)(this, threshold);
        return *this;
    }
    
    bool Queue::Initialize(const QueueBuilder* builder) {
        return NVN_VAR(QueueInitialize)(this, builder);
    }
    
    void Queue::Finalize() {
        NVN_VAR(QueueFinalize)(this);
    }
    
    void Queue::SetDebugLabel(const char* label) {
        NVN_VAR(QueueSetDebugLabel)(this, label);
    }
    
    void Queue::SubmitCommands(int numCommands, const CommandHandle* handles) {
        NVN_VAR(QueueSubmitCommands)(this, numCommands, handles);
    }
    
    void Queue::Flush() {
        NVN_VAR(QueueFlush)(this);
    }
    
    void Queue::Finish() {
        NVN_VAR(QueueFinish)(this);
    }
    
    void Queue::PresentTexture(Window* window, int textureIndex) {
        NVN_VAR(QueuePresentTexture)(this, window, textureIndex);
    }
    
    QueueAcquireTextureResult Queue::AcquireTexture(Window* window, int* textureIndex) {
        return NVN_VAR(QueueAcquireTexture)(this, window, textureIndex);
    }
    
    WindowBuilder& WindowBuilder::SetDevice(Device* device) {
        NVN_VAR(WindowBuilderSetDevice)(this, device);
        return *this;
    }
    
    WindowBuilder& WindowBuilder::SetDefaults() {
        NVN_VAR(WindowBuilderSetDefaults)(this);
        return *this;
    }
    
    WindowBuilder& WindowBuilder::SetNativeWindow(NativeWindow nativeWindow) {
        NVN_VAR(WindowBuilderSetNativeWindow)(this, nativeWindow);
        return *this;
    }
    
    WindowBuilder& WindowBuilder::SetTextures(int numTextures, Texture* const* textures) {
        NVN_VAR(WindowBuilderSetTextures)(this, numTextures, textures);
        return *this;
    }
    
    WindowBuilder& WindowBuilder::SetPresentInterval(int presentInterval) {
        NVN_VAR(WindowBuilderSetPresentInterval)(this, presentInterval);
        return *this;
    }
    
    NativeWindow WindowBuilder::GetNativeWindow() const {
        return NVN_VAR(WindowBuilderGetNativeWindow)(this);
    }
    
    int WindowBuilder::GetPresentInterval() const {
        return NVN_VAR(WindowBuilderGetPresentInterval)(this);
    }
    
    bool Window::Initialize(const WindowBuilder* builder) {
        return NVN_VAR(WindowInitialize)(this, builder);
    }
    
    void Window::Finalize() {
        NVN_VAR(WindowFinalize)(this);
    }
    
    void Window::SetDebugLabel(const char* label) {
        NVN_VAR(WindowSetDebugLabel)(this, label);
    }
    
    WindowAcquireTextureResult Window::AcquireTexture(Sync* textureAvailableSync, int* textureIndex) {
        return NVN_VAR(WindowAcquireTexture)(this, textureAvailableSync, textureIndex);
    }
    
    NativeWindow Window::GetNativeWindow() const {
        return NVN_VAR(WindowGetNativeWindow)(this);
    }
    
    int Window::GetPresentInterval() const {
        return NVN_VAR(WindowGetPresentInterval)(this);
    }
    
    void Window::SetPresentInterval(int presentInterval) {
        NVN_VAR(WindowSetPresentInterval)(this, presentInterval);
    }
    
    void Window::SetCrop(int x, int y, int w, int h) {
        NVN_VAR(WindowSetCrop)(this, x, y, w, h);
    }
    
    bool Program::Initialize(Device* device) {
        return NVN_VAR(ProgramInitialize)(this, device);
    }
    
    void Program::Finalize() {
        NVN_VAR(ProgramFinalize)(this);
    }
    
    void Program::SetDebugLabel(const char* label) {
        NVN_VAR(ProgramSetDebugLabel)(this, label);
    }
    
    bool Program::SetShaders(int count, const ShaderData* stageData) {
        return NVN_VAR(ProgramSetShaders)(this, count, stageData);
    }
    
    MemoryPoolBuilder& MemoryPoolBuilder::SetDevice(Device* device) {
        NVN_VAR(MemoryPoolBuilderSetDevice)(this, device);
        return *this;
    }
    
    MemoryPoolBuilder& MemoryPoolBuilder::SetDefaults() {
        NVN_VAR(MemoryPoolBuilderSetDefaults)(this);
        return *this;
    }
    
    MemoryPoolBuilder& MemoryPoolBuilder::SetStorage(void* memory, size_t size) {
        NVN_VAR(MemoryPoolBuilderSetStorage)(this, memory, size);
        return *this;
    }
    
    MemoryPoolBuilder& MemoryPoolBuilder::SetFlags(MemoryPoolFlags flags) {
        NVN_VAR(MemoryPoolBuilderSetFlags)(this, flags);
        return *this;
    }
    
    void* MemoryPoolBuilder::GetMemory() const {
        return NVN_VAR(MemoryPoolBuilderGetMemory)(this);
    }
    
    size_t MemoryPoolBuilder::GetSize() const {
        return NVN_VAR(MemoryPoolBuilderGetSize)(this);
    }
    
    MemoryPoolFlags MemoryPoolBuilder::GetFlags() const {
        return NVN_VAR(MemoryPoolBuilderGetFlags)(this);
    }
    
    bool MemoryPool::Initialize(const MemoryPoolBuilder* builder) {
        return NVN_VAR(MemoryPoolInitialize)(this, builder);
    }
    
    void MemoryPool::SetDebugLabel(const char* label) {
        NVN_VAR(MemoryPoolSetDebugLabel)(this, label);
    }
    
    void MemoryPool::Finalize() {
        NVN_VAR(MemoryPoolFinalize)(this);
    }
    
    void* MemoryPool::Map() const {
        return NVN_VAR(MemoryPoolMap)(this);
    }
    
    void MemoryPool::FlushMappedRange(ptrdiff_t offset, size_t size) const {
        NVN_VAR(MemoryPoolFlushMappedRange)(this, offset, size);
    }
    
    void MemoryPool::InvalidateMappedRange(ptrdiff_t offset, size_t size) const {
        NVN_VAR(MemoryPoolInvalidateMappedRange)(this, offset, size);
    }
    
    BufferAddress MemoryPool::GetBufferAddress() const {
        return NVN_VAR(MemoryPoolGetBufferAddress)(this);
    }
    
    bool MemoryPool::MapVirtual(int numRequests, const MappingRequest* requests) {
        return NVN_VAR(MemoryPoolMapVirtual)(this, numRequests, requests);
    }
    
    size_t MemoryPool::GetSize() const {
        return NVN_VAR(MemoryPoolGetSize)(this);
    }
    
    MemoryPoolFlags MemoryPool::GetFlags() const {
        return NVN_VAR(MemoryPoolGetFlags)(this);
    }
    
    bool TexturePool::Initialize(const MemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors) {
        return NVN_VAR(TexturePoolInitialize)(this, memoryPool, offset, numDescriptors);
    }
    
    void TexturePool::SetDebugLabel(const char* label) {
        NVN_VAR(TexturePoolSetDebugLabel)(this, label);
    }
    
    void TexturePool::Finalize() {
        NVN_VAR(TexturePoolFinalize)(this);
    }
    
    void TexturePool::RegisterTexture(int id, const Texture* texture, const TextureView* view) const {
        NVN_VAR(TexturePoolRegisterTexture)(this, id, texture, view);
    }
    
    void TexturePool::RegisterImage(int id, const Texture* texture, const TextureView* view) const {
        NVN_VAR(TexturePoolRegisterImage)(this, id, texture, view);
    }
    
    const MemoryPool* TexturePool::GetMemoryPool() const {
        return NVN_VAR(TexturePoolGetMemoryPool)(this);
    }
    
    ptrdiff_t TexturePool::GetMemoryOffset() const {
        return NVN_VAR(TexturePoolGetMemoryOffset)(this);
    }
    
    int TexturePool::GetSize() const {
        return NVN_VAR(TexturePoolGetSize)(this);
    }
    
    bool SamplerPool::Initialize(const MemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors) {
        return NVN_VAR(SamplerPoolInitialize)(this, memoryPool, offset, numDescriptors);
    }
    
    void SamplerPool::SetDebugLabel(const char* label) {
        NVN_VAR(SamplerPoolSetDebugLabel)(this, label);
    }
    
    void SamplerPool::Finalize() {
        NVN_VAR(SamplerPoolFinalize)(this);
    }
    
    void SamplerPool::RegisterSampler(int id, const Sampler* sampler) const {
        NVN_VAR(SamplerPoolRegisterSampler)(this, id, sampler);
    }
    
    const MemoryPool* SamplerPool::GetMemoryPool() const {
        return NVN_VAR(SamplerPoolGetMemoryPool)(this);
    }
    
    ptrdiff_t SamplerPool::GetMemoryOffset() const {
        return NVN_VAR(SamplerPoolGetMemoryOffset)(this);
    }
    
    int SamplerPool::GetSize() const {
        return NVN_VAR(SamplerPoolGetSize)(this);
    }
    
    BufferBuilder& BufferBuilder::SetDevice(Device* device) {
        NVN_VAR(BufferBuilderSetDevice)(this, device);
        return *this;
    }
    
    BufferBuilder& BufferBuilder::SetDefaults() {
        NVN_VAR(BufferBuilderSetDefaults)(this);
        return *this;
    }
    
    BufferBuilder& BufferBuilder::SetStorage(MemoryPool* pool, ptrdiff_t offset, size_t size) {
        NVN_VAR(BufferBuilderSetStorage)(this, pool, offset, size);
        return *this;
    }
    
    MemoryPool* BufferBuilder::GetMemoryPool() const {
        return NVN_VAR(BufferBuilderGetMemoryPool)(this);
    }
    
    ptrdiff_t BufferBuilder::GetMemoryOffset() const {
        return NVN_VAR(BufferBuilderGetMemoryOffset)(this);
    }
    
    size_t BufferBuilder::GetSize() const {
        return NVN_VAR(BufferBuilderGetSize)(this);
    }
    
    bool Buffer::Initialize(const BufferBuilder* builder) {
        return NVN_VAR(BufferInitialize)(this, builder);
    }
    
    void Buffer::SetDebugLabel(const char* label) {
        NVN_VAR(BufferSetDebugLabel)(this, label);
    }
    
    void Buffer::Finalize() {
        NVN_VAR(BufferFinalize)(this);
    }
    
    void* Buffer::Map() const {
        return NVN_VAR(BufferMap)(this);
    }
    
    BufferAddress Buffer::GetAddress() const {
        return NVN_VAR(BufferGetAddress)(this);
    }
    
    void Buffer::FlushMappedRange(ptrdiff_t offset, size_t size) const {
        NVN_VAR(BufferFlushMappedRange)(this, offset, size);
    }
    
    void Buffer::InvalidateMappedRange(ptrdiff_t offset, size_t size) const {
        NVN_VAR(BufferInvalidateMappedRange)(this, offset, size);
    }
    
    MemoryPool* Buffer::GetMemoryPool() const {
        return NVN_VAR(BufferGetMemoryPool)(this);
    }
    
    ptrdiff_t Buffer::GetMemoryOffset() const {
        return NVN_VAR(BufferGetMemoryOffset)(this);
    }
    
    size_t Buffer::GetSize() const {
        return NVN_VAR(BufferGetSize)(this);
    }
    
    uint64_t Buffer::GetDebugID() const {
        return NVN_VAR(BufferGetDebugID)(this);
    }
    
    TextureBuilder& TextureBuilder::SetDevice(Device* device) {
        NVN_VAR(TextureBuilderSetDevice)(this, device);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetDefaults() {
        NVN_VAR(TextureBuilderSetDefaults)(this);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetFlags(TextureFlags flags) {
        NVN_VAR(TextureBuilderSetFlags)(this, flags);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetTarget(TextureTarget target) {
        NVN_VAR(TextureBuilderSetTarget)(this, target);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetWidth(int width) {
        NVN_VAR(TextureBuilderSetWidth)(this, width);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetHeight(int height) {
        NVN_VAR(TextureBuilderSetHeight)(this, height);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetDepth(int depth) {
        NVN_VAR(TextureBuilderSetDepth)(this, depth);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetSize1D(int width) {
        NVN_VAR(TextureBuilderSetSize1D)(this, width);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetSize2D(int width, int height) {
        NVN_VAR(TextureBuilderSetSize2D)(this, width, height);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetSize3D(int width, int height, int depth) {
        NVN_VAR(TextureBuilderSetSize3D)(this, width, height, depth);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetLevels(int numLevels) {
        NVN_VAR(TextureBuilderSetLevels)(this, numLevels);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetFormat(Format format) {
        NVN_VAR(TextureBuilderSetFormat)(this, format);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetSamples(int samples) {
        NVN_VAR(TextureBuilderSetSamples)(this, samples);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b, TextureSwizzle a) {
        NVN_VAR(TextureBuilderSetSwizzle)(this, r, g, b, a);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetDepthStencilMode(TextureDepthStencilMode mode) {
        NVN_VAR(TextureBuilderSetDepthStencilMode)(this, mode);
        return *this;
    }
    
    size_t TextureBuilder::GetStorageSize() const {
        return NVN_VAR(TextureBuilderGetStorageSize)(this);
    }
    
    size_t TextureBuilder::GetStorageAlignment() const {
        return NVN_VAR(TextureBuilderGetStorageAlignment)(this);
    }
    
    TextureBuilder& TextureBuilder::SetStorage(MemoryPool* pool, ptrdiff_t offset) {
        NVN_VAR(TextureBuilderSetStorage)(this, pool, offset);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetPackagedTextureData(const void* data) {
        NVN_VAR(TextureBuilderSetPackagedTextureData)(this, data);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetPackagedTextureLayout(const PackagedTextureLayout* layout) {
        NVN_VAR(TextureBuilderSetPackagedTextureLayout)(this, layout);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetStride(ptrdiff_t stride) {
        NVN_VAR(TextureBuilderSetStride)(this, stride);
        return *this;
    }
    
    TextureBuilder& TextureBuilder::SetGLTextureName(uint32_t name) {
        NVN_VAR(TextureBuilderSetGLTextureName)(this, name);
        return *this;
    }
    
    StorageClass TextureBuilder::GetStorageClass() const {
        return NVN_VAR(TextureBuilderGetStorageClass)(this);
    }
    
    TextureFlags TextureBuilder::GetFlags() const {
        return NVN_VAR(TextureBuilderGetFlags)(this);
    }
    
    TextureTarget TextureBuilder::GetTarget() const {
        return NVN_VAR(TextureBuilderGetTarget)(this);
    }
    
    int TextureBuilder::GetWidth() const {
        return NVN_VAR(TextureBuilderGetWidth)(this);
    }
    
    int TextureBuilder::GetHeight() const {
        return NVN_VAR(TextureBuilderGetHeight)(this);
    }
    
    int TextureBuilder::GetDepth() const {
        return NVN_VAR(TextureBuilderGetDepth)(this);
    }
    
    int TextureBuilder::GetLevels() const {
        return NVN_VAR(TextureBuilderGetLevels)(this);
    }
    
    Format TextureBuilder::GetFormat() const {
        return NVN_VAR(TextureBuilderGetFormat)(this);
    }
    
    int TextureBuilder::GetSamples() const {
        return NVN_VAR(TextureBuilderGetSamples)(this);
    }
    
    void TextureBuilder::GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b, TextureSwizzle* a) const {
        NVN_VAR(TextureBuilderGetSwizzle)(this, r, g, b, a);
    }
    
    TextureDepthStencilMode TextureBuilder::GetDepthStencilMode() const {
        return NVN_VAR(TextureBuilderGetDepthStencilMode)(this);
    }
    
    const void* TextureBuilder::GetPackagedTextureData() const {
        return NVN_VAR(TextureBuilderGetPackagedTextureData)(this);
    }
    
    ptrdiff_t TextureBuilder::GetStride() const {
        return NVN_VAR(TextureBuilderGetStride)(this);
    }
    
    void TextureBuilder::GetSparseTileLayout(TextureSparseTileLayout* layout) const {
        NVN_VAR(TextureBuilderGetSparseTileLayout)(this, layout);
    }
    
    uint32_t TextureBuilder::GetGLTextureName() const {
        return NVN_VAR(TextureBuilderGetGLTextureName)(this);
    }
    
    size_t TextureBuilder::GetZCullStorageSize() const {
        return NVN_VAR(TextureBuilderGetZCullStorageSize)(this);
    }
    
    MemoryPool* TextureBuilder::GetMemoryPool() const {
        return NVN_VAR(TextureBuilderGetMemoryPool)(this);
    }
    
    ptrdiff_t TextureBuilder::GetMemoryOffset() const {
        return NVN_VAR(TextureBuilderGetMemoryOffset)(this);
    }
    
    TextureView& TextureView::SetDefaults() {
        NVN_VAR(TextureViewSetDefaults)(this);
        return *this;
    }
    
    TextureView& TextureView::SetLevels(int baseLevel, int numLevels) {
        NVN_VAR(TextureViewSetLevels)(this, baseLevel, numLevels);
        return *this;
    }
    
    TextureView& TextureView::SetLayers(int minLayer, int numLayers) {
        NVN_VAR(TextureViewSetLayers)(this, minLayer, numLayers);
        return *this;
    }
    
    TextureView& TextureView::SetFormat(Format format) {
        NVN_VAR(TextureViewSetFormat)(this, format);
        return *this;
    }
    
    TextureView& TextureView::SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b, TextureSwizzle a) {
        NVN_VAR(TextureViewSetSwizzle)(this, r, g, b, a);
        return *this;
    }
    
    TextureView& TextureView::SetDepthStencilMode(TextureDepthStencilMode mode) {
        NVN_VAR(TextureViewSetDepthStencilMode)(this, mode);
        return *this;
    }
    
    TextureView& TextureView::SetTarget(TextureTarget target) {
        NVN_VAR(TextureViewSetTarget)(this, target);
        return *this;
    }
    
    bool TextureView::GetLevels(int* baseLevel, int* numLevels) const {
        return NVN_VAR(TextureViewGetLevels)(this, baseLevel, numLevels);
    }
    
    bool TextureView::GetLayers(int* minLayer, int* numLayers) const {
        return NVN_VAR(TextureViewGetLayers)(this, minLayer, numLayers);
    }
    
    bool TextureView::GetFormat(Format* format) const {
        return NVN_VAR(TextureViewGetFormat)(this, format);
    }
    
    bool TextureView::GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b, TextureSwizzle* a) const {
        return NVN_VAR(TextureViewGetSwizzle)(this, r, g, b, a);
    }
    
    bool TextureView::GetDepthStencilMode(TextureDepthStencilMode* mode) const {
        return NVN_VAR(TextureViewGetDepthStencilMode)(this, mode);
    }
    
    bool TextureView::GetTarget(TextureTarget* target) const {
        return NVN_VAR(TextureViewGetTarget)(this, target);
    }
    
    bool TextureView::Compare(const TextureView* otherView) const {
        return NVN_VAR(TextureViewCompare)(this, otherView);
    }
    
    bool Texture::Initialize(const TextureBuilder* builder) {
        return NVN_VAR(TextureInitialize)(this, builder);
    }
    
    size_t Texture::GetZCullStorageSize() const {
        return NVN_VAR(TextureGetZCullStorageSize)(this);
    }
    
    void Texture::Finalize() {
        NVN_VAR(TextureFinalize)(this);
    }
    
    void Texture::SetDebugLabel(const char* label) {
        NVN_VAR(TextureSetDebugLabel)(this, label);
    }
    
    StorageClass Texture::GetStorageClass() const {
        return NVN_VAR(TextureGetStorageClass)(this);
    }
    
    ptrdiff_t Texture::GetViewOffset(const TextureView* textureView) const {
        return NVN_VAR(TextureGetViewOffset)(this, textureView);
    }
    
    TextureFlags Texture::GetFlags() const {
        return NVN_VAR(TextureGetFlags)(this);
    }
    
    TextureTarget Texture::GetTarget() const {
        return NVN_VAR(TextureGetTarget)(this);
    }
    
    int Texture::GetWidth() const {
        return NVN_VAR(TextureGetWidth)(this);
    }
    
    int Texture::GetHeight() const {
        return NVN_VAR(TextureGetHeight)(this);
    }
    
    int Texture::GetDepth() const {
        return NVN_VAR(TextureGetDepth)(this);
    }
    
    int Texture::GetLevels() const {
        return NVN_VAR(TextureGetLevels)(this);
    }
    
    Format Texture::GetFormat() const {
        return NVN_VAR(TextureGetFormat)(this);
    }
    
    int Texture::GetSamples() const {
        return NVN_VAR(TextureGetSamples)(this);
    }
    
    void Texture::GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b, TextureSwizzle* a) const {
        NVN_VAR(TextureGetSwizzle)(this, r, g, b, a);
    }
    
    TextureDepthStencilMode Texture::GetDepthStencilMode() const {
        return NVN_VAR(TextureGetDepthStencilMode)(this);
    }
    
    ptrdiff_t Texture::GetStride() const {
        return NVN_VAR(TextureGetStride)(this);
    }
    
    TextureAddress Texture::GetTextureAddress() const {
        return NVN_VAR(TextureGetTextureAddress)(this);
    }
    
    void Texture::GetSparseTileLayout(TextureSparseTileLayout* layout) const {
        NVN_VAR(TextureGetSparseTileLayout)(this, layout);
    }
    
    void Texture::WriteTexels(const TextureView* textureView, const CopyRegion* region, const void* data) const {
        NVN_VAR(TextureWriteTexels)(this, textureView, region, data);
    }
    
    void Texture::ReadTexels(const TextureView* textureView, const CopyRegion* region, void* data) const {
        NVN_VAR(TextureReadTexels)(this, textureView, region, data);
    }
    
    void Texture::FlushTexels(const TextureView* textureView, const CopyRegion* region) const {
        NVN_VAR(TextureFlushTexels)(this, textureView, region);
    }
    
    void Texture::InvalidateTexels(const TextureView* textureView, const CopyRegion* region) const {
        NVN_VAR(TextureInvalidateTexels)(this, textureView, region);
    }
    
    MemoryPool* Texture::GetMemoryPool() const {
        return NVN_VAR(TextureGetMemoryPool)(this);
    }
    
    ptrdiff_t Texture::GetMemoryOffset() const {
        return NVN_VAR(TextureGetMemoryOffset)(this);
    }
    
    int Texture::GetStorageSize() const {
        return NVN_VAR(TextureGetStorageSize)(this);
    }
    
    bool Texture::Compare(const Texture* otherTexture) const {
        return NVN_VAR(TextureCompare)(this, otherTexture);
    }
    
    uint64_t Texture::GetDebugID() const {
        return NVN_VAR(TextureGetDebugID)(this);
    }
    
    SamplerBuilder& SamplerBuilder::SetDevice(Device* device) {
        NVN_VAR(SamplerBuilderSetDevice)(this, device);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetDefaults() {
        NVN_VAR(SamplerBuilderSetDefaults)(this);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetMinMagFilter(MinFilter min, MagFilter mag) {
        NVN_VAR(SamplerBuilderSetMinMagFilter)(this, min, mag);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetWrapMode(WrapMode s, WrapMode t, WrapMode r) {
        NVN_VAR(SamplerBuilderSetWrapMode)(this, s, t, r);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetLodClamp(float min, float max) {
        NVN_VAR(SamplerBuilderSetLodClamp)(this, min, max);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetLodBias(float bias) {
        NVN_VAR(SamplerBuilderSetLodBias)(this, bias);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetCompare(CompareMode mode, CompareFunc func) {
        NVN_VAR(SamplerBuilderSetCompare)(this, mode, func);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetBorderColor(const float* borderColor) {
        NVN_VAR(SamplerBuilderSetBorderColor)(this, borderColor);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetBorderColori(const int* borderColor) {
        NVN_VAR(SamplerBuilderSetBorderColori)(this, borderColor);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetBorderColorui(const uint32_t* borderColor) {
        NVN_VAR(SamplerBuilderSetBorderColorui)(this, borderColor);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetMaxAnisotropy(float maxAniso) {
        NVN_VAR(SamplerBuilderSetMaxAnisotropy)(this, maxAniso);
        return *this;
    }
    
    SamplerBuilder& SamplerBuilder::SetReductionFilter(SamplerReduction filter) {
        NVN_VAR(SamplerBuilderSetReductionFilter)(this, filter);
        return *this;
    }
    
    void SamplerBuilder::GetMinMagFilter(MinFilter* min, MagFilter* mag) const {
        NVN_VAR(SamplerBuilderGetMinMagFilter)(this, min, mag);
    }
    
    void SamplerBuilder::GetWrapMode(WrapMode* s, WrapMode* t, WrapMode* r) const {
        NVN_VAR(SamplerBuilderGetWrapMode)(this, s, t, r);
    }
    
    void SamplerBuilder::GetLodClamp(float* min, float* max) const {
        NVN_VAR(SamplerBuilderGetLodClamp)(this, min, max);
    }
    
    float SamplerBuilder::GetLodBias() const {
        return NVN_VAR(SamplerBuilderGetLodBias)(this);
    }
    
    void SamplerBuilder::GetCompare(CompareMode* mode, CompareFunc* func) const {
        NVN_VAR(SamplerBuilderGetCompare)(this, mode, func);
    }
    
    void SamplerBuilder::GetBorderColor(float* borderColor) const {
        NVN_VAR(SamplerBuilderGetBorderColor)(this, borderColor);
    }
    
    void SamplerBuilder::GetBorderColori(int* borderColor) const {
        NVN_VAR(SamplerBuilderGetBorderColori)(this, borderColor);
    }
    
    void SamplerBuilder::GetBorderColorui(uint32_t* borderColor) const {
        NVN_VAR(SamplerBuilderGetBorderColorui)(this, borderColor);
    }
    
    float SamplerBuilder::GetMaxAnisotropy() const {
        return NVN_VAR(SamplerBuilderGetMaxAnisotropy)(this);
    }
    
    SamplerReduction SamplerBuilder::GetReductionFilter() const {
        return NVN_VAR(SamplerBuilderGetReductionFilter)(this);
    }
    
    bool Sampler::Initialize(const SamplerBuilder* builder) {
        return NVN_VAR(SamplerInitialize)(this, builder);
    }
    
    void Sampler::Finalize() {
        NVN_VAR(SamplerFinalize)(this);
    }
    
    void Sampler::SetDebugLabel(const char* label) {
        NVN_VAR(SamplerSetDebugLabel)(this, label);
    }
    
    void Sampler::GetMinMagFilter(MinFilter* min, MagFilter* mag) const {
        NVN_VAR(SamplerGetMinMagFilter)(this, min, mag);
    }
    
    void Sampler::GetWrapMode(WrapMode* s, WrapMode* t, WrapMode* r) const {
        NVN_VAR(SamplerGetWrapMode)(this, s, t, r);
    }
    
    void Sampler::GetLodClamp(float* min, float* max) const {
        NVN_VAR(SamplerGetLodClamp)(this, min, max);
    }
    
    float Sampler::GetLodBias() const {
        return NVN_VAR(SamplerGetLodBias)(this);
    }
    
    void Sampler::GetCompare(CompareMode* mode, CompareFunc* func) const {
        NVN_VAR(SamplerGetCompare)(this, mode, func);
    }
    
    void Sampler::GetBorderColor(float* borderColor) const {
        NVN_VAR(SamplerGetBorderColor)(this, borderColor);
    }
    
    void Sampler::GetBorderColori(int* borderColor) const {
        NVN_VAR(SamplerGetBorderColori)(this, borderColor);
    }
    
    void Sampler::GetBorderColorui(uint32_t* borderColor) const {
        NVN_VAR(SamplerGetBorderColorui)(this, borderColor);
    }
    
    float Sampler::GetMaxAnisotropy() const {
        return NVN_VAR(SamplerGetMaxAnisotropy)(this);
    }
    
    SamplerReduction Sampler::GetReductionFilter() const {
        return NVN_VAR(SamplerGetReductionFilter)(this);
    }
    
    bool Sampler::Compare(const Sampler* otherSampler) const {
        return NVN_VAR(SamplerCompare)(this, otherSampler);
    }
    
    uint64_t Sampler::GetDebugID() const {
        return NVN_VAR(SamplerGetDebugID)(this);
    }
    
    BlendState& BlendState::SetDefaults() {
        NVN_VAR(BlendStateSetDefaults)(this);
        return *this;
    }
    
    BlendState& BlendState::SetBlendTarget(int target) {
        NVN_VAR(BlendStateSetBlendTarget)(this, target);
        return *this;
    }
    
    BlendState& BlendState::SetBlendFunc(BlendFunc srcFunc, BlendFunc dstFunc, BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha) {
        NVN_VAR(BlendStateSetBlendFunc)(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
        return *this;
    }
    
    BlendState& BlendState::SetBlendEquation(BlendEquation modeRGB, BlendEquation modeAlpha) {
        NVN_VAR(BlendStateSetBlendEquation)(this, modeRGB, modeAlpha);
        return *this;
    }
    
    BlendState& BlendState::SetAdvancedMode(BlendAdvancedMode overlap) {
        NVN_VAR(BlendStateSetAdvancedMode)(this, overlap);
        return *this;
    }
    
    BlendState& BlendState::SetAdvancedOverlap(BlendAdvancedOverlap overlap) {
        NVN_VAR(BlendStateSetAdvancedOverlap)(this, overlap);
        return *this;
    }
    
    BlendState& BlendState::SetAdvancedPremultipliedSrc(bool premultiplied) {
        NVN_VAR(BlendStateSetAdvancedPremultipliedSrc)(this, premultiplied);
        return *this;
    }
    
    BlendState& BlendState::SetAdvancedNormalizedDst(bool normalized) {
        NVN_VAR(BlendStateSetAdvancedNormalizedDst)(this, normalized);
        return *this;
    }
    
    int BlendState::GetBlendTarget() const {
        return NVN_VAR(BlendStateGetBlendTarget)(this);
    }
    
    void BlendState::GetBlendFunc(BlendFunc* srcFunc, BlendFunc* dstFunc, BlendFunc* srcFuncAlpha, BlendFunc* dstFuncAlpha) const {
        NVN_VAR(BlendStateGetBlendFunc)(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
    }
    
    void BlendState::GetBlendEquation(BlendEquation* modeRGB, BlendEquation* modeAlpha) const {
        NVN_VAR(BlendStateGetBlendEquation)(this, modeRGB, modeAlpha);
    }
    
    BlendAdvancedMode BlendState::GetAdvancedMode() const {
        return NVN_VAR(BlendStateGetAdvancedMode)(this);
    }
    
    BlendAdvancedOverlap BlendState::GetAdvancedOverlap() const {
        return NVN_VAR(BlendStateGetAdvancedOverlap)(this);
    }
    
    bool BlendState::GetAdvancedPremultipliedSrc() const {
        return NVN_VAR(BlendStateGetAdvancedPremultipliedSrc)(this);
    }
    
    bool BlendState::GetAdvancedNormalizedDst() const {
        return NVN_VAR(BlendStateGetAdvancedNormalizedDst)(this);
    }
    
    ColorState& ColorState::SetDefaults() {
        NVN_VAR(ColorStateSetDefaults)(this);
        return *this;
    }
    
    ColorState& ColorState::SetBlendEnable(int index, bool enable) {
        NVN_VAR(ColorStateSetBlendEnable)(this, index, enable);
        return *this;
    }
    
    ColorState& ColorState::SetLogicOp(LogicOp logicOp) {
        NVN_VAR(ColorStateSetLogicOp)(this, logicOp);
        return *this;
    }
    
    ColorState& ColorState::SetAlphaTest(AlphaFunc alphaTest) {
        NVN_VAR(ColorStateSetAlphaTest)(this, alphaTest);
        return *this;
    }
    
    bool ColorState::GetBlendEnable(int index) const {
        return NVN_VAR(ColorStateGetBlendEnable)(this, index);
    }
    
    LogicOp ColorState::GetLogicOp() const {
        return NVN_VAR(ColorStateGetLogicOp)(this);
    }
    
    AlphaFunc ColorState::GetAlphaTest() const {
        return NVN_VAR(ColorStateGetAlphaTest)(this);
    }
    
    ChannelMaskState& ChannelMaskState::SetDefaults() {
        NVN_VAR(ChannelMaskStateSetDefaults)(this);
        return *this;
    }
    
    ChannelMaskState& ChannelMaskState::SetChannelMask(int index, bool r, bool g, bool b, bool a) {
        NVN_VAR(ChannelMaskStateSetChannelMask)(this, index, r, g, b, a);
        return *this;
    }
    
    void ChannelMaskState::GetChannelMask(int index, bool* r, bool* g, bool* b, bool* a) const {
        NVN_VAR(ChannelMaskStateGetChannelMask)(this, index, r, g, b, a);
    }
    
    MultisampleState& MultisampleState::SetDefaults() {
        NVN_VAR(MultisampleStateSetDefaults)(this);
        return *this;
    }
    
    MultisampleState& MultisampleState::SetMultisampleEnable(bool enable) {
        NVN_VAR(MultisampleStateSetMultisampleEnable)(this, enable);
        return *this;
    }
    
    MultisampleState& MultisampleState::SetSamples(int samples) {
        NVN_VAR(MultisampleStateSetSamples)(this, samples);
        return *this;
    }
    
    MultisampleState& MultisampleState::SetAlphaToCoverageEnable(bool enable) {
        NVN_VAR(MultisampleStateSetAlphaToCoverageEnable)(this, enable);
        return *this;
    }
    
    MultisampleState& MultisampleState::SetAlphaToCoverageDither(bool dither) {
        NVN_VAR(MultisampleStateSetAlphaToCoverageDither)(this, dither);
        return *this;
    }
    
    bool MultisampleState::GetMultisampleEnable() const {
        return NVN_VAR(MultisampleStateGetMultisampleEnable)(this);
    }
    
    int MultisampleState::GetSamples() const {
        return NVN_VAR(MultisampleStateGetSamples)(this);
    }
    
    bool MultisampleState::GetAlphaToCoverageEnable() const {
        return NVN_VAR(MultisampleStateGetAlphaToCoverageEnable)(this);
    }
    
    bool MultisampleState::GetAlphaToCoverageDither() const {
        return NVN_VAR(MultisampleStateGetAlphaToCoverageDither)(this);
    }
    
    MultisampleState& MultisampleState::SetRasterSamples(int rasterSamples) {
        NVN_VAR(MultisampleStateSetRasterSamples)(this, rasterSamples);
        return *this;
    }
    
    int MultisampleState::GetRasterSamples() {
        return NVN_VAR(MultisampleStateGetRasterSamples)(this);
    }
    
    MultisampleState& MultisampleState::SetCoverageModulationMode(CoverageModulationMode mode) {
        NVN_VAR(MultisampleStateSetCoverageModulationMode)(this, mode);
        return *this;
    }
    
    CoverageModulationMode MultisampleState::GetCoverageModulationMode() const {
        return NVN_VAR(MultisampleStateGetCoverageModulationMode)(this);
    }
    
    MultisampleState& MultisampleState::SetCoverageToColorEnable(bool enable) {
        NVN_VAR(MultisampleStateSetCoverageToColorEnable)(this, enable);
        return *this;
    }
    
    bool MultisampleState::GetCoverageToColorEnable() const {
        return NVN_VAR(MultisampleStateGetCoverageToColorEnable)(this);
    }
    
    MultisampleState& MultisampleState::SetCoverageToColorOutput(int color) {
        NVN_VAR(MultisampleStateSetCoverageToColorOutput)(this, color);
        return *this;
    }
    
    int MultisampleState::GetCoverageToColorOutput() const {
        return NVN_VAR(MultisampleStateGetCoverageToColorOutput)(this);
    }
    
    MultisampleState& MultisampleState::SetSampleLocationsEnable(bool enable) {
        NVN_VAR(MultisampleStateSetSampleLocationsEnable)(this, enable);
        return *this;
    }
    
    bool MultisampleState::GetSampleLocationsEnable() const {
        return NVN_VAR(MultisampleStateGetSampleLocationsEnable)(this);
    }
    
    void MultisampleState::GetSampleLocationsGrid(int* width, int* height) {
        NVN_VAR(MultisampleStateGetSampleLocationsGrid)(this, width, height);
    }
    
    MultisampleState& MultisampleState::SetSampleLocationsGridEnable(bool enable) {
        NVN_VAR(MultisampleStateSetSampleLocationsGridEnable)(this, enable);
        return *this;
    }
    
    bool MultisampleState::GetSampleLocationsGridEnable() const {
        return NVN_VAR(MultisampleStateGetSampleLocationsGridEnable)(this);
    }
    
    MultisampleState& MultisampleState::SetSampleLocations(int start, int count, const float* values) {
        NVN_VAR(MultisampleStateSetSampleLocations)(this, start, count, values);
        return *this;
    }
    
    PolygonState& PolygonState::SetDefaults() {
        NVN_VAR(PolygonStateSetDefaults)(this);
        return *this;
    }
    
    PolygonState& PolygonState::SetCullFace(Face face) {
        NVN_VAR(PolygonStateSetCullFace)(this, face);
        return *this;
    }
    
    PolygonState& PolygonState::SetFrontFace(FrontFace face) {
        NVN_VAR(PolygonStateSetFrontFace)(this, face);
        return *this;
    }
    
    PolygonState& PolygonState::SetPolygonMode(PolygonMode polygonMode) {
        NVN_VAR(PolygonStateSetPolygonMode)(this, polygonMode);
        return *this;
    }
    
    PolygonState& PolygonState::SetPolygonOffsetEnables(PolygonOffsetEnable enables) {
        NVN_VAR(PolygonStateSetPolygonOffsetEnables)(this, enables);
        return *this;
    }
    
    Face PolygonState::GetCullFace() const {
        return NVN_VAR(PolygonStateGetCullFace)(this);
    }
    
    FrontFace PolygonState::GetFrontFace() const {
        return NVN_VAR(PolygonStateGetFrontFace)(this);
    }
    
    PolygonMode PolygonState::GetPolygonMode() const {
        return NVN_VAR(PolygonStateGetPolygonMode)(this);
    }
    
    PolygonOffsetEnable PolygonState::GetPolygonOffsetEnables() const {
        return NVN_VAR(PolygonStateGetPolygonOffsetEnables)(this);
    }
    
    DepthStencilState& DepthStencilState::SetDefaults() {
        NVN_VAR(DepthStencilStateSetDefaults)(this);
        return *this;
    }
    
    DepthStencilState& DepthStencilState::SetDepthTestEnable(bool enable) {
        NVN_VAR(DepthStencilStateSetDepthTestEnable)(this, enable);
        return *this;
    }
    
    DepthStencilState& DepthStencilState::SetDepthWriteEnable(bool enable) {
        NVN_VAR(DepthStencilStateSetDepthWriteEnable)(this, enable);
        return *this;
    }
    
    DepthStencilState& DepthStencilState::SetDepthFunc(DepthFunc func) {
        NVN_VAR(DepthStencilStateSetDepthFunc)(this, func);
        return *this;
    }
    
    DepthStencilState& DepthStencilState::SetStencilTestEnable(bool enable) {
        NVN_VAR(DepthStencilStateSetStencilTestEnable)(this, enable);
        return *this;
    }
    
    DepthStencilState& DepthStencilState::SetStencilFunc(Face faces, StencilFunc func) {
        NVN_VAR(DepthStencilStateSetStencilFunc)(this, faces, func);
        return *this;
    }
    
    DepthStencilState& DepthStencilState::SetStencilOp(Face faces, StencilOp fail, StencilOp depthFail, StencilOp depthPass) {
        NVN_VAR(DepthStencilStateSetStencilOp)(this, faces, fail, depthFail, depthPass);
        return *this;
    }
    
    bool DepthStencilState::GetDepthTestEnable() const {
        return NVN_VAR(DepthStencilStateGetDepthTestEnable)(this);
    }
    
    bool DepthStencilState::GetDepthWriteEnable() const {
        return NVN_VAR(DepthStencilStateGetDepthWriteEnable)(this);
    }
    
    DepthFunc DepthStencilState::GetDepthFunc() const {
        return NVN_VAR(DepthStencilStateGetDepthFunc)(this);
    }
    
    bool DepthStencilState::GetStencilTestEnable() const {
        return NVN_VAR(DepthStencilStateGetStencilTestEnable)(this);
    }
    
    StencilFunc DepthStencilState::GetStencilFunc(Face face) const {
        return NVN_VAR(DepthStencilStateGetStencilFunc)(this, face);
    }
    
    void DepthStencilState::GetStencilOp(Face face, StencilOp* fail, StencilOp* depthFail, StencilOp* depthPass) const {
        NVN_VAR(DepthStencilStateGetStencilOp)(this, face, fail, depthFail, depthPass);
    }
    
    VertexAttribState& VertexAttribState::SetDefaults() {
        NVN_VAR(VertexAttribStateSetDefaults)(this);
        return *this;
    }
    
    VertexAttribState& VertexAttribState::SetFormat(Format format, ptrdiff_t relativeOffset) {
        NVN_VAR(VertexAttribStateSetFormat)(this, format, relativeOffset);
        return *this;
    }
    
    VertexAttribState& VertexAttribState::SetStreamIndex(int streamIndex) {
        NVN_VAR(VertexAttribStateSetStreamIndex)(this, streamIndex);
        return *this;
    }
    
    void VertexAttribState::GetFormat(Format* format, ptrdiff_t* relativeOffset) const {
        NVN_VAR(VertexAttribStateGetFormat)(this, format, relativeOffset);
    }
    
    int VertexAttribState::GetStreamIndex() const {
        return NVN_VAR(VertexAttribStateGetStreamIndex)(this);
    }
    
    VertexStreamState& VertexStreamState::SetDefaults() {
        NVN_VAR(VertexStreamStateSetDefaults)(this);
        return *this;
    }
    
    VertexStreamState& VertexStreamState::SetStride(ptrdiff_t stride) {
        NVN_VAR(VertexStreamStateSetStride)(this, stride);
        return *this;
    }
    
    VertexStreamState& VertexStreamState::SetDivisor(int divisor) {
        NVN_VAR(VertexStreamStateSetDivisor)(this, divisor);
        return *this;
    }
    
    ptrdiff_t VertexStreamState::GetStride() const {
        return NVN_VAR(VertexStreamStateGetStride)(this);
    }
    
    int VertexStreamState::GetDivisor() const {
        return NVN_VAR(VertexStreamStateGetDivisor)(this);
    }
    
    bool CommandBuffer::Initialize(Device* device) {
        return NVN_VAR(CommandBufferInitialize)(this, device);
    }
    
    void CommandBuffer::Finalize() {
        NVN_VAR(CommandBufferFinalize)(this);
    }
    
    void CommandBuffer::SetDebugLabel(const char* label) {
        NVN_VAR(CommandBufferSetDebugLabel)(this, label);
    }
    
    void CommandBuffer::SetMemoryCallback(CommandBufferMemoryCallback callback) {
        NVN_VAR(CommandBufferSetMemoryCallback)(this, callback);
    }
    
    void CommandBuffer::SetMemoryCallbackData(void* callbackData) {
        NVN_VAR(CommandBufferSetMemoryCallbackData)(this, callbackData);
    }
    
    void CommandBuffer::AddCommandMemory(const MemoryPool* pool, ptrdiff_t offset, size_t size) {
        NVN_VAR(CommandBufferAddCommandMemory)(this, pool, offset, size);
    }
    
    void CommandBuffer::AddControlMemory(void* memory, size_t size) {
        NVN_VAR(CommandBufferAddControlMemory)(this, memory, size);
    }
    
    size_t CommandBuffer::GetCommandMemorySize() const {
        return NVN_VAR(CommandBufferGetCommandMemorySize)(this);
    }
    
    size_t CommandBuffer::GetCommandMemoryUsed() const {
        return NVN_VAR(CommandBufferGetCommandMemoryUsed)(this);
    }
    
    size_t CommandBuffer::GetCommandMemoryFree() const {
        return NVN_VAR(CommandBufferGetCommandMemoryFree)(this);
    }
    
    size_t CommandBuffer::GetControlMemorySize() const {
        return NVN_VAR(CommandBufferGetControlMemorySize)(this);
    }
    
    size_t CommandBuffer::GetControlMemoryUsed() const {
        return NVN_VAR(CommandBufferGetControlMemoryUsed)(this);
    }
    
    size_t CommandBuffer::GetControlMemoryFree() const {
        return NVN_VAR(CommandBufferGetControlMemoryFree)(this);
    }
    
    void CommandBuffer::BeginRecording() {
        NVN_VAR(CommandBufferBeginRecording)(this);
    }
    
    CommandHandle CommandBuffer::EndRecording() {
        return NVN_VAR(CommandBufferEndRecording)(this);
    }
    
    void CommandBuffer::CallCommands(int numCommands, const CommandHandle* handles) {
        NVN_VAR(CommandBufferCallCommands)(this, numCommands, handles);
    }
    
    void CommandBuffer::CopyCommands(int numCommands, const CommandHandle* handles) {
        NVN_VAR(CommandBufferCopyCommands)(this, numCommands, handles);
    }
    
    void CommandBuffer::BindBlendState(const BlendState* blend) {
        NVN_VAR(CommandBufferBindBlendState)(this, blend);
    }
    
    void CommandBuffer::BindChannelMaskState(const ChannelMaskState* channelMask) {
        NVN_VAR(CommandBufferBindChannelMaskState)(this, channelMask);
    }
    
    void CommandBuffer::BindColorState(const ColorState* color) {
        NVN_VAR(CommandBufferBindColorState)(this, color);
    }
    
    void CommandBuffer::BindMultisampleState(const MultisampleState* multisample) {
        NVN_VAR(CommandBufferBindMultisampleState)(this, multisample);
    }
    
    void CommandBuffer::BindPolygonState(const PolygonState* polygon) {
        NVN_VAR(CommandBufferBindPolygonState)(this, polygon);
    }
    
    void CommandBuffer::BindDepthStencilState(const DepthStencilState* depthStencil) {
        NVN_VAR(CommandBufferBindDepthStencilState)(this, depthStencil);
    }
    
    void CommandBuffer::BindVertexAttribState(int numAttribs, const VertexAttribState* attribs) {
        NVN_VAR(CommandBufferBindVertexAttribState)(this, numAttribs, attribs);
    }
    
    void CommandBuffer::BindVertexStreamState(int numStreams, const VertexStreamState* streams) {
        NVN_VAR(CommandBufferBindVertexStreamState)(this, numStreams, streams);
    }
    
    void CommandBuffer::BindProgram(const Program* program, ShaderStageBits stages) {
        NVN_VAR(CommandBufferBindProgram)(this, program, stages);
    }
    
    void CommandBuffer::BindVertexBuffer(int index, BufferAddress buffer, size_t size) {
        NVN_VAR(CommandBufferBindVertexBuffer)(this, index, buffer, size);
    }
    
    void CommandBuffer::BindVertexBuffers(int first, int count, const BufferRange* buffers) {
        NVN_VAR(CommandBufferBindVertexBuffers)(this, first, count, buffers);
    }
    
    void CommandBuffer::BindUniformBuffer(ShaderStage stage, int index, BufferAddress buffer, size_t size) {
        NVN_VAR(CommandBufferBindUniformBuffer)(this, stage, index, buffer, size);
    }
    
    void CommandBuffer::BindUniformBuffers(ShaderStage stage, int first, int count, const BufferRange* buffers) {
        NVN_VAR(CommandBufferBindUniformBuffers)(this, stage, first, count, buffers);
    }
    
    void CommandBuffer::BindTransformFeedbackBuffer(int index, BufferAddress buffer, size_t size) {
        NVN_VAR(CommandBufferBindTransformFeedbackBuffer)(this, index, buffer, size);
    }
    
    void CommandBuffer::BindTransformFeedbackBuffers(int first, int count, const BufferRange* buffers) {
        NVN_VAR(CommandBufferBindTransformFeedbackBuffers)(this, first, count, buffers);
    }
    
    void CommandBuffer::BindStorageBuffer(ShaderStage stage, int index, BufferAddress buffer, size_t size) {
        NVN_VAR(CommandBufferBindStorageBuffer)(this, stage, index, buffer, size);
    }
    
    void CommandBuffer::BindStorageBuffers(ShaderStage stage, int first, int count, const BufferRange* buffers) {
        NVN_VAR(CommandBufferBindStorageBuffers)(this, stage, first, count, buffers);
    }
    
    void CommandBuffer::BindTexture(ShaderStage stage, int index, TextureHandle texture) {
        NVN_VAR(CommandBufferBindTexture)(this, stage, index, texture);
    }
    
    void CommandBuffer::BindTextures(ShaderStage stage, int first, int count, const TextureHandle* textures) {
        NVN_VAR(CommandBufferBindTextures)(this, stage, first, count, textures);
    }
    
    void CommandBuffer::BindImage(ShaderStage stage, int index, ImageHandle image) {
        NVN_VAR(CommandBufferBindImage)(this, stage, index, image);
    }
    
    void CommandBuffer::BindImages(ShaderStage stage, int first, int count, const ImageHandle* images) {
        NVN_VAR(CommandBufferBindImages)(this, stage, first, count, images);
    }
    
    void CommandBuffer::SetPatchSize(int size) {
        NVN_VAR(CommandBufferSetPatchSize)(this, size);
    }
    
    void CommandBuffer::SetInnerTessellationLevels(const float* levels) {
        NVN_VAR(CommandBufferSetInnerTessellationLevels)(this, levels);
    }
    
    void CommandBuffer::SetOuterTessellationLevels(const float* levels) {
        NVN_VAR(CommandBufferSetOuterTessellationLevels)(this, levels);
    }
    
    void CommandBuffer::SetPrimitiveRestart(bool enable, int index) {
        NVN_VAR(CommandBufferSetPrimitiveRestart)(this, enable, index);
    }
    
    void CommandBuffer::BeginTransformFeedback(BufferAddress buffer) {
        NVN_VAR(CommandBufferBeginTransformFeedback)(this, buffer);
    }
    
    void CommandBuffer::EndTransformFeedback(BufferAddress buffer) {
        NVN_VAR(CommandBufferEndTransformFeedback)(this, buffer);
    }
    
    void CommandBuffer::PauseTransformFeedback(BufferAddress buffer) {
        NVN_VAR(CommandBufferPauseTransformFeedback)(this, buffer);
    }
    
    void CommandBuffer::ResumeTransformFeedback(BufferAddress buffer) {
        NVN_VAR(CommandBufferResumeTransformFeedback)(this, buffer);
    }
    
    void CommandBuffer::DrawTransformFeedback(DrawPrimitive mode, BufferAddress buffer) {
        NVN_VAR(CommandBufferDrawTransformFeedback)(this, mode, buffer);
    }
    
    void CommandBuffer::DrawArrays(DrawPrimitive mode, int first, int count) {
        NVN_VAR(CommandBufferDrawArrays)(this, mode, first, count);
    }
    
    void CommandBuffer::DrawElements(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer) {
        NVN_VAR(CommandBufferDrawElements)(this, mode, type, count, indexBuffer);
    }
    
    void CommandBuffer::DrawElementsBaseVertex(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer, int baseVertex) {
        NVN_VAR(CommandBufferDrawElementsBaseVertex)(this, mode, type, count, indexBuffer, baseVertex);
    }
    
    void CommandBuffer::DrawArraysInstanced(DrawPrimitive mode, int first, int count, int baseInstance, int instanceCount) {
        NVN_VAR(CommandBufferDrawArraysInstanced)(this, mode, first, count, baseInstance, instanceCount);
    }
    
    void CommandBuffer::DrawElementsInstanced(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer, int baseVertex, int baseInstance, int instanceCount) {
        NVN_VAR(CommandBufferDrawElementsInstanced)(this, mode, type, count, indexBuffer, baseVertex, baseInstance, instanceCount);
    }
    
    void CommandBuffer::DrawArraysIndirect(DrawPrimitive mode, BufferAddress indirectBuffer) {
        NVN_VAR(CommandBufferDrawArraysIndirect)(this, mode, indirectBuffer);
    }
    
    void CommandBuffer::DrawElementsIndirect(DrawPrimitive mode, IndexType type, BufferAddress indexBuffer, BufferAddress indirectBuffer) {
        NVN_VAR(CommandBufferDrawElementsIndirect)(this, mode, type, indexBuffer, indirectBuffer);
    }
    
    void CommandBuffer::MultiDrawArraysIndirectCount(DrawPrimitive mode, BufferAddress indirectBuffer, BufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride) {
        NVN_VAR(CommandBufferMultiDrawArraysIndirectCount)(this, mode, indirectBuffer, parameterBuffer, maxDrawCount, stride);
    }
    
    void CommandBuffer::MultiDrawElementsIndirectCount(DrawPrimitive mode, IndexType type, BufferAddress indexBuffer, BufferAddress indirectBuffer, BufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride) {
        NVN_VAR(CommandBufferMultiDrawElementsIndirectCount)(this, mode, type, indexBuffer, indirectBuffer, parameterBuffer, maxDrawCount, stride);
    }
    
    void CommandBuffer::ClearColor(int index, const float* color, ClearColorMask mask) {
        NVN_VAR(CommandBufferClearColor)(this, index, color, mask);
    }
    
    void CommandBuffer::ClearColori(int index, const int* color, ClearColorMask mask) {
        NVN_VAR(CommandBufferClearColori)(this, index, color, mask);
    }
    
    void CommandBuffer::ClearColorui(int index, const uint32_t* color, ClearColorMask mask) {
        NVN_VAR(CommandBufferClearColorui)(this, index, color, mask);
    }
    
    void CommandBuffer::ClearDepthStencil(float depthValue, bool depthMask, int stencilValue, int stencilMask) {
        NVN_VAR(CommandBufferClearDepthStencil)(this, depthValue, depthMask, stencilValue, stencilMask);
    }
    
    void CommandBuffer::DispatchCompute(int groupsX, int groupsY, int groupsZ) {
        NVN_VAR(CommandBufferDispatchCompute)(this, groupsX, groupsY, groupsZ);
    }
    
    void CommandBuffer::DispatchComputeIndirect(BufferAddress indirectBuffer) {
        NVN_VAR(CommandBufferDispatchComputeIndirect)(this, indirectBuffer);
    }
    
    void CommandBuffer::SetViewport(int x, int y, int w, int h) {
        NVN_VAR(CommandBufferSetViewport)(this, x, y, w, h);
    }
    
    void CommandBuffer::SetViewports(int first, int count, const float* ranges) {
        NVN_VAR(CommandBufferSetViewports)(this, first, count, ranges);
    }
    
    void CommandBuffer::SetViewportSwizzles(int first, int count, const ViewportSwizzle* swizzles) {
        NVN_VAR(CommandBufferSetViewportSwizzles)(this, first, count, swizzles);
    }
    
    void CommandBuffer::SetScissor(int x, int y, int w, int h) {
        NVN_VAR(CommandBufferSetScissor)(this, x, y, w, h);
    }
    
    void CommandBuffer::SetScissors(int first, int count, const int* rects) {
        NVN_VAR(CommandBufferSetScissors)(this, first, count, rects);
    }
    
    void CommandBuffer::SetDepthRange(float n, float f) {
        NVN_VAR(CommandBufferSetDepthRange)(this, n, f);
    }
    
    void CommandBuffer::SetDepthBounds(bool enable, float n, float f) {
        NVN_VAR(CommandBufferSetDepthBounds)(this, enable, n, f);
    }
    
    void CommandBuffer::SetDepthRanges(int first, int count, const float* ranges) {
        NVN_VAR(CommandBufferSetDepthRanges)(this, first, count, ranges);
    }
    
    void CommandBuffer::SetTiledCacheAction(TiledCacheAction action) {
        NVN_VAR(CommandBufferSetTiledCacheAction)(this, action);
    }
    
    void CommandBuffer::SetTiledCacheTileSize(int tileWidth, int tileHeight) {
        NVN_VAR(CommandBufferSetTiledCacheTileSize)(this, tileWidth, tileHeight);
    }
    
    void CommandBuffer::SetStencilValueMask(Face faces, int mask) {
        NVN_VAR(CommandBufferSetStencilValueMask)(this, faces, mask);
    }
    
    void CommandBuffer::SetStencilMask(Face faces, int mask) {
        NVN_VAR(CommandBufferSetStencilMask)(this, faces, mask);
    }
    
    void CommandBuffer::SetStencilRef(Face faces, int ref) {
        NVN_VAR(CommandBufferSetStencilRef)(this, faces, ref);
    }
    
    void CommandBuffer::SetBlendColor(const float* blendColor) {
        NVN_VAR(CommandBufferSetBlendColor)(this, blendColor);
    }
    
    void CommandBuffer::SetPointSize(float pointSize) {
        NVN_VAR(CommandBufferSetPointSize)(this, pointSize);
    }
    
    void CommandBuffer::SetLineWidth(float lineWidth) {
        NVN_VAR(CommandBufferSetLineWidth)(this, lineWidth);
    }
    
    void CommandBuffer::SetPolygonOffsetClamp(float factor, float units, float clamp) {
        NVN_VAR(CommandBufferSetPolygonOffsetClamp)(this, factor, units, clamp);
    }
    
    void CommandBuffer::SetAlphaRef(float ref) {
        NVN_VAR(CommandBufferSetAlphaRef)(this, ref);
    }
    
    void CommandBuffer::SetSampleMask(int mask) {
        NVN_VAR(CommandBufferSetSampleMask)(this, mask);
    }
    
    void CommandBuffer::SetRasterizerDiscard(bool discard) {
        NVN_VAR(CommandBufferSetRasterizerDiscard)(this, discard);
    }
    
    void CommandBuffer::SetDepthClamp(bool clamp) {
        NVN_VAR(CommandBufferSetDepthClamp)(this, clamp);
    }
    
    void CommandBuffer::SetConservativeRasterEnable(bool enable) {
        NVN_VAR(CommandBufferSetConservativeRasterEnable)(this, enable);
    }
    
    void CommandBuffer::SetConservativeRasterDilate(float dilate) {
        NVN_VAR(CommandBufferSetConservativeRasterDilate)(this, dilate);
    }
    
    void CommandBuffer::SetSubpixelPrecisionBias(int xBits, int yBits) {
        NVN_VAR(CommandBufferSetSubpixelPrecisionBias)(this, xBits, yBits);
    }
    
    void CommandBuffer::CopyBufferToTexture(BufferAddress src, const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, CopyFlags flags) {
        NVN_VAR(CommandBufferCopyBufferToTexture)(this, src, dstTexture, dstView, dstRegion, flags);
    }
    
    void CommandBuffer::CopyTextureToBuffer(const Texture* srcTexture, const TextureView* srcView, const CopyRegion* srcRegion, BufferAddress dst, CopyFlags flags) {
        NVN_VAR(CommandBufferCopyTextureToBuffer)(this, srcTexture, srcView, srcRegion, dst, flags);
    }
    
    void CommandBuffer::CopyTextureToTexture(const Texture* srcTexture, const TextureView* srcView, const CopyRegion* srcRegion, const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, CopyFlags flags) {
        NVN_VAR(CommandBufferCopyTextureToTexture)(this, srcTexture, srcView, srcRegion, dstTexture, dstView, dstRegion, flags);
    }
    
    void CommandBuffer::CopyBufferToBuffer(BufferAddress src, BufferAddress dst, size_t size, CopyFlags flags) {
        NVN_VAR(CommandBufferCopyBufferToBuffer)(this, src, dst, size, flags);
    }
    
    void CommandBuffer::ClearBuffer(BufferAddress dst, size_t size, uint32_t value) {
        NVN_VAR(CommandBufferClearBuffer)(this, dst, size, value);
    }
    
    void CommandBuffer::ClearTexture(const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, const float* color, ClearColorMask mask) {
        NVN_VAR(CommandBufferClearTexture)(this, dstTexture, dstView, dstRegion, color, mask);
    }
    
    void CommandBuffer::ClearTexturei(const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, const int* color, ClearColorMask mask) {
        NVN_VAR(CommandBufferClearTexturei)(this, dstTexture, dstView, dstRegion, color, mask);
    }
    
    void CommandBuffer::ClearTextureui(const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, const uint32_t* color, ClearColorMask mask) {
        NVN_VAR(CommandBufferClearTextureui)(this, dstTexture, dstView, dstRegion, color, mask);
    }
    
    void CommandBuffer::UpdateUniformBuffer(BufferAddress buffer, size_t bufferSize, ptrdiff_t updateOffset, size_t updateSize, const void* data) {
        NVN_VAR(CommandBufferUpdateUniformBuffer)(this, buffer, bufferSize, updateOffset, updateSize, data);
    }
    
    void CommandBuffer::ReportCounter(CounterType counter, BufferAddress buffer) {
        NVN_VAR(CommandBufferReportCounter)(this, counter, buffer);
    }
    
    void CommandBuffer::ResetCounter(CounterType counter) {
        NVN_VAR(CommandBufferResetCounter)(this, counter);
    }
    
    void CommandBuffer::ReportValue(uint32_t value, BufferAddress buffer) {
        NVN_VAR(CommandBufferReportValue)(this, value, buffer);
    }
    
    void CommandBuffer::SetRenderEnable(bool enable) {
        NVN_VAR(CommandBufferSetRenderEnable)(this, enable);
    }
    
    void CommandBuffer::SetRenderEnableConditional(ConditionalRenderMode mode, BufferAddress counters) {
        NVN_VAR(CommandBufferSetRenderEnableConditional)(this, mode, counters);
    }
    
    void CommandBuffer::SetRenderTargets(int numColors, const Texture* const* colors, const TextureView* const* colorViews, const Texture* depthStencil, const TextureView* depthStencilView) {
        NVN_VAR(CommandBufferSetRenderTargets)(this, numColors, colors, colorViews, depthStencil, depthStencilView);
    }
    
    void CommandBuffer::DiscardColor(int index) {
        NVN_VAR(CommandBufferDiscardColor)(this, index);
    }
    
    void CommandBuffer::DiscardDepthStencil() {
        NVN_VAR(CommandBufferDiscardDepthStencil)(this);
    }
    
    void CommandBuffer::Downsample(const Texture* src, const Texture* dst) {
        NVN_VAR(CommandBufferDownsample)(this, src, dst);
    }
    
    void CommandBuffer::TiledDownsample(const Texture* src, const Texture* dst) {
        NVN_VAR(CommandBufferTiledDownsample)(this, src, dst);
    }
    
    void CommandBuffer::Barrier(BarrierBits barrier) {
        NVN_VAR(CommandBufferBarrier)(this, barrier);
    }
    
    void CommandBuffer::WaitSync(const Sync* sync) {
        NVN_VAR(CommandBufferWaitSync)(this, sync);
    }
    
    void CommandBuffer::FenceSync(Sync* sync, SyncCondition condition, SyncFlagBits flags) {
        NVN_VAR(CommandBufferFenceSync)(this, sync, condition, flags);
    }
    
    void CommandBuffer::SetTexturePool(const TexturePool* texturePool) {
        NVN_VAR(CommandBufferSetTexturePool)(this, texturePool);
    }
    
    void CommandBuffer::SetSamplerPool(const SamplerPool* samplerPool) {
        NVN_VAR(CommandBufferSetSamplerPool)(this, samplerPool);
    }
    
    void CommandBuffer::SetShaderScratchMemory(const MemoryPool* pool, ptrdiff_t offset, size_t size) {
        NVN_VAR(CommandBufferSetShaderScratchMemory)(this, pool, offset, size);
    }
    
    void CommandBuffer::SaveZCullData(BufferAddress dst, size_t size) {
        NVN_VAR(CommandBufferSaveZCullData)(this, dst, size);
    }
    
    void CommandBuffer::RestoreZCullData(BufferAddress src, size_t size) {
        NVN_VAR(CommandBufferRestoreZCullData)(this, src, size);
    }
    
    void CommandBuffer::SetCopyRowStride(ptrdiff_t stride) {
        NVN_VAR(CommandBufferSetCopyRowStride)(this, stride);
    }
    
    void CommandBuffer::SetCopyImageStride(ptrdiff_t stride) {
        NVN_VAR(CommandBufferSetCopyImageStride)(this, stride);
    }
    
    ptrdiff_t CommandBuffer::GetCopyRowStride() const {
        return NVN_VAR(CommandBufferGetCopyRowStride)(this);
    }
    
    ptrdiff_t CommandBuffer::GetCopyImageStride() const {
        return NVN_VAR(CommandBufferGetCopyImageStride)(this);
    }
    
    void CommandBuffer::DrawTexture(TextureHandle texture, const DrawTextureRegion* dstRegion, const DrawTextureRegion* srcRegion) {
        NVN_VAR(CommandBufferDrawTexture)(this, texture, dstRegion, srcRegion);
    }
    
    bool Program::SetSubroutineLinkage(int count, const SubroutineLinkageMapPtr* linkageMapPtrs) {
        return NVN_VAR(ProgramSetSubroutineLinkage)(this, count, linkageMapPtrs);
    }
    
    void CommandBuffer::SetProgramSubroutines(Program* program, ShaderStage stage, const int first, const int count, const int* values) {
        NVN_VAR(CommandBufferSetProgramSubroutines)(this, program, stage, first, count, values);
    }
    
    void CommandBuffer::BindCoverageModulationTable(const float* entries) {
        NVN_VAR(CommandBufferBindCoverageModulationTable)(this, entries);
    }
    
    void CommandBuffer::ResolveDepthBuffer() {
        NVN_VAR(CommandBufferResolveDepthBuffer)(this);
    }
    
    void CommandBuffer::PushDebugGroup(const char* description) {
        NVN_VAR(CommandBufferPushDebugGroup)(this, description);
    }
    
    void CommandBuffer::PopDebugGroup() {
        NVN_VAR(CommandBufferPopDebugGroup)(this);
    }
    
    void CommandBuffer::InsertDebugMarker(const char* description) {
        NVN_VAR(CommandBufferInsertDebugMarker)(this, description);
    }
    
    CommandBufferMemoryCallback CommandBuffer::GetMemoryCallback() const {
        return NVN_VAR(CommandBufferGetMemoryCallback)(this);
    }
    
    void* CommandBuffer::GetMemoryCallbackData() const {
        return NVN_VAR(CommandBufferGetMemoryCallbackData)(this);
    }
    
    bool CommandBuffer::IsRecording() const {
        return NVN_VAR(CommandBufferIsRecording)(this);
    }
    
    bool Sync::Initialize(Device* device) {
        return NVN_VAR(SyncInitialize)(this, device);
    }
    
    void Sync::Finalize() {
        NVN_VAR(SyncFinalize)(this);
    }
    
    void Sync::SetDebugLabel(const char* label) {
        NVN_VAR(SyncSetDebugLabel)(this, label);
    }
    
    void Queue::FenceSync(Sync* sync, SyncCondition condition, SyncFlagBits flags) {
        NVN_VAR(QueueFenceSync)(this, sync, condition, flags);
    }
    
    SyncWaitResult Sync::Wait(uint64_t timeoutNs) const {
        return NVN_VAR(SyncWait)(this, timeoutNs);
    }
    
    bool Queue::WaitSync(const Sync* sync) {
        return NVN_VAR(QueueWaitSync)(this, sync);
    }
}
