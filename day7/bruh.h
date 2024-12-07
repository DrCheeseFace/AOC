#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define READ_FILE "input.txt"
#define ROWS 850
#define MAX_NUMS 11
#define MAX_NUMBER_OF_OPERATIONS 10

typedef enum {
    ADD,
    MULTIPLY,
    CONCAT
} Operation;

void initOperators(int count, Operation* operators) {
    for (int i = 0; i < count; i++) {
        operators[i] = ADD;
    }
}

long long int getOperatorSum(int operators_count, Operation* operators, int nums_count, long long int* nums) {
    long long int sum = nums[0];
    int operator_idx  = 0;
    for (int i = 1; i < nums_count; i++) {
        if (operators[operator_idx] == ADD) {
            sum += nums[i];
        } else if (operators[operator_idx] == MULTIPLY) {
            sum *= nums[i];
        } else {
            sum = sum * pow(10, floor(log10(nums[i]) + 1)) + nums[i];
        }
        operator_idx++;
    }
    return sum;
}

void incrementOperators(int count, Operation* operators) {
    for (int i = count - 1; i >= 0; i--) {
        if (operators[i] == ADD) {
            operators[i] = MULTIPLY;
            return;
        } else if (operators[i] == MULTIPLY) {
            operators[i] = CONCAT;
            return;
        } else {
            operators[i] = ADD;
        }
    }
}
