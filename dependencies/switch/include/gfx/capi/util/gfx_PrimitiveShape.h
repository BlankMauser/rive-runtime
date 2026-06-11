/*--------------------------------------------------------------------------------*
  Copyright Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain proprietary
  information of Nintendo and/or its licensed developers and are protected by
  national and international copyright laws. They may not be disclosed to third
  parties or copied or duplicated in any form, in whole or in part, without the
  prior written consent of Nintendo.

  The content herein is highly confidential and should be handled accordingly.
 *--------------------------------------------------------------------------------*/

#pragma once

#include <nn/gfx.h>

namespace nn {
namespace gfx {
namespace util {


//---------------------------------------------------------------------------
//! @deprecated  The API required by this enumerated type does not exist. Use <tt>#PrimitiveShapeFormat</tt> when setting the primitive vertex attributes.
//! @brief  Vertex attribute.
//---------------------------------------------------------------------------
enum NN_DEPRECATED PrimitiveShapeAttribute
{
    PrimitiveShapeAttribute_Pos = 0,
    PrimitiveShapeAttribute_Normal,
    PrimitiveShapeAttribute_Uv,

    PrimitiveShapeAttribute_CountMax
};

//---------------------------------------------------------------------------
//! @brief  Vertex format for primitives.
//---------------------------------------------------------------------------
enum PrimitiveShapeFormat
{
    PrimitiveShapeFormat_Pos       = 0x01, //!<  Format that represents the coordinate component.
    PrimitiveShapeFormat_Normal    = 0x02, //!<  Format that represents the normal component.
    PrimitiveShapeFormat_Uv        = 0x04, //!<  Format that represents the UV component.

