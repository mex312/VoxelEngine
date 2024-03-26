#include "./IBlockBase.h"

namespace engine {
    IBlockBase::IBlockBase(bool isVisible) : isVisible(isVisible) {

    }

    IBlockBase::~IBlockBase() = default;
}