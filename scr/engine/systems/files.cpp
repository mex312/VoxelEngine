#include <VoxelEngine/systems/files.h>
#include <fstream>
#include <algorithm>

namespace engine::files {
    bool read_bytes(const std::filesystem::path& filename, u8 *data, size_t size) {
        std::ifstream fin(filename, std::ios_base::binary);
        if (!fin.is_open()) return false;

        fin.read((char *) data, size);
        fin.close();

        return true;
    }

    u8 *read_bytes(const std::filesystem::path& filename, size_t &length) {
        std::ifstream fin(filename, std::ios::binary);
        if (!fin.is_open()) return nullptr;

        fin.seekg(0, std::ios_base::end);
        length = fin.tellg();
        fin.seekg(0, std::ios_base::beg);

        u8 *data = new u8[length];
        fin.read((char *) data, (i64)length);
        fin.close();

        return data;
    }

    std::string read_string(const std::filesystem::path& filename) {
        size_t size;
        u8 *data = read_bytes(filename, size);

        if (data == nullptr) throw std::runtime_error("Could not read file '" + filename.string() + "'");

        std::string out((char *) data, size);
        delete[] data;
        return out;
    }

    std::vector<std::filesystem::path> get_all_files(const std::filesystem::path &dirname) {
        if(!is_directory(dirname)) throw std::runtime_error("'" + dirname.generic_string() + "' is not a directory");
        auto iter = std::filesystem::directory_iterator(dirname);
        std::vector<std::filesystem::path> out;
        std::copy_if(begin(iter), end(iter), std::back_inserter(out), [](const std::filesystem::path& p){return !is_directory(p);});
        return out;
    }
}