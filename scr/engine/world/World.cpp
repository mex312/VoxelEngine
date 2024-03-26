#include "World.h"
#include "./voxels/TestChunkGenerator.h"
#include "./voxels/Chunk.h"

namespace engine {

    static TestChunkGenerator testGen = TestChunkGenerator();

    void World::render(const Camera *cam) {
        for(const auto& p : chunks) { p.second->getMesh()->draw(cam); }
    }

    Chunk *World::getChunk(i64vec3 chunkPos) {
        auto iter = chunks.find(chunkPos);
        if(iter == chunks.end()) {
            return genChunk(chunkPos, &testGen);
        }
        return iter->second;
    }

    Chunk * World::genChunk(i64vec3 chunkPos, IChunkGenerator *gen) {
        auto* chunk = new Chunk(chunkPos, gen);
        chunks.insert({chunkPos, chunk});
        return chunk;
    }

    bool World::_vec_comp::operator()(const i64vec3 &l, const i64vec3 &r) const {
        return l.z == r.z ? (
                l.y == r.y ? (
                        (l.x < r.x)
                ) : (l.y < r.y)
        ) : (l.z < r.z);;
    }
}