#include "gfx/shape_renderer.hpp"
#include "gfx/res/simple_2d.h"
#include "vector_math.hpp"
#include "gfx/game_camera.hpp"

#define COORDS
#include "environment.hpp"

#include "skyline/inlinehook/And64InlineHook.hpp"

ShapeRenderer::ShapeRenderer()
    : vertex_buffer({VertexBuffer<phx::Vector2f>(g_Device, 0x4000), VertexBuffer<phx::Vector2f>(g_Device, 0x4000), VertexBuffer<phx::Vector2f>(g_Device, 0x4000)}),
      color_uniform(g_Device, 3),
      shaders(),
      blend_state(),
      channel_mask_state(),
      color_state(),
      multisample_state(),
      polygon_state(),
      vertex_attrib_state(1),
      vertex_stream_state(1),
      draw_infos({}),
      api_commands({}),
      buffer_in_use(0)
{
    color_uniform.SetStage(nvn::ShaderStage::FRAGMENT);
    color_uniform.SetId(0);
    color_uniform.SetIndex(0);

    shaders[ShaderStage::Vertex] = ShaderProgram::DataSet(simple_2d::get_vertex_code_bin(), simple_2d::get_vertex_control_bin());
    shaders[ShaderStage::Fragment] = ShaderProgram::DataSet(simple_2d::get_fragment_code_bin(), simple_2d::get_fragment_control_bin());
    SL_ASSERTM(shaders.Initialize(g_Device), "ShapeRenderer::ShapeRenderer failed: failed to initialize shader program");
    blend_state->SetBlendTarget(0)
        .SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD)
        .SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA, nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ZERO);

    color_state->SetBlendEnable(0, true)
        .SetLogicOp(nvn::LogicOp::COPY);

    polygon_state->SetCullFace(nvn::Face::NONE)
        .SetFrontFace(nvn::FrontFace::CCW)
        .SetPolygonMode(nvn::PolygonMode::FILL);

    vertex_attrib_state[0].SetFormat(nvn::Format::RG32F, 0).SetStreamIndex(0);

    vertex_stream_state[0].SetStride(sizeof(phx::Vector2f));
}

ShapeRenderer &ShapeRenderer::Instance()
{
    static ShapeRenderer instance;
    return instance;
}
void ShapeRenderer::DrawLineWithFrames(
    const phx::Vector3f &p1, const phx::Vector3f &p2, const phx::Vector4f &color,
    int num_frames)
{
    auto &instance = Instance();
    instance.api_commands.push_back(ApiDrawCommand{
        .kind = ApiDrawCommandKind::Line,
        .data = ApiDrawCommandData{
            .line = {.a = p1, .b = p2}},
        .color = color,
        .num_frames = num_frames,
    });
}

void ShapeRenderer::DrawSphereWithFrames(
    const phx::Vector3f &center, float radius,
    const phx::Vector4f &color, int num_frames)
{
    auto &instance = Instance();
    instance.api_commands.push_back(ApiDrawCommand{
        .kind = ApiDrawCommandKind::Circle,
        .data = ApiDrawCommandData{
            .circle = {.center = center, .radius = radius}},
        .color = color,
        .num_frames = num_frames,
    });
}

void ShapeRenderer::DrawLine(const phx::Vector3f &p1, const phx::Vector3f &p2, const phx::Vector4f &color)
{
    auto *camera = CameraManager::Instance();
    if (camera == nullptr)
    {
        return;
    }

    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];
    int start = vbuffer.Length();
    vbuffer.SafePush(as_screen_coords(p1));
    vbuffer.SafePush(as_screen_coords(p2));
    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::LINES, start, 2, color));
}

void ShapeRenderer::DrawTriangle(const phx::Vector2f &p1, const phx::Vector2f &p2, const phx::Vector2f &p3, const phx::Vector4f &color)
{
    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];
    int start = vbuffer.Length();
    vbuffer.SafePush(normalize_screen_coords(p1));
    vbuffer.SafePush(normalize_screen_coords(p2));
    vbuffer.SafePush(normalize_screen_coords(p3));
    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLES, start, 3, color));
}

