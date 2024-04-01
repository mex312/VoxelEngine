#include <VoxelEngine/graphics/texture_atlas.h>
#include "../../external/glad.h"

namespace engine {
    texture_atlas::texture_atlas(void *data, u32 pixelLen, u32 texWidth, u32 texHeight, texture_atlas::Channels channels) {
        u32 pixelSize;
        u32 glFormat;
        u32 glType;
        u32 glComp;
        switch (channels) {
            case RGB_U8:
                pixelSize = sizeof(u8) * 3;
                glType = GL_RGB8;
                glFormat = GL_RGB;
                glComp = GL_UNSIGNED_BYTE;
                break;
            case RGBA_U8:
                pixelSize = sizeof(u8) << 2;
                glType = GL_RGBA8;
                glFormat = GL_RGBA;
                glComp = GL_UNSIGNED_BYTE;
                break;
            case RGB_F32:
                pixelSize = sizeof(f32) * 3;
                glType = GL_RGB32F;
                glFormat = GL_RGB;
                glComp = GL_FLOAT;
                break;
            case RGBA_F32:
                pixelSize = sizeof(f32) << 2;
                glType = GL_RGBA32F;
                glFormat = GL_RGBA;
                glComp = GL_FLOAT;
                break;
        }

        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texId);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, glType, (i32)texWidth, (i32)texHeight, (i32)(pixelLen / (texWidth * texHeight)));
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, (i32)texWidth, (i32)texHeight, (i32)(pixelLen / (texWidth * texHeight)), glFormat, glComp, data);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    texture_atlas::~texture_atlas() {
        glDeleteTextures(1, &texId);
    }

    u32 texture_atlas::getGLTexID() const {
        return texId;
    }

    void texture_atlas::enable() const {
        glBindTexture(GL_TEXTURE_2D_ARRAY, texId);
    }
    void texture_atlas::disable() {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }
} // engine