#pragma once

#include <VoxelEngine/engine.h>

namespace engine {

    class camera {
    public:

        i64vec3 uPos;
        i64vec3 cPos;
        vec3 fPos;
        vec2 rot;
        f32 aspect;

        [[nodiscard]] mat4 getView(i64vec3 meshCPos) const;

        void update();

        explicit camera(f32 aspect, i64vec3 uPos = {0, 0, 0}, i64vec3 cPos = {0, 0, 0}, f32vec3 fPos = {0, 0, 0}, vec2 rot = {0, 0});
    };

}
