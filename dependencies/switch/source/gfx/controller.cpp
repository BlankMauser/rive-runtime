#include "gfx/controller.hpp"
#include "json.hpp"

#define COORDS
#include "environment.hpp"
#ifndef __INTELLISENSE__
#include "gfx/res/gcn_images.h"
#include "gfx/res/pro_images.h"
#endif
#include "gfx/res/simple_texture.h"
#include "vector_math.hpp"

#include "utils.hpp"
#include "skyline/inlinehook/And64InlineHook.hpp"

#include <map>

using json = nlohmann::json;

static uint64_t s_PrevButtons = 0;
#define HAS_KEY(state, key) ((state.Buttons & key) != 0)
#define HAS_KEY_PRESS(state, key) (((state.Buttons & key) != 0) && ((s_PrevButtons & key) == 0))

void smash_controller_update_hook(InlineCtx* ctx) {
    auto* controller = InputManager::GetSmashController(static_cast<size_t>(((uint32_t*)(ctx->registers[19].x))[2]));
    controller->buttons = *(SmashControllerButtons*)&ctx->registers[21].x;
}

void smash_controller_update_non_player_hook(InlineCtx* ctx) {
    void* controller_data = ((void**)(ctx->registers[19].x))[1];
    auto* controller = InputManager::GetSmashController(reinterpret_cast<uint32_t*>(controller_data)[2]);
    *(uint32_t*)&controller->buttons = reinterpret_cast<uint32_t*>(controller_data)[3];
    controller->buttons.lstick_x = (signed char)(*reinterpret_cast<float*>(controller_data + 0x40) * (float)INT8_MAX);
    controller->buttons.lstick_y = (signed char)(*reinterpret_cast<float*>(controller_data + 0x44) * (float)INT8_MAX);
}

struct ButtonInfo {
    float x;
    float y;
    float scale;
    bool flip;

    ButtonInfo(json& object)
        : x(-1.0f),
            y(-1.0f),
            scale(1.0f),
            flip(false)
    {
        SL_ASSERTM(object.is_structured(), "json object is not structure");

        SL_ASSERTM(object.contains("x"), "missing x position");
        SL_ASSERTM(object.contains("y"), "missing y position");

        x = object["x"].get<float>();
        y = object["y"].get<float>();

        if (object.contains("scale"))
            scale = object["scale"].get<float>();

        if (object.contains("flip"))
            flip = object["flip"].get<bool>();
    }
};

struct ControllerLayout {
    float source_width;
    float source_height;
    float additional_width;
    std::unordered_map<std::string, ButtonInfo> buttons;

    ControllerLayout(json& object)
        : source_width(0.0f),
            source_height(0.0f),
            additional_width(0.0f),
            buttons()
    {
        SL_ASSERTM(object.contains("source_width"), "missing source width");
        source_width = object["source_width"].get<float>();

        SL_ASSERTM(object.contains("source_height"), "missing source height");
        source_height = object["source_height"].get<float>();

        if (object.contains("additional_width")) {
            additional_width = object["additional_width"].get<float>();
        }

        SL_ASSERTM(object.contains("buttons"), "missing buttons array");

        std::map<std::string, json> button_locs = object["buttons"].get<std::map<std::string, json>>();

        for (auto& entry : button_locs) {
            buttons.insert({ entry.first, ButtonInfo(entry.second) });
        }
    }
};

struct GcJson {
private:
    GcJson()
        : width(-1),
            height(-1),
            tile_size(-1),
            buttons(),
            layout(nullptr)
    {
        std::string json_data;
        {
            auto data = gcn_images::get_gcn_json();
            json_data = std::string(
                reinterpret_cast<const char*>(data.data()),
                data.size()
            );
        }

        json gc_json = json::parse(std::move(json_data));

        SL_ASSERTM(gc_json.contains("width"), "missing image width");

        width = gc_json["width"].get<int>();

        SL_ASSERTM(gc_json.contains("height"), "missing image height");
        
        height = gc_json["height"].get<int>();

        SL_ASSERTM(gc_json.contains("tile_size"), "missing tile size");

        tile_size = gc_json["tile_size"].get<int>();

        SL_ASSERTM(gc_json.contains("buttons"), "missing buttons array");

        std::map<std::string, std::vector<int>> buttons_array = gc_json["buttons"].get<std::map<std::string, std::vector<int>>>();

        for (auto& entry : buttons_array) {
            SL_ASSERTM(entry.second.size() == 2, "buttons entry is too long");

            buttons.insert({ entry.first, { entry.second[0], entry.second[1] }});
        }

        SL_ASSERTM(gc_json.contains("layout"), "missing display layout");

        layout = new ControllerLayout(gc_json["layout"]);
    }

public:
    int width;
    int height;
    int tile_size;

    std::unordered_map<std::string, std::pair<int, int>> buttons;
    ControllerLayout* layout;

    static const GcJson& Get() {
        static GcJson instance;
        return instance;
    }
};

struct ProJson {
private:
    ProJson()
        : width(-1),
            height(-1),
            tile_size(-1),
            buttons(),
            layout(nullptr)
    {
        std::string json_data;
        {
            auto data = pro_images::get_pro_json();
            json_data = std::string(
                reinterpret_cast<const char*>(data.data()),
                data.size()
            );
        }

        json gc_json = json::parse(std::move(json_data));

        SL_ASSERTM(gc_json.contains("width"), "missing image width");

        width = gc_json["width"].get<int>();

        SL_ASSERTM(gc_json.contains("height"), "missing image height");
        
        height = gc_json["height"].get<int>();

        SL_ASSERTM(gc_json.contains("tile_size"), "missing tile size");

        tile_size = gc_json["tile_size"].get<int>();

        SL_ASSERTM(gc_json.contains("buttons"), "missing buttons array");

        std::map<std::string, std::vector<int>> buttons_array = gc_json["buttons"].get<std::map<std::string, std::vector<int>>>();

        for (auto& entry : buttons_array) {
            SL_ASSERTM(entry.second.size() == 2, "buttons entry is too long");

            buttons.insert({ entry.first, { entry.second[0], entry.second[1] }});
        }

        SL_ASSERTM(gc_json.contains("layout"), "missing display layout");

        layout = new ControllerLayout(gc_json["layout"]);
    }

public:
    int width;
    int height;
    int tile_size;

    std::unordered_map<std::string, std::pair<int, int>> buttons;
    ControllerLayout* layout;

    static const ProJson& Get() {
        static ProJson instance;
        return instance;
    }
};

struct ControllerImages {
private:
    ControllerImages()
        : manager(new TextureManager(2, 2)),
            gamecube(nullptr),
            pro(nullptr)
    {
        
    }

    std::shared_ptr<TextureManager> manager;
    std::shared_ptr<Image> gamecube;
    std::shared_ptr<Image> pro;

    static ControllerImages& Instance() {
        static ControllerImages instance;
        return instance;
    }

public:
    static std::shared_ptr<Image> GetOrMakeGamecube(int width, int height) {
        auto& instance = Instance();
        if (instance.gamecube)
            return instance.gamecube;

        auto data = gcn_images::get_gcn_rgba();
        Image::RGBA_Data rgba_data = Image::RGBA_Data {
            .width = width,
            .height = height,
            .data = reinterpret_cast<const uint8_t*>(data.data())
        };

        instance.gamecube = std::make_shared<Image>("gamecube", instance.manager, rgba_data);
        return instance.gamecube;
    }

