#pragma once
#include "types.hpp"

#ifndef RIVE_NVN_SAFE_OBJECTS
#define RIVE_NVN_MEM_POOL_BUILDER_SIZE 512
#define RIVE_NVN_MEM_POOL_SIZE 1024
#define RIVE_NVN_TEXTURE_POOL_SIZE 256
#define RIVE_NVN_SAMPLER_POOL_SIZE 256
#else
#define RIVE_NVN_MEM_POOL_BUILDER_SIZE 16384
#define RIVE_NVN_MEM_POOL_SIZE 16384
#define RIVE_NVN_TEXTURE_POOL_SIZE 8192
#define RIVE_NVN_SAMPLER_POOL_SIZE 8192
#endif

namespace nvn {
    class DeviceBuilder {
        private:
            uint8_t internal[128];
        public:
            void SetDefaults();
            void SetFlags(DeviceFlagBits flags);
    };
    class Device {
        private:
            uint8_t internal[12288];
            Device(const Device&);
            const Device&  operator =(const Device&);
        public:
            Device() {}
            bool Initialize(const DeviceBuilder* builder);
            void Finalize();
            void SetDebugLabel(const char*  label);
            GenericFuncPtr GetProcAddress(const char*  name) const;
            void GetInteger(DeviceInfo pname, int* v) const;
            uint64_t GetCurrentTimestampInNanoseconds() const;
            TextureHandle GetTextureHandle(int textureID, int samplerID) const;
            TextureHandle GetTexelFetchHandle(int textureID) const;
            ImageHandle GetImageHandle(int imageID) const;
            void InstallDebugCallback(const DebugCallback callback, void* callbackData, bool enable);
            void SetWindowOriginMode(WindowOriginMode windowOriginMode);
            void SetDepthMode(DepthMode depthMode);
            bool RegisterFastClearColor(const float* color, Format format);
            bool RegisterFastClearColori(const int* color, Format format);
            bool RegisterFastClearColorui(const uint32_t* color, Format format);
            bool RegisterFastClearDepth(float depth);
            WindowOriginMode GetWindowOriginMode() const;
            DepthMode GetDepthMode() const;
            uint64_t GetTimestampInNanoseconds(const CounterData* counterData) const;
            void ApplyDeferredFinalizes(int age);
            void FinalizeCommandHandle(CommandHandle handles);
            DeviceWaitForErrorResult WaitForError(uint64_t timeoutNs, DeviceErrorData* errorData) const;
    };
    
    class QueueBuilder {
        private:
            uint8_t internal[64];
        public:
            QueueBuilder&  SetDevice(Device* device);
            QueueBuilder&  SetDefaults();
            QueueBuilder&  SetFlags(QueueFlags flags);
            QueueBuilder&  SetCommandMemorySize(size_t size);
            QueueBuilder&  SetComputeMemorySize(size_t size);
            size_t GetQueueMemorySize() const;
            QueueBuilder&  SetQueueMemory(void* memory, size_t size);
            QueueBuilder&  SetCommandFlushThreshold(size_t threshold);
    };
    
    class Queue {
        private:
            uint8_t internal[8192];
            Queue(const Queue&);
            const Queue&  operator =(const Queue&);
        public:
            Queue() {}
            QueueGetErrorResult GetError(QueueErrorInfo* errorInfo);
            bool Initialize(const QueueBuilder* builder);
            void Finalize();
            void SetDebugLabel(const char*  label);
            void SubmitCommands(int numCommands, const CommandHandle* handles);
            void Flush();
            void Finish();
            void PresentTexture(Window* window, int textureIndex);
            QueueAcquireTextureResult AcquireTexture(Window* window, int* textureIndex);
            void FenceSync(Sync* sync, SyncCondition condition, SyncFlagBits flags);
            bool WaitSync(const Sync* sync);
    };
    