void ShapeRenderer::DrawTriangle(const phx::Vector2f &origin, float side_length, float angle, const phx::Vector4f &color)
{
    float lx = origin.x - side_length / 2.0f;
    float rx = origin.x + side_length / 2.0f;
    float mx = origin.x;

    float by = origin.y - side_length / sqrtf(3.0f);
    float ty = by + sqrtf(3.0f) * side_length / 2.0f;

    DrawTriangle(rotate({lx, by}, origin, angle), rotate({rx, by}, origin, angle), rotate({mx, ty}, origin, angle), color);
}

void ShapeRenderer::DrawRectangle(const phx::Vector2f &top_left, float width, float height, const phx::Vector4f &color)
{
    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];

    int start = vbuffer.Length();
    vbuffer.SafePush(normalize_screen_coords(top_left));
    vbuffer.SafePush(normalize_screen_coords({top_left.x + width, top_left.y}));
    vbuffer.SafePush(normalize_screen_coords({top_left.x + width, top_left.y + height}));
    vbuffer.SafePush(normalize_screen_coords({top_left.x, top_left.y + height}));

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, 4, color));
}

void ShapeRenderer::DrawRegularPolygon(const phx::Vector2f &center, float radius, int sides, float angle, const phx::Vector4f &color)
{
    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];

    int start = vbuffer.Length();

    vbuffer.SafePush(normalize_screen_coords(center));

    float angle_step = 2.0f * M_PI / (float)sides;
    for (int i = 0; i <= sides; i++)
    {
        float x = radius * sinf(angle_step * (float)i + angle) + center.x;
        float y = radius * cosf(angle_step * (float)i + angle) + center.y;
        vbuffer.SafePush(normalize_screen_coords({x, y}));
    }

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, sides + 2, color));
}

constexpr phx::Vector4f mult_quat(const phx::Vector4f &left, const phx::Vector4f &right)
{
    return phx::Vector4f{
        left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
        left.w * right.y - left.x * right.z + left.y * right.w + left.z * right.x,
        left.w * right.z + left.x * right.y - left.y * right.x + left.z * right.w,
        left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z};
}

constexpr phx::Vector4f find_rotation(const phx::Vector3f &start, const phx::Vector3f &destination)
{
    float d = start * destination;
    auto axis = cross(start, destination);
    float qw = magnitude(start) * magnitude(destination) + d;
    if (qw < 0.0001f)
    {
        return as_unit(phx::Vector4f{
            -start.x, start.y, start.z, 0.0});
    }
    else
    {
        return as_unit(phx::Vector4f{
            axis.x, axis.y, axis.z, qw});
    }
}

constexpr phx::Vector3f rotate_vec(const phx::Vector3f &vector, const phx::Vector4f &quat)
{
    phx::Vector4f prime = {
        -quat.x,
        -quat.y,
        -quat.z,
        quat.w};

    phx::Vector4f vec = {
        vector.x,
        vector.y,
        vector.z,
        0.0f};

    auto result = mult_quat(mult_quat(quat, vec), prime);
    return phx::Vector3f{
        result.x,
        result.y,
        result.z};
}

constexpr phx::Vector3f rotate_by_angles(const phx::Vector3f &axis, float x, float y, float z)
{
    float cx = cosf(x * 0.5f);
    float cy = cosf(y * 0.5f);
    float cz = cosf(z * 0.5f);
    float sx = sinf(x * 0.5f);
    float sy = sinf(y * 0.5f);
    float sz = sinf(z * 0.5f);

    phx::Vector4f rotation = {
        sx * cy * cz - cx * sy * sz, // x
        cx * sy * cz + sx * cy * sz, // y
        cx * cy * sz - sx * sy * cz, // z
        cx * cy * cz + sx * sy * sz  // w
    };

    return rotate_vec(axis, rotation);
}

