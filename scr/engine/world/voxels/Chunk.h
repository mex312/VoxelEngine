#pragma once

#include "../../engine.h"
#include "./voxel.h"
#include "../../graphics/ChunkMesh.h"

namespace engine {
    class IChunkGenerator;

    const u32 CHUNK_SIDE = 64;
    const u32 CHUNK_SIZE = 64 * 64 * 64;

    class Chunk {
        friend class ChunkMesh;


        i64vec3 pos;

        voxel data[CHUNK_SIZE];

        ChunkMesh mesh;

        bool awake;

    public:

        [[nodiscard]] const voxel & get(u8vec3 voxPos) const noexcept;
        void set(u8vec3 voxPos, voxel vox) noexcept;

        const ChunkMesh* getMesh() noexcept;

        explicit Chunk(i64vec3 pos, IChunkGenerator *gen);
    };
}