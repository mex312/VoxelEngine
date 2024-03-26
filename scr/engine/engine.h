#pragma once

#include <glm.hpp>

namespace engine {
    using namespace glm;

    enum side {
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