constexpr phx::Vector3f matrix_multiply(phx::Vector3f *matrix, const phx::Vector3f &vec)
{
    return phx::Vector3f{
        vec.x * matrix[0].x + vec.y * matrix[0].y + vec.z * matrix[0].z,
        vec.x * matrix[1].x + vec.y * matrix[1].y + vec.z * matrix[1].z,
        vec.x * matrix[2].x + vec.y * matrix[2].y + vec.z * matrix[2].z,
    };
}

constexpr float det2(const phx::Vector2f *matrix)
{
    return matrix[0].x * matrix[1].y - matrix[0].y * matrix[1].x;
}

constexpr float det3(const phx::Vector3f *matrix)
{
    phx::Vector2f left[] = {
        phx::Vector2f{matrix[1].x, matrix[1].y},
        phx::Vector2f{matrix[2].x, matrix[2].y}};

    phx::Vector2f middle[] = {
        phx::Vector2f{matrix[1].x, matrix[1].z},
        phx::Vector2f{matrix[2].x, matrix[2].z}};

    phx::Vector2f right[] = {
        phx::Vector2f{matrix[1].y, matrix[1].z},
        phx::Vector2f{matrix[2].y, matrix[2].z}};

    return matrix[0].x * det2(right) - matrix[0].y * det2(middle) + matrix[0].z * det2(left);
}

constexpr void invert_matrix(const phx::Vector3f *matrix, phx::Vector3f *out)
{
    auto det = det3(matrix);

    phx::Vector2f top_left[]{
        phx::Vector2f{matrix[1].y, matrix[1].z},
        phx::Vector2f{matrix[2].y, matrix[2].z}};

    phx::Vector2f top_mid[]{
        phx::Vector2f{matrix[1].x, matrix[1].z},
        phx::Vector2f{matrix[2].x, matrix[2].z}};

    phx::Vector2f top_right[]{
        phx::Vector2f{matrix[1].x, matrix[1].y},
        phx::Vector2f{matrix[2].x, matrix[2].y}};

    phx::Vector2f mid_left[]{
        phx::Vector2f{matrix[0].y, matrix[0].z},
        phx::Vector2f{matrix[2].y, matrix[2].z}};

    phx::Vector2f mid_mid[]{
        phx::Vector2f{matrix[0].x, matrix[0].z},
        phx::Vector2f{matrix[2].x, matrix[2].z}};

    phx::Vector2f mid_right[]{
        phx::Vector2f{matrix[0].x, matrix[0].y},
        phx::Vector2f{matrix[2].x, matrix[2].y}};

    phx::Vector2f bot_left[]{
        phx::Vector2f{matrix[0].y, matrix[0].z},
        phx::Vector2f{matrix[1].y, matrix[1].z}};

    phx::Vector2f bot_mid[]{
        phx::Vector2f{matrix[0].x, matrix[0].z},
        phx::Vector2f{matrix[1].x, matrix[1].z}};

    phx::Vector2f bot_right[]{
        phx::Vector2f{matrix[0].x, matrix[0].y},
        phx::Vector2f{matrix[1].x, matrix[1].y}};

    out[0] = phx::Vector3f{det2(top_left), -det2(mid_left), det2(bot_left)} * (1.0f / det);
    out[1] = phx::Vector3f{-det2(top_mid), det2(mid_mid), -det2(bot_mid)} * (1.0f / det);
    out[2] = phx::Vector3f{det2(top_right), -det2(mid_right), det2(bot_right)} * (1.0f / det);
}

void ShapeRenderer::DrawSphere(const phx::Vector3f &center, const phx::Vector3f &scale, float radius, const phx::Vector4f &color)
{
    auto *camera = CameraManager::Instance();
    if (camera == nullptr)
    {
        return;
    }

    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];

    int start = vbuffer.Length();

    vbuffer.SafePush(as_screen_coords(center));

    float angle_step = 2.0f * M_PI / 128.0f;
    for (int i = 0; i <= 128; i++)
    {
        float x = radius * sinf(angle_step * (float)i);
        float y = radius * cosf(angle_step * (float)i);
        auto point = phx::Vector3f{
            x,
            y,
            0.0f};
        auto rotated = rotate_by_angles(point, camera->angle_x, camera->angle_y, camera->angle_z);
        vbuffer.SafePush(as_screen_coords(center + phx::Vector3f{
                                                       rotated.x * scale.x,
                                                       rotated.y * scale.y,
                                                       rotated.z * scale.z}));
    }

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, 128 + 2, color));
}

