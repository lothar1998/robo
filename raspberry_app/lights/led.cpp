//
// Created by Piotr on 20.04.2019.
//

#include "led.h"
#include <wiringPi.h>

led::led(led::pin pin):num_pin(pin) {

}

void led::on() {
    digitalWrite(num_pin,HIGH);
}

void led::off(){
    digitalWrite(num_pin,LOW);
}

void led::takeAction(unsigned int command) {

}