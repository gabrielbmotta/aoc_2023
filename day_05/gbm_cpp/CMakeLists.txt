cmake_minimum_required(VERSION 3.14)
project(proc LANGUAGES CXX)

set(SOURCES
    main.cpp)

find_package(OpenMP REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

