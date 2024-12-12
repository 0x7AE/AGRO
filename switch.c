// Include the necessary AVR headers
#include <avr/io.h>
#include <util/delay.h>
#include "include/math.h"
#include "include\h_bridge.h"

// Define pins for the limit switches
#define LIMIT_SWITCH1_PIN PD2  // Pin 2 on PORTD
#define LIMIT_SWITCH2_PIN PD3  // Pin 3 on PORTD

// Define pin for the LED
#define LED_PIN PB7  // Pin 7 on PORTB (Change from PB0 to PB7)


void init_limit_switches() {
    // Set pins as inputs
    DDRD &= ~(1 << LIMIT_SWITCH1_PIN); // Clear DDRD bit for LIMIT_SWITCH1_PIN
    DDRD &= ~(1 << LIMIT_SWITCH2_PIN); // Clear DDRD bit for LIMIT_SWITCH2_PIN

    // Enable internal pull-up resistors
    PORTD |= (1 << LIMIT_SWITCH1_PIN); // Set PORTD bit for LIMIT_SWITCH1_PIN
    PORTD |= (1 << LIMIT_SWITCH2_PIN); // Set PORTD bit for LIMIT_SWITCH2_PIN
}

void init_led() {
    // Set LED pin as output
    DDRB |= (1 << LED_PIN); // Set DDRB bit for LED_PIN
}

void blink_led() {
    // Toggle LED state
    PORTB ^= (1 << LED_PIN); // XOR to toggle the bit
    _delay_ms(500); // Delay to make the blinking visible
}

int main(void) {
    // Initialize the limit switches and LEDs   
    init_limit_switches();
    init_led();

    // Main loop
    while (1) {
        // Read the state of the limit switches
       if (!(PIND & (1 << LIMIT_SWITCH1_PIN)) || !(PIND & (1 << LIMIT_SWITCH2_PIN))) {
            // Either limit switch is pressed
            blink_led(); // Blink LED
        } else {
            // No switch pressed, turn off the LED
            PORTB &= ~(1 << LED_PIN); // Clear LED_PIN bit to turn off the LED
        }

        if (!(PIND & (1 << LIMIT_SWITCH2_PIN))) { // Active low, switch pressed
            // Limit switch 2 triggered
            blink_led(); // Blink LED when limit switch 2 is pressed
        }

        _delay_ms(100); // Delay for debouncing
    }

    return 0;
}
