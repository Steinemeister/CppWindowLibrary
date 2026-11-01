cmake_minimum_required(VERSION 3.14)
project(CppWindowLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. GLFW via FetchContent holen
include(FetchContent)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

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

# GLFW mit deiner Library verknüpfen
target_link_libraries(EasyWindow PUBLIC glfw)

# Suchpfade für Header-Dateien definieren (damit das Beispiel die .hpp findet)
target_include_directories(EasyWindow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 3. Den Beispiel-Ordner für die Executable hinzufügen
add_subdirectory(example)