    static std::shared_ptr<Image> GetOrMakePro(int width, int height) {
        auto& instance = Instance();
        if (instance.pro)
            return instance.pro;

        auto data = pro_images::get_pro_rgba();
        Image::RGBA_Data rgba_data = Image::RGBA_Data {
            .width = width,
            .height = height,
            .data = reinterpret_cast<const uint8_t*>(data.data())
        };

        instance.pro = std::make_shared<Image>("pro", instance.manager, rgba_data);
        return instance.pro;
    }

};

Controller::Controller(uint32_t npad_id)
    : vertex_buffer { VertexBuffer<phx::Vector2f>(g_Device, 0x100), VertexBuffer<phx::Vector2f>(g_Device, 0x100), VertexBuffer<phx::Vector2f>(g_Device, 0x100) },
        tcoord_buffer { VertexBuffer<phx::Vector2f>(g_Device, 0x100), VertexBuffer<phx::Vector2f>(g_Device, 0x100), VertexBuffer<phx::Vector2f>(g_Device, 0x100) },
        mcoord_buffer { VertexBuffer<phx::Vector2f>(g_Device, 0x100), VertexBuffer<phx::Vector2f>(g_Device, 0x100), VertexBuffer<phx::Vector2f>(g_Device, 0x100) },
        index_buffer { IndexBuffer<unsigned short>(g_Device, 0x400), IndexBuffer<unsigned short>(g_Device, 0x400), IndexBuffer<unsigned short>(g_Device, 0x400) },
        draw_mode(g_Device, 1),
        image(nullptr),
        shaders(),
        blend_state(),
        channel_mask_state(),
        color_state(),
        multisample_state(),
        polygon_state(),
        vertex_attrib_state(3),
        vertex_stream_state(3),
        npad_id(npad_id),
        width(-1.0f),
        height(-1.0f)
{
    for (size_t i = 0; i < 3; i++) {
        vertex_buffer[i].SetId(simple_texture::VERTEX_POSITION_BINDING);
        tcoord_buffer[i].SetId(simple_texture::VERTEX_TEXTURE_BINDING);
        mcoord_buffer[i].SetId(simple_texture::VERTEX_MASK_BINDING);
    }

    draw_mode.SetStage(nvn::ShaderStage::FRAGMENT);
    draw_mode.SetId(simple_texture::FRAGMENT_MODE_BINDING);
    draw_mode.SetIndex(0);


    shaders[ShaderStage::Vertex] = ShaderProgram::DataSet(simple_texture::get_vertex_code_bin(), simple_texture::get_vertex_control_bin());
    shaders[ShaderStage::Fragment] = ShaderProgram::DataSet(simple_texture::get_fragment_code_bin(), simple_texture::get_fragment_control_bin());
    SL_ASSERTM(shaders.Initialize(g_Device), "failed to initialize shader program");

    blend_state->SetBlendTarget(0)
        .SetBlendEquation(nvn::BlendEquation::ADD, nvn::BlendEquation::ADD)
        .SetBlendFunc(nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA, nvn::BlendFunc::SRC_ALPHA, nvn::BlendFunc::ONE_MINUS_SRC_ALPHA);

    color_state->SetBlendEnable(0, true)
        .SetLogicOp(nvn::LogicOp::COPY);

    polygon_state->SetCullFace(nvn::Face::NONE)
        .SetFrontFace(nvn::FrontFace::CCW)
        .SetPolygonMode(nvn::PolygonMode::FILL);

    for (size_t i = 0; i < 3; i++) {
        vertex_attrib_state[i].SetFormat(nvn::Format::RG32F, 0)
            .SetStreamIndex(static_cast<int>(i));

        vertex_stream_state[i].SetDefaults().SetStride(sizeof(phx::Vector2f));
    }
}

GamecubeController::GamecubeController(uint32_t npad_id) : Controller(npad_id) {
    const auto& settings = GcJson::Get();
    width = settings.layout->source_width;
    height = settings.layout->source_height;

    image = ControllerImages::GetOrMakeGamecube(settings.width, settings.height);
    image->SetId(simple_texture::FRAGMENT_TEXTURE_BINDING);
    image->SetStage(nvn::ShaderStage::FRAGMENT);
}

ProController::ProController(uint32_t npad_id) : Controller(npad_id) {
    const auto& settings = ProJson::Get();
    width = settings.layout->source_width;
    height = settings.layout->source_height;

    image = ControllerImages::GetOrMakePro(settings.width, settings.height);
    image->SetId(simple_texture::FRAGMENT_TEXTURE_BINDING);
    image->SetStage(nvn::ShaderStage::FRAGMENT);
}

SmashController::SmashController(uint32_t player_id) : Controller(player_id), buttons({}) {
    const auto& settings = GcJson::Get();
    width = settings.layout->source_width + settings.layout->additional_width;
    height = settings.layout->source_height;

    image = ControllerImages::GetOrMakeGamecube(settings.width, settings.height);
    image->SetId(simple_texture::FRAGMENT_TEXTURE_BINDING);
    image->SetStage(nvn::ShaderStage::FRAGMENT);
}

