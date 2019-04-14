//
// Created by Piotr on 14.04.2019.
//

#include "servo.h"
#include <wiringPiI2C.h>
#include <exception>
#include <cmath>

using namespace std;

servo::servo(unsigned int address, channel ch, unsigned int frequency) {
    bus=wiringPiI2CSetup(address);
    this->address=address;
    this->write(__MODE1,0x00);
    this->ch = ch;
    this->setPWMFreq(frequency);
}

void servo::write(servo::reg reg, unsigned int value) {
    wiringPiI2CWriteReg8(bus,reg,value);
}

unsigned int servo::read(servo::reg reg) {
    return wiringPiI2CReadReg8(bus,reg);
}

void servo::setPWMFreq(unsigned int frequency) {
    float prescaleval = 25000000;
    prescaleval /= 4096.0;
    prescaleval /= float(frequency);
    prescaleval -= 1.0;

    int prescale = floor(prescaleval + 0.5);

    unsigned int old_mode = this->read(__MODE1);
    unsigned int new_mode = (old_mode & 0x7F) | 0x10;

    this->write(__MODE1,new_mode);
    this->write(__PRESCALE,int(floor(prescale)));
    this->write(__MODE1, old_mode | 0x80);

}

void servo::setPWM( unsigned int on, unsigned int off) {
    this->write(__LED0_ON_L+4*ch, on & 0xFF);
    this->write(__LED0_OFF_H+4*ch, on >> 8);
    this->write(__LED0_OFF_L+4*ch, off & 0xFF);
    this->write(__LED0_OFF_H+4*ch, off >> 8);
}

void servo::setServoPulse(unsigned int pulse) {
    pulse = pulse*4096/20000;
    this->setPWM(ch, 0, int(pulse));
}
