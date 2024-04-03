#include <VoxelEngine/world/voxels/Chunk.h>
#include <VoxelEngine/systems/storage.h>
#include "./test_chunk_generator.h"
#include "./block_bases/generic_solid.h"

namespace engine {
    voxel test_chunk_generator::getVoxel(i64vec3 chunkPos, u8vec3 voxelPos) {
        return voxelPos.y < 5 ? voxel{1, nullptr} : voxel{0, nullptr};
    }

    void test_chunk_generator::fillChunk(Chunk *chunk) {
        const IBlockBase* bricks = storage::get_block_base({"base", "stone_bricks"});
        const IBlockBase* grass = storage::get_block_base({"base", "grass"});
        const IBlockBase* dirt = storage::get_block_base({"base", "dirt"});
        const IBlockBase* stone = storage::get_block_base({"base", "stone"});

        for (u8 z = 0; z < CHUNK_SIDE; ++z) {
            for (u8 y = 0; y < 5; ++y)
                for (u8 x = 0; x < CHUNK_SIDE; ++x)
                    chunk->set({x, y, z}, {1, stone});
        }

        for (u8 z = 0; z < CHUNK_SIDE; ++z) {
            for (u8 y = 5; y < 7; ++y)
                for (u8 x = 0; x < CHUNK_SIDE; ++x)
                    chunk->set({x, y, z}, {1, dirt});
        }

        for (u8 z = 0; z < CHUNK_SIDE; ++z) {
            for (u8 x = 0; x < CHUNK_SIDE; ++x)
                chunk->set({x, 7, z}, {1, grass});
        }
    }
}