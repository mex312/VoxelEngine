#include <VoxelEngine/world/World.h>
#include <VoxelEngine/world/voxels/Chunk.h>
#include "./voxels/test_chunk_generator.h"

namespace engine {

    static test_chunk_generator testGen = test_chunk_generator();

    void World::render(const Camera *cam) {
        for(const auto& p : chunks) { p.second->getMesh()->draw(cam); }
    }

    Chunk *World::getChunk(i64vec3 chunkPos) const {
        auto iter = chunks.find(chunkPos);
        if(iter == chunks.end()) {
            return nullptr;
        }
        return iter->second;
    }

    Chunk * World::genChunk(i64vec3 chunkPos, IChunkGenerator *gen) {
        auto* _chunk = new Chunk(chunkPos, gen);
        chunks.insert({chunkPos, _chunk});
        return _chunk;
    }

    Chunk *World::getChunk(position pos) const {
        return getChunk(pos.chunk);
    }

    bool World::_vec_comp::operator()(const i64vec3 &l, const i64vec3 &r) const {
        return l.z == r.z ? (
                l.y == r.y ? (
                        (l.x < r.x)
                ) : (l.y < r.y)
        ) : (l.z < r.z);;
    }

    position & position::balance() {
        i32vec3 fl = glm::floor(local);
        local -= fl;
        block += fl;
        chunk += block >> 6;
        block &= 0b111111;

        return *this;
    }

    position position::operator+(const position &other) const {
        return {local + other.local, block + other.block, chunk + other.chunk};
    }

    position position::operator+(const vec3 &delta) const {
        return {local + delta, block, chunk};
    }

    position position::operator-(const position &other) const {
        return {local - other.local, block - other.block, chunk - other.chunk};
    }

    position position::operator-(const vec3 &delta) const {
        return {local - delta, block, chunk};
    }

    vec3 position::single() const {
        return (vec3)chunk * 64.0f + (vec3)block + local;
    }

    position &position::operator+=(const position &other) {
        local += other.local;
        block += other.block;
        chunk += other.chunk;
        return balance();
    }

    position &position::operator+=(const vec3 &delta) {
        local += delta;
        return balance();
    }

    position &position::operator-=(const position &other) {
        local -= other.local;
        block -= other.block;
        chunk -= other.chunk;
        return balance();
    }

    position &position::operator-=(const vec3 &delta) {
        local -= delta;
        return balance();
    }

    position position::operator-() const {
        return {-local, -block, -chunk};
    }
}