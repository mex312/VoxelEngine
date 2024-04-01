#pragma once

#include <VoxelEngine/world/voxels/voxel.h>

namespace engine {
    class chunk;

    class chunk_generator {
    public:
        virtual voxel getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) = 0;
        virtual void fillChunk(chunk* chunk) = 0;

//        virtual ~IChunkGenerator() = 0;
    };

}
