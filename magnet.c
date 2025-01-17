#include <avr/io.h>

#include "include/io.h"

void initMagnet() {
    DDRA |= (1 << MAGNET);
    
}
void magnetOn() {
    PORTA |= (1 << MAGNET);
}

void magnetOff() {
    PORTA &= ~(1 << MAGNET);
}

