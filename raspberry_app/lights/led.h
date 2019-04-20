//
// Created by Piotr on 20.04.2019.
//

#ifndef ROBO1_LED_H
#define ROBO1_LED_H
#include "raspberry_app/action_interface/action.h"

class led: public action {
public:
    enum pin{
        PIN0 = 0,
        PIN1 = 1,
        PIN2 = 2,
        PIN3 = 3,
        PIN4 = 4,
        PIN5 = 5,
        PIN6 = 6,
        PIN7 = 7,
        PIN8 = 8,
        PIN9 = 9,
        PIN10 = 10,
        PIN11 = 11,
        PIN12 = 12,
        PIN13 = 13,
        PIN14 = 14,
        PIN15 = 15,
        PIN16 = 16,
        PIN17 = 17,
        PIN18 = 18,
        PIN19 = 19,
        PIN20 = 20,
        PIN21 = 21,
        PIN22 = 22,
        PIN23 = 23,
        PIN24 = 24,
        PIN25 = 25,
        PIN26 = 26,
        PIN27 = 27,
        PIN28 = 28,
        PIN29 = 29
    };

    led(pin);

    void on();
    void off();

    void takeAction(unsigned int) override ;

private:

    pin num_pin;

};


#endif //ROBO1_LED_H
