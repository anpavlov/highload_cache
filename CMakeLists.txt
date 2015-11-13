cmake_minimum_required(VERSION 2.8.4)
project(cache)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

set(SOURCE_FILES main.c)
add_executable(cache ${SOURCE_FILES})