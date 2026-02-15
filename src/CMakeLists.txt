add_library(calc_lib 
    Runner.cpp
    Parser.cpp
    Checker.cpp
    Calculator.cpp
    Printer.cpp
)
target_include_directories(calc_lib PUBLIC 
    ${mathlib_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(calc_lib PUBLIC 
    mathlib
    nlohmann_json::nlohmann_json
)