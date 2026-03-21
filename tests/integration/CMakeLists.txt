cmake_minimum_required(VERSION 3.21)
project(numops_consumer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(numops CONFIG REQUIRED)

add_executable(consumer src/main.cpp)
target_link_libraries(consumer PRIVATE numops::numops)
