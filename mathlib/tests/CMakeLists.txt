find_package(GTest REQUIRED)

add_executable(mathlib_tests test_math.cpp)

target_link_libraries(mathlib_tests PRIVATE mathlib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(mathlib_tests)