    class CommandBuffer {
        private:
            uint8_t internal[160];
            CommandBuffer(const CommandBuffer&);
            const CommandBuffer&  operator =(const CommandBuffer&);
        public:
            CommandBuffer() {}
            bool Initialize(Device* device);
            void Finalize();
            void SetDebugLabel(const char*  label);
            void SetMemoryCallback(CommandBufferMemoryCallback callback);
            void SetMemoryCallbackData(void* callbackData);
            void AddCommandMemory(const MemoryPool* pool, ptrdiff_t offset, size_t size);
            void AddControlMemory(void* memory, size_t size);
            size_t GetCommandMemorySize() const;
            size_t GetCommandMemoryUsed() const;
            size_t GetCommandMemoryFree() const;
            size_t GetControlMemorySize() const;
            size_t GetControlMemoryUsed() const;
            size_t GetControlMemoryFree() const;
            void BeginRecording();
            CommandHandle EndRecording();
            void CallCommands(int numCommands, const CommandHandle* handles);
            void CopyCommands(int numCommands, const CommandHandle* handles);
            void BindBlendState(const BlendState* blend);
            void BindChannelMaskState(const ChannelMaskState* channelMask);
            void BindColorState(const ColorState* color);
            void BindMultisampleState(const MultisampleState* multisample);
            void BindPolygonState(const PolygonState* polygon);
            void BindDepthStencilState(const DepthStencilState* depthStencil);
            void BindVertexAttribState(int numAttribs, const VertexAttribState* attribs);
            void BindVertexStreamState(int numStreams, const VertexStreamState* streams);
            void BindProgram(const Program* program, ShaderStageBits stages);
            void BindVertexBuffer(int index, BufferAddress buffer, size_t size);
            void BindVertexBuffers(int first, int count, const BufferRange* buffers);
            void BindUniformBuffer(ShaderStage stage, int index, BufferAddress buffer, size_t size);
            void BindUniformBuffers(ShaderStage stage, int first, int count, const BufferRange* buffers);
            void BindTransformFeedbackBuffer(int index, BufferAddress buffer, size_t size);
            void BindTransformFeedbackBuffers(int first, int count, const BufferRange* buffers);
            void BindStorageBuffer(ShaderStage stage, int index, BufferAddress buffer, size_t size);
            void BindStorageBuffers(ShaderStage stage, int first, int count, const BufferRange* buffers);
            void BindTexture(ShaderStage stage, int index, TextureHandle texture);
            void BindTextures(ShaderStage stage, int first, int count, const TextureHandle* textures);
            void BindImage(ShaderStage stage, int index, ImageHandle image);
            void BindImages(ShaderStage stage, int first, int count, const ImageHandle* images);
            void SetPatchSize(int size);
            void SetInnerTessellationLevels(const float* levels);
            void SetOuterTessellationLevels(const float* levels);
            void SetPrimitiveRestart(bool enable, int index);
            void BeginTransformFeedback(BufferAddress buffer);
            void EndTransformFeedback(BufferAddress buffer);
            void PauseTransformFeedback(BufferAddress buffer);
            void ResumeTransformFeedback(BufferAddress buffer);
            void DrawTransformFeedback(DrawPrimitive mode, BufferAddress buffer);
            void DrawArrays(DrawPrimitive mode, int first, int count);
            void DrawElements(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer);
            void DrawElementsBaseVertex(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer, int baseVertex);
            void DrawArraysInstanced(DrawPrimitive mode, int first, int count, int baseInstance, int instanceCount);
            void DrawElementsInstanced(DrawPrimitive mode, IndexType type, int count, BufferAddress indexBuffer, int baseVertex, int baseInstance, int instanceCount);
            void DrawArraysIndirect(DrawPrimitive mode, BufferAddress indirectBuffer);
            void DrawElementsIndirect(DrawPrimitive mode, IndexType type, BufferAddress indexBuffer, BufferAddress indirectBuffer);
            void MultiDrawArraysIndirectCount(DrawPrimitive mode, BufferAddress indirectBuffer, BufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride);
            void MultiDrawElementsIndirectCount(DrawPrimitive mode, IndexType type, BufferAddress indexBuffer, BufferAddress indirectBuffer, BufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride);
            void ClearColor(int index, const float* color, ClearColorMask mask);
            void ClearColori(int index, const int* color, ClearColorMask mask);
            void ClearColorui(int index, const uint32_t* color, ClearColorMask mask);
            void ClearDepthStencil(float depthValue, bool depthMask, int stencilValue, int stencilMask);
            void DispatchCompute(int groupsX, int groupsY, int groupsZ);
            void DispatchComputeIndirect(BufferAddress indirectBuffer);
            void SetViewport(int x, int y, int w, int h);
            void SetViewports(int first, int count, const float* ranges);
            void SetViewportSwizzles(int first, int count, const ViewportSwizzle* swizzles);
            void SetScissor(int x, int y, int w, int h);
            void SetScissors(int first, int count, const int* rects);
            void SetDepthRange(float n, float f);
            void SetDepthBounds(bool enable, float n, float f);
            void SetDepthRanges(int first, int count, const float* ranges);
            void SetTiledCacheAction(TiledCacheAction action);
            void SetTiledCacheTileSize(int tileWidth, int tileHeight);
            void SetStencilValueMask(Face faces, int mask);
            void SetStencilMask(Face faces, int mask);
            void SetStencilRef(Face faces, int ref);
            void SetBlendColor(const float* blendColor);
            void SetPointSize(float pointSize);
            void SetLineWidth(float lineWidth);
            void SetPolygonOffsetClamp(float factor, float units, float clamp);
            void SetAlphaRef(float ref);
            void SetSampleMask(int mask);
            void SetRasterizerDiscard(bool discard);
            void SetDepthClamp(bool clamp);
            void SetConservativeRasterEnable(bool enable);
            void SetConservativeRasterDilate(float dilate);
            void SetSubpixelPrecisionBias(int xBits, int yBits);
            void CopyBufferToTexture(BufferAddress src, const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, CopyFlags flags);
            void CopyTextureToBuffer(const Texture* srcTexture, const TextureView* srcView, const CopyRegion* srcRegion, BufferAddress dst, CopyFlags flags);
            void CopyTextureToTexture(const Texture* srcTexture, const TextureView* srcView, const CopyRegion* srcRegion, const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, CopyFlags flags);
            void CopyBufferToBuffer(BufferAddress src, BufferAddress dst, size_t size, CopyFlags flags);
            void ClearBuffer(BufferAddress dst, size_t size, uint32_t value);
            void ClearTexture(const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, const float* color, ClearColorMask mask);
            void ClearTexturei(const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, const int* color, ClearColorMask mask);
            void ClearTextureui(const Texture* dstTexture, const TextureView* dstView, const CopyRegion* dstRegion, const uint32_t* color, ClearColorMask mask);
            void UpdateUniformBuffer(BufferAddress buffer, size_t bufferSize, ptrdiff_t updateOffset, size_t updateSize, const void* data);
            void ReportCounter(CounterType counter, BufferAddress buffer);
            void ResetCounter(CounterType counter);
            void ReportValue(uint32_t value, BufferAddress buffer);
            void SetRenderEnable(bool enable);
            void SetRenderEnableConditional(ConditionalRenderMode mode, BufferAddress counters);
            void SetRenderTargets(int numColors, const Texture*  const* colors, const TextureView*  const* colorViews, const Texture* depthStencil, const TextureView* depthStencilView);
            void DiscardColor(int index);
            void DiscardDepthStencil();
            void Downsample(const Texture* src, const Texture* dst);
            void TiledDownsample(const Texture* src, const Texture* dst);
            void Barrier(BarrierBits barrier);
            void WaitSync(const Sync* sync);
            void FenceSync(Sync* sync, SyncCondition condition, SyncFlagBits flags);
            void SetTexturePool(const TexturePool* texturePool);
            void SetSamplerPool(const SamplerPool* samplerPool);
            void SetShaderScratchMemory(const MemoryPool* pool, ptrdiff_t offset, size_t size);
            void SaveZCullData(BufferAddress dst, size_t size);
            void RestoreZCullData(BufferAddress src, size_t size);
            void SetCopyRowStride(ptrdiff_t stride);
            void SetCopyImageStride(ptrdiff_t stride);
            ptrdiff_t GetCopyRowStride() const;
            ptrdiff_t GetCopyImageStride() const;
            void DrawTexture(TextureHandle texture, const DrawTextureRegion* dstRegion, const DrawTextureRegion* srcRegion);
            void SetProgramSubroutines(Program* program, ShaderStage stage, const int first, const int count, const int* values);
            void BindCoverageModulationTable(const float* entries);
            void ResolveDepthBuffer();
            void PushDebugGroup(const char*  description);
            void PopDebugGroup();
            void InsertDebugMarker(const char*  description);
            CommandBufferMemoryCallback GetMemoryCallback() const;
            void* GetMemoryCallbackData() const;
            bool IsRecording() const;
    };