void GamecubeController::Update(nvn::CommandBuffer*) {
    const auto& settings = GcJson::Get();
    if (width == -1.0f)
        width = (height / settings.layout->source_height) * settings.layout->source_width;
    else if (height == -1.0f)
        height = (width / settings.layout->source_width) * settings.layout->source_height;

    const float w_scale = width / (settings.layout->source_width);
    const float h_scale = height / (settings.layout->source_height);

    auto origin = phx::Vector2f { x, y };
    auto dimensions = normalize_texture({ width, height }, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });
    auto screen_tile_dims = normalize_texture({ (float)settings.tile_size, (float)settings.tile_size }, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });
    auto tile_dims = normalize_texture({ (float)settings.tile_size, (float)settings.tile_size }, { (float)settings.width, (float)settings.height });

    nn::hid::NpadGcState state;
    nn::hid::GetNpadState(&state, npad_id);

    if (HAS_KEY(state, nn::hid::KEY_L) && HAS_KEY(state, nn::hid::KEY_R) && HAS_KEY(state, nn::hid::KEY_PLUS)) {
        if (HAS_KEY_PRESS(state, nn::hid::KEY_DUP))
            g_DrawSettings.input = !g_DrawSettings.input;
        else if (HAS_KEY_PRESS(state, nn::hid::KEY_DRIGHT))
            g_DrawSettings.ecb = !g_DrawSettings.ecb;
        else if (HAS_KEY_PRESS(state, nn::hid::KEY_DDOWN))
            g_DrawSettings.ledge_grab = !g_DrawSettings.ledge_grab;
        else if (HAS_KEY_PRESS(state, nn::hid::KEY_DLEFT))
            g_DrawSettings.hurtboxes = !g_DrawSettings.hurtboxes;

        if (state.RStickX >= 0.5f)
            g_DrawSettings.camera_angle = 3;
        else if (state.RStickY >= 0.5f)
            g_DrawSettings.camera_angle = 2;
        else if (state.RStickX <= -0.5f)
            g_DrawSettings.camera_angle = 1;
        else if (state.RStickY <= -0.5f)
            g_DrawSettings.camera_angle = 0;
    }

    s_PrevButtons = state.Buttons;

    if (!g_DrawSettings.input)
        return;
    
    const auto& l_buttons = settings.layout->buttons;
    const auto& t_buttons = settings.buttons;

    auto add_on_off_button = [&](const std::string& button_name, uint64_t key, bool ignore_if_off) {
        SL_ASSERT(l_buttons.find(button_name) != l_buttons.end());

        phx::Vector2f tcoords;
        if ((state.Buttons & key) == 0) {
            if (ignore_if_off)
                return;
            std::string new_name = "-" + button_name;
            SL_ASSERT(t_buttons.find(new_name) != t_buttons.end());

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        } else {
            std::string new_name = "+" + button_name;
            if (ignore_if_off)
                new_name = button_name;

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        }

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at(button_name);

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        if (layout.flip) {
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        } else {
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);
    };

    auto add_stick = [&](const std::string& stick_letter, float x, float y, float translate_max) {
        std::string gate = stick_letter + "_gate";
        std::string stick = stick_letter + "_stick";

        SL_ASSERT(t_buttons.find(gate) != t_buttons.end());
        SL_ASSERT(t_buttons.find(stick) != t_buttons.end());
        SL_ASSERT(l_buttons.find(gate) != l_buttons.end());
        SL_ASSERT(l_buttons.find(stick) != l_buttons.end());

        phx::Vector2f tcoords_gate = { (float)t_buttons.at(gate).first, (float)t_buttons.at(gate).second };
        phx::Vector2f tcoords_stick = { (float)t_buttons.at(stick).first, (float)t_buttons.at(stick).second };

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos_gate = { tcoords_gate.x * tile_dims.x, tcoords_gate.y * tile_dims.y };
        const phx::Vector2f t_pos_stick = { tcoords_stick.x * tile_dims.x, tcoords_stick.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos_gate);
        tcoord_buffer.SafePush({ t_pos_gate.x + tile_dims.x, t_pos_gate.y });
        tcoord_buffer.SafePush({ t_pos_gate.x + tile_dims.x, t_pos_gate.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos_gate.x, t_pos_gate.y + tile_dims.y});

        tcoord_buffer.SafePush(t_pos_stick);
        tcoord_buffer.SafePush({ t_pos_stick.x + tile_dims.x, t_pos_stick.y });
        tcoord_buffer.SafePush({ t_pos_stick.x + tile_dims.x, t_pos_stick.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos_stick.x, t_pos_stick.y + tile_dims.y});

        const auto& gate_layout = l_buttons.at(gate);
        const auto& stick_layout = l_buttons.at(stick);

        const phx::Vector2f v_dims_gate = { (float)settings.tile_size * gate_layout.scale * w_scale, (float)settings.tile_size * gate_layout.scale * h_scale };
        const phx::Vector2f v_pos_gate = { origin.x + w_scale * gate_layout.x - v_dims_gate.x / 2.0f, origin.y + h_scale * gate_layout.y - v_dims_gate.y / 2.0f};
        vertex_buffer.SafePush(normalize_screen_coords(v_pos_gate));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x + v_dims_gate.x, v_pos_gate.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x + v_dims_gate.x, v_pos_gate.y + v_dims_gate.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x, v_pos_gate.y + v_dims_gate.y }));

        { // calculations for the stick are more difficult since we are calculating some 3D rotation for it to look nice
            const float magnitude = powf(powf(x, 2.0) + powf(y, 2.0), 0.5);
            float angle;

            if (x == 0.0f) {
                angle = (y < 0.0f) ? -M_PI / 2.0f : M_PI / 2.0f;
            } else {
                angle = atan2f(y, -x);
            }

            angle -= M_PI / 2.0f;


            const float top_shift = magnitude * translate_max * 0.2f * h_scale;
            const float bottom_shift = magnitude * translate_max * 0.4f * h_scale;

            const phx::Vector2f stick_dim = { (float)settings.tile_size * stick_layout.scale * w_scale, (float)settings.tile_size * stick_layout.scale * h_scale };
            const phx::Vector2f stick_pos = { origin.x + w_scale * stick_layout.x - stick_dim.x / 2.0f, origin.y + h_scale * stick_layout.y - stick_dim.y / 2.0f };

            const phx::Vector2f stick_center = { origin.x + w_scale * stick_layout.x, origin.y + h_scale * stick_layout.y };

            phx::Vector2f top_left =     rotate({ stick_pos.x              , stick_pos.y + top_shift }, stick_center, angle);
            phx::Vector2f top_right =    rotate({ stick_pos.x + stick_dim.x, stick_pos.y + top_shift }, stick_center, angle);
            phx::Vector2f bottom_right = rotate({ stick_pos.x + stick_dim.x, stick_pos.y + stick_dim.y - bottom_shift }, stick_center, angle);
            phx::Vector2f bottom_left =  rotate({ stick_pos.x              , stick_pos.y + stick_dim.y - bottom_shift }, stick_center, angle);

            vertex_buffer.SafePush(normalize_screen_coords({ top_left.x + w_scale * translate_max * x, top_left.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ top_right.x + w_scale * translate_max * x, top_right.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ bottom_right.x + w_scale * translate_max * x, bottom_right.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ bottom_left.x + w_scale * translate_max * x, bottom_left.y - h_scale * translate_max * y}));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 8, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);

        index_buffer.SafePush(length + 4);
        index_buffer.SafePush(length + 5);
        index_buffer.SafePush(length + 6);

        index_buffer.SafePush(length + 4);
        index_buffer.SafePush(length + 6);
        index_buffer.SafePush(length + 7);
    };

    auto add_dpad = [&]() {
        SL_ASSERT(l_buttons.find("dpad") != l_buttons.end());

        SL_ASSERT(t_buttons.find("dpad") != t_buttons.end());
        phx::Vector2f tcoords = { (float)t_buttons.at("dpad").first, (float)t_buttons.at("dpad").second };

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at("dpad");

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        vertex_buffer.SafePush(normalize_screen_coords(v_pos));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);

        const std::vector<std::pair<std::string, uint64_t>> directions = { 
            { "dpad_l", nn::hid::KEY_DLEFT  },
            { "dpad_r", nn::hid::KEY_DRIGHT },
            { "dpad_u", nn::hid::KEY_DUP    },
            { "dpad_d", nn::hid::KEY_DDOWN  }
        };

        for (const auto& pair : directions) {
            const auto& direction = pair.first;
            if ((state.Buttons & pair.second) == 0)
                continue;
            SL_ASSERT(t_buttons.find("dpad") != t_buttons.end());
            phx::Vector2f tcoords = { (float)t_buttons.at(direction).first, (float)t_buttons.at(direction).second };

            size_t length = tcoord_buffer.Length();

            const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

            tcoord_buffer.SafePush(t_pos);
            tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
            tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
            tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

            const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
            const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
    
            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });
    
            index_buffer.SafePush(length);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);
    
            index_buffer.SafePush(length);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);
        }
    };

    auto add_triggers = [&](float analog_start, float analog_end) {
        SL_ASSERT(l_buttons.find("trigger_l") != l_buttons.end());
        SL_ASSERT(l_buttons.find("trigger_r") != l_buttons.end());
        SL_ASSERT(t_buttons.find("-trigger") != t_buttons.end());
        SL_ASSERT(t_buttons.find("+trigger") != t_buttons.end());

        const auto& l_layout = l_buttons.at("trigger_l");
        const auto& r_layout = l_buttons.at("trigger_r");

        const float trigger_l = (state.Buttons & nn::hid::KEY_L) ? 1.0f : (state.TriggerL / (float)(INT16_MAX));
        const float trigger_r = (state.Buttons & nn::hid::KEY_R) ? 1.0f : (state.TriggerR / (float)(INT16_MAX));

        const float difference_l = trigger_l * (analog_end - analog_start);
        const float difference_r = (1.0f - trigger_r) * (analog_end - analog_start);

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];

        size_t length = tcoord_buffer.Length();
        if (trigger_l == 1.0f) {
            phx::Vector2f tcoords = { (float)t_buttons.at("+trigger").first * tile_dims.x, (float)t_buttons.at("+trigger").second * tile_dims.y };

            tcoord_buffer.SafePush(tcoords);
            tcoord_buffer.SafePush({ tcoords.x + tile_dims.x, tcoords.y });
            tcoord_buffer.SafePush({ tcoords.x + tile_dims.x, tcoords.y + tile_dims.y });
            tcoord_buffer.SafePush({ tcoords.x, tcoords.y + tile_dims.y });
            
            const phx::Vector2f v_dims = { (float)settings.tile_size * l_layout.scale * w_scale, (float)settings.tile_size * l_layout.scale * h_scale };
            const phx::Vector2f v_pos = { origin.x + w_scale * l_layout.x - v_dims.x / 2.0f, origin.y + h_scale * l_layout.y - v_dims.y / 2.0f};
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));

            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);

            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);
        } else {
            phx::Vector2f tcoords_full  = { (float)t_buttons.at("+trigger").first * tile_dims.x, (float)t_buttons.at("+trigger").second * tile_dims.y };
            phx::Vector2f tcoords_empty = { (float)t_buttons.at("-trigger").first * tile_dims.x, (float)t_buttons.at("-trigger").second * tile_dims.y };

            phx::Vector2f dims = { (float)settings.tile_size * l_layout.scale * w_scale, (float)settings.tile_size * l_layout.scale * h_scale };
            const phx::Vector2f v_pos = normalize_screen_coords({ origin.x + w_scale * l_layout.x - dims.x / 2.0f, origin.y + h_scale * l_layout.y - dims.y / 2.0f});

            dims = normalize_texture(dims, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });

            // for the left trigger, we want to fill from left to right
            // that means that our we start by drawing a triangle with our full width
            tcoord_buffer.SafePush(tcoords_full);
            tcoord_buffer.SafePush({ tcoords_full.x + (analog_start + difference_l) * tile_dims.x, tcoords_full.y });
            tcoord_buffer.SafePush({ tcoords_full.x + (analog_start + difference_l) * tile_dims.x, tcoords_full.y + tile_dims.y });
            tcoord_buffer.SafePush({ tcoords_full.x, tcoords_full.y + tile_dims.y });

            vertex_buffer.SafePush(v_pos);
            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_l) * dims.x, v_pos.y });
            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_l) * dims.x, v_pos.y + dims.y });
            vertex_buffer.SafePush({ v_pos.x, v_pos.y + dims.y });

            // then, we want to draw what's remaining as our empty texture
            tcoord_buffer.SafePush({ tcoords_empty.x + (analog_start + difference_l) * tile_dims.x, tcoords_empty.y });
            tcoord_buffer.SafePush({ tcoords_empty.x + tile_dims.x, tcoords_empty.y });
            tcoord_buffer.SafePush({ tcoords_empty.x + tile_dims.x, tcoords_empty.y + tile_dims.y });
            tcoord_buffer.SafePush({ tcoords_empty.x + (analog_start + difference_l) * tile_dims.x, tcoords_empty.y + tile_dims.y });

            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_l) * dims.x, v_pos.y });
            vertex_buffer.SafePush({ v_pos.x + dims.x, v_pos.y });
            vertex_buffer.SafePush({ v_pos.x + dims.x, v_pos.y + dims.y });
            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_l) * dims.x, v_pos.y + dims.y });

            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 8, phx::Vector2f { 0.0f, 0.0f });

            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);

            index_buffer.SafePush(length + 4);
            index_buffer.SafePush(length + 5);
            index_buffer.SafePush(length + 6);
            index_buffer.SafePush(length + 4);
            index_buffer.SafePush(length + 6);
            index_buffer.SafePush(length + 7);
        }

        length = tcoord_buffer.Length();
        if (trigger_r == 1.0f) {
            phx::Vector2f tcoords = { (float)t_buttons.at("+trigger").first * tile_dims.x, (float)t_buttons.at("+trigger").second * tile_dims.y };

            tcoord_buffer.SafePush(tcoords);
            tcoord_buffer.SafePush({ tcoords.x + tile_dims.x, tcoords.y });
            tcoord_buffer.SafePush({ tcoords.x + tile_dims.x, tcoords.y + tile_dims.y });
            tcoord_buffer.SafePush({ tcoords.x, tcoords.y + tile_dims.y });
            
            const phx::Vector2f v_dims = { (float)settings.tile_size * r_layout.scale * w_scale, (float)settings.tile_size * r_layout.scale * h_scale };
            const phx::Vector2f v_pos = { origin.x + w_scale * r_layout.x - v_dims.x / 2.0f, origin.y + h_scale * r_layout.y - v_dims.y / 2.0f};
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));

            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);

            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);
        } else {
            phx::Vector2f tcoords_full  = { (float)t_buttons.at("+trigger").first * tile_dims.x, (float)t_buttons.at("+trigger").second * tile_dims.y };
            phx::Vector2f tcoords_empty = { (float)t_buttons.at("-trigger").first * tile_dims.x, (float)t_buttons.at("-trigger").second * tile_dims.y };

            phx::Vector2f dims = { (float)settings.tile_size * r_layout.scale * w_scale, (float)settings.tile_size * r_layout.scale * h_scale };
            const phx::Vector2f v_pos = normalize_screen_coords({ origin.x + w_scale * r_layout.x - dims.x / 2.0f, origin.y + h_scale * r_layout.y - dims.y / 2.0f});

            dims = normalize_texture(dims, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });

            // for the left trigger, we want to fill from left to right
            // that means that our we start by drawing a triangle with our full width
            tcoord_buffer.SafePush(tcoords_empty);
            tcoord_buffer.SafePush({ tcoords_empty.x + (analog_start + difference_r) * tile_dims.x, tcoords_empty.y });
            tcoord_buffer.SafePush({ tcoords_empty.x + (analog_start + difference_r) * tile_dims.x, tcoords_empty.y + tile_dims.y });
            tcoord_buffer.SafePush({ tcoords_empty.x, tcoords_empty.y + tile_dims.y });

            vertex_buffer.SafePush(v_pos);
            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_r) * dims.x, v_pos.y });
            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_r) * dims.x, v_pos.y + dims.y });
            vertex_buffer.SafePush({ v_pos.x, v_pos.y + dims.y });

            // then, we want to draw what's remaining as our empty texture
            tcoord_buffer.SafePush({ tcoords_full.x + (analog_start + difference_r) * tile_dims.x, tcoords_full.y });
            tcoord_buffer.SafePush({ tcoords_full.x + tile_dims.x, tcoords_full.y });
            tcoord_buffer.SafePush({ tcoords_full.x + tile_dims.x, tcoords_full.y + tile_dims.y });
            tcoord_buffer.SafePush({ tcoords_full.x + (analog_start + difference_r) * tile_dims.x, tcoords_full.y + tile_dims.y });

            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_r) * dims.x, v_pos.y });
            vertex_buffer.SafePush({ v_pos.x + dims.x, v_pos.y });
            vertex_buffer.SafePush({ v_pos.x + dims.x, v_pos.y + dims.y });
            vertex_buffer.SafePush({ v_pos.x + (analog_start + difference_r) * dims.x, v_pos.y + dims.y });

            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 8, phx::Vector2f { 0.0f, 0.0f });

            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 0);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);

            index_buffer.SafePush(length + 4);
            index_buffer.SafePush(length + 5);
            index_buffer.SafePush(length + 6);
            index_buffer.SafePush(length + 4);
            index_buffer.SafePush(length + 6);
            index_buffer.SafePush(length + 7);
        }
    };

    add_on_off_button("a", nn::hid::KEY_A, false);
    add_on_off_button("b", nn::hid::KEY_B, false);
    add_on_off_button("x", nn::hid::KEY_X, false);
    add_on_off_button("y", nn::hid::KEY_Y, false);
    add_on_off_button("z", nn::hid::KEY_ZL | nn::hid::KEY_ZR, false);
    add_on_off_button("start", nn::hid::KEY_MINUS | nn::hid::KEY_PLUS, false);

    add_stick("a", (float)state.LStickX / (float)(INT16_MAX), (float)state.LStickY / (float)(INT16_MAX), 40.0f);
    add_stick("c", (float)state.RStickX / (float)(INT16_MAX), (float)state.RStickY / (float)(INT16_MAX), 30.0f);
    add_dpad();
    add_triggers(0.125f, 0.875f);
}

