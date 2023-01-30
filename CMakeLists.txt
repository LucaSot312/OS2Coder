cmake_minimum_required(VERSION 3.24)
project(OS2Coder C)

set(CMAKE_C_STANDARD 11)

add_executable(OS2Coder main.c library.h)
target_link_libraries(OS2Coder PUBLIC libcrypt.so)