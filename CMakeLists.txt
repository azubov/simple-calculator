cmake_minimum_required(VERSION 3.28.3)
project(simple_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Опции сборки / предупреждения ---
add_compile_options(
        -Wall -Wextra -Werror -Wpedantic
        -fsanitize=address,undefined -fno-omit-frame-pointer
)
add_link_options(
        -fsanitize=address,undefined -fno-omit-frame-pointer
)

# --- CPM bootstrap (скачивает CPM.cmake при необходимости) ---
if(NOT EXISTS ${CMAKE_BINARY_DIR}/cmake/CPM.cmake)
    file(DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
            ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
    )
endif()
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

# --- Подключаем mathlib из релизного архива ---
CPMAddPackage(
        NAME mathlib
        VERSION 1.0.0
        URL "https://github.com/azubov/mathlib/releases/download/v1.0.0/mathlib-release-static-v1.0.0.tar.gz"
        DOWNLOAD_ONLY YES
)

# Добавляем распакованный префикс в CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH "${mathlib_SOURCE_DIR}")
find_package(mathlib CONFIG REQUIRED)

# --- Приложение ---
add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE mathlib::mathlib)
