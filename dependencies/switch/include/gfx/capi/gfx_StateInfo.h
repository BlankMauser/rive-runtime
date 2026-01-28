/*--------------------------------------------------------------------------------*
  Copyright Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/

/**
* @file
* @brief  Declarations of API resources for the information used to initialize the state.
*/

#pragma once

#include <limits>

#include <nn/nn_Common.h>
#include <nn/nn_Macro.h>
#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_DataAccessorConverter.h>
#include <nn/gfx/gfx_StateInfoData.h>

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/detail/gfx_DataContainer.h>

namespace nn {
namespace gfx {

/**
* @brief  Class representing multisample state information.
*/
class MultisampleStateInfo
    : public detail::DataContainer< MultisampleStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    MultisampleStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetAlphaToCoverageEnabled( false );
*  - SetSampleCount( 1 );
*  - SetSampleMask( 0xFFFFFFFF );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the number of samples.
*
* @param[in] value  Number of samples.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>0xFF</tt>.
*
* @post
*  - The number of samples is set.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetSampleCount( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= 0xFF );
        this->sampleCount = static_cast< uint8_t >( value );
    }

/**
* @brief  Sets the sample mask.
*
* @param[in] value  Sample mask.
*
* @post
*  - The sample mask is set.
*/
    void SetSampleMask( int value ) NN_NOEXCEPT
    {
        this->sampleMask = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets whether to use the alpha value as the coverage during multisampling.
*
* @param[in] value  Boolean value indicating whether to use the alpha value as the coverage.
*
* @post
*  - The setting for whether to use the alpha value as the coverage is set.
*
* @details
*  Set this to the same value as <tt>SetAlphaToCoverageEnabled</tt> in <tt>BlendStateInfo</tt>.
*/
    void SetAlphaToCoverageEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_AlphaToCoverageEnable, value );
    }

/**
* @brief  Determines whether the alpha value is used as the coverage during multisampling.
*
* @return  Returns a Boolean value indicating whether the alpha value is used as the coverage.
*/
    bool IsAlphaToCoverageEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_AlphaToCoverageEnable );
    }

/**
* @brief  Gets the number of samples.
*
* @return  Returns the number of samples.
*/
    int GetSampleCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->sampleCount );
    }

/**
* @brief  Gets the sample mask.
*
* @return  Returns the sample mask.
*/
    int GetSampleMask() const NN_NOEXCEPT
    {
        return static_cast< int >( this->sampleMask );
    }
};

/**
* @brief  Represents the information for initializing a rasterizer state.
*/
class RasterizerStateInfo
    : public detail::DataContainer< RasterizerStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    RasterizerStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetFillMode( nn::gfx::FillMode_Solid );
*  - SetCullMode( nn::gfx::CullMode_Back );
*  - SetFrontFace( nn::gfx::FrontFace_Ccw );
*  - SetPrimitiveTopologyType( nn::gfx::PrimitiveTopologyType_Triangle );
*  - SetRasterEnabled( true );
*  - SetMultisampleEnabled( false );
*  - SetDepthClipEnabled( true );
*  - SetScissorEnabled( false );
*  - SetDepthBias( 0 );
*  - SetDepthBiasClamp( 0.0f );
*  - SetSlopeScaledDepthBias( 0.0f );
*  - SetConservativeRasterizationMode( nn::gfx::ConservativeRasterizationMode_Disable );
*  - EditMultisampleStateInfo().SetDefault();
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the fill mode.
*
* @param[in] value  Fill mode.
*
* @post
*  - The fill mode is set.
*/
    void SetFillMode( FillMode value ) NN_NOEXCEPT
    {
        this->fillMode = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the face to be the front.
*
* @param[in] value  The face to be the front.
*
* @post
*  - The front face is set.
*/
    void SetFrontFace( FrontFace value ) NN_NOEXCEPT
    {
        this->frontFace = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the culling mode.
*
* @param[in] value  Culling mode.
*
* @post
*  - The culling mode is set.
*/
    void SetCullMode( CullMode value ) NN_NOEXCEPT
    {
        this->cullMode = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the primitive topology type.
*
* @param[in] value  The primitive topology type.
*
* @post
*  - The primitive topology type is set.
*/
    void SetPrimitiveTopologyType( PrimitiveTopologyType value ) NN_NOEXCEPT
    {
        this->primitiveTopologyType = static_cast< Bit8 >( value );
    }

/**
* @brief  Enables or disables rasterization.
*
* @param[in] value  Boolean value indicating whether to enable or disable the rasterizer.
*
* @post
*  - The rasterizer is either enabled or disabled.
*/
    void SetRasterEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_RasterDisable, !value );
    }

/**
* @brief  Enables or disables multisampling.
*
* @param[in] value  Boolean value indicating whether to enable multisampling.
*
* @post
*  - Multisampling is set to be enabled or disabled.
*/
    void SetMultisampleEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_MultisampleEnable, value );
    }

/**
* @brief  Enables or disables depth-based clipping.
*
* @param[in] value  Boolean value indicating whether to enable depth-based clipping.
*
* @post
*  - Depth-based clipping is set to be enabled or disabled.
*/
    void SetDepthClipEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_DepthClipDisable, !value );
    }

/**
* @brief  Enables or disables scissoring.
*
* @param[in] value  Boolean value indicating whether to enable scissoring.
*
* @post
*  - Scissoring is set to be enabled or disabled.
*
* @details
*  This must match the viewport state scissoring.
*/
    void SetScissorEnabled( bool value ) NN_NOEXCEPT
    {
        return this->flag.SetBit( Flag_ScissorEnable, value );
    }

/**
* @brief  Sets the value to add to the pixel depth value, scaled according to the maximum depth slope.
*
* @param[in] value  Value to add to the pixel depth value, scaled according to maximum depth slope.
*
* @post
*  - The value to add to the pixel depth value, scaled according to the maximum depth slope, is set.
*/
    void SetSlopeScaledDepthBias( float value ) NN_NOEXCEPT
    {
        this->slopeScaledDepthBias = value;
    }

/**
* @brief  Sets the value to add to the pixel depth value, scaled according to the minimum expressible levels in the depth format.
*
* @param[in] value  Value to add to the pixel depth value, scaled according to the minimum expressible levels in the depth format.
*
* @post
*  - The value to add to the pixel depth value, scaled according to the minimum expressible levels in the depth format, is set.
*/
    void SetDepthBias( int value ) NN_NOEXCEPT
    {
        this->depthBias = static_cast< int32_t >( value );
    }

