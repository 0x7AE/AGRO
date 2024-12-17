#include <stdio.h>

#define ROWS 5
#define COLS 5

// Directions for moving in 4 possible ways (up, down, left, right)
int rowDir[] = {-1, 1, 0, 0};
int colDir[] = {0, 0, -1, 1};

// A structure to represent a cell in the queue
struct QueueNode {
    int x, y, dist;
};

// Function to check if a cell is valid to move into
int isValid(int x, int y, int visited[ROWS][COLS], int array[ROWS][COLS]) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && visited[x][y] == 0);
}

// BFS to find the shortest path from -1 to -2
int findShortestPath(int array[ROWS][COLS], int startX, int startY, int endX, int endY, int path[ROWS][COLS]) {
    // Create a queue to store the cells to visit
    struct QueueNode queue[ROWS * COLS];
    int front = 0, rear = 0;

    // Visited array
    int visited[ROWS][COLS] = {0};

    // Parent array to trace the path
    int parentX[ROWS][COLS];
    int parentY[ROWS][COLS];

    // Initialize path and parent arrays
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            path[i][j] = 0;
            parentX[i][j] = -1;
            parentY[i][j] = -1;
        }
    }

    // Enqueue the starting position
    queue[rear].x = startX;
    queue[rear].y = startY;
    queue[rear].dist = 0;
    rear++;
    visited[startX][startY] = 1;

    // Perform BFS
    while (front < rear) {
        struct QueueNode current = queue[front++];

        // If we reach the destination
        if (current.x == endX && current.y == endY) {
            // Backtrack to reconstruct the path
            int x = endX, y = endY;
            while (!(x == startX && y == startY)) {
                path[x][y] = 1;
                int tempX = parentX[x][y];
                int tempY = parentY[x][y];
                x = tempX;
                y = tempY;
            }
            path[startX][startY] = 1;
            return current.dist;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int newX = current.x + rowDir[i];
            int newY = current.y + colDir[i];

            if (isValid(newX, newY, visited, array)) {
                queue[rear].x = newX;
                queue[rear].y = newY;
                queue[rear].dist = current.dist + 1;
                rear++;
                visited[newX][newY] = 1;
                parentX[newX][newY] = current.x;
                parentY[newX][newY] = current.y;
            }
        }
    }

    // If destination cannot be reached
    return -1;
}

// Function to print the grid with the path
void printGridWithPath(int array[ROWS][COLS], int path[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (path[i][j] == 1) {
                printf(" * ");  // Path marker
            } else if (array[i][j] == -1) {
                printf("-1 ");  // Start marker
            } else if (array[i][j] == -2) {
                printf("-2 ");  // End marker
            } else {
                printf("%2d ", array[i][j]);  // Other cells
            }
        }
        printf("\n");
    }
}

int main() {
    // Initialize a 5x5 array with all elements set to 0
    int array[ROWS][COLS] = {0};
    int path[ROWS][COLS] = {0};

    // Set specific elements to -1 and -2
    array[1][0] = -1;  // Starting point
    array[3][4] = -2;  // Destination point

    // Locate the positions of -1 and -2
    int startX = -1, startY = -1, endX = -1, endY = -1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (array[i][j] == -1 && startX == -1) {
                startX = i;
                startY = j;
            } else if (array[i][j] == -2) {
                endX = i;
                endY = j;
            }
        }
    }

    if (startX == -1 || endX == -1) {
        printf("Error: Start or End point not found.\n");
        return 1;
    }

    // Find the shortest path using BFS
    int shortestPath = findShortestPath(array, startX, startY, endX, endY, path);

    if (shortestPath != -1) {
        printf("The shortest path from -1 to -2 is: %d\n", shortestPath);
        printf("Grid with the path:\n");
        printGridWithPath(array, path);
    } else {
        printf("No path exists from -1 to -2.\n");
    }

    return 0;
}
