#pragma once

#include <VoxelEngine/engine.h>

namespace engine {
    class block_base;

    struct voxel {
        u64 data;
        const block_base* block;
    };
}