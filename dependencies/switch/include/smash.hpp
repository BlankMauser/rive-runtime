#pragma once
#include <arm_neon.h>
#include <cmath>
#include "utils.hpp"

struct lua_State;

namespace usr
{
    struct CameraRange
    {
        float left, right, top, bottom;
    };
}

namespace phx
{
    struct Vector2f
    {
        float x, y;
    };
    struct Vector3f
    {
        float x, y, z;
    };
    struct Vector4f
    {
        float x, y, z, w;
    };
    struct Hash40
    {
        uint64_t hash;
    };

    static_assert(sizeof(Vector2f) == 0x8);
    static_assert(sizeof(Vector3f) == 0xC);
    static_assert(sizeof(Vector4f) == 0x10);
    static_assert(sizeof(Hash40) == sizeof(uint64_t));
}

namespace usr
{
    struct Matrix4
    {
        phx::Vector4f vecs[4];
    };
}

namespace lib
{
    struct L2CTable;

    struct L2CInnerFunctionBase
    {
        uint64_t _x0;
        uint32_t ref_count;
    };

    struct L2CValue
    {
        enum Type : uint32_t
        {
            Void,
            Bool,
            Int,
            Num,
            Pointer,
            Table,
            InnerFunc,
            Hash,
            String
        };

        Type type;
        uint32_t _x4;
        union
        {
            uint64_t raw;
            float raw_float;
            void *raw_ptr;
        } inner;
        uint8_t _x10; // ?

        L2CValue();
        L2CValue(const L2CValue &other);
        L2CValue(bool);
        L2CValue(int32_t);
        L2CValue(uint32_t);
        L2CValue(int64_t);
        L2CValue(uint64_t);
        L2CValue(float);
        L2CValue(void *);
        L2CValue(L2CTable *);
        L2CValue(L2CInnerFunctionBase *);
        L2CValue(phx::Hash40);
        L2CValue(const char *);
        ~L2CValue();

        bool as_bool() const;
        phx::Hash40 as_hash() const;
        L2CInnerFunctionBase *as_inner_function() const;
        uint64_t as_integer() const;
        float as_number() const;
        void *as_pointer() const;
        const char *as_string() const;
        L2CTable *as_table() const;
    };

    struct L2CAgent
    {
        void **vtable;
        lua_State *lua_state_agent;
        void *func_hash_list;
        uint64_t hash_count;
        uint64_t _x20;
        uint64_t _x28;
        uint64_t _x30;
        uint64_t _x38;
        lua_State *lua_state_agent_base;

        inline L2CAgent(lua_State *lua_state)
            : vtable(nullptr), lua_state_agent(lua_state), func_hash_list(nullptr), hash_count(0),
              _x20(0), _x28(0), _x30(0), _x38(0), lua_state_agent_base(nullptr) {}

        L2CValue pop_lua_stack(int);
    };

}

namespace app
{
    struct Article;
    struct AttackData;
    struct BattleObjectModuleAccessor;
    struct BattleObject
    {
        void **vtable;
        u32 id;
        u32 kind;
        u64 _x10;
        u64 agent_hash;
        BattleObjectModuleAccessor *accessor;
    };
    struct Fighter;
    struct GrabData;
    struct SearchData;

    namespace smashball
    {
        bool is_training_mode();
    }

    namespace sv_animcmd
    {
        void ATTACK(lua_State *state);
        void CATCH(lua_State *state);
        void SEARCH(lua_State *state);
    }

    namespace sv_camera_manager
    {
        float32x2_t world_to_screen(const phx::Vector3f &global_pos, bool direct_map);
        usr::CameraRange camera_range();
        void dead_range(lua_State *);
        float get_fov();
        float32x4_t get_pos();
        float32x4_t inverse_mtx_mul(float x, float y, float z);
        float32x4_t inverse_rot();
    }

    namespace fighter
    {
        uint32_t get_id_from_entry_id(int entry_id);
    }

