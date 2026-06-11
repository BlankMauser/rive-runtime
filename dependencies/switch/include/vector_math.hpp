#pragma once
#include <cmath>

#ifndef M_PI
#define MAXFLOAT	3.40282347e+38F

#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		_M_LN2
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#endif

#include "smash.hpp"

using namespace phx;

constexpr float operator*(const Vector2f& a, const Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

constexpr float operator*(const Vector3f& a, const Vector3f& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

constexpr float operator*(const Vector4f& a, const Vector4f& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

constexpr Vector2f operator*(const Vector2f& a, float s) {
    return Vector2f{ a.x * s, a.y * s };
}

constexpr Vector3f operator*(const Vector3f& a, float s) {
    return Vector3f{ a.x * s, a.y * s, a.z * s };
}

constexpr Vector4f operator*(const Vector4f& a, float s) {
    return Vector4f{ a.x * s, a.y * s, a.z * s, a.w * s };
}

constexpr Vector2f operator-(const Vector2f& a) {
    return Vector2f{-a.x, -a.y};
}

constexpr Vector3f operator-(const Vector3f& a) {
    return Vector3f{-a.x, -a.y, -a.z};
}

constexpr Vector4f operator-(const Vector4f& a) {
    return Vector4f{-a.x, -a.y, -a.z, -a.w};
}

constexpr Vector2f operator+(const Vector2f& a, const Vector2f& b) {
    return Vector2f{a.x + b.x, a.y + b.y};
}

constexpr Vector3f operator+(const Vector3f& a, const Vector3f& b) {
    return Vector3f{a.x + b.x, a.y + b.y, a.z + b.z};
}

constexpr Vector4f operator+(const Vector4f& a, const Vector4f& b) {
    return Vector4f{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

constexpr Vector2f operator-(const Vector2f& a, const Vector2f& b) {
    return a + -b;
}

constexpr Vector3f operator-(const Vector3f& a, const Vector3f& b) {
    return a + -b;
}

constexpr Vector4f operator-(const Vector4f& a, const Vector4f& b) {
    return a + -b;
}

constexpr bool operator==(const Vector2f& a, const Vector2f& b) {
    return a.x == b.x && a.y == b.y;
}

constexpr bool operator==(const Vector3f& a, const Vector3f& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

constexpr bool operator==(const Vector4f& a, const Vector4f& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

constexpr float magnitude(const Vector2f& a) {
    return pow(pow(a.x, 2.0) + pow(a.y, 2.0), 0.5);
}

constexpr float magnitude(const Vector3f& a) {
    return pow(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0), 0.5);
}

constexpr float magnitude(const Vector4f& a) {
    return pow(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0) + pow(a.w, 2.0), 0.5);
}

inline Vector2f as_pixels(const Vector3f& a) {
    float32x2_t pixels = app::sv_camera_manager::world_to_screen(a, false);
    return Vector2f{ vget_lane_f32(pixels, 0), vget_lane_f32(pixels, 1) };
}

inline Vector2f as_screen_coords(const Vector2f& pix) {
    Vector2f ret = Vector2f{ pix.x / (1920.0 / 2.0) - 1.0, pix.y / (-1080.0 / 2.0) + 1.0 };
    return ret;
}

inline Vector2f as_screen_coords(const Vector3f& a) {
    Vector2f pix = as_pixels(a);
    // luckily smash doesn't resize this, it's always constant I hope
    pix.x = pix.x / (1920.0 / 2.0) - 1.0;
    pix.y = pix.y / (-1080.0 / 2.0) + 1.0;
    return pix;
}

constexpr Vector2f as_unit(const Vector2f& a) {
    float m = magnitude(a);
    return Vector2f{ a.x / m, a.y / m };
}

constexpr Vector3f as_unit(const Vector3f& a) {
    float m = magnitude(a);
    return Vector3f{ a.x / m, a.y / m, a.z / m };
}

constexpr Vector4f as_unit(const Vector4f& a) {
    float m = magnitude(a);
    return Vector4f{ a.x / m, a.y / m, a.z / m, a.w / m };
}

constexpr Vector3f extend(const Vector2f& a, float val) {
    return Vector3f{a.x, a.y, val};
}

constexpr Vector4f extend4(const Vector2f& a, float val) {
    return Vector4f{a.x, a.y, val, val};
}

constexpr Vector4f extend(const Vector3f& a, float val) {
    return Vector4f{a.x, a.y, a.z, val};
}

constexpr Vector2f truncate(const Vector3f& a) {
    return Vector2f{a.x, a.y};
}

constexpr Vector2f truncate(const Vector4f& a) {
    return Vector2f{a.x, a.y};
}

constexpr Vector3f truncate4(const Vector4f& a) {
    return Vector3f{a.x, a.y, a.z};
}

constexpr Vector2f rotate(const Vector2f& p, const Vector2f& o, float angle) {
    float s = sin(angle);
    float c = cos(angle);

    Vector2f ret = p;
    ret.x -= o.x;
    ret.y -= o.y;
    float x_n = ret.x * c - ret.y * s;
    float y_n = ret.x * s + ret.y * c;
    ret.x = x_n + o.x;
    ret.y = y_n + o.y;
    return ret;
}

constexpr Vector3f rotate(const Vector3f& u, const Vector3f& v, float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    auto v_unit = as_unit(v);
    float nx = u.x * (c + powf(v_unit.x, 2.0f) * (1.0f - c)) + u.y * (v_unit.x * v_unit.y * (1.0f - c) - v_unit.z * s) + u.z * (v_unit.x * v_unit.z * (1.0f - c) + v_unit.y * s);
    float ny = u.x * (v_unit.y * v_unit.x * (1.0f - c) + v_unit.z * s) + u.y * (c + powf(v_unit.y, 2.0f) * (1.0f - c)) + u.z * (v_unit.y * v_unit.z * (1.0f - c) - v_unit.x * s);
    float nz = u.x * (v_unit.z * v_unit.x * (1.0f - c) - v_unit.y * s) + u.y * (v_unit.z * v_unit.y * (1.0f - c) + v_unit.x * s) + u.z * (c + powf(v_unit.z, 2.0f) * (1.0f - c));
    return { nx, ny, nz };
}

constexpr Vector3f cross(const Vector3f& u, const Vector3f& v) {
    float nx = u.y * v.z - u.z * v.y;
    float ny = -(u.x * v.z - u.z * v.x);
    float nz = u.x * v.y - u.y * v.x;
    return { nx, ny, nz };
}

inline Vector2f ortho_cw(const Vector2f& a) {
    float m = magnitude(a);
    return Vector2f{ a.y / m, -a.x / m };
}

inline Vector2f ortho_ccw(const Vector2f& a) {
    float m = magnitude(a);
    return Vector2f{ -a.y / m, a.x / m };
}