cmake_minimum_required(VERSION 3.10)

project(AlgebraProject)

set(CMAKE_C_STANDARD 11)

add_executable(algebra_app src/main.c src/algebra.c)

target_include_directories(algebra_app PRIVATE inc)