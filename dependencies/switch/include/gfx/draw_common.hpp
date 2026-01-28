#pragma once
#include <functional>
#include <any>
#include "smash.hpp"

typedef std::function<phx::Vector2f(const phx::Vector3f&)> TransformFn;
typedef std::function<void(const phx::Vector2f&)> PushVertexFn;

void draw_circle(
    const phx::Vector3f& origin,
    float radius,
    bool is_line_segment,
    PushVertexFn p_fn,
    TransformFn t_fn,
    int sub_divisions
);

void draw_capsule(
    const phx::Vector3f& a,
    const phx::Vector3f& b,
    float radius,
    bool is_line_segment,
    PushVertexFn p_fn,
    TransformFn t_fn,
    int sub_divisions
);

void draw_aabb(
    const phx::Vector3f& origin,
    const phx::Vector3f& dimensions,
    bool is_line_segment,
    PushVertexFn p_fn,
    TransformFn t_fn
);