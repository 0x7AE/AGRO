#ifndef STATE_H

#define STATE_H
    
#include <avr/io.h>

typedef enum {
    IDLE,
    PATHFINDING,
    PICKUP_BLOCK,
    MOVE,
    DROP_BLOCK
} State;


#endif


