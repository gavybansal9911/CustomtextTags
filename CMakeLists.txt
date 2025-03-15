cmake_minimum_required(VERSION 3.22)

project(
    CppProjectTemplate
    VERSION 1.0.0
    LANGUAGES C CXX)

# Force Win32 build
set(CMAKE_GENERATOR_PLATFORM Win32)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXECUTABLE_NAME "Executable")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# Find OpenGL
find_package(OpenGL REQUIRED)

add_subdirectory(external)
add_subdirectory(include)
add_subdirectory(app)
