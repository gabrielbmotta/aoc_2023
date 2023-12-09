cmake_minimum_required(VERSION 3.10)

project(SeedMapper VERSION 1.0)

configure_file(main.h.in main.h)

add_library(SeedMap seed_map.cpp)
target_include_directories(SeedMap PUBLIC
    ${PROJECT_SOURCE_DIR}
)

add_library(SeedMapper seed_mapper.cpp)
target_include_directories(SeedMapper PUBLIC
    ${PROJECT_SOURCE_DIR}
)
target_link_libraries(SeedMapper PUBLIC SeedMap)

add_executable(SeedMapperExe main.cpp)
target_include_directories(SeedMapperExe PUBLIC
    ${PROJECT_BINARY_DIR}
)
target_link_libraries(SeedMapperExe PUBLIC SeedMapper)

enable_testing()

add_test(NAME Example COMMAND SeedMapperExe ${PROJECT_SOURCE_DIR}/input_example)
set_tests_properties(Example
    PROPERTIES PASS_REGULAR_EXPRESSION "Lowest location: 35"
)
