#pragma once

#include <VoxelEngine/engine.h>
#include <map>

namespace engine {
    class Chunk;
    class Camera;
    class IChunkGenerator;
    class IBlockBase;

    struct voxel {
        u64 data;
        const IBlockBase* block;
    };

    struct position {
        f32vec3 local; // [0-1)
        i32vec3 block; // [0-63]
        i64vec3 chunk; // any

        position(const f32vec3& local = {0.0f, 0.0f, 0.0f}, const i32vec3& block = {0, 0, 0}, const i64vec3& chunk = {0, 0, 0}) : // NOLINT(*-explicit-constructor)
            local(local), block(block), chunk(chunk) {balance();};

        vec3 single() const;

        position & balance();

        position operator-() const;

        position operator+(const position& other) const;
        position operator+(const vec3& delta) const;

        position& operator+= (const position& other);
        position& operator+= (const vec3& delta);

        position operator-(const position& other) const;
        position operator-(const vec3& delta) const;

        position& operator-= (const position& other);
        position& operator-= (const vec3& delta);
    };

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
        Chunk *getChunk(position pos);
    };

}