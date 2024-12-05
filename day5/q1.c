#include "lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define RULES_FILE "testrules.txt"
#define RULES_FILE "rules.txt"
// #define UPDATES_FILE "testupdates.txt"
#define UPDATES_FILE "updates.txt"
#define NUMBER_OF_RULES 1176
// #define NUMBER_OF_RULES 21
#define NUMBER_OF_UPDATES 197
// #define NUMBER_OF_UPDATES 6
#define MAX_COLS_OF_UPDATE 23

int main() {
    FILE* read_file = fopen(RULES_FILE, "r");

    int rules[NUMBER_OF_RULES][2];

    int left;
    int right;

    int i;
    for (i = 0; i < NUMBER_OF_RULES; i++) {
        fscanf(read_file, "%d|%d", &left, &right);
        rules[i][0] = left;
        rules[i][1] = right;
    }
    fclose(read_file);

    read_file = fopen(UPDATES_FILE, "r");
    int updates[NUMBER_OF_UPDATES][23];
    char updates_col_count[NUMBER_OF_UPDATES];
    char line[512];
    int row = 0;
    while (row < NUMBER_OF_UPDATES && fgets(line, sizeof(line), read_file)) {
        int col     = 0;
        char* token = strtok(line, ",");

        while (token && col < 23) {
            updates[row][col] = atoi(token);
            col++;
            token = strtok(NULL, ",");
        }

        updates_col_count[row] = col;
        row++;
    }
    fclose(read_file);

    bool valid_rows[NUMBER_OF_UPDATES];
    for (i = 0; i < NUMBER_OF_UPDATES; i++) {
        valid_rows[i] = true;
    }

    int j;
    for (i = 0; i < NUMBER_OF_RULES; i++) {
        for (j = 0; j < NUMBER_OF_UPDATES; j++) {
            if (!followsRules(updates_col_count[j], updates[j], rules[i][0], rules[i][1])) {
                valid_rows[j] = false;
            }
        }
    }

    int count         = 0;
    int invalid_count = 0;
    int mid_idx;
    for (i = 0; i < NUMBER_OF_UPDATES; i++) {
        if (valid_rows[i] == true) {
            mid_idx = updates_col_count[i] / 2;
            count += updates[i][mid_idx];
        } else {
            fix_order(rules, updates[i], updates_col_count[i]);
            mid_idx = updates_col_count[i] / 2;
            invalid_count += updates[i][mid_idx];
        }
    }
    printf("count: %d\n\r", count);
    printf("invalid count: %d\n", invalid_count);

    return 0;
}
