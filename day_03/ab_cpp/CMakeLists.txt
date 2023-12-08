cmake_minimum_required(VERSION 3.10)

project(EngineSchematicSummation)

add_executable(EngineSchematicSummation engine_schematic_summation.cpp)

enable_testing()

add_test(NAME Example COMMAND EngineSchematicSummation input_example
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
set_tests_properties(Example
    PROPERTIES PASS_REGULAR_EXPRESSION "Sum of part numbers: 4361"
)
