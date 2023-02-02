cmake_minimum_required(VERSION 3.24)
project(NumberGuesser)

set(CMAKE_CXX_STANDARD 23)

add_executable(NumberGuesser main.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static")