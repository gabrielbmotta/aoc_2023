cmake_minimum_required(VERSION 3.10)

project(Scratchers)

add_executable(Scratchers scratchers.cpp)

enable_testing()

add_test(NAME Example COMMAND Scratchers ${PROJECT_SOURCE_DIR}/input_example)
set_tests_properties(Example
    PROPERTIES PASS_REGULAR_EXPRESSION "Total points: 13"
)
