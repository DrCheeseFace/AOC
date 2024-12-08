#include <stdbool.h>
#include <stdio.h>
#define READ_FILE "input.txt"
#define XY_LENGTH 50
#define MAX_ANTENA_COUNT 1024

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    char freq;
    Position pos;
} Antena;

int initAntenas(char map[XY_LENGTH][XY_LENGTH + 1], Antena antenas[MAX_ANTENA_COUNT]) {
    int antena_count = 0;
    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            if (map[i][j] != '.') {
                Antena new_antena     = {.freq = map[i][j], .pos.x = j, .pos.y = i};
                antenas[antena_count] = new_antena;
                antena_count++;
            }
        }
    }
    return antena_count;
}

bool hasDuplicateFreq(char map[XY_LENGTH][XY_LENGTH + 1], char freq) {
    int freq_count = 0;
    for (int i = 0; i < XY_LENGTH; i++) {
        for (int j = 0; j < XY_LENGTH; j++) {
            if (map[i][j] == freq) {
                freq_count++;
            }
            if (freq_count>1){
                return true;
            }
        }
    }
    return false;
}

Position calculateAntinode(int x1, int y1, int x2, int y2) {
    int diff_x                 = x1 - x2;
    int diff_y                 = y1 - y2;
    Position antinode_position = {.x = x1 + diff_x, .y = y1 + diff_y};
    return antinode_position;
}

bool isSamePos(Position pos1, Position pos2) {
    if (pos1.x == pos1.x && pos1.y == pos2.y) {
        return true;
    }
    return false;
}

bool isInsideGridBounds(Position pos) {
    if (pos.x < 0 || pos.y < 0) {
        return false;
    }
    if (pos.x >= XY_LENGTH || pos.y >= XY_LENGTH) {
        return false;
    }
    return true;
}

void printAntena(Antena antena) {
    printf("\n\rfreq: %c ", antena.freq);
    printf("x: %d ", antena.pos.x);
    printf("y: %d", antena.pos.y);
}
