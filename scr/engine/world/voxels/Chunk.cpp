#include "Chunk.h"
#include "IChunkGenerator.h"

#include <cstring>

namespace engine {
    static const voxel outOfBoundsVoxel = {0, nullptr};

    const engine::voxel &engine::Chunk::get(u8vec3 voxPos) const noexcept {
        if (voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63) return outOfBoundsVoxel;
        return data[((((u32(voxPos.z) << 6) | voxPos.y) << 6) | voxPos.x)];
    }

    Chunk::Chunk(i64vec3 pos, IChunkGenerator *gen) : pos(pos), mesh(this), data(), awake(true) {
        memset(data, 0, sizeof(data));
        gen->fillChunk(this);
    }

    void Chunk::set(u8vec3 voxPos, voxel vox) noexcept {
        if (!(voxPos.x > 63 || voxPos.y > 63 || voxPos.z > 63)) {
            data[((((u32(voxPos.z) << 6) | voxPos.y) << 6) | voxPos.x)] = vox;

            awake = true;
        }
    }

    const ChunkMesh *Chunk::getMesh() noexcept {
        if(awake) {
            mesh.update();
            awake = false;
        }

        return &mesh;
    }
}