/**
* @brief  Sets the maximum value to add to the pixel depth value.
*
* @param[in] value  Maximum value to add to the pixel depth value.
*
* @post
*  - The maximum value to add to the pixel depth value is set.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetDepthBiasClamp( float value ) NN_NOEXCEPT
    {
        this->depthBiasClamp = value;
    }

/**
* @brief  Sets the conservative rasterization mode.
*
* @param[in] value  The conservative rasterization mode.
*
* @post
*  - The conservative rasterization mode is set.
*/
    void SetConservativeRasterizationMode( ConservativeRasterizationMode value ) NN_NOEXCEPT
    {
        this->conservativeRasterizationMode = static_cast< Bit8 >( value );
    }

/**
* @brief  Edits multisampling state information.
*
* @return  Returns a reference to the multisampling state information.
*/
    MultisampleStateInfo& EditMultisampleStateInfo() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->multisample );
    }

/**
* @brief  Gets the fill mode.
*
* @return  Returns the fill mode.
*/
    FillMode GetFillMode() const NN_NOEXCEPT
    {
        return static_cast< FillMode >( this->fillMode );
    }

/**
* @brief  Gets the face to be the front.
*
* @return  Returns the face to be the front.
*/
    FrontFace GetFrontFace() const NN_NOEXCEPT
    {
        return static_cast< FrontFace >( this->frontFace );
    }

/**
* @brief  Gets the culling mode.
*
* @return  Returns the culling mode.
*/
    CullMode GetCullMode() const NN_NOEXCEPT
    {
        return static_cast< CullMode >( this->cullMode );
    }

/**
* @brief  Gets the primitive topology type.
*
* @return  Returns the primitive topology type.
*/
    PrimitiveTopologyType GetPrimitiveTopologyType() const NN_NOEXCEPT
    {
        return static_cast< PrimitiveTopologyType >( this->primitiveTopologyType );
    }

/**
* @brief  Determines whether the rasterizer is enabled.
*
* @return  Returns a Boolean value indicating whether the rasterizer is enabled.
*/
    bool IsRasterEnabled() const NN_NOEXCEPT
    {
        return !this->flag.GetBit( Flag_RasterDisable );
    }

/**
* @brief  Determines whether multisampling is enabled.
*
* @return  Returns a Boolean value indicating whether multisampling is enabled.
*/
    bool IsMultisampleEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_MultisampleEnable );
    }

/**
* @brief  Determines whether depth-based clipping is enabled.
*
* @return  Returns a Boolean value indicating whether depth-based clipping is enabled.
*/
    bool IsDepthClipEnabled() const NN_NOEXCEPT
    {
        return !this->flag.GetBit( Flag_DepthClipDisable );
    }

/**
* @brief  Determines whether scissoring is enabled.
*
* @return  Returns a Boolean value indicating whether scissoring is enabled.
*/
    bool IsScissorEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_ScissorEnable );
    }

/**
* @brief  Gets the value to add to the pixel depth value, scaled according to the maximum depth slope.
*
* @return  Returns the value to add to the pixel depth value, scaled according to the maximum depth slope.
*/
    float GetSlopeScaledDepthBias() const NN_NOEXCEPT
    {
        return this->slopeScaledDepthBias;
    }

/**
* @brief  Gets the value to add to the pixel depth value, scaled according to the minimum expressible levels in the depth format.
*
* @return  Returns the value to add to the pixel depth value, scaled according to the minimum expressible levels in the depth format.
*/
    int GetDepthBias() const NN_NOEXCEPT
    {
        return static_cast< int >( this->depthBias );
    }

/**
* @brief  Gets the maximum value to add to the pixel depth value.
*
* @return  Returns the maximum value to add to the pixel depth value.
*/
    float GetDepthBiasClamp() const NN_NOEXCEPT
    {
        return this->depthBiasClamp;
    }

/**
* @brief  Gets the conservative rasterization mode.
*
* @return  The conservative rasterization mode.
*/
    ConservativeRasterizationMode GetConservativeRasterizationMode() const NN_NOEXCEPT
    {
        return static_cast< ConservativeRasterizationMode >( this->conservativeRasterizationMode );
    }

/**
* @brief  Gets the multisampling state.
*
* @return  Returns a reference to the multisampling state.
*/
    const MultisampleStateInfo& GetMultisampleStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->multisample );
    }
};

/**
* @brief  Class representing blend target state information.
*/
class BlendTargetStateInfo
    : public detail::DataContainer< BlendTargetStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    BlendTargetStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetBlendEnabled( false );
*  - SetSourceColorBlendFactor( nn::gfx::BlendFactor_One );
*  - SetDestinationColorBlendFactor( nn::gfx::BlendFactor_Zero );
*  - SetColorBlendFunction( nn::gfx::BlendFunction_Add );
*  - SetSourceAlphaBlendFactor( nn::gfx::BlendFactor_One );
*  - SetDestinationAlphaBlendFactor( nn::gfx::BlendFactor_Zero );
*  - SetAlphaBlendFunction( nn::gfx::BlendFunction_Add );
*  - SetChannelMask( nn::gfx::ChannelMask_All );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Enables or disables blending.
*
* @param[in] value  Boolean value indicating whether to enable blending.
*
* @post
*  - Blending is set to be enabled or disabled.
*/
    void SetBlendEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_BlendEnable, value );
    }