    class BlendState {
        private:
            uint8_t internal[8];
        public:
            BlendState& SetDefaults();
            BlendState& SetBlendTarget(int target);
            BlendState& SetBlendFunc(BlendFunc srcFunc, BlendFunc dstFunc, BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha);
            BlendState& SetBlendEquation(BlendEquation modeRGB, BlendEquation modeAlpha);
            BlendState& SetAdvancedMode(BlendAdvancedMode overlap);
            BlendState& SetAdvancedOverlap(BlendAdvancedOverlap overlap);
            BlendState& SetAdvancedPremultipliedSrc(bool premultiplied);
            BlendState& SetAdvancedNormalizedDst(bool normalized);
            int GetBlendTarget() const;
            void GetBlendFunc(BlendFunc* srcFunc, BlendFunc* dstFunc, BlendFunc* srcFuncAlpha, BlendFunc* dstFuncAlpha) const;
            void GetBlendEquation(BlendEquation* modeRGB, BlendEquation* modeAlpha) const;
            BlendAdvancedMode GetAdvancedMode() const;
            BlendAdvancedOverlap GetAdvancedOverlap() const;
            bool GetAdvancedPremultipliedSrc() const;
            bool GetAdvancedNormalizedDst() const;
    };

    class ChannelMaskState {
        private:
            uint8_t internal[4];
        public:
            ChannelMaskState& SetDefaults();
            ChannelMaskState& SetChannelMask(int index, bool r, bool g, bool b, bool a);
            void GetChannelMask(int index, bool* r, bool* g, bool* b, bool* a) const;
    };

