#ifndef _IO_H_
#define _IO_H_

#include <avr/io.h>

// Limit switches for positions of x-axis
#define VERT1 PB1 //  Digital 20
#define VERT2 PB0 // Digital 19
#define VERT3 PB3 // Digital 22
#define VERT4 PB2 // Digital 21
#define VERT5 PK0 // Digital A8
#define HOR1 PK1 // Digital A9
#define HOR2 PK2 // Digital A10
#define HOR3 PK3 // Digital A11
#define HOR4 PK4 // Digital A12
#define HOR5 PK5 // Digital A13
#define MAG1 PK6 // Digital A14


// Magnet pin definitions
#define MAGNET PA0 // Digital 78

// Interface pins
// #define X PA1
// #define Y PA2
// #define START PA4
// #define STOP PA5

// Keypad pins on Port C (for a 4x4 keypad, for example)
// #define KEY_PRT PORTC
// #define KEY_DDR DDRC
// #define KEY_PIN PINC

// Keypad pins definitions
#define OUTPUT1   PC0
#define OUTPUT2   PC1
#define OUTPUT3   PC2
#define OUTPUT4   PC3

#define KEYPAD_PORT     PORTC
#define KEYPAD_DDR      DDRC
#define KEYPAD_PIN      PINC


// Function prototypes
void initSwitches(void);              // Initializes the pins for the switches, magnet, etc.              // Initializes the keypad
void initMagnet(void);  
                                  
void ledOn(uint8_t state);          // Turns an LED on/off based on state
uint8_t readSwitch(void);           // Reads the state of the switches
void magnetOn(void);                // Turns the magnet on
void magnetOff(void);               // Turns the magnet off

#endif