/**
* @brief  Sets the blend factor for source color channels when blending.
*
* @param[in] value  Blend factor for source color channels.
*
* @post
*  - The blend factor for source color channels is set.
*/
    void SetSourceColorBlendFactor( BlendFactor value ) NN_NOEXCEPT
    {
        this->sourceColorBlendFactor = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the blend factor for destination color channels when blending.
*
* @param[in] value  Blend factor for destination color channels.
*
* @post
*  - The blend factor for destination color channels is set.
*/
    void SetDestinationColorBlendFactor( BlendFactor value ) NN_NOEXCEPT
    {
        this->destinationColorBlendFactor = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the blend function for color channels when blending.
*
* @param[in] value  Color channel blend function.
*
* @post
*  - The color channel blend function is set.
*/
    void SetColorBlendFunction( BlendFunction value ) NN_NOEXCEPT
    {
        this->colorBlendFunction = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the blend factor for the source alpha channel when blending.
*
* @param[in] value  Blend factor for the source alpha channel.
*
* @post
*  - The blend factor for the source alpha channel is set.
*/
    void SetSourceAlphaBlendFactor( BlendFactor value ) NN_NOEXCEPT
    {
        this->sourceAlphaBlendFactor = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the blend factor for the destination alpha channel when blending.
*
* @param[in] value  Blend factor for the destination alpha channel.
*
* @post
*  - The blend factor for the destination alpha channel is set.
*/
    void SetDestinationAlphaBlendFactor( BlendFactor value ) NN_NOEXCEPT
    {
        this->destinationAlphaBlendFactor = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the blend function for the alpha channel when blending.
*
* @param[in] value  Alpha channel blend function.
*
* @post
*  - The alpha channel blend function is set.
*/
    void SetAlphaBlendFunction( BlendFunction value ) NN_NOEXCEPT
    {
        this->alphaBlendFunction = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the write mask for each channel.
*
* @param[in] value  Write mask as a combination of <tt>nn::gfx::ChannelMask</tt> values.
*
* @post
*  - The write mask is set.
*/
    void SetChannelMask( int value ) NN_NOEXCEPT
    {
        this->channelMask = static_cast< Bit8 >( value );
    }

/**
* @brief  Determines whether blending is enabled.
*
* @return  Returns a Boolean value indicating whether blending is enabled.
*/
    bool IsBlendEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_BlendEnable );
    }

/**
* @brief  Gets the blend factor for source color channels when blending.
*
* @return  Returns the blend factor for source color channels.
*/
    BlendFactor GetSourceColorBlendFactor() const NN_NOEXCEPT
    {
        return static_cast< BlendFactor >( this->sourceColorBlendFactor );
    }

/**
* @brief  Gets the blend factor for destination color channels when blending.
*
* @return  Returns the blend factor for destination color channels.
*/
    BlendFactor GetDestinationColorBlendFactor() const NN_NOEXCEPT
    {
        return static_cast< BlendFactor >( this->destinationColorBlendFactor );
    }

/**
* @brief  Gets the blend function for colors when blending.
*
* @return  Returns the blend function for color channels.
*/
    BlendFunction GetColorBlendFunction() const NN_NOEXCEPT
    {
        return static_cast< BlendFunction >( this->colorBlendFunction );
    }

/**
* @brief  Gets the blend factor for the source alpha channel when blending.
*
* @return  Returns the blend factor for the source alpha channel.
*/
    BlendFactor GetSourceAlphaBlendFactor() const NN_NOEXCEPT
    {
        return static_cast< BlendFactor >( this->sourceAlphaBlendFactor );
    }

/**
* @brief  Gets the blend factor for the destination alpha channel when blending.
*
* @return  Returns the blend factor for the destination alpha channel.
*/
    BlendFactor GetDestinationAlphaBlendFactor() const NN_NOEXCEPT
    {
        return static_cast< BlendFactor >( this->destinationAlphaBlendFactor );
    }

/**
* @brief  Gets the blend function for the alpha channel when blending.
*
* @return  Returns the blend function for the alpha channel.
*/
    BlendFunction GetAlphaBlendFunction() const NN_NOEXCEPT
    {
        return static_cast< BlendFunction >( this->alphaBlendFunction );
    }

/**
* @brief  Gets the write mask for each channel.
*
* @return  Returns the write mask for each channel as a combination of <tt>nn::gfx::ChannelMask</tt> values.
*/
    int GetChannelMask() const NN_NOEXCEPT
    {
        return static_cast< int >( this->channelMask );
    }
};

/**
* @brief  Represents the information for initializing a blend state.
*/
class BlendStateInfo
    : public detail::DataContainer< BlendStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    BlendStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetAlphaToCoverageEnabled( false );
*  - SetDualSourceBlendEnabled( false );
*  - SetIndependentBlendEnabled( false );
*  - SetLogicOperationEnabled( false );
*  - SetLogicOperation( nn::gfx::LogicOperation_NoOp );
*  - SetBlendConstant( 0.0f, 0.0f, 0.0f, 1.0f );
*  - SetBlendTargetStateInfoArray( NULL, 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the logic operation.
*
* @param[in] value  Logic operation.
*
* @post
*  - The logic operation is set.
*/
    void SetLogicOperation( LogicOperation value ) NN_NOEXCEPT
    {
        this->logicOperation = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets whether to use the alpha value as the coverage during multisampling.
*
* @param[in] value  Boolean value indicating whether to use the alpha value as the coverage.
*
* @post
*  - The setting for whether to use the alpha value as the coverage is set.
*
* @details
*  Set this to the same value as <tt>SetAlphaToCoverageEnabled</tt> in <tt>MultisampleStateInfo</tt>.
*/
    void SetAlphaToCoverageEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_AlphaToCoverageEnable, value );
    }

/**
* @brief  Enables or disables dual source blending.
*
* @param[in] value  Boolean value indicating whether to enable dual source blending.
*
* @post
*  - Dual source blending is set to be enabled or disabled.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetDualSourceBlendEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_DualSourceBlendEnable, value );
    }

/**
* @brief  Sets whether to process blending independently for each color target.
*
* @param[in] value  Boolean value indicating whether to process blending independently,
*
* @post
*  - The setting for whether to use independent blending for each color target is set.
*
* @details
*  If <tt>false</tt> is specified, the 0th setting is applied to all color targets.
*/
    void SetIndependentBlendEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_IndependentBlendEnable, value );
    }

/**
* @brief  Enables or disables the logic operation.
*
* @param[in] value  Boolean value indicating whether to enable the logic operation.
*
* @post
*  - The logic operation is set to be enabled or disabled.
*
* @details
*  Blending is disabled if the logic operation is enabled.
*/
    void SetLogicOperationEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_LogicOperationEnable, value );
    }

/**
* @brief  Sets the blend constant to use for the blend factor.
*
* @param[in] red  The red component of the blend constant.
* @param[in] green  The green component of the blend constant.
* @param[in] blue  The blue component of the blend constant.
* @param[in] alpha  The alpha component of the blend constant.
*
* @post
*  - The blend constant value is set.
*/
    void SetBlendConstant( float red, float green, float blue, float alpha ) NN_NOEXCEPT
    {
        this->blendConstant[ 0 ] = red;
        this->blendConstant[ 1 ] = green;
        this->blendConstant[ 2 ] = blue;
        this->blendConstant[ 3 ] = alpha;
    }

/**
* @brief  Sets the array of blend target state information.
*
* @param[in] pBlendTargetStateInfoArray  Pointer to the array of blend target state information.
* @param[in] blendTargetStateCount  Number of blend target states.
*
* @pre
*  - <tt><var>blendTargetStateCount</var></tt> >= <tt>0</tt> && <tt><var>blendTargetStateCount</var></tt> <= <tt>255</tt>
*
* @post
*  - The blend state information array and count are set.
*
* @details
*  The elements of <tt><var>pBlendTargetStateInfoArray</var></tt> correspond to the render targets in the order listed.
*  The content being pointed to can be destroyed after the object is initialized.
*/
    void SetBlendTargetStateInfoArray( const BlendTargetStateInfo* pBlendTargetStateInfoArray,
        int blendTargetStateCount ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( blendTargetStateCount >= 0 &&
            ( std::numeric_limits< uint8_t >::max )() );
        this->blendTargetCount = static_cast< uint8_t >( blendTargetStateCount );
        this->pBlendTargetArray.ptr = nn::gfx::AccessorToData( pBlendTargetStateInfoArray );
    }

