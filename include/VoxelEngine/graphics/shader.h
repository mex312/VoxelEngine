#pragma once

#include <VoxelEngine/engine.h>
#include <string>

namespace engine {
    class Shader {
    public:
        u32 id;

        explicit Shader(u32 id);

        ~Shader();

        void use() const;

        static Shader *loadShader(const std::string &vertexSource, const std::string &fragmentSource);
    };
}