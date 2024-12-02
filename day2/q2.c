#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isUniform(int arr[], int arr_size) {
    if (arr_size < 2)
        return true;
    bool is_positive = arr[0] < arr[1];
    for (int i = 0; i < arr_size - 1; i++) {
        if ((is_positive && arr[i] >= arr[i + 1]) ||
            (!is_positive && arr[i] <= arr[i + 1])) {
            return false;
        }
    }
    return true;
}

bool isSmooth(int arr[], int arr_size) {
    for (int i = 0; i < arr_size - 1; i++) {
        if (abs(arr[i] - arr[i + 1]) > 3) {
            return false;
        }
    }
    return true;
}

int* removeElement(int arr[], int arr_size, int ignore_idx) {
    int new_size  = arr_size - (ignore_idx != -1 ? 1 : 0);
    int* pNew_arr = (int*)malloc(new_size * sizeof(int));
    if (!pNew_arr) {
        perror("Memory allocation failed");
        exit(1);
    }
    int j = 0;
    for (int i = 0; i < arr_size; i++) {
        if (i != ignore_idx) {
            pNew_arr[j++] = arr[i];
        }
    }
    return pNew_arr;
}

int main() {
    FILE* pFile = fopen("input.txt", "r");
    if (!pFile) {
        perror("Error opening file");
        return 1;
    }

    int** ppData      = NULL;
    int* pRow_lengths = NULL;
    int num_rows      = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), pFile) != NULL) {
        int* pRow     = NULL;
        int row_size  = 0;
        char* pBuffer = buffer;
        int value;

        while (sscanf(pBuffer, "%d", &value) == 1) {
            pRow = realloc(pRow, (row_size + 1) * sizeof(int));
            if (!pRow) {
                perror("Memory allocation failed");
                return 1;
            }
            pRow[row_size++] = value;
            pBuffer          = strchr(pBuffer, ' ');
            if (pBuffer == NULL)
                break;
            pBuffer++;
        }

        ppData       = realloc(ppData, (num_rows + 1) * sizeof(int*));
        pRow_lengths = realloc(pRow_lengths, (num_rows + 1) * sizeof(int));
        if (!ppData || !pRow_lengths) {
            perror("Memory allocation failed");
            return 1;
        }

        ppData[num_rows]       = pRow;
        pRow_lengths[num_rows] = row_size;
        num_rows++;
    }
    fclose(pFile);

    int count = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = -1; j < pRow_lengths[i]; j++) {
            int* pNew_arr = removeElement(ppData[i], pRow_lengths[i], j);
            int len       = (j == -1) ? pRow_lengths[i] : pRow_lengths[i] - 1;
            if (isUniform(pNew_arr, len) && isSmooth(pNew_arr, len)) {
                count++;
                free(pNew_arr);
                break;
            }
            free(pNew_arr);
        }
    }

    printf("%d\n", count);

    for (int i = 0; i < num_rows; i++) {
        free(ppData[i]);
    }
    free(ppData);
    free(pRow_lengths);

    return 0;
}
