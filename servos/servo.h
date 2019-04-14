//
// Created by Piotr on 14.04.2019.
//

#ifndef ROBO1_SERVO_H
#define ROBO1_SERVO_H

class servo {

public:
    typedef unsigned int reg;

    enum channel{
        CH0 = 0,
        CH1 = 1,
        CH2 = 2,
        CH3 = 3,
        CH4 = 4,
        CH5 = 5,
        CH6 = 6,
        CH7 = 7,
        CH8 = 8,
        CH9 = 9,
        CH10 = 10,
        CH11 = 11,
        CH12 = 12,
        CH13 = 13,
        CH14 = 14,
        CH15 = 15
    };

    servo(unsigned int  = 0x40);

    void setPWMFreq(unsigned int);
    void setPWM(channel,unsigned int, unsigned int);
    void setServoPulse(channel, unsigned int);


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

    int bus;
    unsigned int address;
    unsigned int mode;

    void write(reg,unsigned int);
    unsigned int read(reg);
};


#endif //ROBO1_SERVO_H
