#include <VoxelEngine/world/voxels/IBlockBase.h>

namespace engine {
    IBlockBase::IBlockBase(bool isVisible, bool isSolid) : isVisible(isVisible), isSolid(isSolid) {

    }

    IBlockBase::~IBlockBase() = default;
}