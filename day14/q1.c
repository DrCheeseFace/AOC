#include "q1.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define READ_FILE "input.txt"
#define ROBO_COUNT 500
#define SECONDS 100

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
                for (int i = 0; i < ROBO_COUNT; i++) {
                        incrementRobo(&robots[i]);
                }
        }

        int tile_counts[HEIGHT][WIDTH] = {0};
        for (int i = 0; i < ROBO_COUNT; i++) {
                tile_counts[robots[i].py][robots[i].px] += 1;
        }

        // top left quadrant
        int top_left_count = 0;
        for (int j = 0; j < 51; j++) {
                for (int i = 0; i < 50; i++) {
                        top_left_count += tile_counts[j][i];
                }
        }

        // top right quadrant
        int top_right_count = 0;
        for (int j = 0; j < 51; j++) {
                for (int i = 51; i < WIDTH; i++) {
                        top_right_count += tile_counts[j][i];
                }
        }

        // bottom left quadrant
        int bottom_left_count = 0;
        for (int j = 52; j < HEIGHT; j++) {
                for (int i = 0; i < 50; i++) {
                        bottom_left_count += tile_counts[j][i];
                }
        }

        // bottom right quadrant
        int bottom_right_count = 0;
        for (int j = 52; j < HEIGHT; j++) {
                for (int i = 51; i < WIDTH; i++) {
                        bottom_right_count += tile_counts[j][i];
                }
        }
        printf("top left count; %d\n\r", top_left_count);
        printf("top right count; %d\n\r", top_right_count);
        printf("bottom left count; %d\n\r", bottom_left_count);
        printf("bottom right count; %d\n\r", bottom_right_count);

        printf("%d", top_left_count * top_right_count * bottom_left_count * bottom_right_count);

        fclose(file);
        return 0;
}
