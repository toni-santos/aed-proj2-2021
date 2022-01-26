cmake_minimum_required(VERSION 3.20)
project(aed_proj2_2021)

set(CMAKE_CXX_STANDARD 17)

add_executable(aed_proj2_2021 src/main.cpp src/Utils.cpp src/graph.cpp includes/graph.h includes/minHeap.h includes/Utils.h includes/constants.h src/Stop.cpp includes/Stop.h)
