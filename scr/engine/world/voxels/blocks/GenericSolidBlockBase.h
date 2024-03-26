#pragma once

#include "../IBlockBase.h"

namespace engine {

    class GenericSolidBlockBase : public IBlockBase {
        std::array<u32, 6> texes;

    public:
        [[nodiscard]] std::array<u32, 6> getTexes(const voxel& vox) const override;

        explicit GenericSolidBlockBase(const std::array<u32, 6>& texes);

        ~GenericSolidBlockBase() override;
    };

}