    class ColorState {
        private:
            uint8_t internal[4];
        public:
            ColorState& SetDefaults();
            ColorState& SetBlendEnable(int index, bool enable);
            ColorState& SetLogicOp(LogicOp logicOp);
            ColorState& SetAlphaTest(AlphaFunc alphaTest);
            bool GetBlendEnable(int index) const;
            LogicOp GetLogicOp() const;
            AlphaFunc GetAlphaTest() const;
    };

    class DepthStencilState {
        private:
            uint8_t internal[8];
        public:
            DepthStencilState& SetDefaults();
            DepthStencilState& SetDepthTestEnable(bool enable);
            DepthStencilState& SetDepthWriteEnable(bool enable);
            DepthStencilState& SetDepthFunc(DepthFunc func);
            DepthStencilState& SetStencilTestEnable(bool enable);
            DepthStencilState& SetStencilFunc(Face faces, StencilFunc func);
            DepthStencilState& SetStencilOp(Face faces, StencilOp fail, StencilOp depthFail, StencilOp depthPass);
            bool GetDepthTestEnable() const;
            bool GetDepthWriteEnable() const;
            DepthFunc GetDepthFunc() const;
            bool GetStencilTestEnable() const;
            StencilFunc GetStencilFunc(Face face) const;
            void GetStencilOp(Face face, StencilOp* fail, StencilOp* depthFail, StencilOp* depthPass) const;
    };

