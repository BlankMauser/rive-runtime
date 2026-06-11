#pragma once

#include "smash.hpp"
#include "nvn/nvn.hpp"

#include "vbuffer.hpp"
#include "ubuffer.hpp"
#include "shader.hpp"
#include "basic_bindables.hpp"

#include <vector>

/**
 * @brief Singleton to manage rendering 2D primitive shapes to the screen
 *
 */
class ShapeRenderer
{
private:
    ShapeRenderer(); // singleton class

    static ShapeRenderer &Instance();

    struct DrawInfo
    {
        nvn::DrawPrimitive primitive_type;
        int start_offset;
        int vertex_count;
        phx::Vector4f color;

        DrawInfo(nvn::DrawPrimitive primitive, int start, int count, phx::Vector4f col)
        {
            primitive_type = primitive;
            start_offset = start;
            vertex_count = count;
            color = col;
        }
    };

    enum ApiDrawCommandKind
    {
        Circle,
        Line
    };

    union ApiDrawCommandData
    {
        struct
        {
            phx::Vector3f center;
            float radius;
        } circle;

        struct
        {
            phx::Vector3f a;
            phx::Vector3f b;
        } line;
    };

    struct ApiDrawCommand
    {
        ApiDrawCommandKind kind;
        ApiDrawCommandData data;
        phx::Vector4f color;
        int num_frames;
    };

public:
    struct ScaleMatrix
    {
        phx::Vector3f x_axis;
        phx::Vector3f y_axis;
        phx::Vector3f z_axis;
    };

    static void DrawLineWithFrames(
        const phx::Vector3f &p1, const phx::Vector3f &p2, const phx::Vector4f &color,
        int num_frames);

    static void DrawSphereWithFrames(
        const phx::Vector3f &center, float radius,
        const phx::Vector4f &color, int num_frames);

    static void DrawLine(const phx::Vector3f &p1, const phx::Vector3f &p2, const phx::Vector4f &color);

    /**
     * @brief Draws a triangle with vertices at the specified points
     *
     * @param p1 The first point
     * @param p2 The second point
     * @param p3 The third point
     * @param color The color of the triangle
     */
    static void DrawTriangle(const phx::Vector2f &p1, const phx::Vector2f &p2, const phx::Vector2f &p3, const phx::Vector4f &color);

    /**
     * @brief Draws an equilateral triangle with the equidistant center at the specified point
     *
     * @param center The point of the equidistant center
     * @param side_length The side length
     * @param angle The angle to rotate the triangle by
     * @param color The color of the triangle
     */
    static void DrawTriangle(const phx::Vector2f &center, float side_length, float angle, const phx::Vector4f &color);

    /**
     * @brief Draws a rectangle with the specified coordinates and width/height
     *
     * @param top_left The point of the top left corner
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     * @param color The color of the rectangle
     */
    static void DrawRectangle(const phx::Vector2f &top_left, float width, float height, const phx::Vector4f &color);

    /**
     * @brief Draws a regular polygon with the equidistant center at the specified point
     *
     * @param center The point of the equidistant center
     * @param radius The radius of the circle circumscribed about the n-gon
     * @param sides The number of sides
     * @param angle The angle to rotate the n-gon by
     * @param color The color of the n-gon
     */
    static void DrawRegularPolygon(const phx::Vector2f &center, float radius, int sides, float angle, const phx::Vector4f &color);

    /**
     * @brief Draws a billboarded sphere from the game coordinates
     *
     * @param center The point of the center of the sphere
     * @param radius The radius of the sphere
     * @param color The color of the sphere
     */
    static void DrawSphere(const phx::Vector3f &center, const phx::Vector3f &scale, float radius, const phx::Vector4f &color);

    /**
     * @brief Draws a billboarded capsule from the game coordinates
     *
     * @param center1 One of the two center points of the capsule
     * @param center2 The other of the two center points of the capsule
     * @param radius The radius of the capsule
     * @param color The color of the capsule
     */
    static void DrawCapsule(const phx::Vector3f &center1, const phx::Vector3f &center2, float radius, const phx::Vector4f &color);
    static void DrawCapsule2(const phx::Vector3f &center1, const phx::Vector3f &center2, const phx::Vector3f &scale, float radius, const phx::Vector4f &color, std::optional<ScaleMatrix> scale_matrix);

    static void InstallHooks();

    /**
     * @brief Renders the current shape buffer
     *
     * @param cmdbuf The command buffer to render in
     */
    static void Render(nvn::CommandBuffer *cmdbuf);

private:
    VertexBuffer<phx::Vector2f> vertex_buffer[3];
    UniformBuffer<phx::Vector4f> color_uniform;
    ShaderProgram shaders;
    BlendState blend_state;
    ChannelMaskState channel_mask_state;
    ColorState color_state;
    MultisampleState multisample_state;
    PolygonState polygon_state;
    VertexAttribState vertex_attrib_state;
    VertexStreamState vertex_stream_state;

    std::vector<DrawInfo> draw_infos[3];
    std::vector<ApiDrawCommand> api_commands;
    size_t buffer_in_use;
};