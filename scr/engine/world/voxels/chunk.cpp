#include <VoxelEngine/world/voxels/chunk.h>
#include <VoxelEngine/world/voxels/chunk_generator.h>

#include <cstring>

namespace engine {
    static const voxel outOfBoundsVoxel = {0, nullptr};

    const engine::voxel &engine::chunk::get(u8vec3 voxPos) const noexcept {
        if (voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63) return outOfBoundsVoxel;
        return data[((((u32(voxPos.z) << 6) | voxPos.y) << 6) | voxPos.x)];
    }

    chunk::chunk(i64vec3 pos, chunk_generator *gen) : pos(pos), mesh(this), data(), awake(true) {
        memset(data, 0, sizeof(data));
        gen->fillChunk(this);
    }

    void chunk::set(u8vec3 voxPos, voxel vox) noexcept {
        if (!(voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63)) {
            data[((((u32(voxPos.z) << 6) | voxPos.y) << 6) | voxPos.x)] = vox;

            awake = true;
        }
    }

    const chunk_mesh *chunk::getMesh() noexcept {
        if(awake) {
            mesh.update();
            awake = false;
        }

        return &mesh;
    }
}