    class MultisampleState {
        private:
            uint8_t internal[24];
        public:
            MultisampleState& SetDefaults();
            MultisampleState& SetMultisampleEnable(bool enable);
            MultisampleState& SetSamples(int samples);
            MultisampleState& SetAlphaToCoverageEnable(bool enable);
            MultisampleState& SetAlphaToCoverageDither(bool dither);
            bool GetMultisampleEnable() const;
            int GetSamples() const;
            bool GetAlphaToCoverageEnable() const;
            bool GetAlphaToCoverageDither() const;
            MultisampleState& SetRasterSamples(int rasterSamples);
            int GetRasterSamples();
            MultisampleState& SetCoverageModulationMode(CoverageModulationMode mode);
            CoverageModulationMode GetCoverageModulationMode() const;
            MultisampleState& SetCoverageToColorEnable(bool enable);
            bool GetCoverageToColorEnable() const;
            MultisampleState& SetCoverageToColorOutput(int color);
            int GetCoverageToColorOutput() const;
            MultisampleState& SetSampleLocationsEnable(bool enable);
            bool GetSampleLocationsEnable() const;
            void GetSampleLocationsGrid(int* width, int* height);
            MultisampleState& SetSampleLocationsGridEnable(bool enable);
            bool GetSampleLocationsGridEnable() const;
            MultisampleState& SetSampleLocations(int start, int count, const float* values);
    };

    class PolygonState {
        private:
            uint8_t internal[4];
        public:
            PolygonState& SetDefaults();
            PolygonState& SetCullFace(Face face);
            PolygonState& SetFrontFace(FrontFace face);
            PolygonState& SetPolygonMode(PolygonMode polygonMode);
            PolygonState& SetPolygonOffsetEnables(PolygonOffsetEnable enables);
            Face GetCullFace() const;
            FrontFace GetFrontFace() const;
            PolygonMode GetPolygonMode() const;
            PolygonOffsetEnable GetPolygonOffsetEnables() const;
    };

    class VertexAttribState {
        private:
            uint8_t internal[4];
        public:
            VertexAttribState& SetDefaults();
            VertexAttribState& SetFormat(Format format, ptrdiff_t relativeOffset);
            VertexAttribState& SetStreamIndex(int streamIndex);
            void GetFormat(Format* format, ptrdiff_t* relativeOffset) const;
            int GetStreamIndex() const;
    };

    class VertexStreamState {
        private:
            uint8_t internal[8];
        public:
            VertexStreamState& SetDefaults();
            VertexStreamState& SetStride(ptrdiff_t stride);
            VertexStreamState& SetDivisor(int divisor);
            ptrdiff_t GetStride() const;
            int GetDivisor() const;
    };

    class alignas(0x10) Program {
        private:
            uint8_t internal[192];
            Program(const Program&);
            const Program&  operator =(const Program&);
        public:
            Program() {}
            bool Initialize(Device* device);
            void Finalize();
            void SetDebugLabel(const char*  label);
            bool SetShaders(int count, const ShaderData* stageData);
            bool SetSubroutineLinkage(int count, const SubroutineLinkageMapPtr* linkageMapPtrs);
    };

    class alignas(0x10) MemoryPoolBuilder {
        private:
            uint8_t internal[RIVE_NVN_MEM_POOL_BUILDER_SIZE];
        public:
            MemoryPoolBuilder& SetDevice(Device* device);
            MemoryPoolBuilder& SetDefaults();
            MemoryPoolBuilder& SetStorage(void* memory, size_t size);
            MemoryPoolBuilder& SetFlags(MemoryPoolFlags flags);
            void* GetMemory() const;
            size_t GetSize() const;
            MemoryPoolFlags GetFlags() const;
    };

