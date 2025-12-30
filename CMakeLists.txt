cmake_minimum_required(VERSION 3.15)
project(simple_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
        -Wall -Wextra -Werror -Wpedantic
        -fsanitize=address,undefined -fno-omit-frame-pointer
)
add_link_options(
        -fsanitize=address,undefined -fno-omit-frame-pointer
)

include(FetchContent)
FetchContent_Declare(
        mathlib
        GIT_REPOSITORY https://github.com/azubov/mathlib.git
        GIT_TAG master
)
FetchContent_MakeAvailable(mathlib)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE mathlib)
