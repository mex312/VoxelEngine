#include <VoxelEngine/graphics/Camera.h>
#include <gtx/quaternion.hpp>

namespace engine {
    mat4 Camera::getView(position meshPos) const {
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
                        (pos - meshPos).single() * vec3{-1, -1, 1}
                ),
                {1, 1, -1});
    }

    void Camera::update() {

    }

    Camera::Camera(f32 aspect, const position &pos, vec2 rot) : aspect(aspect), pos(pos), rot(rot) {}

    mat4 Camera::getRotation() const {
        return glm::rotate(
                glm::rotate(
                        glm::mat4(1),
                        rot.y,
                        glm::vec3(
                                -1.0f, 0.0f, 0.0f)
                ),
                rot.x,
                vec3(0.0f, -1.0f, 0.0f)
        );
    }
}