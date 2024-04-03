#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/World.h>

namespace engine {

    class Camera {
    public:

        position pos;
        vec2 rot;
        f32 aspect;

        [[nodiscard]] mat4 getView(position meshPos) const;

        void update();

        explicit Camera(f32 aspect, const position& pos = vec3{0.0f, 0.0f, 0.0f}, vec2 rot = {0, 0});
    };

}
