cmake_minimum_required(VERSION 4.1)
project(opencraft CXX)

set(CMAKE_CXX_STANDART 17)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
)
target_sources(${PROJECT_NAME} PRIVATE
        lib/imgui/imgui.cpp
        lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_widgets.cpp
        # Бэкенды для GLFW и Vulkan
        lib/imgui/backends/imgui_impl_glfw.cpp
        lib/imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)

target_include_directories(${PROJECT_NAME} PRIVATE glfw lib/imgui lib/imgui/backends)