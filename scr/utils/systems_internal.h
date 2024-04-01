#include <VoxelEngine/engine.h>

namespace engine {
    namespace time {
        void init();
        void update();
    }

    namespace input {
        void init(void *window);
        void update();
    }

    namespace storage {
        void init();
    }
}