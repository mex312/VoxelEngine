#pragma once

#include <VoxelEngine/engine.h>
#include <string>
#include <filesystem>
#include <vector>

namespace engine {
    namespace json {
        class JObject;
    }

    namespace files {
        extern bool read_bytes(const std::filesystem::path& filename, u8 *data, size_t size);

        extern u8 *read_bytes(const std::filesystem::path& filename, size_t &length);

        extern std::string read_string(const std::filesystem::path& filename);

        extern json::JObject *read_json(const std::filesystem::path& filename);

        extern std::vector<std::filesystem::path> get_all_files(const std::filesystem::path& dirname);
    }
}