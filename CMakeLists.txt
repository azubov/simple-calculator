cmake_minimum_required(VERSION 3.15)
project(simple-calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

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
target_link_libraries(calc PRIVATE calc_lib Threads::Threads)

option(ENABLE_VALGRIND "Run under Valgrind" OFF)

if(ENABLE_VALGRIND)
    find_program(VALGRIND_EXECUTABLE valgrind REQUIRED)

    set(VALGRIND_OPTS
        --error-exitcode=1
        --tool=memcheck
        --leak-check=full
        --show-leak-kinds=all
        --track-origins=yes
        --num-callers=25
    )

    add_custom_target(run-valgrind
        COMMAND ${VALGRIND_EXECUTABLE} ${VALGRIND_OPTS} ${CMAKE_BINARY_DIR}/calc
        DEPENDS calc
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

option(CALCLIB_BUILD_TESTS "Build calclib tests" OFF)

if(CALCLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ═════════════════════════════════════════════════════════════════════════════
# Установка
# ═════════════════════════════════════════════════════════════════════════════

# Бинарник → /usr/bin/calc
install(TARGETS calc
    RUNTIME DESTINATION bin
)

install(TARGETS calc_lib
    LIBRARY DESTINATION lib
)

install(TARGETS mathlib
    LIBRARY DESTINATION lib
)

# systemd unit → /lib/systemd/system/calculator.service
install(FILES calculator.service
    DESTINATION lib/systemd/system
)

# Пример конфига → /etc/calculator/input.json  (документация/defaults)
install(FILES example/input.json
    DESTINATION etc/calculator
    RENAME input.json.example
)

# ═════════════════════════════════════════════════════════════════════════════
# CPack — deb-пакет
# ═════════════════════════════════════════════════════════════════════════════
set(CPACK_GENERATOR "DEB")

# Основные метаданные пакета
set(CPACK_PACKAGE_NAME           "simple-calculator")
set(CPACK_PACKAGE_VERSION        "1.0.0")
set(CPACK_PACKAGE_RELEASE        "1")
set(CPACK_PACKAGE_CONTACT        "https://github.com/azubov")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Simple integer calculator service over ZMQ")
set(CPACK_PACKAGE_DESCRIPTION
    "Calculator daemon that accepts JSON requests via ZeroMQ,\n"
    " stores results in PostgreSQL and runs as a systemd service.")

# DEB-специфичные поля
set(CPACK_DEBIAN_PACKAGE_SECTION  "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")   # или ${CMAKE_SYSTEM_PROCESSOR}

# Автоматический поиск рантайм-зависимостей (libc, libpq, libzmq и т.д.)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

# Скрипты сопровождения пакета (postinst / prerm)
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
    "${CMAKE_CURRENT_SOURCE_DIR}/packaging/postinst"
    "${CMAKE_CURRENT_SOURCE_DIR}/packaging/prerm"
)

# Имя выходного файла: simple-calculator-1.0.0-amd64.deb
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}"
)

include(CPack)