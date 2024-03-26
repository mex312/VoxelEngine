#pragma once

#include "../engine.h"

namespace engine {
    class TextureAtlas {
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

        TextureAtlas(void *data, u32 pixelLen, u32 texWidth, u32 texHeight, TextureAtlas::Channels channels);
        ~TextureAtlas();
    };

}