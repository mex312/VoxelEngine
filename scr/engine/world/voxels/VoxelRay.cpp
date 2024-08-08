#include <VoxelEngine/world/voxels/VoxelRay.h>
#include <VoxelEngine/world/voxels/Chunk.h>
#include <VoxelEngine/world/voxels/IBlockBase.h>
#include <memory>
#include <iostream>

namespace engine {
    std::unique_ptr<voxel_collision> engine::VoxelRay::cast() const {
        auto len = glm::length((end - start).single());

        auto *chunk = world->getChunk(start);
        auto chunkPos = start.chunk;

        auto direction = normalize((end - start).single());
        auto pos = start;
        auto blockPos = start - start.local;

        Side side = NORTH;

        while(glm::length((pos - start).single()) < len) {

            if (blockPos.chunk != chunkPos) {
                chunk = world->getChunk(blockPos);
                chunkPos = blockPos.chunk;
            }

            if(chunk) {
                auto vox = chunk->get(blockPos.block);
                if (vox.block->isSolid) return std::make_unique<voxel_collision>(blockPos, pos, vox, side);
            }

            f32 xStep = direction.x == 0 ? 1024.0f : (
                    direction.x < 0 ?
                    (-pos.local.x / direction.x)
                                    :
                    ((1.0f - pos.local.x) / direction.x)
            );
            f32 yStep = direction.y == 0 ? 1024.0f : (
                    direction.y < 0 ?
                    (-pos.local.y / direction.y)
                                    :
                    ((1.0f - pos.local.y) / direction.y)
            );
            f32 zStep = direction.z == 0 ? 1024.0f : (
                    direction.z < 0 ?
                    (-pos.local.z / direction.z)
                                    :
                    ((1.0f - pos.local.z) / direction.z)
            );

            if(xStep < yStep && xStep < zStep) {
                side = direction.x > 0 ? WEST : EAST;
                pos += direction * (xStep + 0.0001f);
                blockPos += direction.x < 0 ? vec3{-1, 0, 0} : vec3{1, 0, 0};
            } else if(yStep < zStep) {
                side = direction.y > 0 ? DOWN : UP;
                pos += direction * (yStep + 0.0001f);
                blockPos += direction.y < 0 ? vec3{0, -1, 0} : vec3{0, 1, 0};
            } else {
                side = direction.z > 0 ? SOUTH : NORTH;
                pos += direction * (zStep + 0.0001f);
                blockPos += direction.z < 0 ? vec3{0, 0, -1} : vec3{0, 0, 1};
            }
        }

        return nullptr;
    }

    VoxelRay::VoxelRay(World *world, const position &start, const position &end) : world(world), start(start), end(end) {}
}