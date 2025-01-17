#include <avr/io.h>
#include <avr/interrupt.h>
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

void init_motor_a() {
    // Configure Motor A pins as output
    DDR_A_RPWM |= (1 << PIN_A_RPWM);
    DDR_A_LPWM |= (1 << PIN_A_LPWM);
    // Set outputs to low
    PORTB_A_RPWM &= ~(1 << PIN_A_RPWM);
    PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
}

void init_motor_b() {
    // Configure Motor B pins as output
    DDR_B_RPWM |= (1 << PIN_B_RPWM);
    DDR_B_LPWM |= (1 << PIN_B_LPWM);
    // Set outputs to low
    PORTB_B_RPWM &= ~(1 << PIN_B_RPWM);
    PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
}

void init_motor_c() {
    // Configure Motor C pins as output
    DDR_C_RPWM |= (1 << PIN_C_RPWM);
    DDR_C_LPWM |= (1 << PIN_C_LPWM);
    // Set outputs to low
    PORTH_C_RPWM &= ~(1 << PIN_C_RPWM);
    PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
}

void disable_motor_a() {
    PORTB_A_RPWM &= ~(1 << PIN_A_RPWM);
    PORTB_A_LPWM &= ~(1 << PIN_A_LPWM);
}

void disable_motor_b() {
    PORTB_B_RPWM &= ~(1 << PIN_B_RPWM);
    PORTB_B_LPWM &= ~(1 << PIN_B_LPWM);
}

void disable_motor_c() {
    PORTH_C_RPWM &= ~(1 << PIN_C_RPWM);
    PORTH_C_LPWM &= ~(1 << PIN_C_LPWM);
}

void init_h_bridges()
{
    // Configure pins as output
    init_motor_a();
    init_motor_b();
    init_motor_c();

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
    disable_motor_a();
    disable_motor_b();
    disable_motor_c();
   
}

void motor_set_speed_percentage(MotorID motor, signed char percentage) {
    MotorConfig config = motors[motor]; // Get the motor configuration

    if (percentage >= -100 && percentage <= 100) {
        if (percentage >= 0) {
            // Forward: Disable LPWM, enable RPWM
            *(config.port_lpwm) &= ~(1 << config.pin_lpwm);
            *(config.port_rpwm) |= (1 << config.pin_rpwm);

            OCR0B = 0;
            OCR0A = (255 * percentage) / 100;
        } else {
            // Backward: Disable RPWM, enable LPWM
            *(config.port_rpwm) &= ~(1 << config.pin_rpwm);
            *(config.port_lpwm) |= (1 << config.pin_lpwm);

            OCR0A = 0;
            OCR0B = (255 * -percentage) / 100;
        }
    }
}