/**
* @brief  Gets the number of blend targets.
*
* @return  Returns the number of blend targets.
*/
    int GetBlendTargetCount() const NN_NOEXCEPT
    {
        return this->blendTargetCount;
    }

/**
* @brief  Gets the logic operation.
*
* @return  Returns the logic operation.
*/
    LogicOperation GetLogicOperation() const NN_NOEXCEPT
    {
        return static_cast< LogicOperation >( this->logicOperation );
    }

/**
* @brief  Determines whether the alpha value is used as the coverage during multisampling.
*
* @return  Returns a Boolean value indicating whether the alpha value is used as the coverage.
*/
    bool IsAlphaToCoverageEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_AlphaToCoverageEnable );
    }

/**
* @brief  Determines whether dual source blending is enabled.
*
* @return  Returns a Boolean value indicating whether dual source blending is enabled.
*/
    bool IsDualSourceBlendEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_DualSourceBlendEnable );
    }

/**
* @brief  Determines whether to process blending independently for each color target.
*
* @return  Returns a Boolean value indicating whether blending is run independently on each color target.
*/
    bool IsIndependentBlendEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_IndependentBlendEnable );
    }

/**
* @brief  Determines whether the logic operation is enabled.
*
* @return  Returns a Boolean value indicating whether the logic operation is enabled.
*/
    bool IsLogicOperationEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_LogicOperationEnable );
    }

/**
* @brief  Gets the blend constant to use for the blend factor.
*
* @param[in] channel  Blend constant color channel to get.
*
* @return  Returns the blend constant to use for the blend factor.
*/
    float GetBlendConstant( ColorChannel channel ) const NN_NOEXCEPT
    {
        return this->blendConstant[ channel ];
    }

/**
* @brief  Gets the array of blend target state information.
*
* @return  Returns a pointer to the array of blend target state information.
*/
    const BlendTargetStateInfo* GetBlendTargetStateInfoArray() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pBlendTargetArray.ptr );
    }
};

/**
* @brief  Class representing stencil state information.
*/
class StencilStateInfo
    : public detail::DataContainer< StencilStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    StencilStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetStencilFailOperation( nn::gfx::StencilOperation_Keep );
*  - SetDepthFailOperation( nn::gfx::StencilOperation_Keep );
*  - SetDepthPassOperation( nn::gfx::StencilOperation_Keep );
*  - SetComparisonFunction( nn::gfx::ComparisonFunction_Always );
*  - SetStencilRef( 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the stencil operation to use when the stencil test fails.
*
* @param[in] value  Stencil operation for when the stencil test fails.
*
* @post
*  - The stencil operation to use when the stencil test fails is set.
*/
    void SetStencilFailOperation( StencilOperation value ) NN_NOEXCEPT
    {
        this->stencilFailOperation = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the stencil operation to use when the depth test fails.
*
* @param[in] value  Stencil operation for when the depth test fails.
*
* @post
*  - The stencil operation to use when the depth test fails is set.
*/
    void SetDepthFailOperation( StencilOperation value ) NN_NOEXCEPT
    {
        this->depthFailOperation = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the stencil operation to use when the depth test succeeds.
*
* @param[in] value  Stencil operation for when the depth test succeeds.
*
* @post
*  - The stencil operation to use when the depth test succeeds is set.
*/
    void SetDepthPassOperation( StencilOperation value ) NN_NOEXCEPT
    {
        this->depthPassOperation = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the comparison function to use during the stencil test.
*
* @param[in] value  Comparison function for the stencil test.
*
* @post
*  - The comparison function to use for the stencil test is set.
*/
    void SetComparisonFunction( ComparisonFunction value ) NN_NOEXCEPT
    {
        this->comparisonFunction = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the stencil reference to use in the stencil test.
*
* @param[in] value  Stencil reference value.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>255</tt>.
*
* @post
*  - The stencil reference value is set.
*/
    void SetStencilRef( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint8_t >::max )() );
        this->stencilRef = static_cast< uint8_t >( value );
    }

/**
* @brief  Gets the stencil operation to use when the stencil test fails.
*
* @return  Returns the stencil operation to use when the stencil test fails.
*/
    StencilOperation GetStencilFailOperation() const NN_NOEXCEPT
    {
        return static_cast< StencilOperation >( this->stencilFailOperation );
    }

/**
* @brief  Gets the stencil operation to use when the depth test fails.
*
* @return  Returns the stencil operation to use when the depth test fails.
*/
    StencilOperation GetDepthFailOperation() const NN_NOEXCEPT
    {
        return static_cast< StencilOperation >( this->depthFailOperation );
    }

/**
* @brief  Gets the stencil operation to use when the depth test succeeds.
*
* @return  Returns the stencil operation to use when the depth test succeeds.
*/
    StencilOperation GetDepthPassOperation() const NN_NOEXCEPT
    {
        return static_cast< StencilOperation >( this->depthPassOperation );
    }

/**
* @brief  Gets the comparison function for the depth test.
*
* @return  Returns the comparison function for the depth test.
*/
    ComparisonFunction GetComparisonFunction() const NN_NOEXCEPT
    {
        return static_cast< ComparisonFunction >( this->comparisonFunction );
    }

/**
* @brief  Gets the stencil reference to use in the stencil test.
*
* @return  Returns the stencil reference value.
*/
    int GetStencilRef() const NN_NOEXCEPT
    {
        return this->stencilRef;
    }
};

/**
* @brief  Class representing the information for initializing the depth stencil state.
*/
class DepthStencilStateInfo
    : public detail::DataContainer< DepthStencilStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    DepthStencilStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetDepthComparisonFunction( nn::gfx::ComparisonFunction_Less );
*  - SetDepthTestEnabled( false );
*  - SetDepthWriteEnabled( false );
*  - SetStencilTestEnabled( false );
*  - SetDepthBoundsTestEnabled( false );
*  - SetStencilReadMask( static_cast< uint8_t >( ~0 ) );
*  - SetStencilWriteMask( static_cast< uint8_t >( ~0 ) );
*  - EditFrontStencilStateInfo().SetDefault();
*  - EditBackStencilStateInfo().SetDefault();
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the comparison function for the depth test.
*
* @param[in] value  Comparison function for the depth test.
*
* @post
*  - The comparison function to use for the depth test is set.
*/
    void SetDepthComparisonFunction( ComparisonFunction value ) NN_NOEXCEPT
    {
        this->depthComparisonFunction = static_cast< Bit8 >( value );
    }

/**
* @brief  Enables or disables the depth test.
*
* @param[in] value  Boolean value indicating whether to enable the depth test.
*
* @post
*  - The depth test is set to be enabled or disabled.
*/
    void SetDepthTestEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_DepthTestEnable, value );
    }

