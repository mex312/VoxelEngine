#pragma once

#include <VoxelEngine/engine.h>

namespace engine {
    class texture_atlas {
        u32 texId = 0;

    public:
        enum Channels {
            RGB_U8,
            RGBA_U8,
            RGB_F32,
            RGBA_F32,
        };

        void enable() const;
        static void disable();
        [[nodiscard]] u32 getGLTexID() const;

        texture_atlas(void *data, u32 pixelLen, u32 texWidth, u32 texHeight, texture_atlas::Channels channels);
        ~texture_atlas();
    };

}