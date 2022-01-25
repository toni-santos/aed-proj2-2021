cmake_minimum_required(VERSION 3.20)
project(aed_proj2_2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj2_2021 src/main.cpp src/Reader.cpp includes/Reader.h src/Utils.cpp includes/Utils.h includes/constants.h)
