cmake_minimum_required(VERSION 3.21)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(numops CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example PRIVATE numops::numops)
