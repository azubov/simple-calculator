cmake_minimum_required(VERSION 3.15)
project(simple-calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
        mathlib
        GIT_REPOSITORY https://github.com/azubov/mathlib.git
        GIT_TAG master
)
FetchContent_MakeAvailable(mathlib)
set_target_properties(mathlib PROPERTIES CXX_CLANG_TIDY "")

add_subdirectory(src)

add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE calc_lib)

option(CALCLIB_BUILD_TESTS "Build calclib tests" OFF)

if(CALCLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()