#include <cstdint>
#include <memory>
#include "smash.hpp"

class CameraManager
{
public:
    int current_camera_priority;
    int current_camera_kind;
    uint64_t _x8;
    std::shared_ptr<void> active_camera;
    std::shared_ptr<void> cameras[18];
    char _x140[0x12C];
    uint32_t boss_param_filepath_idx;
    char _x270[0x824];
    float default_fov;
    char _xA98[0x188];
    phx::Vector4f range;
    phx::Vector4f blastzones;
    char _xC40[0xF0];
    phx::Vector3f position;
    float _xD3C[21];
    float angle_x;
    float angle_y;
    float angle_z;
    float _xD9C[2];
    float roll_offset;
    float zoom;
    float fov;
    float unk[20];

    static CameraManager* Instance() {
        auto pp_camera = *reinterpret_cast<CameraManager***>(skyline::utils::getRegionAddress(skyline::utils::region::Text) + 0x52b6f00);
        if (pp_camera == nullptr) {
            return nullptr;
        }
        return *pp_camera;
    }
};

static_assert(offsetof(CameraManager, angle_x) == 0xD90);
static_assert(offsetof(CameraManager, roll_offset) == 0xDA4);

void install_camera();