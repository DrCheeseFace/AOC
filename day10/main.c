#include "q1.h"
#include <stdio.h>

#define READ_FILE "input.txt"

int main() {
    FILE* read_file = fopen(READ_FILE, "r");
    char char_grid[XY_LENGTH][XY_LENGTH + 1];
    for (int i = 0; i < XY_LENGTH; i++) {
        fscanf(read_file, "%s", char_grid[i]);
    }

    int grid[XY_LENGTH][XY_LENGTH];
    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            grid[i][j] = char_grid[i][j] - '0';
        }
    }

    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n\r");
    }
    printf("\n\r");

    Position trailheads[XY_LENGTH * XY_LENGTH] = {0};
    int trailheads_count                       = 0;

    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            if (grid[i][j] == 0) {
                Position head                = {.y = i, .x = j, .height = 0};
                trailheads[trailheads_count] = head;
                trailheads_count++;
            }
        }
    }

    int branches_count = 0;
    for (int i = 0; i < trailheads_count; i++) {

        Position level1[XY_LENGTH * XY_LENGTH];
        int level1_count = forZero(trailheads[i], level1, grid);

        Position level2[XY_LENGTH * XY_LENGTH];
        int level2_count = getNybor(level1, level1_count, level2, grid);

        Position level3[XY_LENGTH * XY_LENGTH];
        int level3_count = getNybor(level2, level2_count, level3, grid);

        Position level4[XY_LENGTH * XY_LENGTH];
        int level4_count = getNybor(level3, level3_count, level4, grid);

        Position level5[XY_LENGTH * XY_LENGTH];
        int level5_count = getNybor(level4, level4_count, level5, grid);

        Position level6[XY_LENGTH * XY_LENGTH];
        int level6_count = getNybor(level5, level5_count, level6, grid);

        Position level7[XY_LENGTH * XY_LENGTH];
        int level7_count = getNybor(level6, level6_count, level7, grid);

        Position level8[XY_LENGTH * XY_LENGTH];
        int level8_count = getNybor(level7, level7_count, level8, grid);

        Position level9[XY_LENGTH * XY_LENGTH];
        int level9_count = getNybor(level8, level8_count, level9, grid);

        Position dedup_array[XY_LENGTH * XY_LENGTH];
        // part 1 dedup
        // part 2 dont dedup it dedup

        //  int dedup_array_len = dedup(level9, level9_count, dedup_array);
        branches_count += level9_count;
    }
    printf("branchcount: %d\n\r", branches_count);

    return 1;
}
