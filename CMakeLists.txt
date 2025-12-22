cmake_minimum_required(VERSION 3.28.3)
project(simple_calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
        -std=c++20
        -Wall
        -Wextra
        -Werror
        -Wpedantic
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
)

add_link_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
)

include(CTest)
add_subdirectory(mathlib)

add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE mathlib)