/**
* @brief  Enables or disables writing of the depth value.
*
* @param[in] value  Boolean value indicating whether to enable writing of the depth value.
*
* @post
*  - Writing of the depth value is set to be enabled or disabled.
*/
    void SetDepthWriteEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_DepthWriteEnable, value );
    }

/**
* @brief  Enables or disables the stencil test.
*
* @param[in] value  Boolean value indicating whether to enable the stencil test.
*
* @post
*  - The stencil test is set to be enabled or disabled.
*/
    void SetStencilTestEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_StencilTestEnable, value );
    }

/**
* @brief  Enables or disables the depth bounds test.
*
* @param[in] value  Boolean value indicating whether to enable or disable the depth bounds test.
*
* @post
*  - The depth bounds test is set to be enabled or disabled.
*/
    void SetDepthBoundsTestEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_DepthBoundsTestEnable, value );
    }

/**
* @brief  Sets the mask to apply to stencil reads.
*
* @param[in] value  Mask to use during stencil reads.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>255</tt>.
*
* @post
*  - The mask to use during stencil reads is set.
*/
    void SetStencilReadMask( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint8_t >::max )() );
        this->stencilReadMask = static_cast< uint8_t >( value );
    }

/**
* @brief  Sets the mask to apply to stencil write operations.
*
* @param[in] value  Mask to use during stencil write operations.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>255</tt>.
*
* @post
*  - The mask to use during stencil write operations is set.
*/
    void SetStencilWriteMask( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint8_t >::max )() );
        this->stencilWriteMask = static_cast< uint8_t >( value );
    }

/**
* @brief  Edits stencil state information for the front polygons.
*
* @return  Returns a reference to the stencil state information for the front polygons.
*/
    StencilStateInfo& EditFrontStencilStateInfo() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->frontStencil );
    }

/**
* @brief  Edits stencil state information for the back polygons.
*
* @return  Returns a reference to the stencil state information for the back polygons.
*/
    StencilStateInfo& EditBackStencilStateInfo() NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->backStencil );
    }

/**
* @brief  Gets the comparison function for the depth test.
*
* @return  Returns the comparison function for the depth test.
*/
    ComparisonFunction GetDepthComparisonFunction() const NN_NOEXCEPT
    {
        return static_cast< ComparisonFunction >( this->depthComparisonFunction );
    }

/**
* @brief  Determines whether the depth test is enabled.
*
* @return  Returns a Boolean value indicating whether the depth test is enabled.
*/
    bool IsDepthTestEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_DepthTestEnable );
    }

/**
* @brief  Determines whether depth write operations are enabled.
*
* @return  Returns a Boolean value indicating whether depth write operations are enabled.
*/
    bool IsDepthWriteEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_DepthWriteEnable );
    }

/**
* @brief  Determines whether the stencil test is enabled.
*
* @return  Returns a Boolean value indicating whether the stencil test is enabled.
*/
    bool IsStencilTestEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_StencilTestEnable );
    }

/**
* @brief  Determines whether the depth bounds test is enabled.
*
* @return  Returns a Boolean value indicating whether the depth bounds test is enabled.
*/
    bool IsDepthBoundsTestEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_DepthBoundsTestEnable );
    }

/**
* @brief  Gets the mask to use during stencil read operations.
*
* @return  Returns the mask to use during stencil read operations.
*/
    int GetStencilReadMask() const NN_NOEXCEPT
    {
        return this->stencilReadMask;
    }

/**
* @brief  Gets the mask to use during stencil write operations.
*
* @return  Returns the mask to use during stencil write operations.
*/
    int GetStencilWriteMask() const NN_NOEXCEPT
    {
        return this->stencilWriteMask;
    }

/**
* @brief  Gets the stencil state information for the front polygons.
*
* @return  Returns the stencil state information for the front polygons.
*/
    const StencilStateInfo& GetFrontStencilStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->frontStencil );
    }

/**
* @brief  Gets the stencil state information for the back polygons.
*
* @return  Returns the stencil state information for the back polygons.
*/
    const StencilStateInfo& GetBackStencilStateInfo() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->backStencil );
    }
};

/**
* @brief  Class representing color target state information.
*/
class ColorTargetStateInfo
    : public detail::DataContainer< ColorTargetStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    ColorTargetStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetFormat( nn::gfx::ImageFormat_Undefined );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the image format of the color buffer.
*
* @param[in] value  The color buffer's image format.
*
* @post
*  - The image format of the color buffer is set.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->format = static_cast< Bit32 >( value );
    }

/**
* @brief  Gets the image format of the color buffer.
*
* @return  Returns the image format of the color buffer.
*/
    ImageFormat GetFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->format );
    }
};

/**
* @brief  Class representing render target state information.
*/
class RenderTargetStateInfo
    : public detail::DataContainer< RenderTargetStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    RenderTargetStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetDepthStencilFormat( nn::gfx::ImageFormat_Undefined );
*  - SetColorTargetStateInfoArray( NULL, 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the depth stencil format.
*
* @param[in] value  Depth stencil format.
*
* @post
*  - The depth stencil format is set.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetDepthStencilFormat( ImageFormat value ) NN_NOEXCEPT
    {
        this->depthStencilFormat = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the array of color target state information.
*
* @param[in] pColorTargetStateInfoArray  Pointer to the array of color target state information.
* @param[in] colorTargetStateCount  The number of color target states.
*
* @pre
*  - <tt><var>colorTargetStateCount</var></tt> >= <tt>0</tt> && <tt><var>colorTargetStateCount</var></tt> <= <tt>255</tt>.
*
* @post
*  - The color target state information array and count are set.
*
* @details
*  The content being pointed to can be destroyed after the object is initialized.
*/
    void SetColorTargetStateInfoArray( const ColorTargetStateInfo* pColorTargetStateInfoArray,
        int colorTargetStateCount ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( colorTargetStateCount >= 0 &&
            ( std::numeric_limits< uint8_t >::max )() );
        this->pColorTargetStateArray.ptr = nn::gfx::AccessorToData( pColorTargetStateInfoArray );
        this->colorTargetCount = static_cast< uint8_t >( colorTargetStateCount );
    }

/**
* @brief  Gets the depth stencil format.
*
* @return  Returns the depth stencil format.
*/
    ImageFormat GetDepthStencilFormat() const NN_NOEXCEPT
    {
        return static_cast< ImageFormat >( this->depthStencilFormat );
    }

/**
* @brief  Gets the number of color targets.
*
* @return  Returns the number of color targets.
*/
    int GetColorTargetCount() const NN_NOEXCEPT
    {
        return this->colorTargetCount;
    }

/**
* @brief  Gets the array of color target state information.
*
* @return  Returns a pointer to the array of color target state information.
*/
    const ColorTargetStateInfo* GetColorTargetStateInfoArray() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pColorTargetStateArray.ptr );
    }
};

