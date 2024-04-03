#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/World.h>
#include <VoxelEngine/graphics/chunk_mesh.h>

namespace engine {
    class IChunkGenerator;

    const u32 CHUNK_SIDE = 64;
    const u32 CHUNK_SIZE = 64 * 64 * 64;

    class Chunk {
        friend class chunk_mesh;


        i64vec3 pos;

        voxel data[CHUNK_SIZE];

        chunk_mesh mesh;

        bool awake;

    public:

        [[nodiscard]] const voxel & get(const uvec3 &voxPos) const noexcept;
        void set(const uvec3 &voxPos, voxel vox) noexcept;

        const chunk_mesh* getMesh() noexcept;

        explicit Chunk(i64vec3 pos, IChunkGenerator *gen);
    };
}