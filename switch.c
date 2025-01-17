// Include the necessary AVR headers
#include <avr/io.h>

#include "include/io.h"

void initSwitches() {

    // Initialize magnet on A-pin
    DDRA |= (1 << MAGNET);
    PORTA &= ~(1 << MAGNET);

    // Initialize B-pins for switches 1-4
    for(uint8_t i = SWITCH1; i <= SWITCH4; i++)
    {
        DDRB |= (1<< i);
        PORTB &= ~(1<< i);
    } 

    // Initialize K-pins for switches 5-10
    for(uint8_t i = SWITCH5; i <= SWITCH11; i++)
    {
        DDRK |= (1<< i);
        PORTK &= ~(1<< i);
    } 
}

void readSwitch(uint8_t i) {

}






