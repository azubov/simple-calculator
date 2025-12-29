cmake_minimum_required(VERSION 3.28.3)
project(simple_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- CPM bootstrap (скачивает CPM.cmake при необходимости) ---
if(NOT CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
endif()
if(NOT (EXISTS "${CPM_DOWNLOAD_LOCATION}"))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
            "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake"
            "${CPM_DOWNLOAD_LOCATION}"
            STATUS _cpmdownload_status
            TLS_VERIFY ON
    )
endif()
include(${CPM_DOWNLOAD_LOCATION})

# --- Подключаем mathlib из релизного архива ---
CPMAddPackage(
        NAME mathlib
        VERSION 1.0.0
        URL "https://github.com/azubov/mathlib/releases/download/v1.0.0/mathlib-release-static-v1.0.0.tar.gz"
        DOWNLOAD_ONLY YES
)

# CPM распакует пакет в ${CMAKE_BINARY_DIR}/_deps/mathlib-src
set(MATHLIB_PREFIX "${CMAKE_BINARY_DIR}/_deps/mathlib-src")
message(STATUS "MATHLIB_PREFIX = ${MATHLIB_PREFIX}")

# Добавляем распакованный префикс в CMAKE_PREFIX_PATH, чтобы find_package нашёл lib/cmake/mathlib
list(APPEND CMAKE_PREFIX_PATH "${MATHLIB_PREFIX}")

# Явно вызываем find_package
find_package(mathlib CONFIG REQUIRED)

message(STATUS "mathlib_ADDED = ${mathlib_ADDED}")
message(STATUS "mathlib_FOUND = ${mathlib_FOUND}")
message(STATUS "mathlib_SOURCE_DIR = ${mathlib_SOURCE_DIR}")
message(STATUS "mathlib_BINARY_DIR = ${mathlib_BINARY_DIR}")


# --- Опции сборки / предупреждения ---
add_compile_options(
        -Wall -Wextra -Werror -Wpedantic
        -fsanitize=address,undefined -fno-omit-frame-pointer
)
add_link_options(
        -fsanitize=address,undefined -fno-omit-frame-pointer
)

# --- Приложение ---
add_executable(calc src/main.cpp)
target_link_libraries(calc PRIVATE mathlib::mathlib)
