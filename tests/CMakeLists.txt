set(TEST_SOURCES
    test_dynamic_array.cpp
    test_linked_list.cpp
    test_array_sequence.cpp
    test_list_sequence.cpp
    test_mutable_immutable.cpp
    test_bit_sequence.cpp
    test_functional.cpp
)

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests
    data_structures
    gtest
    gtest_main
    pthread
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    /usr/include/gtest
)

target_compile_options(run_tests PRIVATE -Wall -Wextra -Wpedantic)

add_test(NAME DataStructuresTests COMMAND run_tests)