void ShapeRenderer::DrawCapsule2(
    const phx::Vector3f &center1,
    const phx::Vector3f &center2,
    const phx::Vector3f &scale,
    float radius,
    const phx::Vector4f &color,
    std::optional<ScaleMatrix> scale_matrix)
{
    auto *camera = CameraManager::Instance();
    if (camera == nullptr)
    {
        return;
    }

    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];

    int start = vbuffer.Length();

    phx::Vector3f to_joint[] = {
        phx::Vector3f{1.0f, 0.0f, 0.0f},
        phx::Vector3f{0.0f, 1.0f, 0.0f},
        phx::Vector3f{0.0f, 0.0f, 1.0f}};

    phx::Vector3f to_world[] = {
        phx::Vector3f{1.0f, 0.0f, 0.0f},
        phx::Vector3f{0.0f, 1.0f, 0.0f},
        phx::Vector3f{0.0f, 0.0f, 1.0f}};

    if (scale_matrix.has_value())
    {
        to_world[0] = phx::Vector3f{scale_matrix.value().x_axis.x, scale_matrix.value().y_axis.x, scale_matrix.value().z_axis.x};
        to_world[1] = phx::Vector3f{scale_matrix.value().x_axis.y, scale_matrix.value().y_axis.y, scale_matrix.value().z_axis.y};
        to_world[2] = phx::Vector3f{scale_matrix.value().x_axis.z, scale_matrix.value().y_axis.z, scale_matrix.value().z_axis.z};
        invert_matrix(to_world, to_joint);
    }

    vbuffer.SafePush(as_screen_coords(center1));
    float angle_step = 2.0f * M_PI / 64.0f;
    for (int i = 0; i <= 64; i++)
    {
        float x = radius * sinf(angle_step * (float)i);
        float y = radius * cosf(angle_step * (float)i);
        auto point = phx::Vector3f{
            x,
            y,
            0.0f};
        auto rotated = rotate_by_angles(point, camera->angle_x, camera->angle_y, camera->angle_z);
        auto transformed = matrix_multiply(to_joint, rotated);
        rotated = matrix_multiply(to_world, {transformed.x * scale.x,
                                             transformed.y * scale.y,
                                             transformed.z * scale.z});
        vbuffer.SafePush(as_screen_coords(center1 + rotated));
    }

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, 64 + 2, color));

    start = vbuffer.Length();

    vbuffer.SafePush(as_screen_coords(center2));

    for (int i = 0; i <= 64; i++)
    {
        float x = radius * sinf(angle_step * (float)i);
        float y = radius * cosf(angle_step * (float)i);
        auto point = phx::Vector3f{
            x,
            y,
            0.0f};
        auto rotated = rotate_by_angles(point, camera->angle_x, camera->angle_y, camera->angle_z);
        auto transformed = matrix_multiply(to_joint, rotated);
        rotated = matrix_multiply(to_world, {transformed.x * scale.x,
                                             transformed.y * scale.y,
                                             transformed.z * scale.z});
        vbuffer.SafePush(as_screen_coords(center2 + rotated));
    }

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, 64 + 2, color));

    start = vbuffer.Length();

    for (int i = 0; i <= 64; i++)
    {
        float x = radius * sinf(angle_step * (float)i);
        float y = radius * cosf(angle_step * (float)i);
        auto point = phx::Vector3f{
            x,
            y,
            0.0f};
        auto rotated = rotate_by_angles(point, camera->angle_x, camera->angle_y, camera->angle_z);
        auto transformed = matrix_multiply(to_joint, rotated);
        rotated = matrix_multiply(to_world, {transformed.x * scale.x,
                                             transformed.y * scale.y,
                                             transformed.z * scale.z});
        vbuffer.SafePush(as_screen_coords(center1 + rotated));
        vbuffer.SafePush(as_screen_coords(center2 + rotated));
    }
    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_STRIP, start, 130, color));
}

