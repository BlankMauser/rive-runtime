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
* @brief  Declarations for API resources related to sampler initialization information.
*/

#pragma once

#include <limits>

#include <nn/nn_SdkAssert.h>

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_SamplerInfoData.h>

#include <nn/gfx/detail/gfx_Declare.h>
#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/detail/gfx_DataContainer.h>

#if !defined( NN_GFX_CONFIG_DISABLE_TINFO )

#if defined( NN_GFX_CONFIG_INCLUDE_NVN8 )
    #include <nn/gfx/detail/gfx_SamplerInfo-api.nvn.8.h>
#endif

#endif

namespace nn {
namespace gfx {

/**
* @brief  Represents the information for initializing a sampler.
*/
class SamplerInfo
    : public detail::DataContainer< SamplerInfoData >
{
public:
/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    SamplerInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
    *
* @post
    * - The various parameters are configured.
    *
* @details
    * Equivalent to calling the following.
    * - SetFilterMode( nn::gfx::FilterMode_MinLinear_MagLinear_MipLinear );
    * - SetAddressU( nn::gfx::TextureAddressMode_ClampToEdge );
    * - SetAddressV( nn::gfx::TextureAddressMode_ClampToEdge );
    * - SetAddressW( nn::gfx::TextureAddressMode_ClampToEdge );
    * - SetComparisonFunction( nn::gfx::ComparisonFunction_Never );
    * - SetBorderColorType( nn::gfx::TextureBorderColorType_White );
    * - SetMaxAnisotropy( 1 );
    * - SetMinLod( -1000.0f );
    * - SetMaxLod( 1000.0f );
    * - SetLodBias( 0.0f );
*/
    void SetDefault() NN_NOEXCEPT;

/**
* @brief  Sets the filter mode to apply during sampling.
    *
* @param[in] value  Filter mode.
    *
* @post
    * - The filter mode is set.
*/
    void SetFilterMode( FilterMode value ) NN_NOEXCEPT
    {
        this->filterMode = static_cast< Bit16 >( value );
    }

/**
* @brief  Sets the address mode for the u-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @param[in] value  Address mode.
    *
* @post
    * - The u-coordinate address mode is set.
*/
    void SetAddressU( TextureAddressMode value ) NN_NOEXCEPT
    {
        this->addressU = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the address mode for the v-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @param[in] value  Address mode.
    *
* @post
    * - The v-coordinate address mode is set.
*/
    void SetAddressV( TextureAddressMode value ) NN_NOEXCEPT
    {
        this->addressV = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the address mode for the w-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @param[in] value  Address mode.
    *
* @post
    * - The w-coordinate address mode is set.
*/
    void SetAddressW( TextureAddressMode value ) NN_NOEXCEPT
    {
        this->addressW = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the comparison function to apply when <tt>Comparison</tt> is included in the filter mode.
    *
* @param[in] value  Comparison function.
    *
* @post
    * - The comparison function is set.
*/
    void SetComparisonFunction( ComparisonFunction value ) NN_NOEXCEPT
    {
        this->comparisonFunction = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the border color type to apply when the address mode is <tt>TextureAddressMode_ClampToBorder</tt>.
    *
* @param[in] value  Border color type.
    *
* @post
    * - The border color type is set.
*/
    void SetBorderColorType( TextureBorderColorType value ) NN_NOEXCEPT
    {
        this->borderColorType = static_cast< Bit8 >( value );
    }

/**
* @brief  Sets the maximum sample count for anisotropic filtering to apply when the filter mode includes <tt>Anisotropy</tt>.
    *
* @param[in] value  Maximum sample count for anisotropic filtering.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>255</tt>.
    *
* @post
    * - The maximum sample count for anisotropic filtering is set.
*/
    void SetMaxAnisotropy( int value ) NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( value >= 0 && value <= ( std::numeric_limits< uint8_t >::max )() );
        this->maxAnisotropy = static_cast< uint8_t >( value );
    }

/**
* @brief  Sets the minimum LOD to use in mipmapping.
    *
* @param[in] value  Minimum mipmap level of detail.
    *
* @post
    * - The minimum LOD for mipmapping is set.
*/
    void SetMinLod( float value ) NN_NOEXCEPT
    {
        this->minLod = value;
    }

/**
* @brief  Sets the maximum LOD to use in mipmapping.
    *
* @param[in] value  Maximum mipmap level of detail.
    *
* @post
    * - The maximum LOD for mipmapping is set.
*/
    void SetMaxLod( float value ) NN_NOEXCEPT
    {
        this->maxLod = value;
    }

/**
* @brief  Sets the offset value to apply to the calculated mipmap level.
    *
* @param[in] value  Mipmap level offset value.
    *
* @post
    * - The mipmap level offset value is set.
*/
    void SetLodBias( float value ) NN_NOEXCEPT
    {
        this->lodBias = value;
    }

/**
* @brief  Gets the filter mode to apply during sampling.
    *
* @return  Returns the filter mode.
*/
    FilterMode GetFilterMode() const NN_NOEXCEPT
    {
        return static_cast< FilterMode >( this->filterMode );
    }

/**
* @brief  Gets the address mode for the u-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @return  Returns the u-coordinate address mode.
*/
    TextureAddressMode GetAddressU() const NN_NOEXCEPT
    {
        return static_cast< TextureAddressMode >( this->addressU );
    }

/**
* @brief  Gets the address mode for the v-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @return  Returns the v-coordinate address mode.
*/
    TextureAddressMode GetAddressV() const NN_NOEXCEPT
    {
        return static_cast< TextureAddressMode >( this->addressV );
    }

/**
* @brief  Gets the address mode for the w-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @return  Returns the w-coordinate address mode.
*/
    TextureAddressMode GetAddressW() const NN_NOEXCEPT
    {
        return static_cast< TextureAddressMode >( this->addressW );
    }

/**
* @brief  Gets the comparison function to apply when the filter mode includes <tt>Comparison</tt> in its name.
    *
* @return  Returns the comparison function.
*/
    ComparisonFunction GetComparisonFunction() const NN_NOEXCEPT
    {
        return static_cast< ComparisonFunction >( this->comparisonFunction );
    }

/**
* @brief  Gets the border color type to apply when the address mode is <tt>TextureAddressMode_ClampToBorder</tt>.
    *
* @return  Returns the border color type.
*/
    TextureBorderColorType GetBorderColorType() const NN_NOEXCEPT
    {
        return static_cast< TextureBorderColorType >( this->borderColorType );
    }

/**
* @brief  Gets the maximum sample count for anisotropic filtering to apply when the filter mode includes <tt>Anisotropy</tt>.
    *
* @return  Returns the maximum sample count for anisotropic filtering.
*/
    int GetMaxAnisotropy() const NN_NOEXCEPT
    {
        return this->maxAnisotropy;
    }

/**
* @brief  Gets the minimum LOD to use in mipmapping.
    *
* @return  Returns the minimum mipmap level of detail.
*/
    float GetMinLod() const NN_NOEXCEPT
    {
        return this->minLod;
    }

/**
* @brief  Gets the maximum LOD to use in mipmapping.
    *
* @return  Returns the maximum mipmap level of detail.
*/
    float GetMaxLod() const NN_NOEXCEPT
    {
        return this->maxLod;
    }

/**
* @brief  Gets the offset value to apply to the calculated mipmap level.
    *
* @return  Returns the mipmap level offset value.
*/
    float GetLodBias() const NN_NOEXCEPT
    {
        return this->lodBias;
    }
};

/**
* @brief  Graphics abstraction layer representing information for initializing a sampler.
*/
template< typename TTarget >
class TSamplerInfo
    : public detail::TargetInfoImpl< detail::SamplerInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, SamplerInfo >::Type
{
    typedef typename detail::TargetInfoImpl< detail::SamplerInfoImpl<
        typename detail::TargetVariation< TTarget >::Type >, SamplerInfo >::Type Impl;

public:
/**
* @brief  The target low-level graphics API.
*/
    typedef typename detail::TargetVariation< TTarget >::Type Target;

/**
* @brief  Converts common-version information to special edition information.
    *
* @param[in] pDstInfo  Pointer to the destination for the converted special edition information.
* @param[in] info  The common-version information that serves as the source.
    *
* @pre
    * - <tt><var>pDstInfo</var></tt> != <tt>NULL</tt>.
*/
    static void ConvertFromInfo( TSamplerInfo< TTarget >* pDstInfo, const SamplerInfo& info ) NN_NOEXCEPT
    {
        return detail::InfoHelper::ConvertFromInfo< Impl >( pDstInfo, info );
    }

/**
* @brief  Constructor.
    *
* @post
    * - All parameters have been initialized to zero.
*/
    TSamplerInfo() NN_NOEXCEPT
    {
    }

/**
* @brief  A helper function for setting the default value for each parameter.
    *
* @post
    * - The various parameters are configured.
    *
* @details
    * Equivalent to calling the following.
    * - SetFilterMode( nn::gfx::FilterMode_MinLinear_MagLinear_MipLinear );
    * - SetAddressU( nn::gfx::TextureAddressMode_ClampToEdge );
    * - SetAddressV( nn::gfx::TextureAddressMode_ClampToEdge );
    * - SetAddressW( nn::gfx::TextureAddressMode_ClampToEdge );
    * - SetComparisonFunction( nn::gfx::ComparisonFunction_Never );
    * - SetBorderColorType( nn::gfx::TextureBorderColorType_White );
    * - SetMaxAnisotropy( 1 );
    * - SetMinLod( -1000.0f );
    * - SetMaxLod( 1000.0f );
    * - SetLodBias( 0.0f );
*/
    void SetDefault() NN_NOEXCEPT
    {
        return Impl::SetDefault();
    }

/**
* @brief  Sets the filter mode to apply during sampling.
    *
* @param[in] value  Filter mode.
    *
* @post
    * - The filter mode is set.
*/
    void SetFilterMode( FilterMode value ) NN_NOEXCEPT
    {
        return Impl::SetFilterMode( value );
    }

/**
* @brief  Sets the address mode for the u-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @param[in] value  Address mode.
    *
* @post
    * - The u-coordinate address mode is set.
*/
    void SetAddressU( TextureAddressMode value ) NN_NOEXCEPT
    {
        return Impl::SetAddressU( value );
    }

/**
* @brief  Sets the address mode for the v-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @param[in] value  Address mode.
    *
* @post
    * - The v-coordinate address mode is set.
*/
    void SetAddressV( TextureAddressMode value ) NN_NOEXCEPT
    {
        return Impl::SetAddressV( value );
    }

/**
* @brief  Sets the address mode for the w-coordinate when sampling outside the <tt>0.0</tt> to <tt>1.0</tt> range.
    *
* @param[in] value  Address mode.
    *
* @post
    * - The w-coordinate address mode is set.
*/
    void SetAddressW( TextureAddressMode value ) NN_NOEXCEPT
    {
        return Impl::SetAddressW( value );
    }

/**
* @brief  Sets the comparison function to apply when <tt>Comparison</tt> is included in the filter mode.
    *
* @param[in] value  Comparison function.
    *
* @post
    * - The comparison function is set.
*/
    void SetComparisonFunction( ComparisonFunction value ) NN_NOEXCEPT
    {
        return Impl::SetComparisonFunction( value );
    }

/**
* @brief  Sets the border color type to apply when the address mode is <tt>TextureAddressMode_ClampToBorder</tt>.
    *
* @param[in] value  Border color type.
    *
* @post
    * - The border color type is set.
*/
    void SetBorderColorType( TextureBorderColorType value ) NN_NOEXCEPT
    {
        return Impl::SetBorderColorType( value );
    }

/**
* @brief  Sets the maximum sample count for anisotropic filtering to apply when the filter mode includes <tt>Anisotropy</tt>.
    *
* @param[in] value  Maximum sample count for anisotropic filtering.
    *
* @pre
    * - <tt><var>value</var></tt> >= <tt>0</tt> && <tt><var>value</var></tt> <= <tt>255</tt>.
    *
* @post
    * - The maximum sample count for anisotropic filtering is set.
*/
    void SetMaxAnisotropy( int value ) NN_NOEXCEPT
    {
        return Impl::SetMaxAnisotropy( value );
    }

/**
* @brief  Sets the minimum LOD to use in mipmapping.
    *
* @param[in] value  Minimum mipmap level of detail.
    *
* @post
    * - The minimum LOD for mipmapping is set.
*/
    void SetMinLod( float value ) NN_NOEXCEPT
    {
        return Impl::SetMinLod( value );
    }

/**
* @brief  Sets the maximum LOD to use in mipmapping.
    *
* @param[in] value  Maximum mipmap level of detail.
    *
* @post
    * - The maximum LOD for mipmapping is set.
*/
    void SetMaxLod( float value ) NN_NOEXCEPT
    {
        return Impl::SetMaxLod( value );
    }

/**
* @brief  Sets the offset value to apply to the calculated mipmap level.
    *
* @param[in] value  Mipmap level offset value.
    *
* @post
    * - The mipmap level offset value is set.
*/
    void SetLodBias( float value ) NN_NOEXCEPT
    {
        return Impl::SetLodBias( value );
    }
};

}
}
