#include <VoxelEngine/world/voxels/VoxelRay.h>
#include <VoxelEngine/world/voxels/Chunk.h>

namespace engine {
    voxel_collision *engine::VoxelRay::cast() const {
        auto *chunk = world->getChunk(start);
        if (!chunk) return nullptr;

        auto direction = normalize((end - start).single());
        auto pos = start;
        auto blockPos = start;
        auto vox = chunk->get(blockPos.block);

//        while() TODO: stepping

        return new voxel_collision();
    }
}