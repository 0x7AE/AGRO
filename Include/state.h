#ifndef STATE_H

#define STATE_H

#include <avr/io.h>


typedef int AGRO_EVENT;
typedef void AGRO_ACTION;

enum AGRO_STATE {
    MOVINGx,  MOVINGy,  MOVINGz, PICKING, STOPPED
};

 
int noEvent(); 
int noAction();
int isLedOn();
void turnLedOn();

#endif


