#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/voxels/voxel.h>
#include <array>

namespace engine {

    class block_base {
    public:
        const bool isVisible;

        [[nodiscard]] virtual std::array<u32, 6> getTexes(const voxel& vox) const = 0;

        explicit block_base(bool isVisible);
        virtual ~block_base();
    };

}
