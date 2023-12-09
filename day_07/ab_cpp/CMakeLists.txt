cmake_minimum_required(VERSION 3.10)

project(CamelCardWinner VERSION 1.0)

configure_file(main.h.in main.h)

add_executable(CamelCardWinner main.cpp)
target_include_directories(CamelCardWinner PUBLIC
    ${PROJECT_BINARY_DIR}
)
