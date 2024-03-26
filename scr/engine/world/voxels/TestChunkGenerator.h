#pragma once

#include "./IChunkGenerator.h"

namespace engine {

    class TestChunkGenerator : public IChunkGenerator {
    public:
        voxel getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) override;
        void fillChunk(Chunk* chunk) override;

//        ~TestChunkGenerator() override = default;
    };

}