void ProController::Update(nvn::CommandBuffer* cmdbuf) {
    const auto& settings = ProJson::Get();
    if (width == -1.0f)
        width = (height / settings.layout->source_height) * settings.layout->source_width;
    else if (height == -1.0f)
        height = (width / settings.layout->source_width) * settings.layout->source_height;

    const float w_scale = width / (settings.layout->source_width);
    const float h_scale = height / (settings.layout->source_height);

    auto origin = phx::Vector2f { x, y };
    auto dimensions = normalize_texture({ width, height }, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });
    auto screen_tile_dims = normalize_texture({ (float)settings.tile_size, (float)settings.tile_size }, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });
    auto tile_dims = normalize_texture({ (float)settings.tile_size, (float)settings.tile_size }, { (float)settings.width, (float)settings.height });

    nn::hid::NpadFullKeyState state;
    nn::hid::GetNpadState(&state, npad_id);

    if ((state.Flags & 1) == 0) {
        nn::hid::GetNpadState((nn::hid::NpadJoyDualState*)&state, npad_id);
        if ((npad_id == 0) && ((state.Flags & 1) == 0))
            nn::hid::GetNpadState((nn::hid::NpadHandheldState*)&state, 0x20);
    }

    if (HAS_KEY(state, nn::hid::KEY_L) && HAS_KEY(state, nn::hid::KEY_R) && HAS_KEY(state, nn::hid::KEY_PLUS)) {
        if (HAS_KEY_PRESS(state, nn::hid::KEY_DUP))
            g_DrawSettings.input = !g_DrawSettings.input;
        else if (HAS_KEY_PRESS(state, nn::hid::KEY_DRIGHT))
            g_DrawSettings.ecb = !g_DrawSettings.ecb;
        else if (HAS_KEY_PRESS(state, nn::hid::KEY_DDOWN))
            g_DrawSettings.ledge_grab = !g_DrawSettings.ledge_grab;
        else if (HAS_KEY_PRESS(state, nn::hid::KEY_DLEFT))
            g_DrawSettings.hurtboxes = !g_DrawSettings.hurtboxes;

        if (state.RStickX >= 0.5f)
            g_DrawSettings.camera_angle = 3;
        else if (state.RStickY >= 0.5f)
            g_DrawSettings.camera_angle = 2;
        else if (state.RStickX <= -0.5f)
            g_DrawSettings.camera_angle = 1;
        else if (state.RStickY <= -0.5f)
            g_DrawSettings.camera_angle = 0;
    }

    s_PrevButtons = state.Buttons;

    if (!g_DrawSettings.input)
        return;
    
    const auto& l_buttons = settings.layout->buttons;
    const auto& t_buttons = settings.buttons;

    auto add_on_off_button = [&](const std::string& button_name, uint64_t key, bool ignore_if_off) {
        SL_ASSERT(l_buttons.find(button_name) != l_buttons.end());

        phx::Vector2f tcoords;
        if ((state.Buttons & key) == 0) {
            if (ignore_if_off)
                return;
            std::string new_name = "-" + button_name;
            SL_ASSERT(t_buttons.find(new_name) != t_buttons.end());

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        } else {
            std::string new_name = "+" + button_name;
            if (ignore_if_off)
                new_name = button_name;

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        }

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at(button_name);

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        if (layout.flip) {
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        } else {
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);
    };

    auto add_stick = [&](const std::string& stick_letter, uint64_t key, float x, float y, float translate_max) {
        std::string gate = stick_letter + "_gate";
        std::string stick = stick_letter + "_stick";
        std::string t_stick;

        if (state.Buttons & key) {
            t_stick = "+" + stick;
        } else {
            t_stick = "-" + stick;
        }

        SL_ASSERT(t_buttons.find(gate) != t_buttons.end());
        SL_ASSERT(t_buttons.find(t_stick) != t_buttons.end());
        SL_ASSERT(l_buttons.find(gate) != l_buttons.end());
        SL_ASSERT(l_buttons.find(stick) != l_buttons.end());

        phx::Vector2f tcoords_gate = { (float)t_buttons.at(gate).first, (float)t_buttons.at(gate).second };
        phx::Vector2f tcoords_stick = { (float)t_buttons.at(t_stick).first, (float)t_buttons.at(t_stick).second };

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos_gate = { tcoords_gate.x * tile_dims.x, tcoords_gate.y * tile_dims.y };
        const phx::Vector2f t_pos_stick = { tcoords_stick.x * tile_dims.x, tcoords_stick.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos_gate);
        tcoord_buffer.SafePush({ t_pos_gate.x + tile_dims.x, t_pos_gate.y });
        tcoord_buffer.SafePush({ t_pos_gate.x + tile_dims.x, t_pos_gate.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos_gate.x, t_pos_gate.y + tile_dims.y});

        tcoord_buffer.SafePush(t_pos_stick);
        tcoord_buffer.SafePush({ t_pos_stick.x + tile_dims.x, t_pos_stick.y });
        tcoord_buffer.SafePush({ t_pos_stick.x + tile_dims.x, t_pos_stick.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos_stick.x, t_pos_stick.y + tile_dims.y});

        const auto& gate_layout = l_buttons.at(gate);
        const auto& stick_layout = l_buttons.at(stick);

        const phx::Vector2f v_dims_gate = { (float)settings.tile_size * gate_layout.scale * w_scale, (float)settings.tile_size * gate_layout.scale * h_scale };
        const phx::Vector2f v_pos_gate = { origin.x + w_scale * gate_layout.x - v_dims_gate.x / 2.0f, origin.y + h_scale * gate_layout.y - v_dims_gate.y / 2.0f};
        vertex_buffer.SafePush(normalize_screen_coords(v_pos_gate));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x + v_dims_gate.x, v_pos_gate.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x + v_dims_gate.x, v_pos_gate.y + v_dims_gate.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x, v_pos_gate.y + v_dims_gate.y }));

        { // calculations for the stick are more difficult since we are calculating some 3D rotation for it to look nice
            const float magnitude = powf(powf(x, 2.0) + powf(y, 2.0), 0.5);
            float angle;

            if (x == 0.0f) {
                angle = (y < 0.0f) ? -M_PI / 2.0f : M_PI / 2.0f;
            } else {
                angle = atan2f(y, -x);
            }

            angle -= M_PI / 2.0f;


            const float top_shift = magnitude * translate_max * 0.2f;
            const float bottom_shift = magnitude * translate_max * 0.4f;

            const phx::Vector2f stick_dim = { (float)settings.tile_size * stick_layout.scale * w_scale, (float)settings.tile_size * stick_layout.scale * h_scale };
            const phx::Vector2f stick_pos = { origin.x + w_scale * stick_layout.x - stick_dim.x / 2.0f, origin.y + h_scale * stick_layout.y - stick_dim.y / 2.0f };

            const phx::Vector2f stick_center = { origin.x + w_scale * stick_layout.x, origin.y + h_scale * stick_layout.y };

            phx::Vector2f top_left =     rotate({ stick_pos.x              , stick_pos.y + top_shift }, stick_center, angle);
            phx::Vector2f top_right =    rotate({ stick_pos.x + stick_dim.x, stick_pos.y + top_shift }, stick_center, angle);
            phx::Vector2f bottom_right = rotate({ stick_pos.x + stick_dim.x, stick_pos.y + stick_dim.y - bottom_shift }, stick_center, angle);
            phx::Vector2f bottom_left =  rotate({ stick_pos.x              , stick_pos.y + stick_dim.y - bottom_shift }, stick_center, angle);

            vertex_buffer.SafePush(normalize_screen_coords({ top_left.x + w_scale * translate_max * x, top_left.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ top_right.x + w_scale * translate_max * x, top_right.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ bottom_right.x + w_scale * translate_max * x, bottom_right.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ bottom_left.x + w_scale * translate_max * x, bottom_left.y - h_scale * translate_max * y}));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 8, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);

        index_buffer.SafePush(length + 4);
        index_buffer.SafePush(length + 5);
        index_buffer.SafePush(length + 6);

        index_buffer.SafePush(length + 4);
        index_buffer.SafePush(length + 6);
        index_buffer.SafePush(length + 7);
    };

    auto add_dpad = [&]() {
        SL_ASSERT(l_buttons.find("dpad") != l_buttons.end());

        SL_ASSERT(t_buttons.find("dpad") != t_buttons.end());
        phx::Vector2f tcoords = { (float)t_buttons.at("dpad").first, (float)t_buttons.at("dpad").second };

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at("dpad");

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        vertex_buffer.SafePush(normalize_screen_coords(v_pos));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);

        const std::vector<std::pair<std::string, uint64_t>> directions = { 
            { "dpad_l", nn::hid::KEY_DLEFT  },
            { "dpad_r", nn::hid::KEY_DRIGHT },
            { "dpad_u", nn::hid::KEY_DUP    },
            { "dpad_d", nn::hid::KEY_DDOWN  }
        };

        for (const auto& pair : directions) {
            const auto& direction = pair.first;
            if ((state.Buttons & pair.second) == 0)
                continue;
            SL_ASSERT(t_buttons.find("dpad") != t_buttons.end());
            phx::Vector2f tcoords = { (float)t_buttons.at(direction).first, (float)t_buttons.at(direction).second };

            size_t length = tcoord_buffer.Length();

            const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

            tcoord_buffer.SafePush(t_pos);
            tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
            tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
            tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

            const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
            const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
    
            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });
    
            index_buffer.SafePush(length);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);
    
            index_buffer.SafePush(length);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);
        }
    };

    add_on_off_button("zl", nn::hid::KEY_ZL, false);
    add_on_off_button("zr", nn::hid::KEY_ZR, false);

    add_on_off_button("l", nn::hid::KEY_L, false);
    add_on_off_button("r", nn::hid::KEY_R, false);

    add_on_off_button("a", nn::hid::KEY_A, false);
    add_on_off_button("b", nn::hid::KEY_B, false);
    add_on_off_button("x", nn::hid::KEY_X, false);
    add_on_off_button("y", nn::hid::KEY_Y, false);

    add_on_off_button("plus", nn::hid::KEY_PLUS, false);
    add_on_off_button("minus", nn::hid::KEY_MINUS, false);

    add_dpad();

    add_stick("a", nn::hid::KEY_LSTICK, (float)state.LStickX / (float)INT16_MAX, (float)state.LStickY / (float)INT16_MAX, 35.0f);
    add_stick("c", nn::hid::KEY_RSTICK, (float)state.RStickX / (float)INT16_MAX, (float)state.RStickY / (float)INT16_MAX, 35.0f);
}

