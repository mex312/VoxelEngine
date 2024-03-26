#include "files.h"
#include <fstream>

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
        fin.read((char *) data, length);
        fin.close();

        return data;
    }

    std::string read_string(const std::filesystem::path& filename) {
        size_t size;
        u8 *data = read_bytes(filename, size);

        if (data == nullptr) throw std::runtime_error("could not read file '" + filename.string() + "'");

        std::string out((char *) data, size);
        delete[] data;
        return out;
    }
}