#pragma once

#include <VoxelEngine/world/World.h>

namespace engine {
    class Chunk;

    class IChunkGenerator {
    public:
        virtual voxel getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) = 0;
        virtual void fillChunk(Chunk* chunk) = 0;

//        virtual ~IChunkGenerator() = 0;
    };

}
