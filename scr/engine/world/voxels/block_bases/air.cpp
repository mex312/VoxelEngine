#include "air.h"

namespace engine {

    std::array<u32, 6> air::getTexes(const voxel &vox) const {
        return {0, 0, 0, 0, 0, 0};
    }

    air::air() : IBlockBase(false, false) {}

    air::~air() = default;
}