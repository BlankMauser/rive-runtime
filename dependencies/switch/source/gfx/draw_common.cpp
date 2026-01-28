#include "vector_math.hpp"
#include "gfx/draw_common.hpp"
#include "nvn/nvn.hpp"

/**
 * @brief Draws a circle as a hollow line
 * 
 * @param origin The origin of the circle
 * @param radius The radius of the circle
 * @param p_fn The function to push vertices
 * @param t_fn The function to transfrm vertices
 * @param sub_divisions The number of subdivisions around the circle
 * @return A pair of the drawing primitive and the number of elements
 */
std::pair<nvn::DrawPrimitive, size_t> draw_circle_line(
    const phx::Vector3f& origin,
    float radius,
    PushVertexFn p_fn,
    TransformFn t_fn,
    int sub_divisions
)
{
    phx::Vector3f translate = { 0.0 };

    // push every vertex around the circle
    for (int i = 0; i < sub_divisions; i++) {
        auto angle = i * M_PI / 64.0f;
        translate.y = sinf(angle);
        translate.x = cosf(angle);
        phx::Vector3f current_pos = origin + translate;
        phx::Vector2f screen = t_fn(current_pos);
        p_fn(screen);
    }

    return std::make_pair(nvn::DrawPrimitive::LINE_LOOP, static_cast<size_t>(sub_divisions));
}

/**
 * @brief Draws a circle as a solid entity.
 * 
 * @param origin The origin of the circle
 * @param radius The radius of the circle
 * @param p_fn The function to push vertices
 * @param t_fn The function to transfrm vertices
 * @param sub_divisions The number of subdivisions around the circle
 * @return A pair of the drawing primitive and the number of elements
 */
std::pair<nvn::DrawPrimitive, size_t> draw_circle(
    const phx::Vector3f& origin,
    float radius,
    PushVertexFn p_fn,
    TransformFn t_fn,
    int sub_divisions
)
{
    phx::Vector3f translate = { 0.0 };

    // convert the origin to screen coordinates and push it so that we can do triangle fan
    phx::Vector2f screen_origin = t_fn(origin);
    p_fn(screen_origin);

    // Push every vertex around the circle
    for (int i = 0; i <= sub_divisions; i++) {
        auto angle = i * M_PI / 64.0f;
        translate.y = sinf(angle);
        translate.x = cosf(angle);
        phx::Vector3f current_pos = origin + translate;
        phx::Vector2f screen = t_fn(current_pos);
        p_fn(screen);
    }

    return std::make_pair(nvn::DrawPrimitive::TRIANGLE_FAN, static_cast<size_t>(2 + sub_divisions));
}

void draw_capsule(
    const phx::Vector3f& a,
    const phx::Vector3f& b,
    float radius,
    bool is_line_segment,
    PushVertexFn p_fn,
    TransformFn t_fn,
    int sub_divisions
)
{
    debug_log("draw_capsule not implemented");
}

void draw_aabb(
    const phx::Vector3f& origin,
    const phx::Vector3f& dimensions,
    bool is_line_segment,
    PushVertexFn p_fn,
    TransformFn t_fn
)
{
    debug_log("draw_aabb not implemented");
}