    //!  This format includes the coordinate component, normal component, and UV component.
    PrimitiveShapeFormat_Default   = PrimitiveShapeFormat_Pos | PrimitiveShapeFormat_Normal | PrimitiveShapeFormat_Uv
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information for the primitive.
//---------------------------------------------------------------------------
class PrimitiveShape
{
    NN_DISALLOW_COPY( PrimitiveShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~PrimitiveShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Returns a pointer to the index buffer.
    //!
    //! @return  Returns the pointer.
    //!
    //! @pre
    //!  - <tt>Calculate</tt> has been called.
    //---------------------------------------------------------------------------
    void* GetIndexBuffer() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets a pointer to the vertex buffer.
    //!
    //! @return  Returns the pointer.
    //!
    //! @pre
    //!  - <tt>Calculate</tt> has been called.
    //---------------------------------------------------------------------------
    void* GetVertexBuffer() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the size of the stride of the vertex buffer.
    //!
    //! @return  Returns the size of the stride size in bytes.
    //---------------------------------------------------------------------------
    size_t GetStride() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the size of the vertex buffer.
    //!
    //! @return  Returns the size of the vertex buffer in bytes.
    //---------------------------------------------------------------------------
    size_t GetVertexBufferSize() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the size of the index buffer.
    //!
    //! @return  Returns the size of the index buffer in bytes.
    //---------------------------------------------------------------------------
    size_t GetIndexBufferSize() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The vertex format.
    //!
    //! @return  The vertex format.
    //---------------------------------------------------------------------------
    PrimitiveShapeFormat GetVertexFormat() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The primitive topology.
    //!
    //! @return  The primitive topology.
    //---------------------------------------------------------------------------
    nn::gfx::PrimitiveTopology GetPrimitiveTopology() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The index buffer format.
    //!
    //! @return  The index buffer format.
    //---------------------------------------------------------------------------
    nn::gfx::IndexFormat GetIndexBufferFormat() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int GetVertexCount() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The number of indices.
    //---------------------------------------------------------------------------
    int GetIndexCount() const NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Writes the vertex and index information to the buffer that is passed.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    void Calculate( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //---------------------------------------------------------------------------
    PrimitiveShape( int vertexFormat, nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  A pure virtual function that implements the <tt>Calculate()</tt> function.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @details  Implement as a class that inherits <tt>PrimitiveShape</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT = 0;

    //---------------------------------------------------------------------------
    //! @brief  Sets a pointer to the vertex buffer.
    //!
    //! @param[in] pVertexBuffer  Starting address of the vertex buffer.
    //!
    //! @pre
    //!  - <tt><var>pVertexBuffer</var></tt> != <tt>NULL</tt>.
    //---------------------------------------------------------------------------
    void SetVertexBuffer( void* pVertexBuffer ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the pointer to the index buffer.
    //!
    //! @param[in] pIndexBuffer  Starting address of the index buffer.
    //!
    //! @pre
    //!  - <tt><var>pIndexBuffer</var></tt> != <tt>NULL</tt>.
    //---------------------------------------------------------------------------
    void SetIndexBuffer( void* pIndexBuffer ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @deprecated  Do not use this function because an appropriate buffer size is set when using <tt>SetVertexCount()</tt> to specify the vertex count.
    //!
    //! @brief  Sets the size of the vertex buffer.
    //!
    //! @param[in] vertexBufferSize  Vertex buffer size.
    //---------------------------------------------------------------------------
    NN_DEPRECATED void SetVertexBufferSize( size_t vertexBufferSize ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @deprecated  Do not use this function because an appropriate buffer size is set when using <tt>SetIndexCount()</tt> to specify the index count.
    //!
    //! @brief  Sets the index buffer size.
    //!
    //! @param[in] indexBufferSize  Index buffer size.
    //---------------------------------------------------------------------------
    NN_DEPRECATED void SetIndexBufferSize( size_t indexBufferSize ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the number of vertices.
    //!
    //! @param[in] vertexCount  The number of vertices.
    //!
    //! @pre
    //!  - <tt><var>vertexCount</var></tt> > <tt>0</tt>.
    //!
    //! @details  Sets the value specified by <tt><var>vertexCount</var></tt> as the vertex count.
    //!  At the same time, sets the size of the vertex buffer based on the specified vertex count.
    //---------------------------------------------------------------------------
    void SetVertexCount( int vertexCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Sets the number of indices.
    //!
    //! @param[in] indexCount  The number of indices.
    //!
    //! @pre
    //!  - <tt><var>indexCount</var></tt> > <tt>0</tt>.
    //!
    //! @details  Sets the value specified by <tt><var>indexCount</var></tt> as the index count.
    //!  At the same time, sets the size of the index buffer based on the specified index count.
    //---------------------------------------------------------------------------
    void SetIndexCount( int indexCount ) NN_NOEXCEPT;

private:
    void*                      m_pIndexBuffer;      //!<  Pointer to the start of the index buffer.
    void*                      m_pVertexBuffer;     //!<  Pointer to the start of the vertex buffer.
    PrimitiveShapeFormat       m_VertexFormat;      //!<  The format of the vertex buffer.
    nn::gfx::IndexFormat       m_IndexBufferFormat; //!<  The format of the index buffer.
    nn::gfx::PrimitiveTopology m_PrimitiveTopology; //!<  Primitive topologies.
    int                        m_VertexCount;       //!<  The number of vertices.
    int                        m_IndexCount;        //!<  The number of indices.
    size_t                     m_VertexBufferSize;  //!<  The size of the vertex buffer.
    size_t                     m_IndexBufferSize;   //!<  The size of the index buffer.
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information for the sphere.
//---------------------------------------------------------------------------
class SphereShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( SphereShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  Number of slices of the circle.
    //! @param[in] stackCount  Number of slices in the height direction.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineList</tt>.
    //!  - <tt><var>sliceCount</var></tt> >= <tt>3</tt>.
    //!  - <tt><var>stackCount</var></tt> >= <tt>2</tt>.
    //---------------------------------------------------------------------------
    SphereShape( int                        vertexFormat,
                 nn::gfx::PrimitiveTopology primitiveTopology,
                 int                        sliceCount,
                 int                        stackCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~SphereShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>SphereShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>SphereShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;

    int m_SliceCount; //!<  Number of slices of the circle.
    int m_StackCount; //!<  Number of slices in the height direction.
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information for the circle.
//---------------------------------------------------------------------------
class CircleShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( CircleShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  Number of slices of the circle.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineStrip</tt>.
    //!  - <tt><var>sliceCount</var></tt> >= <tt>3</tt>.
    //---------------------------------------------------------------------------
    CircleShape( int vertexFormat, nn::gfx::PrimitiveTopology primitiveTopology, int sliceCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~CircleShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>CircleShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>CircleShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:
    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;

    int m_SliceCount; //!<  Number of slices of the circle.
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information of the cube.
//---------------------------------------------------------------------------
class CubeShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( CubeShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineList</tt>.
    //---------------------------------------------------------------------------
    CubeShape( int vertexFormat, nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~CubeShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>CubeShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>CubeShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:
    //---------------------------------------------------------------------------
    //! @brief  The number of vertices for <tt>Cube</tt>.
    //---------------------------------------------------------------------------
    enum CubeVertex
    {
        CubeVertexCount_Wired = 8,
        CubeVertexCount_Solid = 24
    };

    //---------------------------------------------------------------------------
    //! @brief  The number of indices for <tt>Cube</tt>.
    //---------------------------------------------------------------------------
    enum CubeIndex
    {
        CubeIndexCount_Wired = 48,
        CubeIndexCount_Solid = 36
    };

    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information for the quadrilateral.
//---------------------------------------------------------------------------
class QuadShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( QuadShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineStrip</tt>.
    //---------------------------------------------------------------------------
    QuadShape( int vertexFormat, nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~QuadShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>QuadShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>QuadShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:
    //---------------------------------------------------------------------------
    //! @brief  The number of vertices for <tt>Quad</tt>.
    //---------------------------------------------------------------------------
    enum QuadVertex
    {
        QuadVertexCount = 4
    };

    //---------------------------------------------------------------------------
    //! @brief  The number of indices for <tt>Quad</tt>.
    //---------------------------------------------------------------------------
    enum QuadIndex
    {
        QuadIndexCount_Wired = 5,
        QuadIndexCountt_Solid = 6
    };

    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information for the hemisphere.
//---------------------------------------------------------------------------
class HemiSphereShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( HemiSphereShape );

public:

    //---------------------------------------------------------------------------
    //! @deprecated  Use <tt>HemiSphereShape( int, PrimitiveTopology, int, int )</tt>.
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The format of the vertex buffer.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  The number of slices on the xz-plane.
    //---------------------------------------------------------------------------
    NN_DEPRECATED HemiSphereShape( PrimitiveShapeFormat         vertexFormat,
                                   nn::gfx::PrimitiveTopology   primitiveTopology,
                                   int                          sliceCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  The number of slices on the xz-plane.
    //! @param[in] stackCount  Number of slices in the height direction.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineList</tt>.
    //!  - <tt><var>sliceCount</var></tt> >= <tt>3</tt>.
    //!  - <tt><var>stackCount</var></tt> >= <tt>1</tt>.
    //---------------------------------------------------------------------------
    HemiSphereShape( int                        vertexFormat,
                     nn::gfx::PrimitiveTopology primitiveTopology,
                     int                        sliceCount,
                     int                        stackCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~HemiSphereShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>HemiSphereShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>HemiSphereShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:
    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;

    int m_SliceCount; //!<  The number of slices on the xz-plane.
    int m_StackCount; //!<  Number of slices in the height direction.
};


//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information for the pipe.
//---------------------------------------------------------------------------
class PipeShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( PipeShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  Number of pipe slices.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineList</tt>.
    //!  - <tt><var>sliceCount</var></tt> >= <tt>3</tt>.
    //---------------------------------------------------------------------------
    PipeShape( int vertexFormat, nn::gfx::PrimitiveTopology primitiveTopology, int sliceCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~PipeShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>PipeShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>PipeShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:
    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;

    int m_SliceCount; //!<  Number of slices of the circle.
};

//---------------------------------------------------------------------------
//! @brief  Calculates the cylinder vertex information.
//---------------------------------------------------------------------------
class CylinderShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( CylinderShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  Number of slices of the cylinder.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineList</tt>.
    //!  - <tt><var>sliceCount</var></tt> >= <tt>3</tt>.
    //---------------------------------------------------------------------------
    CylinderShape( int                        vertexFormat,
                   nn::gfx::PrimitiveTopology primitiveTopology,
                   int                        sliceCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~CylinderShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>CylinderShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>CylinderShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:
    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;

    int m_SliceCount; //!<  Number of slices of the circle.
};

//---------------------------------------------------------------------------
//! @brief  Calculates the vertex information of the cone.
//---------------------------------------------------------------------------
class ConeShape : public PrimitiveShape
{
    NN_DISALLOW_COPY( ConeShape );

public:

    //---------------------------------------------------------------------------
    //! @brief  Constructor.
    //!
    //! @param[in] vertexFormat  The vertex buffer format, and the logical OR of <tt>#PrimitiveShapeFormat</tt>.
    //! @param[in] primitiveTopology  Primitive topology.
    //! @param[in] sliceCount  Number of slices of the circle.
    //!
    //! @pre
    //!  - ( <tt>#PrimitiveShapeFormat_Pos</tt> <= <tt><var>vertexFormat</var></tt> ) && ( <tt><var>vertexFormat</var></tt> <= <tt>#PrimitiveShapeFormat_Default</tt> )
    //!  - If displaying with surface modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_TriangleList</tt>.
    //!  - If displaying with wireframe modeling, <tt><var>primitiveTopology</var></tt> == <tt>nn::gfx::PrimitiveTopology_LineList</tt>.
    //!  - <tt><var>sliceCount</var></tt> >= <tt>3</tt>.
    //---------------------------------------------------------------------------
    ConeShape( int vertexFormat, nn::gfx::PrimitiveTopology primitiveTopology, int sliceCount ) NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Destructor.
    //---------------------------------------------------------------------------
    virtual ~ConeShape() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Determines whether this is a primitive topology that can be passed to the constructor of the <tt>ConeShape</tt> class.
    //!
    //! @param[in] primitiveTopology  Primitive topology.
    //!
    //! @return  Returns whether this is a primitive topology that can be passed to the constructor.
    //---------------------------------------------------------------------------
    static bool IsPrimitiveTopologySupported( nn::gfx::PrimitiveTopology primitiveTopology ) NN_NOEXCEPT;

protected:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of vertices.
    //!
    //! @return  Gets the number of vertices.
    //---------------------------------------------------------------------------
    int CalculateVertexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the number of indices.
    //!
    //! @return  The number of indices.
    //---------------------------------------------------------------------------
    int CalculateIndexCount() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  The implementation of <tt>Calculate()</tt> in the <tt>ConeShape</tt> class.
    //!
    //! @param[out] pVertexMemory  Pointer to the memory for writing vertex information.
    //! @param[in] vertexSize  Size of allocated memory (in bytes).
    //! @param[out] pIndexMemory  Pointer to the memory for writing index information.
    //! @param[in] indexSize  Size of allocated memory (in bytes).
    //!
    //! @pre
    //!  - <tt><var>pVertexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>pIndexMemory</var></tt> != <tt>NULL</tt>.
    //!  - <tt><var>vertexSize</var></tt> >= <tt>GetVertexBufferSize()</tt>.
    //!  - <tt><var>indexSize</var></tt> >= <tt>GetIndexBufferSize()</tt>.
    //---------------------------------------------------------------------------
    virtual void CalculateImpl( void* pVertexMemory, size_t vertexSize, void* pIndexMemory, size_t indexSize ) NN_NOEXCEPT;

private:

    //---------------------------------------------------------------------------
    //! @brief  Calculates the vertex buffer.
    //!
    //! @return  Returns the end address of the vertex buffer.
    //---------------------------------------------------------------------------
    void* CalculateVertexBuffer() NN_NOEXCEPT;

    //---------------------------------------------------------------------------
    //! @brief  Calculates the index buffer.
    //---------------------------------------------------------------------------
    template < typename T >
    void CalculateIndexBuffer() NN_NOEXCEPT;

    int m_SliceCount; //!<  Number of slices of the circle.
};

} // namespace util
} // namespace gfx
} // namespace nn
