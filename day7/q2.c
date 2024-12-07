#include "bruh.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // init shizz
    FILE* file = fopen(READ_FILE, "r");
    long long int sums[ROWS];
    long long int* nums[ROWS];
    int nums_counts[ROWS] = {0};
    int line_count        = 0;

    char line[256];
    while (fgets(line, sizeof(line), file) && line_count < ROWS) {
        long long int before;
        char* ptr = line;

        if (sscanf(ptr, "%lld:", &before) != 1) {
            fprintf(stderr, "fuk1: %s", line);
            continue;
        }
        sums[line_count] = before;

        ptr = strchr(line, ':');
        ptr += 2;
        nums[line_count] = malloc(MAX_NUMS * sizeof(long long int) + 1);

        long long int num;
        while (sscanf(ptr, "%lld", &num) == 1) {
            nums[line_count][nums_counts[line_count]++] = num;
            ptr                                         = strchr(ptr, ' ');
            if (!ptr)
                break;
            ptr++;
        }

        line_count++;
    }
    fclose(file);

    // logic
    long long int total = 0;
    for (int i = 0; i < ROWS; i++) {
        int operators_count = nums_counts[i] - 1; // cuz off by one is so fun to deal with
        Operation operators[operators_count];
        initOperators(operators_count, operators);

        long long int operations_combinations_count = truncf(pow(3, nums_counts[i] - 1));
        for (int j = 0; j < operations_combinations_count; j++) {
            long long int operator_sum = getOperatorSum(operators_count, operators, nums_counts[i], nums[i]);
            if (operator_sum == sums[i]) {
                total += sums[i];
                break;
            }
            incrementOperators(operators_count, operators);
        }
    }

    for (int i = 0; i < ROWS; i++) {
        free(nums[i]);
    }

    printf("total: %lld", total);
    return 0;
}
