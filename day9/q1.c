#include "bruh.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_INPUT_LENGTH 19999
// #define MAX_INPUT_LENGTH 19
#define READ_FILE "input.txt"

int main() {
    // init shizz
    FILE* file = fopen(READ_FILE, "r");
    char condensed_input[MAX_INPUT_LENGTH + 1];
    fscanf(file, "%s", condensed_input);
    fclose(file);

    int expanded_input_count = 0;
    for (int i = 0; i < MAX_INPUT_LENGTH; i++) {
        expanded_input_count += condensed_input[i] - '0';
    }

    Block expanded_input[expanded_input_count];

    int id                 = 0;
    int expanded_input_idx = 0;
    for (int i = 0; i < MAX_INPUT_LENGTH; i += 2) {
        for (int j = 0; j < condensed_input[i] - '0'; j++) {
            Block fileblock                    = {.id = id};
            expanded_input[expanded_input_idx] = fileblock;
            expanded_input_idx++;
        }

        if (condensed_input[i + 1] != '\0') {
            int free_blocks_len = condensed_input[i + 1] - '0';
            for (int j = 0; j < free_blocks_len; j++) {
                Block fileblock                    = {.id = -1};
                expanded_input[expanded_input_idx] = fileblock;
                expanded_input_idx++;
            }
        } else {
            break;
        }
        id++;
    }

    printf("\n\n\r");
    printf("expanded file system: \n\r");
    for (int i = 0; i < expanded_input_count; i++) {
        if (expanded_input[i].id == -1) {
            printf(".");
        } else {
            printf("%d", expanded_input[i].id);
        }
    }
    printf("\n\n\r");

    int pExpanded_input = 0;
    for (int i = expanded_input_count - 1; i >= 0; i--) {
        if (expanded_input[i].id != -1) {
            int firstFreeIdx = getIdxOfFirstFreeBlock(expanded_input, expanded_input_count);
            if (firstFreeIdx >= i) {
                break;
            }
            expanded_input[firstFreeIdx] = expanded_input[i];
            expanded_input[i].id         = -1;
        }
    }

    printf("squashed file system: \n\r");
    for (int i = 0; i < expanded_input_count; i++) {
        if (expanded_input[i].id == -1) {
            printf(".");
        } else {
            printf("%d", expanded_input[i].id);
        }
    }
    printf("\n\n\r");


    long long int checksum_total = 0;
    for (int i = 0; i < expanded_input_count; i++) {
        if (expanded_input[i].id != -1) {
            checksum_total += i * expanded_input[i].id;
        }
    }

    printf("checksum total: %lld", checksum_total);

    return 0;
}
