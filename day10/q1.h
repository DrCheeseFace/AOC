#include <stdbool.h>
#include <stdio.h>
#define XY_LENGTH 56

typedef struct {
    int x;
    int y;
    int height;
} Position;

int getNybor(Position* roots, int roots_count, Position* branches, int grid[XY_LENGTH][XY_LENGTH]) {

    int branches_count = 0;
    for (int i = 0; i < roots_count; i++) {
        int west  = grid[roots[i].y][roots[i].x - 1];
        int east  = grid[roots[i].y][roots[i].x + 1];
        int south = grid[roots[i].y + 1][roots[i].x];
        int north = grid[roots[i].y - 1][roots[i].x];
        // printf("root y:%d x:%d\n\rh: %d\n\r", roots[i].y, roots[i].x, roots[i].height);
        // printf("NORTH y:%d x:%d\n\rh: %d\n\n\r", roots[i].y - 1, roots[i].x, north);
        // printf("GRIDGRID:%d", grid[0][0]);
        if (roots[i].y - 1 >= 0 && grid[roots[i].y - 1][roots[i].x] == roots[i].height + 1) {
            Position north           = {.x = roots[i].x, .y = roots[i].y - 1, .height = roots[i].height + 1};
            branches[branches_count] = north;
            branches_count++;
        }

        if (roots[i].y + 1 < XY_LENGTH && south == roots[i].height + 1) {
            Position south           = {.x = roots[i].x, .y = roots[i].y + 1, .height = roots[i].height + 1};
            branches[branches_count] = south;
            branches_count++;
        }

        if (roots[i].x + 1 < XY_LENGTH && east == roots[i].height + 1) {
            Position east            = {.x = roots[i].x + 1, .y = roots[i].y, .height = roots[i].height + 1};
            branches[branches_count] = east;
            branches_count++;
        }

        if (roots[i].x - 1 >= 0 && west == roots[i].height + 1) {
            Position west            = {.x = roots[i].x - 1, .y = roots[i].y, .height = roots[i].height + 1};
            branches[branches_count] = west;
            branches_count++;
        }
    }

    return branches_count;
}

int forZero(Position root, Position* branches, int grid[XY_LENGTH][XY_LENGTH]) {
    int branches_count = 0;
    int west           = grid[root.y][root.x - 1];
    int east           = grid[root.y][root.x + 1];
    int south          = grid[root.y + 1][root.x];
    int north          = grid[root.y - 1][root.x];
    if (root.y - 1 >= 0 && north == root.height + 1) {
        Position north           = {.x = root.x, .y = root.y - 1, .height = root.height + 1};
        branches[branches_count] = north;
        branches_count++;
    }

    if (root.y + 1 < XY_LENGTH && south == root.height + 1) {
        Position south           = {.x = root.x, .y = root.y + 1, .height = root.height + 1};
        branches[branches_count] = south;
        branches_count++;
    }

    if (root.x + 1 < XY_LENGTH && east == root.height + 1) {
        Position east            = {.x = root.x + 1, .y = root.y, .height = root.height + 1};
        branches[branches_count] = east;
        branches_count++;
    }

    if (root.x - 1 >= 0 && west == root.height + 1) {
        Position west            = {.x = root.x - 1, .y = root.y, .height = root.height + 1};
        branches[branches_count] = west;
        branches_count++;
    }

    return branches_count;
}

bool isInArray(Position* haystack, int arr_len, Position needle) {
    for (int i = 0; i < arr_len; i++) {
        if (haystack[i].x == needle.x && haystack[i].y == needle.y) {
            return true;
        }
    }
    return false;
}

int dedup(Position* arr, int arr_len, Position* dedup_array) {
    int dedup_array_count = 0;
    for (int i = 0; i < arr_len; i++) {
        if (!isInArray(dedup_array, dedup_array_count, arr[i])) {
            dedup_array[dedup_array_count++] = arr[i];
        }
    }
    // breakpoint
    return dedup_array_count;
}
