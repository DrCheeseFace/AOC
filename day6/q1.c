#include "bruh.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
    // init shizz
    FILE* read_file = fopen(READ_FILE, "r");
    char grid[HEIGHT][WIDTH + 1];
    int obstacles[HEIGHT * WIDTH][2];
    bool visited[HEIGHT][WIDTH + 1];

    for (int i = 0; i < HEIGHT; i++) {
        fscanf(read_file, "%s", grid[i]);
    }
    fclose(read_file);

    Guard guard = {.x = -1, .y = -1, .direction = none};
    initGuard(&guard, grid);
    int obstacle_count = initObstaclesList(grid, obstacles);

    // actual logic
    visited[guard.y][guard.x] = true; // initialize track visted with guard position
    while (true) {
        if (isBlocked(guard, obstacles, obstacle_count)) {
            turnGuard(&guard.direction);
        } else {
            stepGuard(&guard);
            if (isGuardOutside(guard.x, guard.y)) {
                break;
            }
            visited[guard.y][guard.x] = true;
        }
    }

    int distinct_visited_count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (visited[i][j] == true) {
                distinct_visited_count++;
            }
        }
    }

    printf("distinct visits: %d", distinct_visited_count);

    return 0;
}