void ShapeRenderer::DrawCapsule(const phx::Vector3f &center1, const phx::Vector3f &center2, float radius, const phx::Vector4f &color)
{
    auto *camera = CameraManager::Instance();
    if (camera == nullptr)
    {
        return;
    }

    auto &instance = Instance();
    auto &vbuffer = instance.vertex_buffer[instance.buffer_in_use];

    auto start = vbuffer.Length();

    auto length = magnitude(center1 - center2);
    auto rotation = find_rotation({length, 0.0f, 0.0f}, center2 - center1);

    auto c1 = as_pixels(center1);
    auto c2 = as_pixels(center2);
    auto dir = c1 - c2;
    float l = magnitude(dir);
    float angle = atan2(dir.y, dir.x);
    if (dir.x == 0.0f)
    {
        angle = M_PI / 2;
    }

    float angle_step = 2 * M_PI / 64.0f;
    float avg_radius1 = 0.0f;
    float avg_radius2 = 0.0f;
    for (int i = 0; i <= 64; i++)
    {
        float x = radius * sinf(angle_step * (float)i);
        float y = radius * cosf(angle_step * (float)i);
        auto point = rotate_by_angles({x, y, 0.0f}, camera->angle_x, camera->angle_y, camera->angle_z);

        avg_radius1 += magnitude(as_pixels(center1 + rotate_vec(point, rotation)) - c1);
        avg_radius2 += magnitude(as_pixels(center1 + rotate_vec(point + phx::Vector3f{length, 0.0f, 0.0f}, rotation)) - c2);
    }
    avg_radius1 /= 65.0f;
    avg_radius2 /= 65.0f;

    debug_log("%.2f %.2f", avg_radius1, avg_radius2);

    float tangent_len = pow(pow(length, 2.0) - pow(avg_radius2 - avg_radius1, 2.0), 0.5);
    float tangent_angle = M_PI / 2 - asin((avg_radius2 - avg_radius1) / l);

    if (avg_radius1 == avg_radius2)
        tangent_angle = M_PI / 2;

    float b = angle + tangent_angle;
    float b2 = angle - tangent_angle;

    phx::Vector2f circle1 = {
        cosf(b),
        sinf(b)};

    phx::Vector2f circle2 = {
        cosf(b2),
        sinf(b2)};

    vbuffer.SafePush(as_screen_coords(c1 + circle2 * avg_radius1));
    vbuffer.SafePush(as_screen_coords(c2 + circle2 * avg_radius2));
    vbuffer.SafePush(as_screen_coords(c1));
    vbuffer.SafePush(as_screen_coords(c2));
    vbuffer.SafePush(as_screen_coords(c1 + circle1 * avg_radius1));
    vbuffer.SafePush(as_screen_coords(c2 + circle1 * avg_radius2));

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo{nvn::DrawPrimitive::TRIANGLE_STRIP, start, 6, color});

    start = vbuffer.Length();

    angle = (avg_radius1 == avg_radius2) ? M_PI : acosf((circle1 * circle2) / (magnitude(circle1) * magnitude(circle2)));
    float x_angle = acosf(circle1.x / magnitude(circle1));
    if (circle1.y <= 0.0)
        x_angle = -x_angle;

    float del = (avg_radius2 > avg_radius1) ? (2 * M_PI - angle) / 64.0f : angle / 64.0f;

    vbuffer.SafePush(as_screen_coords(c2));
    for (int i = 0; i <= 64; i++)
    {
        vbuffer.SafePush(as_screen_coords(c2 + phx::Vector2f{avg_radius2 * cosf((float)i * del + x_angle), avg_radius2 * sinf((float)i * del + x_angle)}));
    }

    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, 66, color));
    start = vbuffer.Length();
    del = (avg_radius2 > avg_radius1) ? angle / 64.0f : (2 * M_PI - angle) / 64.0f;

    vbuffer.SafePush(as_screen_coords(c1));
    for (int i = 0; i <= 64; i++)
    {
        vbuffer.SafePush(as_screen_coords(c1 + phx::Vector2f{avg_radius1 * cosf((float)-i * del + x_angle), avg_radius1 * sinf((float)-i * del + x_angle)}));
    }
    instance.draw_infos[instance.buffer_in_use].push_back(DrawInfo(nvn::DrawPrimitive::TRIANGLE_FAN, start, 66, color));
}

