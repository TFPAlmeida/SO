cmake_minimum_required(VERSION 3.20)
project(SO C)

set(CMAKE_C_STANDARD 99)

add_executable(SO main.c process.c process.h pipes.c pipes.h)
