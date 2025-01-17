/*
 * h_bridge.h - XvR 2020
 */

#ifndef MOTORS_H
#define MOTORS_H

#include <avr/io.h>

// These pins are available on the shield via the header:
//
//		Mega	Uno
// digital 5	PE3	PD5
// digital 6    
// digital 9	PH6	PB1
// analog 5	PF5	PC5

// The settings below are for the Mega, modify
// in case you want to use other pins
#define PORTB_A_RPWM  PORTB 
#define PIN_A_RPWM	PB7 // Digital pin 13 on Mega
#define DDR_A_RPWM	DDRB

#define PORTB_A_LPWM PORTB 
#define PIN_A_LPWM	PB6 // Digital pin 12 on Mega
#define DDR_A_LPWM	DDRB

#define PORTB_B_RPWM PORTB
#define PIN_B_RPWM	PB5 // Digital pin 11 on Mega
#define DDR_B_RPWM	DDRB

#define PORTB_B_LPWM PORTB
#define PIN_B_LPWM	PB4 // Digital pin 10 on Mega
#define DDR_B_LPWM	DDRB

#define PORTH_C_RPWM	PORTH
#define PIN_C_RPWM	PH6 // Digital pin 9 on Mega
#define DDR_C_RPWM	DDRH

#define PORTH_C_LPWM PORTH
#define PIN_C_LPWM	PH5 // Digital pin 8 on Mega
#define DDR_C_LPWM	DDRH
typedef enum {
    MOTOR_A,
    MOTOR_B,
    MOTOR_C
} MotorID;
// H-Bridge control function declarations
extern void init_h_bridges(void);
extern void init_motor_a(void);
extern void init_motor_b(void);
extern void init_motor_c(void);
extern void disable_motor_a(void);
extern void disable_motor_b(void);
extern void disable_motor_c(void);
extern void disable_h_bridges(void);
extern void motor_set_speed_percentage(MotorID id, signed char percentage);



typedef struct {
    volatile uint8_t *port_rpwm; // Pointer to RPWM port
    uint8_t pin_rpwm;            // RPWM pin number
    volatile uint8_t *port_lpwm; // Pointer to LPWM port
    uint8_t pin_lpwm;            // LPWM pin number
} MotorConfig;

MotorConfig motors[] = {
    {&PORTB, PIN_A_RPWM, &PORTB, PIN_A_LPWM}, // MOTOR_A
    {&PORTB, PIN_B_RPWM, &PORTB, PIN_B_LPWM}, // MOTOR_B
    {&PORTH, PIN_C_RPWM, &PORTH, PIN_C_LPWM}  // MOTOR_C
};

#endif /* _H_BRIDGE_H_ */
