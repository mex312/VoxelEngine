#pragma once

#include <VoxelEngine/engine.h>
#include <vector>

namespace engine {
    class chunk;
    class camera;

    class chunk_mesh {
        friend class chunk;

        struct chunk_vertex {
            u32 data;
            u32 tex;
        };


        u32 vao;
        u32 vbo;
        u32 idb;

        u32 vboCapacity;

        std::vector<chunk_vertex> vertexBuffers[6];

        chunk* chunk;


        void update();

    public:

        explicit chunk_mesh(chunk* chunk);

        ~chunk_mesh();

        void draw(const camera *cam) const noexcept;

    };
}