    class alignas(0x10) MemoryPool {
        private:
            uint8_t internal[RIVE_NVN_MEM_POOL_SIZE];
            MemoryPool(const MemoryPool&);
            const MemoryPool&  operator =(const MemoryPool&);
        public:
            MemoryPool() {}
            bool Initialize(const MemoryPoolBuilder* builder);
            void SetDebugLabel(const char*  label);
            void Finalize();
            void* Map() const;
            void FlushMappedRange(ptrdiff_t offset, size_t size) const;
            void InvalidateMappedRange(ptrdiff_t offset, size_t size) const;
            BufferAddress GetBufferAddress() const;
            bool MapVirtual(int numRequests, const MappingRequest* requests);
            size_t GetSize() const;
            MemoryPoolFlags GetFlags() const;
    };

    class alignas(0x10) TexturePool {
        private:
            uint8_t internal[RIVE_NVN_TEXTURE_POOL_SIZE];
            TexturePool(const TexturePool&);
            const TexturePool&  operator =(const TexturePool&);
        public:
            TexturePool() {}
            bool Initialize(const MemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors);
            void SetDebugLabel(const char*  label);
            void Finalize();
            void RegisterTexture(int id, const Texture* texture, const TextureView* view) const;
            void RegisterImage(int id, const Texture* texture, const TextureView* view) const;
            const MemoryPool*  GetMemoryPool() const;
            ptrdiff_t GetMemoryOffset() const;
            int GetSize() const;
    };

    class alignas(0x10) SamplerPool {
        private:
            uint8_t internal[RIVE_NVN_SAMPLER_POOL_SIZE];
            SamplerPool(const SamplerPool&);
            const SamplerPool&  operator =(const SamplerPool&);
        public:
            SamplerPool() {}
            bool Initialize(const MemoryPool* memoryPool, ptrdiff_t offset, int numDescriptors);
            void SetDebugLabel(const char*  label);
            void Finalize();
            void RegisterSampler(int id, const Sampler* sampler) const;
            const MemoryPool*  GetMemoryPool() const;
            ptrdiff_t GetMemoryOffset() const;
            int GetSize() const;
    };

    class alignas(0x10) BufferBuilder {
        private:
            uint8_t internal[128];
        public:
            BufferBuilder& SetDevice(Device* device);
            BufferBuilder& SetDefaults();
            BufferBuilder& SetStorage(MemoryPool* pool, ptrdiff_t offset, size_t size);
            MemoryPool*  GetMemoryPool() const;
            ptrdiff_t GetMemoryOffset() const;
            size_t GetSize() const;
    };

    class alignas(0x10) Buffer {
        private:
            uint8_t internal[96];
            Buffer(const Buffer&);
            const Buffer&  operator =(const Buffer&);
        public:
            Buffer() {}
            bool Initialize(const BufferBuilder* builder);
            void SetDebugLabel(const char*  label);
            void Finalize();
            void* Map() const;
            BufferAddress GetAddress() const;
            void FlushMappedRange(ptrdiff_t offset, size_t size) const;
            void InvalidateMappedRange(ptrdiff_t offset, size_t size) const;
            MemoryPool*  GetMemoryPool() const;
            ptrdiff_t GetMemoryOffset() const;
            size_t GetSize() const;
            uint64_t GetDebugID() const;
    };

