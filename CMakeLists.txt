cmake_minimum_required(VERSION 3.16)
project(CppWindowLibrary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 REQUIRED)

if(TARGET glfw)
    set(GLFW_TARGET glfw)
elseif(TARGET glfw3)
    set(GLFW_TARGET glfw3)
elseif(TARGET glfw3::glfw)
    set(GLFW_TARGET glfw3::glfw)
else()
    message(FATAL_ERROR "Found glfw3 but no supported CMake target was exported")
endif()

add_library(CppWindowLibrary
    src/Window.cpp
    src/WindowManager.cpp
)

target_include_directories(CppWindowLibrary
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(CppWindowLibrary
    PUBLIC
        ${GLFW_TARGET}
)

add_executable(multiwindow_demo
    examples/multiwindow_demo.cpp
)

target_link_libraries(multiwindow_demo
    PRIVATE
        CppWindowLibrary
)
