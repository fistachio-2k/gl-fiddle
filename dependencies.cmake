# Enable folders in the Visual Studio solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

# --- GLFW ---
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    ON
    EXCLUDE_FROM_ALL # Completely hides targets that aren't used by the main project (like uninstall and update_mappings)
)
FetchContent_MakeAvailable(glfw)
set_target_properties(glfw PROPERTIES FOLDER "deps")

# --- GLAD ---
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v2.0.8
    GIT_SHALLOW    ON
    SOURCE_SUBDIR  cmake # This points to the correct CMakeLists.txt within the repo
)
FetchContent_MakeAvailable(glad)

glad_add_library(
    glad_gl_core_33 
	STATIC
    REPRODUCIBLE 
    LOADER API gl:core=3.3 # Specifies OpenGL core profile version 3.3
)
set_target_properties(glad_gl_core_33 PROPERTIES FOLDER "deps")

# --- STB Image ---
message(STATUS "STB Image: Downloading stb_image.h...")
set(STB_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/stb-src")
set(STB_IMAGE_HEADER "${STB_DIR}/stb_image.h")
file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" "${STB_IMAGE_HEADER}")

# Generate stb_image.cpp dynamically in the build directory
set(STB_IMAGE_CPP "${STB_DIR}/stb_image.cpp")
file(WRITE "${STB_IMAGE_CPP}" "#define STB_IMAGE_IMPLEMENTATION\n#include \"stb_image.h\"\n")

# stb_image target
add_library(stb STATIC "${STB_IMAGE_CPP}" "${STB_IMAGE_HEADER}")
target_include_directories(stb PUBLIC "${STB_DIR}")
set_target_properties(stb PROPERTIES FOLDER "deps")

# --- GLM ---
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        master
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(glm)
set_target_properties(glm PROPERTIES FOLDER "deps")