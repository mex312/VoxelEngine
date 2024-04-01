#pragma once

#include <VoxelEngine/world/voxels/block_base.h>
#include <VoxelEngine/systems/storage.h>

namespace engine {

    class generic_solid : public block_base {
        std::array<u32, 6> texes;

    public:
        [[nodiscard]] std::array<u32, 6> getTexes(const voxel& vox) const override;

        explicit generic_solid(const std::array<u32, 6>& texes);
        explicit generic_solid(const std::array<game_id, 6>& texes);

        ~generic_solid() override;
    };

}