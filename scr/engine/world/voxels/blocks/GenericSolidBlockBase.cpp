#include "GenericSolidBlockBase.h"

namespace engine {
    std::array<u32, 6> GenericSolidBlockBase::getTexes(const voxel &vox) const {
        return texes;
    }

    GenericSolidBlockBase::GenericSolidBlockBase(const std::array<u32, 6>& texes) : IBlockBase(true), texes(texes) {}

    GenericSolidBlockBase::~GenericSolidBlockBase() = default;
}