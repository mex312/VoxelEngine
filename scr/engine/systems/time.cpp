#include <VoxelEngine/systems/time.h>
#include "../../utils/systems_internal.h"

using namespace std::chrono;

namespace engine::time {
    static high_resolution_clock::time_point _start = high_resolution_clock::now();
    static nanoseconds _delta = 0s;
    static nanoseconds _elapsed = 0s;
    static f64 _deltaTimeD = 0.0;
    static f32 _deltaTime = 0.0;


    void init() {
        time::_start = high_resolution_clock::now();
    }

    void update() {
        auto elapsedNew = high_resolution_clock::now() - _start;
        _delta = elapsedNew - _elapsed;
        _elapsed = elapsedNew;

        _deltaTimeD = (f64) _delta.count() / (f64) duration_cast<nanoseconds>(1s).count();
        _deltaTime = (f32) _deltaTimeD;
    }

    f32 delta_time() {
        return time::_deltaTime;
    }

    f64 delta_time_d() {
        return time::_deltaTimeD;
    }
}