void SmashController::Update(nvn::CommandBuffer* cmdbuf) {
    const auto& settings = GcJson::Get();
    const float full_width = settings.layout->source_width + settings.layout->additional_width;
    if (width == -1.0f)
        width = (height / settings.layout->source_height) * full_width;
    else if (height == -1.0f)
        height = (width / full_width) * settings.layout->source_height;

    const float w_scale = width / (full_width);
    const float h_scale = height / (settings.layout->source_height);

    auto origin = phx::Vector2f { x, y };
    auto dimensions = normalize_texture({ width, height }, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });
    auto screen_tile_dims = normalize_texture({ (float)settings.tile_size, (float)settings.tile_size }, { (float)1920.0f / 2.0f, (float)-1080.0f / 2.0f });
    auto tile_dims = normalize_texture({ (float)settings.tile_size, (float)settings.tile_size }, { (float)settings.width, (float)settings.height });

    if (!g_DrawSettings.input) {
        return;
    }
    
    const auto& l_buttons = settings.layout->buttons;
    const auto& t_buttons = settings.buttons;

    auto add_on_off_button = [&](const std::string& button_name, bool draw, bool ignore_if_off) {
        SL_ASSERT(l_buttons.find(button_name) != l_buttons.end());

        phx::Vector2f tcoords;
        if (!draw) {
            if (ignore_if_off)
                return;
            std::string new_name = "-" + button_name;
            SL_ASSERT(t_buttons.find(new_name) != t_buttons.end());

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        } else {
            std::string new_name = "+" + button_name;
            if (ignore_if_off)
                new_name = button_name;

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        }

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at(button_name);

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        if (layout.flip) {
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        } else {
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);
    };
    
    auto add_on_off_button2 = [&](const std::string& button_name, const std::string& layout_name, bool draw, bool ignore_if_off) {
        SL_ASSERT(l_buttons.find(layout_name) != l_buttons.end());

        phx::Vector2f tcoords;
        if (!draw) {
            if (ignore_if_off)
                return;
            std::string new_name = "-" + button_name;
            SL_ASSERT(t_buttons.find(new_name) != t_buttons.end());

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        } else {
            std::string new_name = "+" + button_name;
            if (ignore_if_off)
                new_name = button_name;

            tcoords = { (float)t_buttons.at(new_name).first, (float)t_buttons.at(new_name).second };
        }

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at(layout_name);

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        if (layout.flip) {
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        } else {
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);
    };

    auto add_stick = [&](const std::string& stick_letter, float x, float y, float translate_max) {
        std::string gate = stick_letter + "_gate";
        std::string stick = stick_letter + "_stick";

        SL_ASSERT(t_buttons.find(gate) != t_buttons.end());
        SL_ASSERT(t_buttons.find(stick) != t_buttons.end());
        SL_ASSERT(l_buttons.find(gate) != l_buttons.end());
        SL_ASSERT(l_buttons.find(stick) != l_buttons.end());

        phx::Vector2f tcoords_gate = { (float)t_buttons.at(gate).first, (float)t_buttons.at(gate).second };
        phx::Vector2f tcoords_stick = { (float)t_buttons.at(stick).first, (float)t_buttons.at(stick).second };

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos_gate = { tcoords_gate.x * tile_dims.x, tcoords_gate.y * tile_dims.y };
        const phx::Vector2f t_pos_stick = { tcoords_stick.x * tile_dims.x, tcoords_stick.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos_gate);
        tcoord_buffer.SafePush({ t_pos_gate.x + tile_dims.x, t_pos_gate.y });
        tcoord_buffer.SafePush({ t_pos_gate.x + tile_dims.x, t_pos_gate.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos_gate.x, t_pos_gate.y + tile_dims.y});

        tcoord_buffer.SafePush(t_pos_stick);
        tcoord_buffer.SafePush({ t_pos_stick.x + tile_dims.x, t_pos_stick.y });
        tcoord_buffer.SafePush({ t_pos_stick.x + tile_dims.x, t_pos_stick.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos_stick.x, t_pos_stick.y + tile_dims.y});

        const auto& gate_layout = l_buttons.at(gate);
        const auto& stick_layout = l_buttons.at(stick);

        const phx::Vector2f v_dims_gate = { (float)settings.tile_size * gate_layout.scale * w_scale, (float)settings.tile_size * gate_layout.scale * h_scale };
        const phx::Vector2f v_pos_gate = { origin.x + w_scale * gate_layout.x - v_dims_gate.x / 2.0f, origin.y + h_scale * gate_layout.y - v_dims_gate.y / 2.0f};
        vertex_buffer.SafePush(normalize_screen_coords(v_pos_gate));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x + v_dims_gate.x, v_pos_gate.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x + v_dims_gate.x, v_pos_gate.y + v_dims_gate.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos_gate.x, v_pos_gate.y + v_dims_gate.y }));

        { // calculations for the stick are more difficult since we are calculating some 3D rotation for it to look nice
            const float magnitude = powf(powf(x, 2.0) + powf(y, 2.0), 0.5);
            float angle;

            if (x == 0.0f) {
                angle = (y < 0.0f) ? -M_PI / 2.0f : M_PI / 2.0f;
            } else {
                angle = atan2f(y, -x);
            }

            angle -= M_PI / 2.0f;


            const float top_shift = magnitude * translate_max * 0.2f * h_scale;
            const float bottom_shift = magnitude * translate_max * 0.4f * h_scale;

            const phx::Vector2f stick_dim = { (float)settings.tile_size * stick_layout.scale * w_scale, (float)settings.tile_size * stick_layout.scale * h_scale };
            const phx::Vector2f stick_pos = { origin.x + w_scale * stick_layout.x - stick_dim.x / 2.0f, origin.y + h_scale * stick_layout.y - stick_dim.y / 2.0f };

            const phx::Vector2f stick_center = { origin.x + w_scale * stick_layout.x, origin.y + h_scale * stick_layout.y };

            phx::Vector2f top_left =     rotate({ stick_pos.x              , stick_pos.y + top_shift }, stick_center, angle);
            phx::Vector2f top_right =    rotate({ stick_pos.x + stick_dim.x, stick_pos.y + top_shift }, stick_center, angle);
            phx::Vector2f bottom_right = rotate({ stick_pos.x + stick_dim.x, stick_pos.y + stick_dim.y - bottom_shift }, stick_center, angle);
            phx::Vector2f bottom_left =  rotate({ stick_pos.x              , stick_pos.y + stick_dim.y - bottom_shift }, stick_center, angle);

            vertex_buffer.SafePush(normalize_screen_coords({ top_left.x + w_scale * translate_max * x, top_left.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ top_right.x + w_scale * translate_max * x, top_right.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ bottom_right.x + w_scale * translate_max * x, bottom_right.y - h_scale * translate_max * y}));
            vertex_buffer.SafePush(normalize_screen_coords({ bottom_left.x + w_scale * translate_max * x, bottom_left.y - h_scale * translate_max * y}));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 8, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);

        index_buffer.SafePush(length + 4);
        index_buffer.SafePush(length + 5);
        index_buffer.SafePush(length + 6);

        index_buffer.SafePush(length + 4);
        index_buffer.SafePush(length + 6);
        index_buffer.SafePush(length + 7);
    };

    auto add_dpad = [&]() {
        SL_ASSERT(l_buttons.find("dpad") != l_buttons.end());

        SL_ASSERT(t_buttons.find("dpad") != t_buttons.end());
        phx::Vector2f tcoords = { (float)t_buttons.at("dpad").first, (float)t_buttons.at("dpad").second };

        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at("dpad");

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        vertex_buffer.SafePush(normalize_screen_coords(v_pos));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);

        const std::vector<std::pair<std::string, bool>> directions = { 
            { "dpad_l", this->buttons.appeal_s_l != 0 },
            { "dpad_r", this->buttons.appeal_s_r != 0 },
            { "dpad_u", this->buttons.appeal_hi  != 0 },
            { "dpad_d", this->buttons.appeal_lw  != 0 }
        };

        for (const auto& pair : directions) {
            const auto& direction = pair.first;
            if (!pair.second)
                continue;
            SL_ASSERT(t_buttons.find("dpad") != t_buttons.end());
            phx::Vector2f tcoords = { (float)t_buttons.at(direction).first, (float)t_buttons.at(direction).second };

            size_t length = tcoord_buffer.Length();

            const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

            tcoord_buffer.SafePush(t_pos);
            tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
            tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
            tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

            const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
            const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
    
            mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });
    
            index_buffer.SafePush(length);
            index_buffer.SafePush(length + 1);
            index_buffer.SafePush(length + 2);
    
            index_buffer.SafePush(length);
            index_buffer.SafePush(length + 2);
            index_buffer.SafePush(length + 3);
        }
    };

    int slot_count = 0;
    auto add_raw_slot = [&](const std::string& button_name, bool draw) {
        if (!draw)
            return;
        
        std::string layout_slot = "slot_" + std::to_string(slot_count);
        slot_count++;
        SL_ASSERT(l_buttons.find(layout_slot) != l_buttons.end());
        SL_ASSERT(t_buttons.find(button_name) != t_buttons.end());

        phx::Vector2f tcoords =  { (float)t_buttons.at(button_name).first, (float)t_buttons.at(button_name).second };


        auto& tcoord_buffer = this->tcoord_buffer[this->buffer_in_use];
        auto& mcoord_buffer = this->mcoord_buffer[this->buffer_in_use];
        auto& vertex_buffer = this->vertex_buffer[this->buffer_in_use];
        auto& index_buffer  = this->index_buffer[this->buffer_in_use];
        size_t length = tcoord_buffer.Length();

        const phx::Vector2f t_pos = { tcoords.x * tile_dims.x, tcoords.y * tile_dims.y };

        tcoord_buffer.SafePush(t_pos);
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y });
        tcoord_buffer.SafePush({ t_pos.x + tile_dims.x, t_pos.y + tile_dims.y });
        tcoord_buffer.SafePush({ t_pos.x, t_pos.y + tile_dims.y});

        const auto& layout = l_buttons.at(layout_slot);

        const phx::Vector2f v_dims = { (float)settings.tile_size * layout.scale * w_scale, (float)settings.tile_size * layout.scale * h_scale };
        const phx::Vector2f v_pos = { origin.x + w_scale * layout.x - v_dims.x / 2.0f, origin.y + h_scale * layout.y - v_dims.y / 2.0f};
        if (layout.flip) {
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
        } else {
            vertex_buffer.SafePush(normalize_screen_coords(v_pos));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x + v_dims.x, v_pos.y + v_dims.y }));
            vertex_buffer.SafePush(normalize_screen_coords({ v_pos.x, v_pos.y + v_dims.y }));
        }

        mcoord_buffer.SafeResize(mcoord_buffer.Length() + 4, phx::Vector2f { 0.0f, 0.0f });

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 1);
        index_buffer.SafePush(length + 2);

        index_buffer.SafePush(length);
        index_buffer.SafePush(length + 2);
        index_buffer.SafePush(length + 3);
    };

    add_on_off_button("a", (buttons.attack != 0) || (buttons.attack_raw != 0), false);
    add_on_off_button("b", (buttons.special != 0) || (buttons.special_raw != 0) || (buttons.special_raw2 != 0), false);
    add_on_off_button("x", buttons.jump_mini != 0, false);
    add_on_off_button("y", (buttons.jump != 0) || (buttons.jump_mini != 0), false);
    add_on_off_button("z", buttons.catch_ != 0, false);
    add_on_off_button("start", false, false);
    add_on_off_button2("trigger", "trigger_l", buttons.guard_hold != 0, false);
    add_on_off_button2("trigger", "trigger_r", (buttons.guard_hold != 0) || (buttons.guard != 0), false);

    add_raw_slot("shield_lock", buttons.guard_hold != 0);
    add_raw_slot("stock_share", buttons.stock_share != 0);
    add_raw_slot("c_stick_on", buttons.c_stick_on != 0);
    add_raw_slot("short_hop", buttons.jump_mini != 0);
    add_raw_slot("smash", buttons.smash != 0);

    if (buttons.c_stick_on != 0) {
        add_stick("a", 0.0f, 0.0f, 40.0f);
        add_stick("c", (float)buttons.lstick_x / (float)(INT8_MAX), (float)buttons.lstick_y / (float)(INT8_MAX), 30.0f);
    } else {
        add_stick("a", (float)buttons.lstick_x / (float)(INT8_MAX), (float)buttons.lstick_y / (float)(INT8_MAX), 40.0f);
        add_stick("c", 0.0f, 0.0f, 30.0f);
    }

    add_dpad();
}

