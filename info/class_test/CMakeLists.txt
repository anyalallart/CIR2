cmake_minimum_required(VERSION 3.23)
project(class_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(class_test main.cpp class.h cmake-build-debug/class.cpp class.cpp)
