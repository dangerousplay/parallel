cmake_minimum_required(VERSION 3.17)
project(parallel)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable(parallel pthread.cpp sort.h)

find_package(Threads REQUIRED)
FIND_PACKAGE(OpenMP)

target_link_libraries(parallel PRIVATE Threads::Threads)