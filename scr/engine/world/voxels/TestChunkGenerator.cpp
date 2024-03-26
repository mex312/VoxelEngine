#include "TestChunkGenerator.h"
#include "./Chunk.h"
#include "./blocks/GenericSolidBlockBase.h"

namespace engine {
    static GenericSolidBlockBase* bricks = new GenericSolidBlockBase({0, 0, 0, 0, 0, 0});

    voxel TestChunkGenerator::getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) {
        return voxelPos.y < 5 ? voxel{1, nullptr} : voxel{0, nullptr};
    }

    void TestChunkGenerator::fillChunk(Chunk *chunk) {
        for (u8 z = 0; z < CHUNK_SIDE; ++z)
            for (u8 y = 0; y < 5; ++y)
                for (u8 x = 0; x < CHUNK_SIDE; ++x)
                    chunk->set({x, y, z}, {1, bricks});
    }
}