#include <avr/io.h>
#include <util/delay.h>
#include "include/motors.h"


void calibrate(int* x1, int* y1) {
    // Move to (1, 1) from current position (x1, y1)
    while (*x1 != 1 || *y1 != 1) {
        // Clear the current position
        array[*x1][*y1] = *x1 * 5 + *y1 + 1;

        // Movement direction for X-axis
        if (*x1 < 1) {
            motor_set_speed_percentage(MOTOR_A, 50);  // Move right
        } else if (*x1 > 1) {
            motor_set_speed_percentage(MOTOR_A, -50); // Move left
        } else {
            motor_set_speed_percentage(MOTOR_A, 0);   // Stop Motor A
        }

        // Movement direction for Y-axis
        if (*y1 < 1) {
            motor_set_speed_percentage(MOTOR_B, 50);  // Move down
        } else if (*y1 > 1) {
            motor_set_speed_percentage(MOTOR_B, -50); // Move up
        } else {
            motor_set_speed_percentage(MOTOR_B, 0);   // Stop Motor B
        }

        // Update position
        if (*x1 < 1) {
            (*x1)++;
        } else if (*x1 > 1) {
            (*x1)--;
        }

        if (*y1 < 1) {
            (*y1)++;
        } else if (*y1 > 1) {
            (*y1)--;
        }

        // Place -1 in the new position
        array[*x1][*y1] = -1;

        // Wait for a short delay to simulate the movement
        _delay_ms(500);

        // Stop motors momentarily after each movement step
        motor_set_speed_percentage(MOTOR_A, 0);
        motor_set_speed_percentage(MOTOR_B, 0);
    }

    // Ensure the motors are stopped at the final position
    motor_set_speed_percentage(MOTOR_A, 0);
    motor_set_speed_percentage(MOTOR_B, 0);
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
        return 1; // Invalid input
    }

    // Place -1 and -2 in the array (start and goal)
    array[x1][y1] = -1;
    array[x2][y2] = -2;

    // Move -1 towards -2
    while (x1 != x2 || y1 != y2) {
        // Clear the current position of -1
        array[x1][y1] = x1 * 5 + y1 + 1;

        // Determine movement direction for X and Y
        int dx = 0, dy = 0;

        if (x1 < x2) {
            dx = 1;  // Move right
            motor_set_speed_percentage(MOTOR_A, 100);  // Motor A (X-axis) moves forward
        } else if (x1 > x2) {
            dx = -1; // Move left
            motor_set_speed_percentage(MOTOR_A, -100); // Motor A (X-axis) moves backward
        } else {
            motor_set_speed_percentage(MOTOR_A, 0);   // Stop Motor A
        }

        if (y1 < y2) {
            dy = 1;  // Move down
            motor_set_speed_percentage(MOTOR_B, 100);  // Motor B (Y-axis) moves forward
        } else if (y1 > y2) {
            dy = -1; // Move up
            motor_set_speed_percentage(MOTOR_B, -100); // Motor B (Y-axis) moves backward
        } else {
            motor_set_speed_percentage(MOTOR_B, 0);   // Stop Motor B
        }

        // Update position
        x1 += dx;
        y1 += dy;

        // Place -1 in the new position
        array[x1][y1] = -1;

        // Wait for a short delay to simulate the movement (adjust delay as needed)
        _delay_ms(500);

        // Stop motors momentarily after each movement step
        motor_set_speed_percentage(MOTOR_A, 0);
        motor_set_speed_percentage(MOTOR_B, 0);
    }

    // Stop motors after reaching the goal
    motor_set_speed_percentage(MOTOR_A, 0);
    motor_set_speed_percentage(MOTOR_B, 0);

    return 0;
}
