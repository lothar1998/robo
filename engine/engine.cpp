//
// Created by Piotr on 12.04.2019.
//

#include "engine.h"
#include <wiringPi.h>

engine::engine(pwmPin pwmPinNumber,enginePin enginePin1, enginePin enginePin2):pwmPinNumber(pwmPinNumber),enginePinNumber1(enginePin1),enginePinNumber2(enginePin2){
    pinMode(pwmPinNumber,PWM_OUTPUT);
    pinMode(enginePin1,OUTPUT);
    pinMode(enginePin2,OUTPUT);
}

void engine::stop() {
    digitalWrite(enginePinNumber1,LOW);
    digitalWrite(enginePinNumber2,LOW);
    pwmWrite(pwmPinNumber,0);
}

void engine::enable_engine(engine::direction dir, engine::customSpeed engineSpeed, engine::time runtime) {
    if(dir==FORWARD){
        digitalWrite(enginePinNumber1,HIGH);
        digitalWrite(enginePinNumber2,LOW);
    }
    else{
        digitalWrite(enginePinNumber1,HIGH);
        digitalWrite(enginePinNumber2,LOW);
    }

    if(engineSpeed>0)
        pwmWrite(pwmPinNumber,engineSpeed);
    else
        pwmWrite(pwmPinNumber,512);

    if(runtime>0){
        delay(runtime);
        this->stop();
    }
}

void engine::run(engine::direction dir) {

    enable_engine(dir,0,0);
}

void engine::run(engine::direction dir, engine::speed speedOfEngine) {

    enable_engine(dir,speedOfEngine,0);
}

void engine::run(engine::direction dir, engine::customSpeed speedOfEngine) {

    enable_engine(dir,speedOfEngine,0);
}

void engine::run(engine::direction dir, engine::speed speedOfEngine, engine::time runtime) {

    enable_engine(dir,speedOfEngine,runtime);
}

void engine::run(engine::direction dir, engine::customSpeed speedOfEngine, engine::time runtime) {

    enable_engine(dir,speedOfEngine,runtime);
}