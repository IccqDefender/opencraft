cmake_minimum_required(VERSION 4.1)
project(opencraft CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Configure GLFW to skip pkg-config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_subdirectory(lib/glm)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Core/Engine.cpp
        src/Core/Engine.h
        src/WindowManager/WindowManager.cpp
        src/WindowManager/WindowManager.h
        src/Render/Render.cpp
        src/Render/Render.h
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