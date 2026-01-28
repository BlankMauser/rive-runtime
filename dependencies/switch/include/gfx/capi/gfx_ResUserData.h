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
* @brief  API declarations for user data resources.
*/

#pragma once

#include <nn/util/util_AccessorBase.h>

#include <nn/gfx/gfx_ResUserDataData.h>

namespace nn {
namespace gfx {

/**
* @brief  Class indicating user data resources.
*/
class ResUserData
    : public nn::util::AccessorBase< ResUserDataData >
{
    NN_DISALLOW_COPY( ResUserData );

public:
/**
* @brief  The data type.
*/
    enum Type
    {
        Type_Int, //!<  Signed 32-bit integer.
        Type_Float, //!<  Floating-point number.
        Type_String, //!<  The UTF-8 string.
        Type_Stream //!<  Byte array.
    };

/**
* @brief  Gets the user data name.
*
* @return  Returns a pointer to the user data name.
*/
    const char* GetName() const NN_NOEXCEPT
    {
        return this->pName.Get()->GetData();
    }

/**
* @brief  Gets the data count.
*
* @return  Returns the data count.
*/
    int GetCount() const NN_NOEXCEPT
    {
        return this->count;
    }

/**
* @brief  Gets the data type.
*
* @return  Returns the data type.
*/
    Type GetType() const NN_NOEXCEPT
    {
        return static_cast< Type >( this->type );
    }

/**
* @brief  Gets the data as an integer array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Int</tt>.
*
* @return  Returns a pointer to the start of the <tt>int32_t</tt> array.
*/
    int32_t* GetInt() NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Int );
        return static_cast< int32_t* >( this->pData.Get() );
    }

/**
* @brief  Gets the data as an integer array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Int</tt>.
*
* @return  Returns a pointer to the start of the <tt>int32_t</tt> array.
*/
    const int32_t* GetInt() const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Int );
        return static_cast< const int32_t* >( this->pData.Get() );
    }

/**
* @brief  Gets the data as an integer value.
*
* @param[in] index  Index of the data being obtained.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Int</tt>.
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetCount()</tt>.
*
* @return  Returns the element specified in the <tt>int32_t</tt> array index.
*/
    int32_t GetInt( int index ) const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES(this->type == Type_Int);
        NN_SDK_REQUIRES_RANGE(index, 0, GetCount());
        return static_cast< const int32_t* >(this->pData.Get())[index];
    }

/**
* @brief  Gets the data as a floating-point number array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Float</tt>.
*
* @return  Returns a pointer to the start of the <tt>float</tt> array.
*/
    float* GetFloat() NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Float );
        return static_cast< float* >( this->pData.Get() );
    }

/**
* @brief  Gets the data as a floating-point number array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Float</tt>.
*
* @return  Returns a pointer to the start of the <tt>float</tt> array.
*/
    const float* GetFloat() const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Float );
        return static_cast< const float* >( this->pData.Get() );
    }

/**
* @brief  Gets the data as a floating-point number.
*
* @param[in] index  Index of the data being obtained.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Float</tt>.
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetCount()</tt>.
*
* @return  Returns the element specified in the <tt>float</tt> array index.
*/
    float GetFloat( int index ) const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES(this->type == Type_Float);
        NN_SDK_REQUIRES_RANGE(index, 0, GetCount());
        return static_cast< const float* >(this->pData.Get())[index];
    }

/**
* @brief  Gets the data as a string.
*
* @param[in] index  Index for the string to get.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_String</tt>.
*  - <tt><var>index</var></tt> >= <tt>0</tt> && <tt><var>index</var></tt> < <tt>GetCount()</tt>.
*
* @return  Returns a pointer to a <tt>char</tt> array.
*/
    const char* GetString( int index ) const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_String );
        NN_SDK_REQUIRES_RANGE( index, 0, GetCount() );
        nn::util::BinPtrToString pString = static_cast<
            const nn::util::BinPtrToString* >( this->pData.Get() )[ index ];
        return pString.Get()->GetData();
    }

/**
* @brief  Gets data as a byte array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Stream</tt>.
*
* @return  Returns a pointer to a byte array.
*/
    void* GetStream() NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Stream );
        return this->pData.Get();
    }

/**
* @brief  Gets data as a byte array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Stream</tt>.
*
* @return  Returns a pointer to a byte array.
*/
    const void* GetStream() const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Stream );
        return this->pData.Get();
    }

/**
* @brief  Gets the size of the byte array.
*
* @pre
*  - <tt>GetType()</tt>  ==  <tt>Type_Stream</tt>.
*
* @return  Returns the size of the byte array.
*/
    size_t GetStreamSize() const NN_NOEXCEPT
    {
        NN_SDK_REQUIRES( this->type == Type_Stream );
        return this->count;
    }
};

}
}

