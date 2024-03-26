#pragma once

#include "../IBlockBase.h"

namespace engine {

    class AirBlockBase : public IBlockBase {
    public:
        [[nodiscard]] std::array<u32, 6> getTexes(const voxel& vox) const override;

        AirBlockBase();
        ~AirBlockBase() override;
    };

}
