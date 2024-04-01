#pragma once

#include <VoxelEngine/engine.h>
#include <map>

namespace engine {
    class chunk;
    class camera;
    class chunk_generator;

    class world {
        struct _vec_comp {
            bool operator()(const i64vec3 &l, const i64vec3 &r) const;
        };

        std::map<i64vec3, chunk *, _vec_comp> chunks;

    public:

        void render(const camera *cam);

        void update();

        chunk *genChunk(i64vec3 chunkPos, chunk_generator *gen);

        chunk *getChunk(i64vec3 chunkPos);
    };

}