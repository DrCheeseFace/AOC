#include <stdio.h>

#define ARRAY_LENGTH 1000
#define FILE_NAME "input.txt"

int CountOccurances(int a, int arr[ARRAY_LENGTH]) {
    int count = 0;
    int j;
    for (j = 0; j < ARRAY_LENGTH; j++) {
        if (arr[j] == a) {
            count++;
        }
    }
    return count;
}

int main() {
    int left_number;
    int right_number;

    int left_numbers[ARRAY_LENGTH];
    int right_numbers[ARRAY_LENGTH];

    FILE* read_file;
    read_file = fopen(FILE_NAME, "r");

    int i;
    for (i = 0; i < ARRAY_LENGTH; i++) {
        fscanf(read_file, "%d %d", &left_number, &right_number);
        left_numbers[i]  = left_number;
        right_numbers[i] = right_number;
    }

    int score = 0;
    for (i = 0; i < ARRAY_LENGTH; i++) {
        score +=
            left_numbers[i] * CountOccurances(left_numbers[i], right_numbers);
    }

    printf("%d", score);
}