void Controller::Draw(nvn::CommandBuffer* cmdbuf) {
    shaders.Bind(cmdbuf);
    draw_mode.Bind(cmdbuf);
    blend_state.Bind(cmdbuf);
    channel_mask_state.Bind(cmdbuf);
    color_state.Bind(cmdbuf);
    multisample_state.Bind(cmdbuf);
    polygon_state.Bind(cmdbuf);
    vertex_attrib_state.Bind(cmdbuf);
    vertex_stream_state.Bind(cmdbuf);

    vertex_buffer[buffer_in_use].Bind(cmdbuf);
    tcoord_buffer[buffer_in_use].Bind(cmdbuf);
    mcoord_buffer[buffer_in_use].Bind(cmdbuf);

    image->Bind(cmdbuf);

    index_buffer[buffer_in_use].Draw(cmdbuf);

    buffer_in_use = (buffer_in_use + 1) % 3;
    vertex_buffer[buffer_in_use].Clear();
    tcoord_buffer[buffer_in_use].Clear();
    mcoord_buffer[buffer_in_use].Clear();
    index_buffer[buffer_in_use].Clear();
}

InputManager::InputManager()
    : gc_controller(0),
        pro_controller(0),
        smash_controllers { SmashController(0), SmashController(1) },
        active(&gc_controller)
{

}

