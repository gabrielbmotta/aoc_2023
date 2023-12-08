cmake_minimum_required(VERSION 3.10)

project(EngineSchematicSummation)

add_executable(EngineSchematicSummation engine_schematic_summer.cpp)

enable_testing()

add_test(NAME Example COMMAND EngineSchematicSummation)
