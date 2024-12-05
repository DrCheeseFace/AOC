#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LIB_H
#define LIB_H
// #define RULES_FILE "testrules.txt"
#define RULES_FILE "rules.txt"
// #define UPDATES_FILE "testupdates.txt"
#define UPDATES_FILE "updates.txt"
#define NUMBER_OF_RULES 1176
// #define NUMBER_OF_RULES 21
#define NUMBER_OF_UPDATES 197
// #define NUMBER_OF_UPDATES 6
#define MAX_COLS_OF_UPDATE 23

bool followsRules(int len, int update[MAX_COLS_OF_UPDATE], int left, int right) {
    int left_loc = -1;
    int i;

    for (i = 0; i < len; i++) {
        if (update[i] == left) {
            left_loc = i;
            break;
        }
    }
    if (left_loc == -1) {
        return true;
    }

    for (i = 0; i < left_loc; i++) {
        if (update[i] == right) {
            return false;
        }
    }
    return true;
}

int compare(int page_left, int page_right, int rules[NUMBER_OF_RULES][2]) {
    for (int i = 0; i < NUMBER_OF_RULES; i++) {
        if (rules[i][0] == page_left && rules[i][1] == page_right) {
            return true;
        }
    }
    return false;
}

void fix_order(int rules[NUMBER_OF_RULES][2], int update[MAX_COLS_OF_UPDATE], int update_len) {
    while (true) {
        bool swapped = false;
        for (int i = 1; i < update_len; i++) {
            if (!compare(update[i - 1], update[i], rules) == true) {
                int temp      = update[i - 1];
                update[i - 1] = update[i];
                update[i]     = temp;
                swapped       = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
}

#endif // MY_FUNCTIONS_H
