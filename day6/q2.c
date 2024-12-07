#include "bruh.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
    // init shizz
    FILE* read_file                                 = fopen(READ_FILE, "r");
    char grid[HEIGHT][WIDTH + 1]                    = {0};
    int obstacles[HEIGHT * WIDTH][2]                = {0};
    bool visited[HEIGHT][WIDTH + 1]                 = {0};
    Direction visited_directions[HEIGHT][WIDTH + 1] = {0};

    for (int i = 0; i < HEIGHT; i++) {
        fscanf(read_file, "%s", grid[i]);
    }
    fclose(read_file);

    Guard guard = {.x = -1, .y = -1, .direction = up};

    // actual logic
    char current_grid[HEIGHT][WIDTH + 1] = {0};
    dupeGrid(grid, current_grid);

    int cyclical_count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dupeGrid(grid, current_grid);
            current_grid[i][j] = '#';
            int obstacle_count = initObstaclesList(current_grid, obstacles);
            initGuard(&guard, current_grid);
            resetVisited(visited);
            resetVisitedDirections(visited_directions);

            while (true) {
                if (isBlocked(guard, obstacles, obstacle_count + 1)) {
                    turnGuard(&guard.direction);
                } else {
                    stepGuard(&guard);
                    if (isGuardOutside(guard.x, guard.y)) {
                        break;
                    }
                    if (visited[guard.y][guard.x] == true && visited_directions[guard.y][guard.x] == guard.direction) {
                        cyclical_count++;
                        break;
                    } else {
                        visited_directions[guard.y][guard.x] = guard.direction;
                        visited[guard.y][guard.x]            = true;
                    }
                }
            }
        }
        // printf("\r   %d/130", i);
    }

    printf("\n\n count: %d", cyclical_count);
    return 0;
}
