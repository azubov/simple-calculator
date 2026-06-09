add_library(calc_lib 
    Runner.cpp
    Parser.cpp
    Checker.cpp
    SimpleCalculator.cpp
    CpuHeavyCalculator.cpp
    PGConnection.cpp
    StatementInitializer.cpp
    PostgresCalculatorRepository.cpp
    CachedCalculatorRepository.cpp
    CalculatorService.cpp
    Printer.cpp
    Application.cpp
    SystemSignal.cpp
    ZmqServer.cpp
)
target_include_directories(calc_lib PUBLIC 
    ${mathlib_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PostgreSQL_INCLUDE_DIRS}
)

find_package(nlohmann_json REQUIRED) 
find_package(spdlog REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(cppzmq REQUIRED)

target_link_libraries(calc_lib PUBLIC 
    mathlib
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    PostgreSQL::PostgreSQL
    cppzmq
)

option(ENABLE_CPU_LOAD "Enable calculator with cpu load" OFF)

if(ENABLE_CPU_LOAD)
    target_compile_definitions(calc_lib PRIVATE ENABLE_CPU_LOAD)
endif()

# --- systemd support ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD REQUIRED libsystemd)

target_include_directories(calc_lib PRIVATE ${SYSTEMD_INCLUDE_DIRS})
target_link_libraries(calc_lib PRIVATE ${SYSTEMD_LIBRARIES})