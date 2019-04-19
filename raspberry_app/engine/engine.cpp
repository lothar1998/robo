//
// Created by Piotr on 12.04.2019.
//

#include "engine.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <cmath>

engine::engine(engine::channel ch, unsigned int frequency, unsigned int address):ch(ch),frequency(frequency),address(address){
    bus=wiringPiI2CSetup(address);
    this->write(__MODE1,0x00);
    this->setPWMFreq(frequency);
}

void engine::write(unsigned int reg, unsigned int value) {
    wiringPiI2CWriteReg8(bus,reg,value);
}

unsigned int engine::read(unsigned int reg) {
    return wiringPiI2CReadReg8(bus,reg);
}

void engine::setPWMFreq(unsigned int frequency) {
    float prescaleval = 25000000;
    prescaleval /= 4096.0;
    prescaleval /= float(frequency);
    prescaleval -= 1.0;

    int prescale = floor(prescaleval + 0.5);

    unsigned int old_mode = this->read(__MODE1);
    unsigned int new_mode = (old_mode & 0x7Fu) | 0x10u;

    this->write(__MODE1, new_mode);
    this->write(__PRESCALE, prescale);
    this->write(__MODE1, old_mode | 0x80u);
}

void engine::setPWM(unsigned int ch, unsigned int on, unsigned int off) {
    this->write(__LED0_ON_L+4*ch, on & 0xFFu);
    this->write(__LED0_OFF_H+4*ch, on >> 8u);
    this->write(__LED0_OFF_L+4*ch, off & 0xFFu);
    this->write(__LED0_OFF_H+4*ch, off >> 8u);
}

bool engine::startEngine(engine::direction dir, engine::speed speed, engine::runtime time) {

    if(speed>=0&&speed<=4095) {
        if (dir == FORWARD) {
            if(ch==CH1){
                this->setPWM(ch, 0, speed);
                this->setPWM(1, 0, 0);
                this->setPWM(2, 0, 4095);
            } else{
                this->setPWM(ch, 0, speed);
                this->setPWM(3, 0, 0);
                this->setPWM(4, 0, 4095);
            }
        } else if(dir == BACKWARD){
            if(ch==CH1){
                this->setPWM(ch, 0, speed);
                this->setPWM(1, 0, 4095);
                this->setPWM(2, 0, 0);
            } else{
                this->setPWM(ch, 0, speed);
                this->setPWM(3, 0, 4095);
                this->setPWM(4, 0, 0);
            }
        }

        if (time > 0) {
            delay(time);
            this->stopEngine();
        }

        return true;
    }
    else
        return false;
}

bool engine::startEngine(engine::direction dir, engine::speed speed) {
    return this->startEngine(dir,speed,0);
}

bool engine::startEngineMin(engine::direction dir) {
    return this->startEngine(dir,engine::speedLevel::SLOW,0);
}

bool engine::startEngineMin(engine::direction dir, engine::runtime time) {
    return this->startEngine(dir,engine::speedLevel::SLOW,time);
}

bool engine::startEngineMid(engine::direction dir) {
    return this->startEngine(dir,engine::speedLevel::MEDIUM,0);
}

bool engine::startEngineMid(engine::direction dir, engine::runtime time) {
    return this->startEngine(dir,engine::speedLevel::MEDIUM,time);
}

bool engine::startEngineMax(engine::direction dir) {
    return this->startEngine(dir,engine::speedLevel::FAST,0);
}

bool engine::startEngineMax(engine::direction dir, engine::runtime time) {
    return this->startEngine(dir,engine::speedLevel::FAST,time);
}

void engine::stopEngineImmediately() {
    this->setPWM(ch,0,0);
}

void engine::stopEngine(){
    if(ch==CH1){
        this->setPWM(ch,0,0);
        this->setPWM(1,0,0);
        this->setPWM(2,0,0);
    } else{
        this->setPWM(ch,0,0);
        this->setPWM(3,0,0);
        this->setPWM(4,0,0);
    }
}

void engine::takeAction(unsigned int command) {

}