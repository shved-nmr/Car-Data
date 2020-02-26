cmake_minimum_required(VERSION 3.14)
project(cardata)

set(CMAKE_CXX_STANDARD 14)

add_executable(cardata main.cpp cmake-build-debug/Data.cpp cmake-build-debug/Data.h)