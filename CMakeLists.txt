cmake_minimum_required(VERSION 3.27)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(VoxelGame
        scr/main.cpp
)

add_library(vox_engine STATIC
        scr/engine/systems/input.cpp
        scr/engine/systems/time.cpp
        scr/external/glad.c
        scr/engine/engine.cpp
        scr/engine/systems/files.cpp
        scr/engine/graphics/shader.cpp
        scr/engine/graphics/chunk_mesh.cpp
        scr/engine/world/voxels/Chunk.cpp
        scr/engine/world/voxels/voxel.cpp
        scr/engine/graphics/Camera.cpp
        scr/engine/world/World.cpp
        scr/engine/world/voxels/test_chunk_generator.cpp
        scr/engine/world/voxels/block_bases/generic_solid.cpp
        scr/engine/world/voxels/block_bases/air.cpp
        scr/engine/world/voxels/IBlockBase.cpp
        scr/engine/systems/storage.cpp
        scr/external/stb_image.cpp
        scr/engine/graphics/texture_atlas.cpp
        scr/engine/world/voxels/VoxelRay.cpp
)

target_link_libraries(VoxelGame vox_engine)

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.4)
target_link_libraries(vox_engine glfw)
target_link_libraries(VoxelGame glfw)

include_directories(include)
include_directories(C:/Users/mex312/source/libraries/cpp/glm/glm)
include_directories(C:/Users/mex312/source/libraries/cpp/glfw-3.4/include)