/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "include/h_bridge.h"
	
volatile uint8_t motor_stop_flag = 0;
 

ISR(TIMER0_OVF_vect)
{
	if (OCR0A == 0 && OCR0B == 0)
	{
		PORT_A_RPWM &= ~(1<<PIN_A_RPWM);
		PORT_A_LPWM &= ~(1<<PIN_A_LPWM);
		PORT_B_RPWM &= ~(1<<PIN_B_RPWM);
		PORT_B_LPWM &= ~(1<<PIN_B_LPWM);
		PORT_C_RPWM &= ~(1<<PIN_C_RPWM);
		PORT_C_LPWM &= ~(1<<PIN_C_LPWM);
	}
	else if (OCR0A != 0)
	{
		PORT_A_LPWM &= ~(1<<PIN_A_LPWM);
		PORT_A_RPWM |= (1<<PIN_A_RPWM);
		PORT_B_LPWM &= ~(1<<PIN_B_LPWM);
		PORT_B_RPWM |= (1<<PIN_B_RPWM);
		PORT_C_LPWM &= ~(1<<PIN_C_LPWM);
		PORT_C_RPWM |= (1<<PIN_C_RPWM);
	}
	else if (OCR0B != 0)
	{
		PORT_A_LPWM &= ~(1<<PIN_A_LPWM);
		PORT_A_RPWM |= (1<<PIN_A_RPWM);
		PORT_B_LPWM &= ~(1<<PIN_B_LPWM);
		PORT_B_RPWM |= (1<<PIN_B_RPWM);
		PORT_C_LPWM &= ~(1<<PIN_C_LPWM);
		PORT_C_RPWM |= (1<<PIN_C_RPWM);
	}
}

ISR(TIMER0_COMPA_vect)
{
	if (OCR0A != 255)
	{
		PORT_A_RPWM &= ~(1<<PIN_A_RPWM);
		PORT_B_RPWM &= ~(1<<PIN_B_RPWM);
		PORT_C_RPWM &= ~(1<<PIN_C_RPWM);
	}
}

ISR(TIMER0_COMPB_vect)
{
	if (OCR0B != 255)
	{
		PORT_A_LPWM &= ~(1<<PIN_A_LPWM);
		PORT_B_RPWM &= ~(1<<PIN_B_RPWM);
		PORT_C_RPWM &= ~(1<<PIN_C_RPWM);
	}
}

void init_h_bridges(void)
{
	// Config pins as output
	DDR_A_RPWM |= (1<<PIN_A_RPWM);
	DDR_A_LPWM |= (1<<PIN_A_LPWM);
	DDR_B_RPWM |= (1<<PIN_B_RPWM);
	DDR_B_LPWM |= (1<<PIN_B_LPWM);
	DDR_C_RPWM |= (1<<PIN_C_RPWM);
	DDR_C_LPWM |= (1<<PIN_C_LPWM);

	// Output low
	PORT_A_RPWM &= ~(1<<PIN_A_RPWM);
	PORT_A_LPWM &= ~(1<<PIN_A_LPWM);
	PORT_B_RPWM &= ~(1<<PIN_B_RPWM);
	PORT_B_LPWM &= ~(1<<PIN_B_LPWM);
	PORT_C_RPWM &= ~(1<<PIN_C_RPWM);
	PORT_C_LPWM &= ~(1<<PIN_C_LPWM);

	TCCR0A = 0;
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);

	// Disable PWM output
	OCR0A = 0;
	OCR0B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK0 = (1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0);

	sei();
}

void disable_h_bridges(void) {

}

void motor_set_speed_percentage(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		if (percentage >= 0)
		{
			// Disable LPWM, calculate RPWM
			OCR0B = 0;
			OCR0A = (255*percentage)/100;
		}
		else // percentage < 0
		{
			// Disable RPWM, calculate LPWM
			OCR0A = 0;
			OCR0B = (255*percentage)/-100;
		}
	}
}

