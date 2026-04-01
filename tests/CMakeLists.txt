find_package(GTest REQUIRED)

add_executable(calc_tests
    runner_tests.cpp
    parser_tests.cpp
    checker_tests.cpp
    simple_calculator_tests.cpp
    printer_tests.cpp
    calculator_cache_repository_tests.cpp
    calculator_service_tests.cpp
    leak_memchecked_test.cpp
)

target_compile_definitions(calc_lib PRIVATE USE_NULL_LOGGER)

target_link_libraries(calc_tests PRIVATE calc_lib GTest::gtest_main GTest::gmock_main)
set_target_properties(calc_tests PROPERTIES CXX_CLANG_TIDY "")

if(ENABLE_VALGRIND)
    add_test(
        NAME calc_tests
        COMMAND ${VALGRIND_EXECUTABLE} ${VALGRIND_OPTS} $<TARGET_FILE:calc_tests>
    )
else()
    include(GoogleTest)
    gtest_discover_tests(calc_tests)
endif()