void ShapeRenderer::Render(nvn::CommandBuffer *cmdbuf)
{
    auto &instance = Instance();

    size_t i = 0;
    while (true)
    {
        if (i >= instance.api_commands.size())
        {
            break;
        }

        if (instance.api_commands[i].num_frames == 0)
        {
            instance.api_commands.erase(instance.api_commands.begin() + i);
            continue;
        }

        instance.api_commands[i].num_frames--;
        auto &command = instance.api_commands[i];
        switch (command.kind)
        {
        case ApiDrawCommandKind::Line:
            DrawLine(command.data.line.a, command.data.line.b, command.color);
            break;

        case ApiDrawCommandKind::Circle:
            DrawSphere(command.data.circle.center, {1.0, 1.0, 1.0}, command.data.circle.radius, command.color);
            break;
        }

        i++;
    }

    auto draw_buffer = (instance.buffer_in_use + 2) % 3;
    // bind the more complex structures
    instance.shaders.Bind(cmdbuf);
    instance.vertex_buffer[draw_buffer].Bind(cmdbuf);
    instance.color_uniform.Bind(cmdbuf);

    // bind the basic structures
    instance.blend_state.Bind(cmdbuf);
    instance.channel_mask_state.Bind(cmdbuf);
    instance.color_state.Bind(cmdbuf);
    instance.multisample_state.Bind(cmdbuf);
    instance.polygon_state.Bind(cmdbuf);
    instance.vertex_attrib_state.Bind(cmdbuf);
    instance.vertex_stream_state.Bind(cmdbuf);

    // go through each of our processed shapes and update the color uniform, then continue
    for (auto &info : instance.draw_infos[draw_buffer])
    {
        instance.color_uniform.Update(cmdbuf, &info.color);
        cmdbuf->DrawArrays(info.primitive_type, info.start_offset, info.vertex_count);
    }

    instance.buffer_in_use++;
    instance.buffer_in_use %= 3;
    instance.vertex_buffer[draw_buffer].Clear();
    instance.draw_infos[draw_buffer].clear();
}

static phx::Vector4f DEBUG_DRAW_COLOR = phx::Vector4f{1.0, 1.0, 1.0, 1.0};

void draw_circle_hook(const phx::Vector2f &center, float radius, int num_frames)
{
    ShapeRenderer::DrawSphereWithFrames(extend(center, 0.0), radius, DEBUG_DRAW_COLOR, num_frames);
}

void set_draw_color(float r, float g, float b, float a)
{
    DEBUG_DRAW_COLOR = {r, g, b, a};
}

void draw_line_hook(const phx::Vector2f &a, const phx::Vector2f &b, int num_frames)
{
    ShapeRenderer::DrawLineWithFrames(extend(a, 0.0), extend(b, 0.0), DEBUG_DRAW_COLOR, num_frames);
}

void ShapeRenderer::InstallHooks()
{
    A64HookFunction(
        reinterpret_cast<void *>(app::sv_debug_draw::draw_circle),
        reinterpret_cast<void *>(draw_circle_hook),
        nullptr);

    A64HookFunction(
        reinterpret_cast<void *>(app::sv_debug_draw::draw_line),
        reinterpret_cast<void *>(draw_line_hook),
        nullptr);

    A64HookFunction(
        reinterpret_cast<void *>(app::sv_debug_draw::set_draw_color),
        reinterpret_cast<void *>(set_draw_color),
        nullptr);
}