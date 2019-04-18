cmake_minimum_required(VERSION 3.13)
project(robo1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(raspberry_app/path)
include_directories(raspberry_app/robo)

add_executable(robo1
        raspberry_app/path/coordinates.cpp
        raspberry_app/path/coordinates.h
        raspberry_app/path/path.cpp
        raspberry_app/path/path.h
        raspberry_app/path/path_base.cpp
        raspberry_app/path/path_base.h
        raspberry_app/robo/main.cpp raspberry_app/engine/engine.cpp raspberry_app/engine/engine.h raspberry_app/servos/servo.cpp raspberry_app/servos/servo.h raspberry_app/controller/controller.cpp raspberry_app/controller/controller.h raspberry_app/action_interface/action.h raspberry_app/test/remote.cpp raspberry_app/test/controller_test.cpp)
