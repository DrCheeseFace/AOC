#include <stdbool.h>
#include <stdio.h>

// free space = -1
typedef struct {
    signed int id;
} Block;

int getIdxOfFirstFreeBlock(Block* blocks, int count) {
    for (int i = 0; i < count; i++) {
        if (blocks[i].id == -1) {
            return i;
        }
    }
    return -1;
}

int getFreeIdsArray(Block* blocks, int block_count, int* free_ids, int free_ids_count) {
    int free_ids_idx = 0;
    for (int i = 0; i < block_count; i++) {
        if (blocks[i + 1].id == -1 && blocks[i].id != -1) {
            free_ids[free_ids_idx] = blocks[i].id;
            free_ids_idx++;
        }
    }
    return free_ids_idx;
}
