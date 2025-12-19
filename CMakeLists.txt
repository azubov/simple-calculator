cmake_minimum_required(VERSION 4.1)
project(p1)

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

add_executable(p1 main.cpp)
