project(mathlib LANGUAGES CXX)

add_library(mathlib STATIC src/math_operations.cpp)

target_include_directories(mathlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)