#pragma once

#include "../engine.h"
#include <map>

namespace engine {
    class Chunk;
    class Camera;
    class IChunkGenerator;

    class World {
        struct _vec_comp {
            bool operator()(const i64vec3 &l, const i64vec3 &r) const;
        };

        std::map<i64vec3, Chunk *, _vec_comp> chunks;

    public:

        void render(const Camera *cam);

        void update();

        Chunk *genChunk(i64vec3 chunkPos, IChunkGenerator *gen);

        Chunk *getChunk(i64vec3 chunkPos);
    };

}