//
// Created by Piotr on 14.04.2019.
//

#include "servo.h"
#include <wiringPiI2C.h>
#include <exception>
#include <cmath>
#include <iostream>

using namespace std;

servo::servo(channel ch, unsigned int frequency, unsigned int address) {
    bus=wiringPiI2CSetup(address);
    this->address=address;
    this->write(__MODE1,0x00);
    this->ch = ch;
    this->frequency=frequency;
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

bool servo::setServoAngle(unsigned int angle) {
    std::cout<<"servoAngle"<<std::endl;
    if(angle>=0&&angle<=360) {
        this->setPWM(0, angle + 140);
        return true;
    }
    else
        return false;
}

bool servo::setServoMin() {
    std::cout<<"setMin"<<std::endl;
    return this->setServoAngle(0);
}

bool servo::setServoMid() {
    std::cout<<"setMid"<<std::endl;
    return this->setServoAngle(180);
}

bool servo::setServoMax() {
    std::cout<<"setMax"<<std::endl;
    return this->setServoAngle(360);
}

void servo::takeAction(const unsigned int command){
    std::cout<<command<<std::endl;
    if(((command)>>28u)==0x0)
        if((((command)>>24u)&0xFu)==(unsigned int)ch){
            switch(((command)>>16u)&0xFFu){
                case 0x00: this->setServoAngle(((command)&0xFFFFu));
                    break;
                case 0x01: this->setServoMin();
                    break;
                case 0x02: this->setServoMid();
                    break;
                case 0x03: this->setServoMax();
                    break;
                default:
                    break;
            }
        }
}