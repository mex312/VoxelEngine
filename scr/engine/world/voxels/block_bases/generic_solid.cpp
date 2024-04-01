#include "generic_solid.h"
#include <iostream>

namespace engine {
    std::array<u32, 6> generic_solid::getTexes(const voxel &vox) const {
        return texes;
    }

    generic_solid::generic_solid(const std::array<u32, 6>& texes) : block_base(true), texes(texes) {}

    generic_solid::generic_solid(const std::array<game_id, 6> &texes) : block_base(true), texes{
        storage::get_texture_id(texes[0]),
        storage::get_texture_id(texes[1]),
        storage::get_texture_id(texes[2]),
        storage::get_texture_id(texes[3]),
        storage::get_texture_id(texes[4]),
        storage::get_texture_id(texes[5])
    } {
        for(auto& a : texes) {
            std::cout << a.source << " : " << a.name << std::endl;
        }
    }

    generic_solid::~generic_solid() = default;
}