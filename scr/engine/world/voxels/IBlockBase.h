#pragma once

#include "../../engine.h"
#include "./voxel.h"
#include <array>

namespace engine {

    class IBlockBase {
    public:
        const bool isVisible;

        [[nodiscard]] virtual std::array<u32, 6> getTexes(const voxel& vox) const = 0;

        explicit IBlockBase(bool isVisible);
        virtual ~IBlockBase();
    };

}
