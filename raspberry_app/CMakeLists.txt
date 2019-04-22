cmake_minimum_required(VERSION 3.13)
project(robo1)

set(CMAKE_CXX_STANDARD 14)

include_directories(..)
include_directories(path)
include_directories(robo)

add_executable(robo1
        path/coordinates.cpp
        path/coordinates.h
        path/path.cpp
        path/path.h
        path/path_base.cpp
        path/path_base.h
        robo/main.cpp engine/engine.cpp engine/engine.h servos/servo.cpp servos/servo.h controller/controller.cpp controller/controller.h action_interface/action.h lights/led.cpp lights/led.h controller/connection/sender/sender.cpp controller/connection/sender/sender.h controller/connection/receiver/receiver.cpp controller/connection/receiver/receiver.h)
