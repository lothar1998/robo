cmake_minimum_required(VERSION 3.13)
project(robo1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(path)
include_directories(robo)

add_executable(robo1
        path/coordinates.cpp
        path/coordinates.h
        path/path.cpp
        path/path.h
        path/path_base.cpp
        path/path_base.h
        robo/main.cpp)
