#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_uniform(int arr[], int arr_size) {
    bool is_positive = true;
    if (arr[0] < arr[1]) {
        is_positive = true;
    } else {
        is_positive = false;
    }

    int i;
    for (i = 0; i < arr_size - 1; i++) {
        if (is_positive) {
            if (arr[i] >= arr[i + 1]) {
                return false;
            }
            continue;
        } else {
            if (arr[i] <= arr[i + 1]) {
                return false;
            }
            continue;
        }
    }
    return true;
}

bool is_smooth(int arr[], int arr_size) {
    int i;
    for (i = 0; i < arr_size - 1; i++) {
        if (abs(arr[i] - arr[i + 1]) != 0 && abs(arr[i] - arr[i + 1]) <= 3) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    FILE* file       = fopen("input.txt", "r");
    int** data       = NULL;
    int* row_lengths = NULL;
    int num_rows     = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int* row     = NULL;
        int row_size = 0;
        int value;
        char* ptr = buffer;

        while (sscanf(ptr, "%d", &value) == 1) {
            row           = realloc(row, (row_size + 1) * sizeof(int));
            row[row_size] = value;
            row_size++;

            ptr = strchr(ptr, ' ');
            if (ptr == NULL)
                break;
            ptr++;
        }

        data           = realloc(data, (num_rows + 1) * sizeof(int*));
        row_lengths    = realloc(row_lengths, (num_rows + 1) * sizeof(int));
        data[num_rows] = row;
        row_lengths[num_rows] = row_size;
        num_rows++;
    }

    int count = 0;
    int i;
    for (i = 0; i < 1000; i++) {
        if (is_uniform(data[i], row_lengths[i])) {
            if (is_smooth(data[i], row_lengths[i])) {
                count++;
            }
        }
    }
    printf("%d", count);
}
