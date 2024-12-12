#ifndef _INPUT_H_

#define _INPUT_H_

#include <avr\io.h>

#define SWITCH1_PIN PD2 // First limit switch
#define LED  PB5
// #define SWITCH2_PIN     PA2 // Second limit switch
// #define SWITCH3_PIN     PA4 // Third limit switch
// #define SWITCH4_PIN     PC2  // Fourth limit switch
// #define SWITCH5_PIN     PA3  // Fifth limit switch

// Function prototypes
void initPins(void);
void ledOn(uint8_t state);
uint8_t readSwitch(void);


#endif