/**
* @brief  Class representing vertex attribute state information.
*/
class VertexAttributeStateInfo
    : public detail::DataContainer< VertexAttributeStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    VertexAttributeStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetSemanticIndex( 0 );
*  - SetShaderSlot( -1 );
*  - SetBufferIndex( 0 );
*  - SetOffset( 0 );
*  - SetFormat( nn::gfx::AttributeFormat_Undefined );
*  - SetNamePtr( NULL );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the semantic index for attributes that take multiple elements.
*
* @param[in] value  Semantic index of the elements.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>255</tt>.
*
* @post
*  - The semantic index of the elements is set.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetSemanticIndex( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint8_t >::max )() );
        this->semanticIndex = static_cast< uint8_t >( value );
    }

/**
* @brief  Sets the slot number in the shader.
*
* @param[in] value  Slot number.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>-1</tt> && <tt><var>value</var></tt> <= <tt>32767</tt>.
*
* @post
*  - The slot number is set in the shader.
*
* @details
*  Set the slot number to the value retrieved from the shader.
*  If <tt>SetNamePtr</tt> is set to anything other than <tt>NULL</tt>, that value is prioritized.
*  Specify <tt>-1</tt> to set an invalid slot number.
*/
    void SetShaderSlot( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= -1 && value <= ( std::numeric_limits< int16_t >::max )() );
        this->shaderSlot = static_cast< int16_t >( value );
    }

/**
* @brief  Sets the index of the vertex buffer to fetch.
*
* @param[in] value  The index of the vertex buffer.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>65535</tt>.
*
* @post
*  - The vertex buffer index is set.
*/
    void SetBufferIndex( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint16_t >::max )() );
        this->bufferIndex = static_cast< uint16_t >( value );
    }

/**
* @brief  Sets the offset from the start in the vertex buffer.
*
* @param[in] value  The offset from the start in the vertex buffer.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>4294967295</tt>.
*
* @post
*  - The offset from the start in the vertex buffer is set.
*/
    void SetOffset( ptrdiff_t value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( static_cast< int64_t >( value ) >= 0 &&  static_cast< int64_t >( value ) <= ( std::numeric_limits< uint32_t >::max )() );
        this->offset = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the vertex attribute format.
*
* @param[in] value  Vertex attribute format.
*
* @post
*  - The vertex attribute format is set.
*/
    void SetFormat( AttributeFormat value ) NN_NOEXCEPT
    {
        this->format = static_cast< Bit32 >( value );
    }

/**
* @brief  Sets the symbolic name of the vertex attribute in the shader.
*
* @param[in] value  Pointer to the symbolic name of the vertex attribute.
*
* @post
*  - The symbolic name of the vertex attribute is set.
*
* @details
*  The <tt>SetShaderSlot</tt> value is used if <tt>NULL</tt> is specified in this function.
*/
    void SetNamePtr( const char* value ) NN_NOEXCEPT
    {
        this->pName = value;
    }

/**
* @brief  Gets the semantic index for attributes that take multiple elements.
*
* @return  Returns the semantic index.
*/
    int GetSemanticIndex() const NN_NOEXCEPT
    {
        return static_cast< int >( this->semanticIndex );
    }

/**
* @brief  Gets the slot number in the shader.
*
* @return  Returns the slot number in the shader.
*/
    int GetShaderSlot() const NN_NOEXCEPT
    {
        return static_cast< int >( this->shaderSlot );
    }

/**
* @brief  Gets the index of the vertex buffer to fetch.
*
* @return  Returns the index of the vertex buffer to fetch.
*/
    int GetBufferIndex() const NN_NOEXCEPT
    {
        return static_cast< int >( this->bufferIndex );
    }

/**
* @brief  The offset from the start of the vertex buffer.
*
* @return  The offset from the start of the vertex buffer.
*/
    ptrdiff_t GetOffset() const NN_NOEXCEPT
    {
        return static_cast< ptrdiff_t >( this->offset );
    }

/**
* @brief  Gets the vertex attribute format.
*
* @return  Returns the vertex attribute format.
*/
    AttributeFormat GetFormat() const NN_NOEXCEPT
    {
        return static_cast< AttributeFormat >( this->format );
    }

/**
* @brief  Gets the symbolic name in the shader.
*
* @return  Returns the symbolic name in the shader.
*/
    const char* GetNamePtr() const NN_NOEXCEPT
    {
        return this->pName;
    }
};

/**
* @brief  Class representing vertex buffer state information.
*/
class VertexBufferStateInfo
    : public detail::DataContainer< VertexBufferStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    VertexBufferStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetStride( 0 );
