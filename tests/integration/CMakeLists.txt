find_package(cppzmq REQUIRED)

add_executable(client client.cpp)
target_link_libraries(client PRIVATE cppzmq)

configure_file(
    ${CMAKE_SOURCE_DIR}/tests/integration/test_cases.txt
    ${CMAKE_BINARY_DIR}/tests/integration/test_cases.txt
    COPYONLY
)