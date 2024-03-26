#include "ChunkMesh.h"
#include "../../external/glad.h"
#include "../world/voxels/Chunk.h"
#include "../systems/files.h"
#include "./shader.h"
#include "Camera.h"
#include <iostream>
#include "../world/voxels/IBlockBase.h"
#include "../systems/storage.h"
#include "./TextureAtlas.h"

namespace engine {

    struct DrawArraysIndirectCommand{
        u32  count;
        u32  instanceCount;
        u32  first;
        u32  baseInstance;
    };

    static u32 quadVBO = 0;
    static Shader* shader = nullptr;

    static const u32 quad[] = {
            0b00,
            0b01,
            0b11,
            0b10,
    };


    ChunkMesh::ChunkMesh(engine::Chunk *chunk) : chunk(chunk), vao(0), vbo(0), idb(0), vboCapacity(0) {
        glGenVertexArrays(1, &vao);
        glGenBuffers(2, &vbo);

        if(!quadVBO) {
            glGenBuffers(1, &quadVBO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(vao);

        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, idb);
        glBufferData(GL_DRAW_INDIRECT_BUFFER, 96, nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(u32), nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(chunk_vertex), nullptr);
        glVertexAttribDivisor(1, 1);
        glEnableVertexAttribArray(2);
        glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(chunk_vertex), (void*)4);
        glVertexAttribDivisor(2, 1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    ChunkMesh::~ChunkMesh() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(2, &vbo);
    }

    void ChunkMesh::update() {
        for (auto &vBuff: vertexBuffers) vBuff.clear();

        for (u32 z = 0; z < CHUNK_SIDE; ++z)
            for (u32 y = 0; y < CHUNK_SIDE; ++y)
                for (u32 x = 0; x < CHUNK_SIDE; ++x) {
                    voxel now = chunk->get({x, y, z});
                    if (!now.block) continue;
                    if (!now.block->isVisible) continue;

                    voxel v = chunk->get({x, y, z - 1});
                    if (!v.data) vertexBuffers[SOUTH].push_back({x | (y << 6) | (z << 12), 0});

                    v = chunk->get({x + 1, y, z});
                    if (!v.data) vertexBuffers[WEST].push_back({x | (y << 6) | (z << 12), 0});

                    v = chunk->get({x, y, z + 1});
                    if (!v.data) vertexBuffers[NORTH].push_back({x | (y << 6) | (z << 12), 0});

                    v = chunk->get({x - 1, y, z});
                    if (!v.data) vertexBuffers[EAST].push_back({x | (y << 6) | (z << 12), 0});

                    v = chunk->get({x, y + 1, z});
                    if (!v.data) vertexBuffers[UP].push_back({x | (y << 6) | (z << 12), 0});

                    v = chunk->get({x, y - 1, z});
                    if (!v.data) vertexBuffers[DOWN].push_back({x | (y << 6) | (z << 12), 0});
                }

        u32 bLen =
                vertexBuffers[0].size() +
                vertexBuffers[1].size() +
                vertexBuffers[2].size() +
                vertexBuffers[3].size() +
                vertexBuffers[4].size() +
                vertexBuffers[5].size();

        if(!bLen) return;

        glBindVertexArray(vao);

        if (bLen > vboCapacity) {
            if (!vboCapacity) vboCapacity = 1;
            while (bLen > vboCapacity) {
                vboCapacity <<= 1;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vboCapacity * (GLsizei) sizeof(chunk_vertex), nullptr, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, idb);
        auto *idbPtr = (DrawArraysIndirectCommand *) glMapBuffer(GL_DRAW_INDIRECT_BUFFER, GL_WRITE_ONLY);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        auto *vboPtr = (chunk_vertex *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        u32 summ = 0;
        for (auto &vBuff: vertexBuffers) {
            u32 len = vBuff.size();
            *idbPtr = {4, len, 0, summ};
            memcpy(vboPtr, vBuff.data(), len * sizeof(chunk_vertex));
            vboPtr += len;
            summ += len;
            ++idbPtr;
        }
        glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

        glBindVertexArray(0);
    }

    void ChunkMesh::draw(const Camera *cam) const noexcept {
        if (!(vertexBuffers[0].size() +
        vertexBuffers[1].size() +
        vertexBuffers[2].size() +
        vertexBuffers[3].size() +
        vertexBuffers[4].size() +
        vertexBuffers[5].size()))
            return;

        if(!shader) {
            shader = Shader::loadShader(files::read_string("../res/shaders/chunk_voxel_shader.vert"), files::read_string("../res/shaders/chunk_voxel_shader.frag"));
        }

        shader->use();
        glUniformMatrix4fv(glGetUniformLocation(shader->id, "MVP"), 1, false, &cam->getView(chunk->pos)[0][0]);
        glUniform1i(glGetUniformLocation(shader->id, "tex"), 0);

        glBindTexture(GL_TEXTURE_2D_ARRAY, storage::getAtlas()->getGLTexID());

        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, idb);
        glBindVertexArray(vao);
        glMultiDrawArraysIndirect(GL_TRIANGLE_FAN, nullptr, 6, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        glUseProgram(0);
    }
}