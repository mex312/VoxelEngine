#include "Camera.h"
#include <gtx/quaternion.hpp>

namespace engine {
    Camera::Camera(f32 aspect, i64vec3 uPos, i64vec3 cPos, f32vec3 fPos, vec2 rot)
            : aspect(aspect), uPos(uPos), cPos(cPos), fPos(fPos), rot(rot) {}

    mat4 Camera::getView(i64vec3 meshCPos) const {
        return glm::scale(
                glm::perspective(
                        glm::radians(45.0f),
                        aspect,
                        0.01f,
                        float(1 << 16)
                ) * glm::translate(
                        glm::rotate(
                                glm::mat4(1),
                                rot.y,
                                glm::vec3(1.0f, 0.0f, 0.0f)
                        ) * glm::rotate(
                                mat4(1),
                                rot.x,
                                vec3(0.0f, 1.0f, 0.0f)
                        ),
                        (vec3(((uPos - meshCPos) * 64ll) + cPos) + fPos) * vec3{-1, -1, 1}
                ),
                {1, 1, -1});
    }

    void Camera::update() {
        vec3 deltaUPos;
        fPos = glm::modf(fPos, deltaUPos);
        cPos += deltaUPos;
        for(u8 i = 0; i < 3; ++i) {
            if (fPos[i] < 0) {
                ++fPos[i];
                --cPos[i];
            }
            uPos[i] += cPos[i] >> 6;
            cPos[i] &= 0b111111;
            if (cPos[i] < 0) {
                cPos[i] += 64;
                ++uPos[i];
            }
        }
    }
}