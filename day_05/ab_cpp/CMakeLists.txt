cmake_minimum_required(VERSION 3.10)

project(SeedMapper VERSION 1.0)

configure_file(seed_mapper.h.in seed_mapper.h)

add_executable(SeedMapper seed_mapper.cpp)
target_include_directories(SeedMapper PUBLIC
    ${PROJECT_BINARY_DIR}
)
