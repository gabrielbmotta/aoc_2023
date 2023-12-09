cmake_minimum_required(VERSION 3.10)

project(BoatingSchool VERSION 1.0)

configure_file(main.h.in main.h)

add_executable(BoatingSchool main.cpp)
target_include_directories(BoatingSchool PUBLIC
    ${PROJECT_BINARY_DIR}
)