    class alignas(0x10) Texture {
        private:
            uint8_t internal[256];
            Texture(const Texture&);
            const Texture&  operator =(const Texture&);
        public:
            Texture() {}
            bool Initialize(const TextureBuilder* builder);
            size_t GetZCullStorageSize() const;
            void Finalize();
            void SetDebugLabel(const char*  label);
            StorageClass GetStorageClass() const;
            ptrdiff_t GetViewOffset(const TextureView* textureView) const;
            TextureFlags GetFlags() const;
            TextureTarget GetTarget() const;
            int GetWidth() const;
            int GetHeight() const;
            int GetDepth() const;
            int GetLevels() const;
            Format GetFormat() const;
            int GetSamples() const;
            void GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b, TextureSwizzle* a) const;
            TextureDepthStencilMode GetDepthStencilMode() const;
            ptrdiff_t GetStride() const;
            TextureAddress GetTextureAddress() const;
            void GetSparseTileLayout(TextureSparseTileLayout* layout) const;
            void WriteTexels(const TextureView* textureView, const CopyRegion* region, const void* data) const;
            void ReadTexels(const TextureView* textureView, const CopyRegion* region, void* data) const;
            void FlushTexels(const TextureView* textureView, const CopyRegion* region) const;
            void InvalidateTexels(const TextureView* textureView, const CopyRegion* region) const;
            MemoryPool*  GetMemoryPool() const;
            ptrdiff_t GetMemoryOffset() const;
            int GetStorageSize() const;
            bool Compare(const Texture* otherTexture) const;
            uint64_t GetDebugID() const;
    };

    class alignas(0x10) TextureBuilder {
        private:
            uint8_t internal[256];
        public:
            TextureBuilder& SetDevice(Device* device);
            TextureBuilder& SetDefaults();
            TextureBuilder& SetFlags(TextureFlags flags);
            TextureBuilder& SetTarget(TextureTarget target);
            TextureBuilder& SetWidth(int width);
            TextureBuilder& SetHeight(int height);
            TextureBuilder& SetDepth(int depth);
            TextureBuilder& SetSize1D(int width);
            TextureBuilder& SetSize2D(int width, int height);
            TextureBuilder& SetSize3D(int width, int height, int depth);
            TextureBuilder& SetLevels(int numLevels);
            TextureBuilder& SetFormat(Format format);
            TextureBuilder& SetSamples(int samples);
            TextureBuilder& SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b, TextureSwizzle a);
            TextureBuilder& SetDepthStencilMode(TextureDepthStencilMode mode);
            size_t GetStorageSize() const;
            size_t GetStorageAlignment() const;
            TextureBuilder& SetStorage(MemoryPool* pool, ptrdiff_t offset);
            TextureBuilder& SetPackagedTextureData(const void* data);
            TextureBuilder& SetPackagedTextureLayout(const PackagedTextureLayout* layout);
            TextureBuilder& SetStride(ptrdiff_t stride);
            TextureBuilder& SetGLTextureName(uint32_t name);
            StorageClass GetStorageClass() const;
            TextureFlags GetFlags() const;
            TextureTarget GetTarget() const;
            int GetWidth() const;
            int GetHeight() const;
            int GetDepth() const;
            int GetLevels() const;
            Format GetFormat() const;
            int GetSamples() const;
            void GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b, TextureSwizzle* a) const;
            TextureDepthStencilMode GetDepthStencilMode() const;
            const void*  GetPackagedTextureData() const;
            ptrdiff_t GetStride() const;
            void GetSparseTileLayout(TextureSparseTileLayout* layout) const;
            uint32_t GetGLTextureName() const;
            size_t GetZCullStorageSize() const;
            MemoryPool*  GetMemoryPool() const;
            ptrdiff_t GetMemoryOffset() const;
    };

    class TextureView {
        private:
            uint8_t internal[40];
        public:
            TextureView& SetDefaults();
            TextureView& SetLevels(int baseLevel, int numLevels);
            TextureView& SetLayers(int minLayer, int numLayers);
            TextureView& SetFormat(Format format);
            TextureView& SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b, TextureSwizzle a);
            TextureView& SetDepthStencilMode(TextureDepthStencilMode mode);
            TextureView& SetTarget(TextureTarget target);
            bool GetLevels(int* baseLevel, int* numLevels) const;
            bool GetLayers(int* minLayer, int* numLayers) const;
            bool GetFormat(Format* format) const;
            bool GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b, TextureSwizzle* a) const;
            bool GetDepthStencilMode(TextureDepthStencilMode* mode) const;
            bool GetTarget(TextureTarget* target) const;
            bool Compare(const TextureView* otherView) const;
    };

    class alignas(0x10) SamplerBuilder {
        private:
            uint8_t internal[128];
        public:
            SamplerBuilder& SetDevice(Device* device);
            SamplerBuilder& SetDefaults();
            SamplerBuilder& SetMinMagFilter(MinFilter min, MagFilter mag);
            SamplerBuilder& SetWrapMode(WrapMode s, WrapMode t, WrapMode r);
            SamplerBuilder& SetLodClamp(float min, float max);
            SamplerBuilder& SetLodBias(float bias);
            SamplerBuilder& SetCompare(CompareMode mode, CompareFunc func);
            SamplerBuilder& SetBorderColor(const float* borderColor);
            SamplerBuilder& SetBorderColori(const int* borderColor);
            SamplerBuilder& SetBorderColorui(const uint32_t* borderColor);
            SamplerBuilder& SetMaxAnisotropy(float maxAniso);
            SamplerBuilder& SetReductionFilter(SamplerReduction filter);
            void GetMinMagFilter(MinFilter* min, MagFilter* mag) const;
            void GetWrapMode(WrapMode* s, WrapMode* t, WrapMode* r) const;
            void GetLodClamp(float* min, float* max) const;
            float GetLodBias() const;
            void GetCompare(CompareMode* mode, CompareFunc* func) const;
            void GetBorderColor(float* borderColor) const;
            void GetBorderColori(int* borderColor) const;
            void GetBorderColorui(uint32_t* borderColor) const;
            float GetMaxAnisotropy() const;
            SamplerReduction GetReductionFilter() const;
    };

    class alignas(0x10) Sampler {
        private:
            uint8_t internal[128];
            Sampler(const Sampler&);
            const Sampler&  operator =(const Sampler&);
        public:
            Sampler() {}
            bool Initialize(const SamplerBuilder* builder);
            void Finalize();
            void SetDebugLabel(const char*  label);
            void GetMinMagFilter(MinFilter* min, MagFilter* mag) const;
            void GetWrapMode(WrapMode* s, WrapMode* t, WrapMode* r) const;
            void GetLodClamp(float* min, float* max) const;
            float GetLodBias() const;
            void GetCompare(CompareMode* mode, CompareFunc* func) const;
            void GetBorderColor(float* borderColor) const;
            void GetBorderColori(int* borderColor) const;
            void GetBorderColorui(uint32_t* borderColor) const;
            float GetMaxAnisotropy() const;
            SamplerReduction GetReductionFilter() const;
            bool Compare(const Sampler* otherSampler) const;
            uint64_t GetDebugID() const;
    };

    class Sync {
        private:
            uint8_t internal[64];
            Sync(const Sync&);
            const Sync&  operator =(const Sync&);
        public:
            Sync() {}
            bool Initialize(Device* device);
            void Finalize();
            void SetDebugLabel(const char*  label);
            SyncWaitResult Wait(uint64_t timeoutNs) const;
    };

    class Window {
        private:
            uint8_t internal[384];
            Window(const Window&);
            const Window&  operator =(const Window&);
        public:
            Window() {}
            bool Initialize(const WindowBuilder* builder);
            void Finalize();
            void SetDebugLabel(const char*  label);
            WindowAcquireTextureResult AcquireTexture(Sync* textureAvailableSync, int* textureIndex);
            NativeWindow GetNativeWindow() const;
            int GetPresentInterval() const;
            void SetPresentInterval(int presentInterval);
            void SetCrop(int x, int y, int w, int h);
    };

    class WindowBuilder {
        private:
            uint8_t internal[64];
        public:
            WindowBuilder& SetDevice(Device* device);
            WindowBuilder& SetDefaults();
            WindowBuilder& SetNativeWindow(NativeWindow nativeWindow);
            WindowBuilder& SetTextures(int numTextures, Texture*  const* textures);
            WindowBuilder& SetPresentInterval(int presentInterval);
            NativeWindow GetNativeWindow() const;
            int GetPresentInterval() const;
    };
}
