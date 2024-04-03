#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/World.h>

namespace engine {
    struct voxel_collision {
        position voxPos = {};
        position collPos = {};
        voxel vox = {};
    };

    class VoxelRay {
    public:

        World* world;

        position start;
        position end;

        voxel_collision * cast() const; // nullable
    };
}
