#include <VoxelEngine/world/voxels/Chunk.h>
#include <VoxelEngine/world/voxels/IChunkGenerator.h>
#include <VoxelEngine/systems/storage.h>
#include "./block_bases/air.h"

namespace engine {
    static const voxel airVoxel = {0, new air()};

    const engine::voxel &engine::Chunk::get(const uvec3 &voxPos) const noexcept {
        if (voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63) return airVoxel;
        return data[((((voxPos.z << 6) | voxPos.y) << 6) | voxPos.x)];
    }

    Chunk::Chunk(i64vec3 pos, IChunkGenerator *gen) : pos(pos), mesh(this), data(), awake(true) {
        auto air = storage::get_block_base("base:air");
        for(auto& v : data) {
            v = {0, air};
        }
        gen->fillChunk(this);
    }

    void Chunk::set(const uvec3 &voxPos, voxel vox) noexcept {
        if (!(voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63)) {
            data[((((voxPos.z << 6) | voxPos.y) << 6) | voxPos.x)] = vox;

            awake = true;
        }
    }

    const chunk_mesh *Chunk::getMesh() noexcept {
        if(awake) {
            mesh.update();
            awake = false;
        }

        return &mesh;
    }
}