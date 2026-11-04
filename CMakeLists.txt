cmake_minimum_required(VERSION 3.14)
project(CppWindowLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan-Bibliothek finden
find_package(Vulkan REQUIRED)

# 1. GLFW via FetchContent holen
include(FetchContent)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# FetchContent_Declare() lädt die GLFW-Bibliothek von GitHub herunter und macht sie verfügbar
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# 2. Die Library selbst erstellen (Aus dem src-Ordner)
add_library(EasyWindow STATIC 
    src/EasyWindow.h
    src/Window.h
    src/Window.cpp
    src/Keyboard.h
    src/Keyboard.cpp
    src/Mouse.h
    src/Mouse.cpp
    src/Controller.h
    src/Controller.cpp
    src/Debug.h
    src/Debug.cpp
)
target_link_libraries(EasyWindow PUBLIC glfw Vulkan::Vulkan)

# Suchpfade für Header-Dateien definieren (damit das Beispiel die .hpp findet)
target_include_directories(EasyWindow PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
    )

add_library(EasyWindow::EasyWindow ALIAS EasyWindow)

# 3. Beispielprojekt erstellen (nur, wenn CMakeLists.txt direkt ausgeführt wird)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(example)
endif()