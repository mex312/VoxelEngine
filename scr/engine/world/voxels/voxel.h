#pragma once

#include "../../engine.h"

namespace engine {
    class IBlockBase;

    struct voxel {
        u64 data;
        IBlockBase* block;
    };
}