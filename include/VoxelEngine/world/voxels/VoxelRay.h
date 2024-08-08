#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/World.h>
#include <memory>

namespace engine {
    struct voxel_collision {
        position voxPos = {};
        position collPos = {};
        voxel vox = {};
        Side side = NORTH;
    };

    class VoxelRay {
    public:

        const World* const world;

        const position start;
        const position end;

        [[nodiscard]] std::unique_ptr<voxel_collision> cast() const; // nullable

        VoxelRay(World* world, const position& start, const position& end);
    };
}
