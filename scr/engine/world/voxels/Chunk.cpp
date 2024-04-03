#include <VoxelEngine/world/voxels/Chunk.h>
#include <VoxelEngine/world/voxels/IChunkGenerator.h>

#include <cstring>

namespace engine {
    static const voxel outOfBoundsVoxel = {0, nullptr};

    const engine::voxel &engine::Chunk::get(const uvec3 &voxPos) const noexcept {
        if (voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63) return outOfBoundsVoxel;
        return data[((((voxPos.z << 6) | voxPos.y) << 6) | voxPos.x)];
    }

    Chunk::Chunk(i64vec3 pos, IChunkGenerator *gen) : pos(pos), mesh(this), data(), awake(true) {
        memset(data, 0, sizeof(data));
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