    namespace lua_bind
    {
        uint32_t Article__get_battle_object_id_impl(Article *);
        void *ArticleModule__get_article_impl(BattleObjectModuleAccessor *, int);
        int ArticleModule__get_active_num_impl(BattleObjectModuleAccessor *, int);
        AttackData *AttackModule__attack_data_impl(BattleObjectModuleAccessor *, int, bool);
        bool AttackModule__is_attack_impl(BattleObjectModuleAccessor *, int, bool);
        void AttackModule__clear_impl(BattleObjectModuleAccessor *, int, bool);
        void AttackModule__clear_all_impl(BattleObjectModuleAccessor *);
        bool ControlModule__check_button_on_impl(BattleObjectModuleAccessor *, int);
        float ControlModule__get_stick_x_impl(BattleObjectModuleAccessor *);
        float ControlModule__get_stick_y_impl(BattleObjectModuleAccessor *);
        bool GrabModule__is_grab_impl(BattleObjectModuleAccessor *, int id);
        void GrabModule__clear_impl(BattleObjectModuleAccessor *, int);
        void GrabModule__clear_all_impl(BattleObjectModuleAccessor *);
        float KineticModule__get_sum_speed_impl(BattleObjectModuleAccessor *, int);
        phx::Vector3f ModelModule__joint_global_axis_impl(BattleObjectModuleAccessor *, phx::Hash40, int, bool);
        void ModelModule__joint_global_position_with_offset_impl(BattleObjectModuleAccessor *, phx::Hash40, const phx::Vector3f &, phx::Vector3f &, bool);
        float ModelModule__scale_impl(BattleObjectModuleAccessor *);
        void ModelModule__set_visibility_impl(BattleObjectModuleAccessor *, bool);
        bool MotionModule__clear_joint_srt_impl(BattleObjectModuleAccessor *, phx::Hash40);
        float MotionModule__frame_impl(BattleObjectModuleAccessor *);
        void MotionModule__joint_local_tra_impl(BattleObjectModuleAccessor *, phx::Hash40, bool, phx::Vector3f &);
        void MotionModule__joint_local_rotation_impl(BattleObjectModuleAccessor *, phx::Hash40, phx::Vector3f &);
        float MotionModule__rate_impl(BattleObjectModuleAccessor *);
        float MotionModule__trans_joint_scale_impl(BattleObjectModuleAccessor *);
        float PostureModule__lr_impl(BattleObjectModuleAccessor *);
        float PostureModule__pos_x_impl(BattleObjectModuleAccessor *);
        float PostureModule__scale_impl(BattleObjectModuleAccessor *);
        float PostureModule__base_scale_impl(BattleObjectModuleAccessor *);
        void PostureModule__set_pos_impl(BattleObjectModuleAccessor *, const phx::Vector3f &);
        bool SearchModule__is_search_impl(BattleObjectModuleAccessor *, int id);
        void SearchModule__clear_impl(BattleObjectModuleAccessor *, int);
        void SearchModule__clear_all_impl(BattleObjectModuleAccessor *);
        int StatusModule__status_kind_impl(BattleObjectModuleAccessor *);
        int WorkModule__get_int_impl(BattleObjectModuleAccessor *, int);
        float WorkModule__get_float_impl(BattleObjectModuleAccessor *, int);
        bool WorkModule__is_flag_impl(BattleObjectModuleAccessor *, int);
        bool VisibilityModule__is_visible_impl(BattleObjectModuleAccessor *);

        namespace ArticleModule
        {
            inline void *get_article_impl(BattleObjectModuleAccessor *boma, int article)
            {
                return ArticleModule__get_article_impl(boma, article);
            }
        }

        namespace AttackModule
        {
            inline AttackData *attack_data_impl(BattleObjectModuleAccessor *boma, int id, bool unk)
            {
                return AttackModule__attack_data_impl(boma, id, unk);
            }
            inline bool is_attack_impl(BattleObjectModuleAccessor *boma, int hitbox_id, bool unk)
            {
                return AttackModule__is_attack_impl(boma, hitbox_id, unk);
            }
            inline void clear_impl(BattleObjectModuleAccessor *boma, int id, bool unk)
            {
                AttackModule__clear_impl(boma, id, unk);
            }
            inline void clear_all_impl(BattleObjectModuleAccessor *boma)
            {
                AttackModule__clear_all_impl(boma);
            }
        }

