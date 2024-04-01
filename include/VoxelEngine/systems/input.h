#pragma once

#include <VoxelEngine/engine.h>
#include <GLFW/glfw3.h>

namespace engine::input {
    constexpr u64 KEYS_BUFFER_SIZE = 1056;
    constexpr u64 MOUSE_BUTTONS_OFFSET = 1024;


    bool pressed(i32 key);

    bool just_pressed(i32 key);

    glm::vec2 mouse_pos();

    glm::vec2 mouse_delta();
}
