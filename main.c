#include <stdio.h>

int main() {
    // Make an array thing with numbers
    int array[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            array[i][j] = i * 5 + j + 1; 
        }
    }

    // Ask where to put the -1 and -2
    int x1, y1, x2, y2;
    printf("Enter the position of -1 (row and column, 0-4): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter the position of -2 (row and column, 0-4): ");
    scanf("%d %d", &x2, &y2);

    // Check if the numbers you gave make sense, then shove -1 and -2 in there
    if (x1 >= 0 && x1 < 5 && y1 >= 0 && y1 < 5 && x2 >= 0 && x2 < 5 && y2 >= 0 && y2 < 5) {
        array[x1][y1] = -1;
        array[x2][y2] = -2;
    } else {
        printf("You messed up. Do better next time. Exiting program.\n");
        return 1;
    }

    // Show off the initial state we made
    printf("\nStarting state of the array:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%3d ", array[i][j]);
        }
        printf("\n");
    }

    // Variable to control movement
    int move = 0;

    // Keep moving the -1 until it smacks into the -2
    while (x1 != x2 || y1 != y2) {
        // Wait until movement is allowed
        if (move == 0) {
            printf("\nWaiting for move to be set to 1...\n");
            scanf("%d", &move);
            if (move != 1) continue;
        }

        array[x1][y1] = x1 * 5 + y1 + 1; // Put the old value back like nothing happened

        // Variables to track movement direction
        int dx = 0, dy = 0;

        // Try to make -1 get closer to -2
        if (x1 == x2 || y1 == y2) {
            // Move in a straight line
            if (x1 < x2) dx = 1;
            else if (x1 > x2) dx = -1;
            if (y1 < y2) dy = 1;
            else if (y1 > y2) dy = -1;
        } else {
            // Move diagonally because it’s not in a straight line
            if (x1 < x2) dx = 1;
            else if (x1 > x2) dx = -1;

            if (y1 < y2) dy = 1;
            else if (y1 > y2) dy = -1;
        }

        // Update position
        x1 += dx;
        y1 += dy;

        // Reset move variable
        move = 0;

        // Put -1 in its new spot
        array[x1][y1] = -1;

        // Show how the square looks now
        printf("\nArray after moving -1:\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                printf("%3d ", array[i][j]);
            }
            printf("\n");
        }
    }

    printf("\n-1 has reached -2 at position (%d, %d).\n", x2, y2);

    return 0;
}