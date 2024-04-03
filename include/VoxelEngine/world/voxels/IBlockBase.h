#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/World.h>
#include <array>

namespace engine {

    class IBlockBase {
    public:
        const bool isVisible;
        const bool isSolid;

        [[nodiscard]] virtual std::array<u32, 6> getTexes(const voxel& vox) const = 0;

        explicit IBlockBase(bool isVisible, bool isSolid);
        virtual ~IBlockBase();
    };

}
