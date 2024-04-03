#pragma once

#include <VoxelEngine/world/voxels/IChunkGenerator.h>

namespace engine {

    class test_chunk_generator : public IChunkGenerator {
    public:
        voxel getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) override;
        void fillChunk(Chunk* chunk) override;

//        ~TestChunkGenerator() override = default;
    };

}
