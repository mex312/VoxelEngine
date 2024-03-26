#include "AirBlockBase.h"

namespace engine {

    std::array<u32, 6> AirBlockBase::getTexes(const voxel &vox) const {
        return {0, 0, 0, 0, 0, 0};
    }

    AirBlockBase::AirBlockBase() : IBlockBase(false) {}

    AirBlockBase::~AirBlockBase() = default;
}