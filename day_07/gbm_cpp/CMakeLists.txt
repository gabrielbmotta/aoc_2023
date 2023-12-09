cmake_minimum_required(VERSION 3.14)
project(caravan LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

