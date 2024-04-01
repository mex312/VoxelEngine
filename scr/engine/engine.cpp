#include <VoxelEngine/engine.h>
#include <GLFW/glfw3.h>
#include <VoxelEngine/systems/input.h>
#include <VoxelEngine/systems/time.h>
#include <VoxelEngine/systems/files.h>
#include <VoxelEngine/systems/storage.h>
#include <VoxelEngine/world/voxels/chunk.h>
#include <VoxelEngine/graphics/camera.h>
#include <VoxelEngine/world/world.h>
#include "./world/voxels/test_chunk_generator.h"
#include "./world/voxels/block_bases/generic_solid.h"
#include "../utils/systems_internal.h"
#include "../utils/engine_internal.h"
#include "../external/glad.h"
#include <iostream>

extern "C" {
[[gnu::dllexport]] uint8_t NvOptimusEnablement = 0x00000001;
}

namespace engine {
    static f32 _screen_aspect(800.0f / 600.0f);
    static GLFWwindow *_window = nullptr;


    void framebuffer_size_callback(GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);

        _screen_aspect = (float) width / (float) height;
    }

    int init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(800, 600, "RawGL", nullptr, nullptr);
        if (_window == nullptr) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(_window);
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glfwSwapInterval(0);
        glfwSwapInterval(144);

        time::init();
        input::init(_window);
        storage::init();

        return 0;
    }


    void start() {
        init();

        auto vec = files::get_all_files("../res/textures");

        for (auto &f: vec) {
            std::cout << f.filename() << std::endl;
        }

        storage::reg_block_base(new generic_solid(
                {
                        "base:stone_bricks",
                        "base:stone_bricks",
                        "base:stone_bricks",
                        "base:stone_bricks",
                        "base:stone_bricks",
                        "base:stone_bricks"
                }), "base:stone_bricks");
        storage::reg_block_base(new generic_solid(
                {
                        "base:dirt",
                        "base:dirt",
                        "base:dirt",
                        "base:dirt",
                        "base:dirt",
                        "base:dirt"
                }), "base:dirt");
        storage::reg_block_base(new generic_solid(
                {
                        "base:grass_side",
                        "base:grass_side",
                        "base:grass_side",
                        "base:grass_side",
                        "base:grass_top",
                        "base:dirt"
                }), "base:grass");

        f64 elapsed = 0.0;
        u64 frames = 0;

        constexpr float SPEED = 10.0f;
        constexpr float SENSITIVITY = 0.005f;

        auto cam = camera(0, {0, 0, 0});

        auto world = world();

        chunk_generator *gen = new test_chunk_generator();
        for (u8 z = 0; z < 8; ++z) for (u8 x = 0; x < 8; ++x) world.genChunk({x, 0, z}, gen);

        f32 blockTimer = 0;
        uvec3 posToPlace = {0, 0, 0};

        while (!glfwWindowShouldClose(_window)) {
            input::update();
            time::update();

            elapsed += time::delta_time_d();
            blockTimer += time::delta_time();
            frames++;
            cam.aspect = _screen_aspect;

            if (elapsed >= 1.0) {
                std::cout << frames << "\n";
                elapsed -= 1.0;
                frames = 0;
            }

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_ESCAPE))) glfwSetWindowShouldClose(_window, true);

            cam.rot += input::mouse_delta() * SENSITIVITY;
            cam.rot.y = glm::clamp(cam.rot.y, -glm::radians(90.0f), glm::radians(90.0f));
            cam.rot.x = glm::mod(cam.rot.x, glm::radians(360.0f));

            mat4 motionRotation = glm::rotate(mat4(1), -cam.rot.x, vec3(0.0f, 1.0f, 0.0f));

            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_W)))
                cam.fPos += glm::vec3(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) * SPEED * time::delta_time() * motionRotation);
            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_S)))
                cam.fPos += glm::vec3(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f) * SPEED * time::delta_time() * motionRotation);
            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_A)))
                cam.fPos += glm::vec3(glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f) * SPEED * time::delta_time() * motionRotation);
            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_D)))
                cam.fPos += glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * SPEED * time::delta_time() * motionRotation);
            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_LEFT_SHIFT)))
                cam.fPos += glm::vec3(glm::vec4(0.0f, -1.0f, 0.0f, 1.0f) * SPEED * time::delta_time() * motionRotation);
            if (input::pressed(glfwGetKeyScancode(GLFW_KEY_SPACE)))
                cam.fPos += glm::vec3(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) * SPEED * time::delta_time() * motionRotation);

            cam.update();

            world.render(&cam);

            GLenum err = glGetError();

            switch (err) {
                case 0:
                    break;
                case (GL_INVALID_ENUM):
                    std::cout << "GL_INVALID_ENUM" << std::endl;
                    break;
                case (GL_INVALID_VALUE):
                    std::cout << "GL_INVALID_VALUE" << std::endl;
                    break;
                case (GL_INVALID_OPERATION):
                    std::cout << "GL_INVALID_OPERATION" << std::endl;
                    break;
                default:
                    std::cout << err << std::endl;
                    break;
            }


            glfwSwapBuffers(_window);
            glfwPollEvents();
        }

        glBindVertexArray(0);

        glfwTerminate();
    }
}