*  - SetDivisor( 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the stride of the buffer.
*
* @param[in] value  Stride in bytes.
*
* @post
*  - The buffer stride is set.
*
* @platformbegin{GL}
*  This parameter does not affect object initialization.
* @platformend
*/
    void SetStride( ptrdiff_t value ) NN_NOEXCEPT
    {
        this->stride = static_cast< int32_t >( value );
    }

/**
* @brief  Sets the instance divisor that represents the number of instances to advance for each element.
*
* @param[in] value  Instance divisor.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt>.
*
* @post
*  - The instance divisor is set.
*
* @details
*  A value of <tt>0</tt> indicates data in vertex units instead of instance units.
*/
    void SetDivisor( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->divisor = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets the stride of the buffer.
*
* @return  Returns the stride in bytes.
*/
    ptrdiff_t GetStride() const NN_NOEXCEPT
    {
        return static_cast< ptrdiff_t >( this->stride );
    }

/**
* @brief  Gets the instance divisor that represents the number of instances to advance for each element.
*
* @return  Returns the instance divisor.
*
* @details
*  A return value of <tt>0</tt> indicates data in vertex units instead of instance units.
*/
    int GetDivisor() const NN_NOEXCEPT
    {
        return static_cast< int >( this->divisor );
    }
};

/**
* @brief  Class representing the information for initializing a vertex state.
*/
class VertexStateInfo
    : public detail::DataContainer< VertexStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    VertexStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetVertexAttributeStateInfoArray( NULL, 0 );
*  - SetVertexBufferStateInfoArray( NULL, 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the array of vertex attribute state information.
*
* @param[in] pVertexAttributeStateInfoArray  Pointer to the vertex attribute state information array.
* @param[in] vertexAttributeStateCount  The number of vertex attribute states.
*
* @pre
*  - <tt><var>vertexAttributeStateCount</var></tt> >= <tt>0</tt> && <tt><var>vertexAttributeStateCount</var></tt> <= <tt>65535</tt>.
*
* @post
*  - The vertex attribute state information array and count are set.
*
* @details
*  The content being pointed to can be destroyed after the object is initialized.
*/
    void SetVertexAttributeStateInfoArray( const VertexAttributeStateInfo* pVertexAttributeStateInfoArray,
        int vertexAttributeStateCount ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( vertexAttributeStateCount >= 0 &&
            ( std::numeric_limits< uint16_t >::max )() );
        this->pAttributeArray.ptr = nn::gfx::AccessorToData( pVertexAttributeStateInfoArray );
        this->attributeCount = static_cast< uint16_t >( vertexAttributeStateCount );
    }

/**
* @brief  Sets the array of vertex buffer state information.
*
* @param[in] pVertexBufferStateInfoArray  Pointer to the array of vertex buffer state information.
* @param[in] vertexBufferStateCount  The number of vertex buffer states.
*
* @pre
*  - <tt><var>vertexBufferStateCount</var></tt> >= <tt>0</tt> && <tt><var>vertexBufferStateCount</var></tt> <= <tt>65535</tt>.
*
* @post
*  - The vertex buffer state information array and count are set.
*
* @details
*  The content being pointed to can be destroyed after the object is initialized.
*/
    void SetVertexBufferStateInfoArray( const VertexBufferStateInfo* pVertexBufferStateInfoArray,
        int vertexBufferStateCount) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( vertexBufferStateCount >= 0 &&
            ( std::numeric_limits< uint16_t >::max )() );
        this->pBufferArray.ptr = nn::gfx::AccessorToData( pVertexBufferStateInfoArray );
        this->bufferCount = static_cast< uint16_t >( vertexBufferStateCount );
    }

/**
* @brief  Gets the number of vertex attributes.
*
* @return  Returns the number of vertex attributes.
*/
    int GetVertexAttributeCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->attributeCount );
    }

/**
* @brief  Gets the number of vertex buffers.
*
* @return  Returns the number of vertex buffers.
*/
    int GetVertexBufferCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->bufferCount );
    }

/**
* @brief  Gets the array of vertex attribute state information.
*
* @return  Pointer to the vertex attribute state information array.
*/
    const VertexAttributeStateInfo* GetVertexAttributeStateInfoArray() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pAttributeArray.ptr );
    }

/**
* @brief  Gets the array of vertex buffer state information.
*
* @return  Pointer to the vertex buffer state information array.
*/
    const VertexBufferStateInfo* GetVertexBufferStateInfoArray() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pBufferArray.ptr );
    }
};

/**
* @brief  Class representing the tessellation state.
*/
class TessellationStateInfo
    : public detail::DataContainer< TessellationStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    TessellationStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetPatchControlPointCount( 1 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the number of packed triangles.
*
* @param[in] value  The number of patch control points.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> < <tt>65535</tt>.
*
* @post
*  - The number of patch control points is set.
*/
    void SetPatchControlPointCount( int value ) NN_NOEXCEPT
    {
        NN_SDK_ASSERT( value >= 0 && value < ( std::numeric_limits< uint16_t >::max )() );
        this->patchControlPointCount = static_cast< uint16_t >( value );
    }

/**
* @brief  Gets the number of patch control points.
*
* @return  Returns the number of patch control points.
*/
    int GetPatchControlPointCount() const NN_NOEXCEPT
    {
        return this->patchControlPointCount;
    }
};

/**
* @brief  Class representing viewport information.
*/
class ViewportStateInfo
    : public detail::DataContainer< ViewportStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    ViewportStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetOriginX( 0.0f );
*  - SetOriginY( 0.0f );
*  - SetWidth( 0.0f );
*  - SetHeight( 0.0f );
*  - SetMinDepth( 0.0f );
*  - SetMaxDepth( 1.0f );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the x-coordinate of the viewport origin.
*
* @param[in] value  X-coordinate of the viewport origin.
*
* @post
*  - The x-coordinate of the viewport origin is set.
*/
    void SetOriginX( float value ) NN_NOEXCEPT
    {
        this->originX = value;
    }

/**
* @brief  Sets the y-coordinate of the viewport origin.
*
* @param[in] value  Y-coordinate of the viewport origin.
*
* @post
*  - The y-coordinate of the viewport origin is set.
*/
    void SetOriginY( float value ) NN_NOEXCEPT
    {
        this->originY = value;
    }

/**
* @brief  Sets the width of the viewport.
*
* @param[in] value  Width of the viewport.
*
* @post
*  - The width of the viewport is set.
*/
    void SetWidth( float value ) NN_NOEXCEPT
    {
        this->width = value;
    }

/**
* @brief  Sets the height of the viewport.
*
* @param[in] value  Height of the viewport.
*
* @post
*  - The height of the viewport is set.
*/
    void SetHeight( float value ) NN_NOEXCEPT
    {
        this->height = value;
    }

/**
* @brief  Sets the minimum depth of the viewport.
*
* @param[in] value  Minimum depth of the viewport.
*
* @post
*  - The minimum depth of the viewport is set.
*/
    void SetMinDepth( float value ) NN_NOEXCEPT
    {
        this->depthRange.minDepth = value;
    }

/**
* @brief  Sets the maximum depth of the viewport.
*
* @param[in] value  Maximum depth of the viewport.
*
* @post
*  - The maximum depth of the viewport is set.
*/
    void SetMaxDepth( float value ) NN_NOEXCEPT
    {
        this->depthRange.maxDepth = value;
    }

/**
* @brief  Gets the x-coordinate of the viewport origin.
*
* @return  Returns the x-coordinate of the viewport origin.
*/
    float GetOriginX() const NN_NOEXCEPT
    {
        return this->originX;
    }

/**
* @brief  Gets the y-coordinate of the viewport origin.
*
* @return  Returns the y-coordinate of the viewport origin.
*/
    float GetOriginY() const NN_NOEXCEPT
    {
        return this->originY;
    }

/**
* @brief  Gets the width of the viewport.
*
* @return  Returns the width of the viewport.
*/
    float GetWidth() const NN_NOEXCEPT
    {
        return this->width;
    }

/**
* @brief  Gets the height of the viewport.
*
* @return  Returns the height of the viewport.
*/
    float GetHeight() const NN_NOEXCEPT
    {
        return this->height;
    }

/**
* @brief  Gets the minimum depth of the viewport.
*
* @return  Returns the minimum depth of the viewport.
*/
    float GetMinDepth() const NN_NOEXCEPT
    {
        return this->depthRange.minDepth;
    }

