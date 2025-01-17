#include <avr/io.h>
#include "include/motors.h"

ISR(TIMER0_OVF_vect)
{
    if (OCR0A == 0 && OCR0B == 0)
    {
        PORTB_A_RPWM &= ~(1 << PIN_A_RPWM);
        PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
        PORTB_B_RPWM &= ~(1 << PIN_B_RPWM);
        PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
        PORTH_C_RPWM &= ~(1 << PIN_C_RPWM);
        PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
    }
    else if (OCR0A != 0)
    {
        PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
        PORTB_A_RPWM |= (1 << PIN_A_RPWM);
        PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
        PORTB_B_RPWM |= (1 << PIN_B_RPWM);
        PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
        PORTH_C_RPWM |= (1 << PIN_C_RPWM);
    }
    else if (OCR0B != 0)
    {
        PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
        PORTB_A_RPWM |= (1 << PIN_A_RPWM);
        PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
        PORTB_B_RPWM |= (1 << PIN_B_RPWM);
        PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
        PORTH_C_RPWM |= (1 << PIN_C_RPWM);
    }
}

ISR(TIMER0_COMPA_vect)
{
    if (OCR0A != 255)
    {
        PORTB_A_RPWM &= ~(1 << PIN_A_RPWM);
        PORTB_B_RPWM &= ~(1 << PIN_B_RPWM);
        PORTH_C_RPWM &= ~(1 << PIN_C_RPWM);
    }
}

ISR(TIMER0_COMPB_vect)
{
    if (OCR0B != 255)
    {
        PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
        PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
        PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
    }
}

void init_h_bridges()
{
    // Configure pins as output
    DDR_A_RPWM |= (1 << PIN_A_RPWM);
    DDR_A_LPWM |= (1 << PIN_A_LPWM);
    DDR_B_RPWM |= (1 << PIN_B_RPWM);
    DDR_B_LPWM |= (1 << PIN_B_LPWM);
    DDR_C_RPWM |= (1 << PIN_C_RPWM);
    DDR_C_LPWM |= (1 << PIN_C_LPWM);

    // Set outputs to low
    PORTB_A_RPWM &= ~(1 << PIN_A_RPWM);
    PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
    PORTB_B_RPWM &= ~(1 << PIN_B_RPWM);
    PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
    PORTH_C_RPWM &= ~(1 << PIN_C_RPWM);
    PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);

    // Configure Timer0
    TCCR0A = 0;
    TCCR0B = (0 << CS02) | (1 << CS01) | (1 << CS00);

    // Disable PWM output initially
    OCR0A = 0;
    OCR0B = 0;

    // Enable interrupts for compare match A, compare match B, and overflow
    TIMSK0 = (1 << OCIE0B) | (1 << OCIE0A) | (1 << TOIE0);

    sei(); // Enable global interrupts
}

void disable_h_bridges()
{
    // Set all H-bridge pins to low to disable them
    PORTB_A_RPWM &= ~(1 << PIN_A_RPWM);
    PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
    PORTB_B_RPWM &= ~(1 << PIN_B_RPWM);
    PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
    PORTH_C_RPWM &= ~(1 << PIN_C_RPWM);
    PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
}

void motor_set_speed_percentage(signed char percentage)
{
    if (percentage >= -100 && percentage <= 100)
    {
        if (percentage >= 0)
        {
            // Disable LPWM, calculate RPWM
            OCR0B = 0;
            OCR0A = (255 * percentage) / 100;
        }
        else
        {
            // Disable RPWM, calculate LPWM
            OCR0A = 0;
            OCR0B = (255 * -percentage) / 100;
        }
    }
}
