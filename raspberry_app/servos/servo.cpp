//
// Created by Piotr on 14.04.2019.
//

#include "servo.h"
#include <wiringPiI2C.h>
#include <cmath>


using namespace std;

servo::servo(channel ch, unsigned int frequency, unsigned int address):ch(ch),frequency(frequency),address(address) {
    bus=wiringPiI2CSetup(address);
    this->write(__MODE1,0x00);
    this->setPWMFreq(frequency);
}

void servo::write(unsigned int reg, unsigned int value) {
    wiringPiI2CWriteReg8(bus,reg,value);
}

unsigned int servo::read(unsigned int reg) {
    return wiringPiI2CReadReg8(bus,reg);
}

void servo::setPWMFreq(unsigned int frequency) {
    float prescaleval = 25000000;
    prescaleval /= 4096.0;
    prescaleval /= float(frequency);
    prescaleval -= 1.0;

    int prescale = floor(prescaleval + 0.5);

    unsigned int old_mode = this->read(__MODE1);
    unsigned int new_mode = (old_mode & 0x7Fu) | 0x10u;

    this->write(__MODE1,new_mode);
    this->write(__PRESCALE,int(floor(prescale)));
    this->write(__MODE1, old_mode | 0x80u);

}

void servo::setPWM( unsigned int on, unsigned int off) {
    this->write(__LED0_ON_L+4*ch, on & 0xFFu);
    this->write(__LED0_OFF_H+4*ch, on >> 8u);
    this->write(__LED0_OFF_L+4*ch, off & 0xFFu);
    this->write(__LED0_OFF_H+4*ch, off >> 8u);
}

bool servo::setServoAngle(unsigned int angle) {

    if(angle>=0&&angle<=360) {
        this->setPWM(0, angle + 140);
        return true;
    }
    else
        return false;
}

bool servo::setServoMin() {

    return this->setServoAngle(0);
}

bool servo::setServoMid() {

    return this->setServoAngle(180);
}

bool servo::setServoMax() {

    return this->setServoAngle(360);
}

void servo::takeSetAction(const unsigned int command){

    if(((command)>>28u)==0x0)
        if((((command)>>24u)&0x0Fu)==(unsigned int)ch){
            switch((((command)>>16u)&0x00FFu)){
                case 0x00: this->setServoAngle(((command)&0x0000FFFFu));
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