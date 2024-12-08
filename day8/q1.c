#include "bruh.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
    // init shizz
    FILE* file = fopen(READ_FILE, "r");
    char grid[XY_LENGTH][XY_LENGTH + 1];
    bool antinodes[XY_LENGTH][XY_LENGTH + 1] = {0};

    for (int i = 0; i < XY_LENGTH; i++) {
        fscanf(file, "%s", grid[i]);
    }
    fclose(file);
    for (int i = 0; i < XY_LENGTH; i++) {
        printf("%s\n\r", grid[i]);
    }

    Antena antenas[MAX_ANTENA_COUNT] = {0};
    int antena_count                 = initAntenas(grid, antenas);
    for (int i = 0; i < antena_count; i++) {
        for (int j = 0; j < antena_count; j++) {
            if (antenas[i].freq == antenas[j].freq && !isSamePos(antenas[i].pos, antenas[j].pos)) {
                Position antinode = calculateAntinode(antenas[i].pos.x, antenas[i].pos.y,
                                                      antenas[j].pos.x, antenas[j].pos.y);
                if (isInsideGridBounds(antinode)) {
                    antinodes[antinode.y][antinode.x] = true;
                }
            }
        }
    }

    printf("\n\r");
    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            printf("%b", antinodes[i][j]);
        }
        printf("\n\r");
    }

    int antinode_count = 0;
    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            if (antinodes[i][j] == true) {
                antinode_count++;
            }
        }
    }
    printf("antindoe count: %d", antinode_count);
    return 0;
}
