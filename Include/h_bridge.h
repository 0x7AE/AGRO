/*
 * h_bridge.h - XvR 2020
 */

#ifndef _H_BRIDGE_H_
#define _H_BRIDGE_H_

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
#define PIN_A_RPWM	PB7
#define DDR_A_RPWM	DDRB

#define PORTB_A_LPWM PORTB
#define PIN_A_LPWM	PB6
#define DDR_A_LPWM	DDRB

#define PORTB_B_RPWM PORTB
#define PIN_B_RPWM	PB5
#define DDR_B_RPWM	DDRB

#define PORTB_B_LPWM PORTB
#define PIN_B_LPWM	PB4
#define DDR_B_LPWM	DDRB

#define PORTB_C_RPWM	PORTH
#define PIN_C_RPWM	PH6
#define DDR_C_RPWM	DDRH

#define PORTB_C_LPWM PORTH
#define PIN_C_LPWM	PH5
#define DDR_C_LPWM	DDRH


void init_h_bridges(void);
void motor_set_speed_percentage(signed char percentage);

#endif /* _H_BRIDGE_H_ */
