#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "include/io.h"
#include "include/device_state.h"
#include "include/motors.h"

#include "magnet.c"
#include "pathfinding.c"
#include "motors.c"
// #include "keypad.c"


int main(void) {

    init_h_bridges();   

    calibrate(1, 1);

    findpath(1, 1, 4, 4);

    
    return 0;

}