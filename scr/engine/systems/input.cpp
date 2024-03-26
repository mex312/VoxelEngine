#include "input.h"
#include "../../utils/systems_internal.h"


namespace engine::input {
    static GLFWwindow *_window = nullptr;
    static i32 _keys[KEYS_BUFFER_SIZE] = {0};
    static u64 _keyFrames[KEYS_BUFFER_SIZE] = {0};
    static u64 _frame = 0;
    static glm::vec2 _mouseDelta = {0.0f, 0.0f};
    static glm::vec2 _mousePos = {0.0f, 0.0f};


    void update() {
        _frame++;

        glm::dvec2 temp = {0, 0};
        glfwGetCursorPos(_window, &(temp.x), &(temp.y));

        _mouseDelta = (glm::vec2) temp - _mousePos;
        _mousePos = temp;
    }


    void keyCallback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods) {
        _keys[scancode] = action;
        _keyFrames[scancode] = (action & 1) ? _frame + 1 : _keyFrames[scancode];
    }

    bool pressed(i32 key) {
        return _keys[key];
    }

    bool just_pressed(i32 key) {
        return _keyFrames[key] == _frame;
    }

    glm::vec2 mouse_pos() {
        return _mousePos;
    }

    glm::vec2 mouse_delta() {
        return _mouseDelta;
    }


    void mouseButtonCallback(GLFWwindow *window, i32 button, i32 action, i32 mods) {
        _keys[button + MOUSE_BUTTONS_OFFSET] = action;
        _keyFrames[button + MOUSE_BUTTONS_OFFSET] = (action & 1) ? _frame : _keyFrames[button +
                                                                                       MOUSE_BUTTONS_OFFSET];
    }


    void init(void *window) {
        _window = (GLFWwindow *) window;

        glfwSetKeyCallback(_window, keyCallback);
        glfwSetMouseButtonCallback(_window, mouseButtonCallback);

        glm::dvec2 temp;
        glfwGetCursorPos(_window, &temp.x, &temp.y);

        _mousePos = temp;
    }
}
