// Include the necessary AVR headers
#include <avr/io.h>
#include <util/delay.h>
#include "include/math.h"
#include "include\h_bridge.h"

#include "include\switch.h"

void initSwitches() {

    for(uint8_t i = S1; i <= S4; i++)
    {
        DDRB |= (1<< i);
        PORTB &= ~(1<< i);
    } 

    for(uint8_t i = S5; i <= S10; i++)
    {
        DDRK |= (1<< i);
        PORTK &= ~(1<< i);
    } 
    // DDRB &= ~(1<< S1);
    // DDRB &= ~(1<< S2);
    // DDRB &= ~(1<< S3);
    // DDRB &= ~(1<< S4);
    // DDRK &= ~(1<< S5);
    // DDRK &= ~(1<< S6);
    // DDRK &= ~(1<< S7);
    // DDRK &= ~(1<< S8);
    // DDRK &= ~(1<< S9);
    // DDRK &= ~(1<< S10);
   
    // PORTB |= (1 << S1);
    // PORTB |= (1 << S2);
    // PORTB |= (1 << S3);
    // PORTB |= (1 << S4);
    // PORTK |= (1 << S5);
    // PORTK |= (1 << S6);
    // PORTK |= (1 << S7);
    // PORTK |= (1 << S8);
    // PORTK |= (1 << S9);
    // PORTK |= (1 << S10);

}







