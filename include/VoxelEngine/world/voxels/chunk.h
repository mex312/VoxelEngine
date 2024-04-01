#pragma once

#include <VoxelEngine/engine.h>
#include <VoxelEngine/world/voxels/voxel.h>
#include <VoxelEngine/graphics/chunk_mesh.h>

namespace engine {
    class chunk_generator;

    const u32 CHUNK_SIDE = 64;
    const u32 CHUNK_SIZE = 64 * 64 * 64;

    class chunk {
        friend class chunk_mesh;


        i64vec3 pos;

        voxel data[CHUNK_SIZE];

        chunk_mesh mesh;

        bool awake;

    public:

        [[nodiscard]] const voxel & get(u8vec3 voxPos) const noexcept;
        void set(u8vec3 voxPos, voxel vox) noexcept;

        const chunk_mesh* getMesh() noexcept;

        explicit chunk(i64vec3 pos, chunk_generator *gen);
    };
}