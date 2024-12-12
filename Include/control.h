#ifndef CONTROL_H

#define CONTROL_H
    
#include <avr/io.h>


typedef bool (*AGRO_EVENT)(void);
typedef void (*AGRO_ACTION )(void);

typedef enum AGRO_STATE {
    MOVINGx,  MOVINGy,  MOVINGz, PICKING, STOPPED
} 

typedef struct AGRO_EVENTS {
     AGRO_STATE current;
     AGRO_EVENT ledOn;
     AGRO_EVENT switchOff;
}
 
bool noEvent();
bool noAction();
bool isLedOn();
void turnLedOn();

#endif


