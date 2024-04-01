#pragma once

#include <VoxelEngine/world/voxels/block_base.h>

namespace engine {

    class air : public block_base {
    public:
        [[nodiscard]] std::array<u32, 6> getTexes(const voxel& vox) const override;

        air();
        ~air() override;
    };

}
