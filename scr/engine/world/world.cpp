#include <VoxelEngine/world/world.h>
#include <VoxelEngine/world/voxels/chunk.h>
#include "./voxels/test_chunk_generator.h"

namespace engine {

    static test_chunk_generator testGen = test_chunk_generator();

    void world::render(const camera *cam) {
        for(const auto& p : chunks) { p.second->getMesh()->draw(cam); }
    }

    chunk *world::getChunk(i64vec3 chunkPos) {
        auto iter = chunks.find(chunkPos);
        if(iter == chunks.end()) {
            return genChunk(chunkPos, &testGen);
        }
        return iter->second;
    }

    chunk * world::genChunk(i64vec3 chunkPos, chunk_generator *gen) {
        auto* chunk = new chunk(chunkPos, gen);
        chunks.insert({chunkPos, chunk});
        return chunk;
    }

    bool world::_vec_comp::operator()(const i64vec3 &l, const i64vec3 &r) const {
        return l.z == r.z ? (
                l.y == r.y ? (
                        (l.x < r.x)
                ) : (l.y < r.y)
        ) : (l.z < r.z);;
    }
}