        namespace ControlModule
        {
            inline bool check_button_on_impl(BattleObjectModuleAccessor *boma, int flag)
            {
                return ControlModule__check_button_on_impl(boma, flag);
            }
            inline bool get_stick_x_impl(BattleObjectModuleAccessor *boma)
            {
                return ControlModule__get_stick_x_impl(boma);
            }
            inline bool get_stick_y_impl(BattleObjectModuleAccessor *boma)
            {
                return ControlModule__get_stick_y_impl(boma);
            }
        }

        namespace GrabModule
        {
            inline bool is_grab_impl(BattleObjectModuleAccessor *boma, int id)
            {
                return GrabModule__is_grab_impl(boma, id);
            }
            inline void clear_impl(BattleObjectModuleAccessor *boma, int id)
            {
                GrabModule__clear_impl(boma, id);
            }
            inline void clear_all_impl(BattleObjectModuleAccessor *boma)
            {
                GrabModule__clear_all_impl(boma);
            }
            inline GrabData *grab_data_impl(BattleObjectModuleAccessor *boma, int id)
            {
                uint64_t *grab_module = ((uint64_t **)boma)[0x158 / 0x8];
                GrabData *(*impl)(uint64_t *, int) = *(GrabData * (**)(uint64_t *, int))(*grab_module + 0xA0);
                return impl(grab_module, id);
            }
        }

        namespace ModelModule
        {
            inline void joint_global_position_with_offset_impl(BattleObjectModuleAccessor *boma, phx::Hash40 joint, const phx::Vector3f &offset, phx::Vector3f &out, bool unk)
            {
                uint64_t model_module = *(uint64_t *)((uint64_t)boma + 0x78);
                auto callable = reinterpret_cast<phx::Vector3f (*)(void *, phx::Hash40, const phx::Vector3f &, phx::Vector3f &, bool)>(*(uint64_t *)(*(uint64_t *)model_module + 0x160));
                callable((void *)model_module, joint, offset, out, true);
            }

            inline phx::Vector3f joint_global_axis_impl(BattleObjectModuleAccessor *boma, phx::Hash40 joint, int unk, bool unk2)
            {
                return ModelModule__joint_global_axis_impl(boma, joint, unk, unk2);
            }

            inline float scale_impl(BattleObjectModuleAccessor *boma)
            {
                return ModelModule__scale_impl(boma);
            }

            inline void set_visibility_impl(BattleObjectModuleAccessor *boma, bool enable)
            {
                ModelModule__set_visibility_impl(boma, enable);
            }
        }

        namespace MotionModule
        {
            inline bool clear_joint_srt_impl(BattleObjectModuleAccessor *boma, phx::Hash40 joint)
            {
                return MotionModule__clear_joint_srt_impl(boma, joint);
            }
            inline float frame_impl(BattleObjectModuleAccessor *boma)
            {
                return MotionModule__frame_impl(boma);
            }
            inline void joint_local_tra_impl(BattleObjectModuleAccessor *boma, phx::Hash40 joint, bool unk, phx::Vector3f &out)
            {
                MotionModule__joint_local_tra_impl(boma, joint, unk, out);
            }
            inline void joint_local_rotation_impl(BattleObjectModuleAccessor *boma, phx::Hash40 joint, phx::Vector3f &out)
            {
                MotionModule__joint_local_rotation_impl(boma, joint, out);
            }
            inline float rate_impl(BattleObjectModuleAccessor *boma)
            {
                return MotionModule__rate_impl(boma);
            }
            inline float trans_joint_scale_impl(BattleObjectModuleAccessor *boma)
            {
                return MotionModule__trans_joint_scale_impl(boma);
            }
        }

        namespace PostureModule
        {
            inline float lr_impl(BattleObjectModuleAccessor *boma)
            {
                return PostureModule__lr_impl(boma);
            }
            inline float pos_x_impl(BattleObjectModuleAccessor *boma)
            {
                return PostureModule__pos_x_impl(boma);
            }
            inline float scale_impl(BattleObjectModuleAccessor *boma)
            {
                return PostureModule__scale_impl(boma);
            }
            inline float base_scale_impl(BattleObjectModuleAccessor *boma)
            {
                return PostureModule__base_scale_impl(boma);
            }
            inline void set_pos_impl(BattleObjectModuleAccessor *boma, const phx::Vector3f &pos)
            {
                PostureModule__set_pos_impl(boma, pos);
            }
        }

