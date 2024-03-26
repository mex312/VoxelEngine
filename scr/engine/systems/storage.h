#pragma once
#include "../engine.h"
#include <string>

namespace engine {
    class IBlockBase;
    class TextureAtlas;

    struct game_id {
        std::string source;
        std::string name;

        bool operator==(const game_id& other) const;
    };

    namespace storage {

        IBlockBase* getBlockBase(u32 id);
        IBlockBase* getBlockBase(const game_id& id);

        TextureAtlas* getAtlas();
    }
}