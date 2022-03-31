cmake_minimum_required(VERSION 3.16)
project(task211)

set(CMAKE_CXX_STANDARD 20)

add_executable(run main.cpp src/filesearch_algo.cpp src/filesearch_algo.h src/SuffixAuto.cpp src/SuffixAuto.h)
