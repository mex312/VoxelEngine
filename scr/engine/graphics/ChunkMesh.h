#pragma once
#include "../engine.h"

#include <vector>

namespace engine {
    class Chunk;
    class Camera;

    class ChunkMesh {
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

        Chunk* chunk;


        void update();

    public:

        explicit ChunkMesh(Chunk* chunk);

        ~ChunkMesh();

        void draw(const Camera *cam) const noexcept;

    };
}