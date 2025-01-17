#ifndef DEVICE_STATE_H

#define DEVICE_STATE_H
    
#include <avr/io.h>

// Robot movement states
typedef enum {
    IDLE,
    FORWARD,
    REVERSE,
    STOP
} DeviceState;

typedef enum {
    MAGNET_ON,
    MAGNET_OFF
} Component;

#endif


