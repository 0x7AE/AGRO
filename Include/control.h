#ifndef CONTROL_H

#define CONTROL_H

#include <avr/io.h>


typedef int AGRO_EVENT;
typedef void AGRO_ACTION;

enum AGRO_STATE {
    MOVINGx,  MOVINGy,  MOVINGz, PICKING, STOPPED
};

struct AGRO_EVENTS {
     AGRO_EVENT ledOn;r
     AGRO_EVENT switchOff;
};
 
int noEvent(); c dx
int noAction();
int isLedOn();
void turnLedOn();

#endif


