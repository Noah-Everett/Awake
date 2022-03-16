cmake_minimum_required(VERSION 3.21)
project(Awake)

set(CMAKE_CXX_STANDARD 20)

add_executable(awake main.cpp)

install(TARGETS awake)