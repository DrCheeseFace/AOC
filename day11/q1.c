#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_FILE "test.txt"
#define ITERATION_COUNT 25
#define MAX_ARR_LEN 500000
#define INITIAL_STONE_COUNT 2

int getDigitCount(long long int num) {
        if (num == 0)
                return 1;
        int count = 0;
        while (num > 0) {
                count++;
                num /= 10;
        }
        return count;
}

void splitNumber(int num, int* left, int* right) {
        char str_num[100];
        snprintf(str_num, sizeof(str_num), "%d", num);
        int len = strlen(str_num);
        int mid = len / 2;

        char left_part[mid + 1];
        char right_part[len - mid + 1];
        strncpy(left_part, str_num, mid);
        strncpy(right_part, str_num + mid, len - mid);
        left_part[mid]        = '\0';
        right_part[len - mid] = '\0';

        *left  = atoi(left_part);
        *right = atoi(right_part);
}

void printArr(int count, long long int arr[]) {
        for (int i = 0; i < count; i++) {
                printf("%lld ", arr[i]);
        }
        printf("\n");
}

int main() {
        FILE* read_file                   = fopen(READ_FILE, "r");
        long long int stones[MAX_ARR_LEN] = {0};
        long long int stones_count        = INITIAL_STONE_COUNT;

        for (int i = 0; i < INITIAL_STONE_COUNT; i++) {
                fscanf(read_file, "%lld", &stones[i]);
        }
        fclose(read_file);

        for (int i = 0; i < ITERATION_COUNT; i++) {
                printf("iter: %d\n\r", i + 1);
                long long int next_gen[MAX_ARR_LEN] = {0};
                int next_gen_count                  = 0;

                for (int j = 0; j < stones_count; j++) {
                        // rule 1
                        if (stones[j] == 0) {
                                next_gen[next_gen_count++] = 1;
                                continue;
                        }
                        // rule 2
                        int digit_count = getDigitCount(stones[j]);
                        if (digit_count % 2 == 0) {
                                int left, right;
                                splitNumber(stones[j], &left, &right);
                                next_gen[next_gen_count++] = left;
                                next_gen[next_gen_count++] = right;
                                continue;
                        }
                        // rule 3
                        next_gen[next_gen_count++] = stones[j] * 2024;
                }

                for (int k = 0; k < next_gen_count; k++) {
                        stones[k] = next_gen[k];
                }
                stones_count = next_gen_count;
        }

        printArr(stones_count, stones);
        printf("count: %lld", stones_count);

        return 0;
}

