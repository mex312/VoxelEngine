#pragma once

#include <VoxelEngine/world/voxels/IBlockBase.h>

namespace engine {

    class air : public IBlockBase {
    public:
        [[nodiscard]] std::array<u32, 6> getTexes(const voxel& vox) const override;

        air();
        ~air() override;
    };

}
