#ifndef SWITCH_H

#define SWITCH_H

// Led Pins
#define D1 PH1
#define D2 PH2
#define D3 PH3


// Switch pins
#define S1 PD1
#define S2 PD2
#define S3 PD3


void initSwitches();
void initLed();
void activateLed();


#endif