        namespace SearchModule
        {
            inline bool is_search_impl(BattleObjectModuleAccessor *boma, int id)
            {
                return SearchModule__is_search_impl(boma, id);
            }
            inline void clear_impl(BattleObjectModuleAccessor *boma, int id)
            {
                SearchModule__clear_impl(boma, id);
            }
            inline void clear_all_impl(BattleObjectModuleAccessor *boma)
            {
                SearchModule__clear_all_impl(boma);
            }
            inline SearchData *search_data_impl(BattleObjectModuleAccessor *boma, int id)
            {
                uint64_t *search_module = ((uint64_t **)boma)[0xE0 / 0x8];
                SearchData *(*impl)(uint64_t *, int) = *(SearchData * (**)(uint64_t *, int))(*search_module + 0xA0);
                return impl(search_module, id);
            }
        }

        namespace StatusModule
        {
            inline int status_kind_impl(BattleObjectModuleAccessor *boma)
            {
                return StatusModule__status_kind_impl(boma);
            }
        }

        namespace WorkModule
        {
            inline int get_int_impl(BattleObjectModuleAccessor *boma, int req)
            {
                return WorkModule__get_int_impl(boma, req);
            }
            inline float get_float_impl(BattleObjectModuleAccessor *boma, int req)
            {
                return WorkModule__get_float_impl(boma, req);
            }
            inline bool is_flag_impl(BattleObjectModuleAccessor *boma, int req)
            {
                return WorkModule__is_flag_impl(boma, req);
            }
        }

        namespace VisibilityModule
        {
            inline bool is_visible_impl(BattleObjectModuleAccessor *boma)
            {
                return VisibilityModule__is_visible_impl(boma);
            }
        }
    }

    namespace sv_battle_object
    {
        bool is_active(uint32_t id);
        uint32_t get_founder_id(uint32_t id);
        BattleObjectModuleAccessor *module_accessor(uint32_t id);
    }

    namespace sv_system
    {
        app::BattleObject *battle_object(lua_State *);
        app::BattleObjectModuleAccessor *battle_object_module_accessor(lua_State *);
        uint32_t battle_object_category(lua_State *);
        uint32_t battle_object_kind(lua_State *);
    }

    namespace sv_debug_draw
    {
        void draw_circle(const phx::Vector2f &center, float radius, int num_frames);
        void set_draw_color(float r, float g, float b, float a);
        void draw_line(const phx::Vector2f &a, const phx::Vector2f &b, int num_frames);
        void draw_text(const phx::Vector2f &origin, const char *text, int num_frames);
    }

    namespace utility
    {
        uint32_t get_category(uint32_t boid);
    }

    struct AttackData
    {
        f32 x, y, z;
        u32 _xC;
        f32 x2, y2, z2;
        u32 _x1C;
        f32 power;
        f32 size;
        int angle;
        int r_eff;
        int r_fix;
        int r_add;
        f32 slip;
        f32 stop_frame;
        f32 stop_delay;
        phx::Hash40 node;
        u16 check_type;
        u16 target_situation;
        u16 target_lr;
        u16 target_part;
        phx::Hash40 attr;
        u16 sound_level;
        u16 sound_attr;
        u8 _x60[0x13];
        u8 is_capsule;
        // ...
    };

    struct GrabData
    {
        f32 x, y, z;
        u32 _xC;
        f32 x2, y2, z2;
        u32 _x1C;
        f32 size;
        u32 _x24;
        phx::Hash40 node;
        u16 status_kind;
        u16 _x32;
        u16 situation_kind;
        u16 _x36;
        u8 is_capsule;
        // ...
    };

    struct SearchData
    {
        f32 x, y, z;
        u32 _xC;
        f32 x2, y2, z2;
        u32 _x1C;
        f32 size;
        u32 _x24;
        phx::Hash40 node;
        u8 collision;
        u8 _x31;
        u16 collision_category;
        u8 ground_air;
        u8 collision_parts;
        u8 hit_status;
        u8 _x37;
        u16 _x38;
        bool _x3A;
        u8 is_capsule;
        // ...
    };
}