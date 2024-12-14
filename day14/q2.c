#include "q1.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_FILE "input.txt"
#define ROBO_COUNT 500
#define SECONDS 99999

int main() {
        FILE* file = fopen(READ_FILE, "r");
        if (file == NULL) {
                perror("Failed to open file");
                return 1;
        }

        Robo robots[ROBO_COUNT] = {0};
        int px, py, vx, vy;
        for (int i = 0; i < ROBO_COUNT; i++) {
                fscanf(file, "p=%d,%d v=%d,%d\n", &robots[i].px, &robots[i].py, &robots[i].vx, &robots[i].vy);
        }

        for (int j = 0; j < SECONDS; j++) {
                int canvas[HEIGHT][WIDTH] = {0};
                for (int i = 0; i < ROBO_COUNT; i++) {
                        incrementRobo(&robots[i]);
                        canvas[robots[i].py][robots[i].px] += 1;
                }

                int unique = 0;
                for (int y = 0; y < HEIGHT; y++) {
                        for (int x = 0; x < WIDTH; x++) {
                                if (canvas[y][x] == 1) {
                                        unique += 1;
                                }
                        }
                }
                if (unique == 500) {
                        printf("hurah %d\n\r", j);
                }
        }

        fclose(file);
        return 0;
}
