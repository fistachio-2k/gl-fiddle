cmake_minimum_required(VERSION 4.0)

project(gl-fiddle)

set(CMAKE_SKIP_INSTALL_RULES ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(dependencies.cmake)

source_group("Shaders" FILES shaders/shader.vert shaders/shader.frag)
source_group("CMake" FILES dependencies.cmake)
add_executable(gl-fiddle src/main.cpp src/Shader.h shaders/shader.vert shaders/shader.frag dependencies.cmake)

target_link_libraries(gl-fiddle PRIVATE glfw glad_gl_core_33 stb glm)

add_custom_command(TARGET gl-fiddle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:gl-fiddle>/shaders"
    COMMENT "Copying shaders to output directory"
)