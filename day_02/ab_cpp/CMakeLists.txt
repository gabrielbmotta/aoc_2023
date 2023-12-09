cmake_minimum_required(VERSION 3.10)

project(CubeGame)

add_executable(CubeGame cube_game.cpp)

enable_testing()
add_test(NAME Example COMMAND CubeGame ${PROJECT_SOURCE_DIR}/test_input)
set_tests_properties(Example
    PROPERTIES PASS_REGULAR_EXPRESSION "8"
)
