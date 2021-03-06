//
// Created by Piotr on 12.04.2019.
//
#ifndef ROBO1_ENGINE_H
#define ROBO1_ENGINE_H
#include "raspberry_app/action_interface/setAction.h"


class engine: public setAction{
public:

    typedef unsigned int runtime;
    typedef unsigned int speed;

    enum channel{
        CH0 = 0,
        CH1 = 5
    };

    enum direction{
        FORWARD = 1,
        BACKWARD = 0,
    };


    engine(channel,unsigned int = 50, unsigned int = 0x41);

    bool startEngine(direction,speed);
    bool startEngine(direction,speed,runtime);

    bool startEngineMin(direction);
    bool startEngineMin(direction,runtime);

    bool startEngineMid(direction);
    bool startEngineMid(direction,runtime);

    bool startEngineMax(direction);
    bool startEngineMax(direction,runtime);

    void stopEngineImmediately();
    void stopEngine();

    void takeSetAction(unsigned int) override;


private:

    enum registers{
        __SUBADR1            = 0x02,
        __SUBADR2            = 0x03,
        __SUBADR3            = 0x04,
        __MODE1              = 0x00,
        __PRESCALE           = 0xFE,
        __LED0_ON_L          = 0x06,
        __LED0_ON_H          = 0x07,
        __LED0_OFF_L         = 0x08,
        __LED0_OFF_H         = 0x09,
        __ALLLED_ON_L        = 0xFA,
        __ALLLED_ON_H        = 0xFB,
        __ALLLED_OFF_L       = 0xFC,
        __ALLLED_OFF_H       = 0xFD
    };

    enum speedLevel{
        SLOW = 20,
        MEDIUM = 50,
        FAST = 100
    };

    int bus;

    channel ch;
    unsigned int frequency;
    unsigned int address;

    void write(unsigned int,unsigned int);
    unsigned int read(unsigned int);
    void setPWMFreq(unsigned int);
    void setPWM(unsigned int, unsigned int, unsigned int);

};


#endif //ROBO1_ENGINE_H
