#pragma once

#include <VoxelEngine/engine.h>
#include <vector>

namespace engine {
    class Chunk;
    class Camera;

    class chunk_mesh {
        friend class Chunk;

        struct chunk_vertex {
            u32 data;
            u32 tex;
        };


        u32 vao;
        u32 vbo;
        u32 idb;

        u32 vboCapacity;

        std::vector<chunk_vertex> vertexBuffers[6];

        Chunk* _chunk;


        void update();

    public:

        explicit chunk_mesh(Chunk* _chunk);

        ~chunk_mesh();

        void draw(const Camera *cam) const noexcept;

    };
}