#pragma once

#include <VoxelEngine/engine.h>
#include <string>

namespace engine {
    class IBlockBase;
    class texture_atlas;

    struct game_id {
        std::string source;
        std::string name;

        bool operator==(const game_id& other) const;

        game_id(const std::string& gluedID);
        game_id(const char* gluedID);
        game_id(std::string  source, std::string  name);
    };

    namespace storage {

        const IBlockBase * get_block_base(u32 id);
        const IBlockBase * get_block_base(const game_id& id);
        u32 get_texture_id(const game_id& id);

        void reg_block_base(const IBlockBase *blockBase, const game_id &id);

        const texture_atlas * get_atlas();
    }
}