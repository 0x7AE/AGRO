#include <avr/io.h>
#include <util/delay.h>

#include "include/motors.h"

// Motor speed for the x-axis
void motor_set_x_speed(int speed) {
    // Simulate motor movement with LEDs
    if (speed > 0) {
        LED_on(PB4); // LED on pin 4 indicates moving right
    } else if (speed < 0) {
        LED_on(PB5); // LED on pin 5 indicates moving left
    } else {
        LED_off(PB4);
        LED_off(PB5);
    }
}

// Motor speed for the y-axis
void motor_set_y_speed(int speed) {
    // Simulate motor movement with LEDs
    if (speed > 0) {
        LED_on(PB6); // LED on pin 6 indicates moving down
    } else if (speed < 0) {
        LED_on(PB7); // LED on pin 7 indicates moving up
    } else {
        LED_off(PB6);
        LED_off(PB7);
    }
}

// TESTING (!)
// Simple LED indicators for feedback (assuming LEDs are connected to PORTD pins)
void LED_on(uint8_t pin) {
    DDRB |= (1 << pin); // Turn on LED on specified pin
}

void LED_off(uint8_t pin) {
    DDRB &= ~(1 << pin); // Turn off LED on specified pin
}

// Main function for pathfinding with motor control
int findpath(int x1, int y1, int x2, int y2) {
    // Initialize the array with numbers
    int array[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            array[i][j] = i * 5 + j + 1;
        }
    }

    // Validate the input coordinates (must be within bounds)
    if (x1 < 0 || x1 >= 5 || y1 < 0 || y1 >= 5 || x2 < 0 || x2 >= 5 || y2 < 0 || y2 >= 5) {
        // Use LED feedback for invalid input
        LED_on(0); // Turn on LED on pin 0 to indicate an error
        _delay_ms(1000); // Wait for 1 second
        LED_off(0); // Turn off LED
        return 1;
    }

    // Place -1 and -2 in the array (start and goal)
    array[x1][y1] = -1;
    array[x2][y2] = -2;

    // Indicate that the pathfinding has started by turning on an LED
    LED_on(PB4); // Turn on LED on pin 1
    _delay_ms(500); // Wait for a short time
    LED_off(PB4); // Turn off LED

    // Move -1 towards -2
    while (x1 != x2 || y1 != y2) {
        // Clear the current position of -1
        array[x1][y1] = x1 * 5 + y1 + 1;

        // Determine movement direction for X and Y
        int dx = 0, dy = 0;

        if (x1 < x2) {
            dx = 1;  // Move right
            motor_set_x_speed(100);  // Simulate motor speed for X axis (forward)
        } else if (x1 > x2) {
            dx = -1; // Move left
            motor_set_x_speed(-100); // Simulate motor speed for X axis (reverse)
        } else {
            motor_set_x_speed(0);  // Stop moving on the X axis
        }

        if (y1 < y2) {
            dy = 1;  // Move down
            motor_set_y_speed(100);  // Simulate motor speed for Y axis (forward)
        } else if (y1 > y2) {
            dy = -1; // Move up
            motor_set_y_speed(-100); // Simulate motor speed for Y axis (reverse)
        } else {
            motor_set_y_speed(0);  // Stop moving on the Y axis
        }

        // Update position
        x1 += dx;
        y1 += dy;

        // Place -1 in the new position
        array[x1][y1] = -1;

        // Wait for a short delay to simulate the movement (adjust delay as needed)
        (500);

        // Flash LED to indicate progress (for debugging)
        LED_on(PB6); // Flash LED on pin 2
        _delay_ms(100);
        LED_off(PB6);
    }

    // Path found! Indicate success by lighting up LED on pin 3
    LED_on(PB7);
    _delay_ms(1000); // Wait for 1 second
    LED_off(PB7); // Turn off LED

    // Stop motors after reaching the goal
    motor_set_x_speed(0);
    motor_set_y_speed(0);

    return 0;
}
