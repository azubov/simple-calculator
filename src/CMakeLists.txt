add_library(calc_lib 
    Runner.cpp
    Parser.cpp
    Checker.cpp
    SimpleCalculator.cpp
    PGConnection.cpp
    StatementInitializer.cpp
    PostgresCalculatorRepository.cpp
    CachedCalculatorRepository.cpp
    CalculatorService.cpp
    Printer.cpp
)
target_include_directories(calc_lib PUBLIC 
    ${mathlib_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PostgreSQL_INCLUDE_DIRS}
)

find_package(nlohmann_json REQUIRED) 
find_package(spdlog REQUIRED)
find_package(PostgreSQL REQUIRED)

target_link_libraries(calc_lib PUBLIC 
    mathlib
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    PostgreSQL::PostgreSQL
)