set(IMGUI_SOURCES
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui.cpp
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/include/ImGUI/imgui_impl_opengl3.cpp
)

add_executable(${EXECUTABLE_NAME} main.cc ${IMGUI_SOURCES})

target_link_directories(${EXECUTABLE_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/external/GLEW/"
    "${PROJECT_SOURCE_DIR}/external/GLFW/")

target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    glfw3
    glew32
    opengl32
    shell32)

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/include/"
    "${PROJECT_SOURCE_DIR}/include/GLEW/"
    "${PROJECT_SOURCE_DIR}/include/GLFW/"
    "${PROJECT_SOURCE_DIR}/include/ImGUI/")
