cmake_minimum_required(VERSION 4.0)

project(gl-fiddle)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Forces an error if the compiler doesn't support C++23

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    ON
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v2.0.8
    SOURCE_SUBDIR  cmake # This points to the correct CMakeLists.txt within the repo
)
FetchContent_MakeAvailable(glad)

glad_add_library(
    glad_gl_core_33 
	STATIC
    REPRODUCIBLE 
    LOADER API gl:core=3.3 # Specifies OpenGL core profile version 4.3
)

add_executable(gl-fiddle src/main.cpp)

target_link_libraries(gl-fiddle PRIVATE glfw glad_gl_core_33)