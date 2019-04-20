//
// Created by Piotr on 20.04.2019.
//

#include "led.h"
#include <wiringPi.h>

led::led(led::pin pin):num_pin(pin) {
    wiringPiSetup();
    pinMode(num_pin, OUTPUT);
}

void led::on() {
    digitalWrite(num_pin,HIGH);
}

void led::off(){
    digitalWrite(num_pin,LOW);
}

void led::takeAction(unsigned int command) {
    if(((command)>>28u)==0x2)
        if((((command)>>20u)&0x0FFu)==(unsigned int)num_pin){
            switch((((command)>>16u)&0x000Fu)){
                case 0x0: this->on();
                    break;
                case 0x1: this->off();
                    break;
                default:
                    break;
            }
        }
}