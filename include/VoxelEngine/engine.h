#pragma once

#include <glm.hpp>
#include <gtx/quaternion.hpp>

namespace engine {
    using namespace glm;

    enum Side {
        // z+
        SOUTH,
        // x-
        WEST,
        // z-
        NORTH,
        // x+
        EAST,
        // y+
        UP,
        // y-
        DOWN,
    };
}