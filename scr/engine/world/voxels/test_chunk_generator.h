#pragma once

#include <VoxelEngine/world/voxels/chunk_generator.h>

namespace engine {

    class test_chunk_generator : public chunk_generator {
    public:
        voxel getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) override;
        void fillChunk(chunk* chunk) override;

//        ~TestChunkGenerator() override = default;
    };

}
