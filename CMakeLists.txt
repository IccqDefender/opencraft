cmake_minimum_required(VERSION 3.10)
project(opencraft)

# Стандарт C++ (можно менять)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------
# 1. GLFW (из исходников в external/glfw)
# --------------------------------------------
# Явно включаем Wayland (опционально, можно убрать для автоопределения)
set(GLFW_BUILD_WAYLAND ON)
set(GLFW_BUILD_X11 OFF)   # или ON, если нужна поддержка X11
add_subdirectory(external/glfw)

# --------------------------------------------
# 2. GLAD (статическая библиотека из external/glad)
# --------------------------------------------
add_library(glad STATIC external/glad/src/glad.c
)
target_include_directories(glad PUBLIC external/glad/include)

# --------------------------------------------
# 3. GLM (header-only библиотека)
# --------------------------------------------
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE external/glm)

# --------------------------------------------
# 4. Dear ImGui (сборка ядра без бэкендов)
# --------------------------------------------
# Собираем все .cpp файлы из external/imgui, кроме бэкендов
add_library(imgui STATIC
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        external/imgui
        external/imgui/backends
)

# Бэкенд GLFW зависит от glfw и opengl32, но НЕ нужен find_package(OpenGL) до этого
target_link_libraries(imgui PUBLIC glfw)

if (WIN32)
    target_link_libraries(imgui PUBLIC opengl32)
endif()

# --------------------------------------------
# 5. Системная OpenGL
# --------------------------------------------
find_package(OpenGL REQUIRED)

# --------------------------------------------
# 6. Исполняемый файл игры
# --------------------------------------------
# Собираем все .cpp файлы из src/ (включая подпапки)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(opencraft ${SOURCES}
        src/core/Window.cpp
        src/core/Window.h
        src/game/Game.cpp
        src/game/Game.h
)

# Линкуем все библиотеки к игре
target_link_libraries(opencraft
    glfw          # GLFW
    glad          # GLAD (загрузчик OpenGL)
    glm           # GLM (математика)
    imgui         # Dear ImGui
    ${OPENGL_gl_LIBRARY}   # системная OpenGL
)

# Для Linux добавляем dl и pthread (может понадобиться для GLFW)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(opencraft ${CMAKE_DL_LIBS} pthread)
endif()

# Дополнительные пути для заголовков (на всякий случай)
target_include_directories(opencraft PRIVATE
    ${OPENGL_INCLUDE_DIR}
    external/glad/include
    external/glm
    external/imgui
    external/imgui/backends
)

# --------------------------------------------
# 7. Опции для Windows (если понадобится)
# --------------------------------------------
if (WIN32)
    target_link_libraries(opencraft
        opengl32
        gdi32
    )
endif()

# --------------------------------------------
# 8. Дополнительные настройки (по желанию)
# --------------------------------------------
# Например, можно включить предупреждения
# target_compile_options(opencraft PRIVATE -Wall -Wextra)