/**
* @brief  Gets the maximum depth of the viewport.
*
* @return  Returns the maximum depth of the viewport.
*/
    float GetMaxDepth() const NN_NOEXCEPT
    {
        return this->depthRange.maxDepth;
    }
};

/**
* @brief  Class representing scissoring state information.
*/
class ScissorStateInfo
    : public detail::DataContainer< ScissorStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    ScissorStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetOriginX( 0 );
*  - SetOriginY( 0 );
*  - SetWidth( 0 );
*  - SetHeight( 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the x-coordinate of the scissoring origin.
*
* @param[in] value  X-coordinate of the scissoring origin.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt>.
*
* @post
*  - The x-coordinate of the scissoring origin is set.
*/
    void SetOriginX( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->originX = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the y-coordinate of the scissoring origin.
*
* @param[in] value  Y-coordinate of the scissoring origin.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt>.
*
* @post
*  - The y-coordinate of the scissoring origin is set.
*/
    void SetOriginY( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->originY = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the scissoring width.
*
* @param[in] value  Scissoring width.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt>.
*
* @post
*  - The scissoring width is set.
*/
    void SetWidth( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->width = static_cast< uint32_t >( value );
    }

/**
* @brief  Sets the scissoring height.
*
* @param[in] value  Scissoring height.
*
* @pre
*  - <tt><var>value</var></tt> >= <tt>0</tt>.
*
* @post
*  - The scissoring height is set.
*/
    void SetHeight( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 );
        this->height = static_cast< uint32_t >( value );
    }

/**
* @brief  Gets the x-coordinate of the scissoring origin.
*
* @return  Returns the x-coordinate of the scissoring origin.
*/
    int GetOriginX() const NN_NOEXCEPT
    {
        return static_cast< int >( this->originX );
    }

/**
* @brief  Gets the y-coordinate of the scissoring origin.
*
* @return  Returns the y-coordinate of the scissoring origin.
*/
    int GetOriginY() const NN_NOEXCEPT
    {
        return static_cast< int >( this->originY );
    }

/**
* @brief  Gets the scissoring width.
*
* @return  Returns the scissoring width.
*/
    int GetWidth() const NN_NOEXCEPT
    {
        return static_cast< int >( this->width );
    }

/**
* @brief  Gets the scissoring height.
*
* @return  Returns the scissoring height.
*/
    int GetHeight() const NN_NOEXCEPT
    {
        return static_cast< int >( this->height );
    }
};

/**
* @brief  Class representing the information for initializing the viewport scissoring state.
*/
class ViewportScissorStateInfo
    : public detail::DataContainer< ViewportScissorStateInfoData >
{
public:
/**
* @brief  Constructor.
*
* @post
*  - All parameters have been initialized to zero.
*/
    ViewportScissorStateInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
*
* @post
*  - The various parameters are configured.
*
* @details
*  Equivalent to calling the following.
*  - SetScissorEnabled( false );
*  - SetViewportStateInfoArray( NULL, 0 );
*  - SetScissorStateInfoArray( NULL, 0 );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Enables or disables scissoring.
*
* @param[in] value  Boolean value indicating whether to enable scissoring.
*
* @post
*  - Scissoring is set to be enabled or disabled.
*
* @details
*  This setting must match the rasterizer state scissoring.
*/
    void SetScissorEnabled( bool value ) NN_NOEXCEPT
    {
        this->flag.SetBit( Flag_ScissorEnable, value );
    }

/**
* @brief  Sets the array of viewport state information.
*
* @param[in] pViewportStateInfoArray  Pointer to the array of viewport state information.
* @param[in] viewportStateCount  Number of viewport states.
*
* @pre
*  - <tt><var>viewportStateCount</var></tt> >= <tt>0</tt> && <tt><var>viewportStateCount</var></tt> <= <tt>65535</tt>.
*
* @post
*  - The viewport state information array and count are set.
*
* @details
*  The content being pointed to can be destroyed after the object is initialized.
*  When scissoring is enabled, the number of viewport states must match the number of scissor states.
*/
    void SetViewportStateInfoArray( const ViewportStateInfo* pViewportStateInfoArray,
        int viewportStateCount ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( viewportStateCount >= 0 &&
            viewportStateCount <= ( std::numeric_limits< uint16_t >::max )() );
        this->pViewportArray.ptr = nn::gfx::AccessorToData( pViewportStateInfoArray );
        this->viewportCount = static_cast< uint16_t >( viewportStateCount );
    }

/**
* @brief  Sets the array of scissor state information.
*
* @param[in] pScissorStateInfoArray  Pointer to the array of scissor state information.
* @param[in] scissorStateCount  Number of scissor states.
*
* @pre
*  - <tt><var>scissorStateCount</var></tt> >= <tt>0</tt> && <tt><var>scissorStateCount</var></tt> <= <tt>65535</tt>.
*
* @post
*  - The scissor state information array and count are set.
*
* @details
*  The content being pointed to can be destroyed after the object is initialized.
*  When scissoring is enabled, the number of scissor states must match the number of viewport states.
*/
    void SetScissorStateInfoArray( const ScissorStateInfo* pScissorStateInfoArray,
        int scissorStateCount ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( scissorStateCount >= 0 &&
            scissorStateCount <= ( std::numeric_limits< uint16_t >::max )() );
        this->pScissorArray.ptr = nn::gfx::AccessorToData( pScissorStateInfoArray );
        this->scissorCount = static_cast< uint16_t >( scissorStateCount );
    }

/**
* @brief  Determines whether scissoring is enabled.
*
* @return  Returns a Boolean value indicating whether scissoring is enabled.
*/
    bool IsScissorEnabled() const NN_NOEXCEPT
    {
        return this->flag.GetBit( Flag_ScissorEnable );
    }

/**
* @brief  Gets the number of viewports.
*
* @return  Returns the number of viewports.
*/
    int GetViewportCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->viewportCount );
    }

/**
* @brief  Gets the number of scissors.
*
* @return  Returns the number of scissors.
*/
    int GetScissorCount() const NN_NOEXCEPT
    {
        return static_cast< int >( this->scissorCount );
    }

/**
* @brief  Gets the array of viewport state information.
*
* @return  Returns a pointer to the array of viewport state information.
*/
    const ViewportStateInfo* GetViewportStateInfoArray() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pViewportArray.ptr );
    }

/**
* @brief  Gets the array of scissoring state information.
*
* @return  Returns a pointer to the array of scissoring state information.
*/
    const ScissorStateInfo* GetScissorStateInfoArray() const NN_NOEXCEPT
    {
        return nn::gfx::DataToAccessor( this->pScissorArray.ptr );
    }
};

}
}
