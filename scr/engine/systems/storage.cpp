#include <VoxelEngine/systems/storage.h>
#include <VoxelEngine/systems/files.h>
#include <VoxelEngine/graphics/texture_atlas.h>
#include "../../utils/systems_internal.h"
#include "../../external/stb_image.h"
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

template <>
struct std::hash<engine::game_id> {
    std::size_t operator()(const engine::game_id& id) const {
        return hash<string>()(id.source) ^ hash<string>()(id.name);
    }
};


namespace engine::storage {

    static std::vector<const IBlockBase*> _blockBases;
    static std::unordered_map<game_id, u32> _blockBaseIDs;
    static std::unordered_map<game_id, u32> _textureIDs;
    static texture_atlas* _atlas;


    void init() {
        auto textures = files::get_all_files("../res/textures");
        (void)std::remove_if(textures.begin(), textures.end(), [](const std::filesystem::path& f) {return !f.generic_string().ends_with(".png");});

        u8* texBuffer = new u8[textures.size() << 10];
        u8* texBufferPtr = texBuffer;
        u32 texI = 0;


        auto i = textures.begin();
        for(; i != textures.end(); ++i) {
            if(i->filename().generic_string() == (std::string)"null.png") {
                i32 x, y, c;
                u8* temp = stbi_load(i->generic_string().c_str(), &x, &y, &c, STBI_rgb_alpha);
                if (x == 16 && y == 16) {
                    memcpy(texBufferPtr, temp, 1 << 10);
                    texBufferPtr += 1 << 10;
                    std::string filename = i->filename().generic_string();
                    (void)_textureIDs.emplace(game_id{"base", filename.substr(0, filename.find_last_of('.'))}, texI);
                    ++texI;
                }
                delete[] temp;
                break;
            }
        }
        if(i != textures.end()) textures.erase(i);

        for(auto& t : textures) {
            i32 x, y, c;
            u8* temp = stbi_load(t.generic_string().c_str(), &x, &y, &c, STBI_rgb_alpha);
            if (x == 16 && y == 16) {
                memcpy(texBufferPtr, temp, 1 << 10);
                texBufferPtr += 1 << 10;
                std::string filename = t.filename().generic_string();
                (void)_textureIDs.emplace(game_id{"base", filename.substr(0, filename.find_last_of('.'))}, texI);
                ++texI;
            }
            delete[] temp;
        }

        _atlas = new texture_atlas(texBuffer, (texBufferPtr - texBuffer) >> 2, 16, 16, texture_atlas::RGBA_U8);

        delete[] texBuffer;
    }


    const IBlockBase * get_block_base(u32 id) {
        if(id >= _blockBases.size()) return nullptr;
        return _blockBases[id];
    }

    const IBlockBase * get_block_base(const game_id& id) {
        auto iter = _blockBaseIDs.find(id);
        if(iter == _blockBaseIDs.end()) return nullptr;
        return _blockBases[iter->second];
    }

    const texture_atlas * get_atlas() {
        return _atlas;
    }

    void reg_block_base(const IBlockBase *blockBase, const game_id &id) {
        _blockBaseIDs.emplace(id, _blockBases.size());
        _blockBases.push_back(blockBase);
    }

    u32 get_texture_id(const game_id &id) {
        auto iter = _textureIDs.find(id);
        if(iter == _textureIDs.end()) return 0; else return iter->second;
    }
}

bool engine::game_id::operator==(const engine::game_id &other) const {
    return source == other.source && name == other.name;
}

engine::game_id::game_id(const std::string &gluedID) {
    u32 column = gluedID.find_last_of(':');
    source = gluedID.substr(0, column);
    name = gluedID.substr(column + 1, gluedID.length());
}

engine::game_id::game_id(const char *gluedID) {
    std::string str = gluedID;
    u32 column = str.find_last_of(':');
    source = str.substr(0, column);
    name = str.substr(column + 1, str.length());
}

engine::game_id::game_id(std::string source, std::string name) : source(std::move(source)), name(std::move(name)) {}
