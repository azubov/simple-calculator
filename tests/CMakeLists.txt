find_package(GTest REQUIRED)

add_executable(calc_tests Printer_test.cpp)
target_link_libraries(calc_tests PRIVATE calc_lib GTest::gtest_main)
set_target_properties(calc_tests PROPERTIES CXX_CLANG_TIDY "")

include(GoogleTest)
gtest_discover_tests(calc_tests)