InputManager& InputManager::Instance() {
    static InputManager instance;
    return instance;
}

void InputManager::Update(nvn::CommandBuffer* cmdbuf) {
    const uint32_t id = 0;
    auto& instance = Instance();
    float w, h, offset;

    if (g_IsReplay) {
        auto& settings = GcJson::Get();
        w = (float)(settings.layout->source_width + settings.layout->additional_width);
        h = (float)(settings.layout->source_height);
        offset = 0.0f;
    } else if ((nn::hid::GetNpadStyleSet(id) & (1 << 5)) != 0) {
        instance.active = &instance.gc_controller;
        w = (float)GcJson::Get().layout->source_width;
        h = (float)GcJson::Get().layout->source_height;
        offset = 0.55f;
    }
    else {
        instance.active = &instance.pro_controller;
        w = (float)ProJson::Get().layout->source_width;
        h = (float)ProJson::Get().layout->source_height;
        offset = 0.6f;
    }

    if (g_IsReplay) {
        instance.smash_controllers[0].SetPos(0.0f, 1080.0f - h);
        instance.smash_controllers[1].SetPos(1920.0f - w, 1080.0f - h);
        instance.smash_controllers[0].Update(cmdbuf);
        instance.smash_controllers[1].Update(cmdbuf);
        return;
    } else if (sl_is_match_active() && app::smashball::is_training_mode()) {
        instance.active->SetPos(1920.0f - w, 1080.0f - h);
        instance.active->SetFromWidth(w);
    } else {
        float x = 1920.0f / 2.0f - w * 0.85f * offset;
        instance.active->SetPos(x, 1080.0f - h * 0.85f);
        instance.active->SetFromWidth(0.85f * w);
    }

    instance.active->Update(cmdbuf);
}

void InputManager::Render(nvn::CommandBuffer* cmdbuf) {
    if (g_IsReplay) {
        Instance().smash_controllers[0].Draw(cmdbuf);
        Instance().smash_controllers[1].Draw(cmdbuf);
    } else {
        Instance().active->Draw(cmdbuf);
    }
}

void InputManager::InstallHooks() {
    A64InlineHook(
        skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x3f7260,
        reinterpret_cast<void*>(smash_controller_update_hook)
    );
    A64InlineHook(
        skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x6b7ff8,
        reinterpret_cast<void*>(smash_controller_update_non_player_hook)
    );
}

SmashController* InputManager::GetSmashController(size_t id) {
    return &Instance().smash_controllers[id];
}