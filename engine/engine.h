//
// Created by Piotr on 12.04.2019.
//
#pragma once
#ifndef ROBO1_ENGINE_H
#define ROBO1_ENGINE_H
#include <wiringPi.h>


class engine {



public:

    typedef unsigned int enginePin;
    typedef unsigned int pwmPin;
    typedef unsigned int customSpeed;
    typedef unsigned int time;

    enum direction{
        FORWARD = 0,
        BACKWARD = 1
    };

    enum speed{
        STOP = 0,
        SLOW = 700,
        MEDIUM = 850,
        FAST = 1024
    };

    engine() = default;
    engine(pwmPin,enginePin,enginePin);

    void run(direction);
    void run(direction,speed);
    void run(direction,speed, time);
    void run(direction,customSpeed);
    void run(direction,customSpeed,time);

    void stop();

private:
    enginePin enginePinNumber1, enginePinNumber2;
    pwmPin pwmPinNumber;
    void enable_engine(direction,customSpeed,time);

};


#endif //ROBO1_ENGINE_H
