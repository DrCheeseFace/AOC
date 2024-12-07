#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define READ_FILE "test.txt"
#define HEIGHT 10
#define WIDTH 10
#define GUARD_CHAR '^'
#define OBSTACLE '#'

typedef enum {
    up,
    down,
    left,
    right,
    none,
} Direction;

typedef struct {
    int x;
    int y;
    Direction direction;
} Guard;

void dupeGrid(char src[HEIGHT][WIDTH + 1], char dest[HEIGHT][WIDTH + 1]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int initObstaclesList(char grid[HEIGHT][WIDTH + 1], int obstacles[HEIGHT * WIDTH][2]) {
    int obstable_count = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == OBSTACLE) {
                obstacles[obstable_count][0] = y;
                obstacles[obstable_count][1] = x;
                obstable_count++;
            }
        }
    }
    return obstable_count;
}

void resetVisitedDirections(Direction visited_directions[HEIGHT][WIDTH + 1]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            visited_directions[i][j] = none;
        }
    }
}

void resetVisited(bool visited[HEIGHT][WIDTH + 1]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            visited[i][j] = false;
        }
    }
}

void initGuard(Guard* guard, char grid[HEIGHT][WIDTH + 1]) {
    guard->direction = up;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == GUARD_CHAR) {
                guard->x = j;
                guard->y = i;
                return;
            }
        }
    }
}

void turnGuard(Direction* direction) {
    if (*direction == up) {
        *direction = right;
    } else if (*direction == right) {
        *direction = down;
    } else if (*direction == down) {
        *direction = left;
    } else if (*direction == left) {
        *direction = up;
    }
}

void stepGuard(Guard* guard) {
    if (guard->direction == up) {
        guard->y = guard->y - 1;
    } else if (guard->direction == down) {
        guard->y = guard->y + 1;
    } else if (guard->direction == left) {
        guard->x = guard->x - 1;
    } else if (guard->direction == right) {
        guard->x = guard->x + 1;
    }
}

bool isGuardOutside(int x, int y) {
    if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
        return true;
    }
    return false;
}

bool xyInObstables(int x, int y, int obstacles[HEIGHT * WIDTH][2], int obstable_count) {
    for (int i = 0; i < obstable_count; i++) {
        if (obstacles[i][0] == y && obstacles[i][1] == x) {
            return true;
        }
    }
    return false;
}

bool isBlocked(Guard guard, int obstacles[HEIGHT * WIDTH][2], int obstable_count) {
    if (guard.direction == up) {
        return xyInObstables(guard.x, guard.y - 1, obstacles, obstable_count);
    }
    if (guard.direction == down) {
        return xyInObstables(guard.x, guard.y + 1, obstacles, obstable_count);
    }
    if (guard.direction == left) {
        return xyInObstables(guard.x - 1, guard.y, obstacles, obstable_count);
    }
    if (guard.direction == right) {
        return xyInObstables(guard.x + 1, guard.y, obstacles, obstable_count);
    }
    return false;
}
