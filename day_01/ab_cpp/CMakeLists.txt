cmake_minimum_required(VERSION 3.10)

project(Trebuchet)

add_executable(Trebuchet trebuchet.cpp)

enable_testing()

add_test(NAME Example COMMAND Trebuchet ${PROJECT_SOURCE_DIR}/test_input.txt)
set_tests_properties(Example
    PROPERTIES PASS_REGULAR_EXPRESSION "Sum of all of the calibration values: 142"
)

add_test(NAME Example2 COMMAND Trebuchet ${PROJECT_SOURCE_DIR}/test_input_2.txt)
set_tests_properties(Example2
    PROPERTIES PASS_REGULAR_EXPRESSION "Sum of all of the calibration values: 281"
)
