cmake_minimum_required(VERSION 3.26)
project(opencraft CXX)

set(CMAKE_CXX_STANDART 17)

add_subdirectory(lib/glfw)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE lib)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)