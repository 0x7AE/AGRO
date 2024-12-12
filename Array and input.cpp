#include <Arduino.h>
#include <stdio.h>

int main() {
    int array[5][5] = {0};

    int start_positions[3][2];
    int dest_positions[3][2];

    printf("Enter the starting positions (row and column) to set to -1:\n");

    for (int i = 0; i < 3; i++) {
        printf("Starting Position %d (row column): ", i + 1);
        scanf("%d %d", &start_positions[i][0], &start_positions[i][1]);
    }

    for (int i = 0; i < 3; i++) {
        int row = start_positions[i][0];
        int col = start_positions[i][1];
        if (row >= 0 && row < 5 && col >= 0 && col < 5) {
            array[row][col] = -1;
        }
    }

    printf("Enter the destination positions (row and column):\n");

    for (int i = 0; i < 3; i++) {
        printf("Destination Position %d (row column): ", i + 1);
        scanf("%d %d", &dest_positions[i][0], &dest_positions[i][1]);
    }

    for (int i = 0; i < 3; i++) {
        int row = dest_positions[i][0];
        int col = dest_positions[i][1];
        if (row >= 0 && row < 5 && col >= 0 && col < 5) {
            array[row][col] = -2;
        }
    }

    printf("Updated 5x5 Array:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}