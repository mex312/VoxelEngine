#include "./storage.h"

#include <unordered_map>
#include <vector>
#include "../../utils/systems_internal.h"
#include "../graphics/TextureAtlas.h"
#include "../../external/stb_image.h"

template <>
struct std::hash<engine::game_id> {
    std::size_t operator()(const engine::game_id& id) const {
        return hash<string>()(id.source) ^ hash<string>()(id.name);
    }
};


namespace engine::storage {

    static std::vector<IBlockBase*> _blockBases;
    static std::unordered_map<game_id, u32> _blockBaseIds;
    static TextureAtlas* atlas;


    void init() {
        u64 trash;

        atlas = new TextureAtlas(stbi_load("../res/textures/stone_bricks.png", (i32*)&trash, (i32*)&trash, (i32*)&trash, STBI_rgb_alpha), 256, 16, 16, TextureAtlas::RGBA_U8);
    }


    IBlockBase *getBlockBase(u32 id) {
        if(id >= _blockBases.size()) return nullptr;
        return _blockBases[id];
    }

    IBlockBase *getBlockBase(const game_id& id) {
        auto iter = _blockBaseIds.find(id);
        if(iter == _blockBaseIds.end()) return nullptr;
        return _blockBases[iter->second];
    }

    TextureAtlas* getAtlas() {
        return atlas;
    }
}

bool engine::game_id::operator==(const engine::game_id &other) const {
    return source == other.source && name == other.name;
}