#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "test.txt"
#define XY_LENGTH 10
#define SEARCH_STRING "XMAS"

int countLeftToRightOccurances(char* pString) {
    if (strlen(pString) < 4) {
        return 0;
    }
    int count        = 0;
    const char* temp = pString;

    while ((temp = strstr(temp, SEARCH_STRING)) != NULL) {
        count++;
        temp += strlen(SEARCH_STRING);
    }
    return count;
}

char** mirrorGridDiagonally(char(data)[XY_LENGTH][XY_LENGTH + 1]) {
    char** pYrotated_data = malloc((XY_LENGTH) * sizeof(char*));
    for (int i = 0; i < XY_LENGTH; i++) {
        pYrotated_data[i] = malloc(XY_LENGTH + 1);
    }

    for (int row = 0; row < XY_LENGTH; row++) {
        for (int col = 0; col < XY_LENGTH; col++) {
            pYrotated_data[row][col] = data[col][row];
        }
        pYrotated_data[row][XY_LENGTH] = '\0';
    }
    return pYrotated_data;
}

char* reverseString(char* pString) {
    int length             = strlen(pString);
    char* pReversed_string = malloc((length + 1) * sizeof(char)); // Correct allocation
    for (int i = 0; i < length; i++) {
        pReversed_string[i] = pString[length - i - 1];
    }
    pReversed_string[length] = '\0';
    return pReversed_string;
}

char** getDiagonalsArrays(char data[XY_LENGTH][XY_LENGTH + 1]) {
    int max_diagonals = XY_LENGTH * 4 - 2;
    char** diagonals  = (char**)calloc(max_diagonals, sizeof(char*));

    char diagonal[XY_LENGTH + 1];
    int count = 0;

    for (int start = 0; start < XY_LENGTH; start++) {
        int row = start, col = 0, len = 0;
        while (row >= 0 && col < XY_LENGTH) {
            diagonal[len++] = data[row--][col++];
        }
        diagonal[len]      = '\0';
        diagonals[count++] = strdup(diagonal);
    }

    for (int start = 1; start < XY_LENGTH; start++) {
        int row = XY_LENGTH - 1, col = start, len = 0;
        while (row >= 0 && col < XY_LENGTH) {
            diagonal[len++] = data[row--][col++];
        }
        diagonal[len]      = '\0';
        diagonals[count++] = strdup(diagonal);
    }

    for (int start = 0; start < XY_LENGTH; start++) {
        int row = start, col = XY_LENGTH - 1, len = 0;
        while (row >= 0 && col < XY_LENGTH) {
            diagonal[len++] = data[row--][col--];
        }
        diagonal[len]      = '\0';
        diagonals[count++] = strdup(diagonal);
    }

    for (int start = 1; start < XY_LENGTH; start++) {
        int row = XY_LENGTH - 1, col = start, len = 0;
        while (row >= 0 && col < XY_LENGTH) {
            diagonal[len++] = data[row--][col--];
        }
        diagonal[len]      = '\0';
        diagonals[count++] = strdup(diagonal);
    }

    return diagonals;
}

int main() {
    FILE* read_file = fopen(FILE_NAME, "r");

    char data[XY_LENGTH][XY_LENGTH + 1];
    for (int i = 0; i < XY_LENGTH; i++) {
        fscanf(read_file, "%s", data[i]);
        data[i][XY_LENGTH] = '\0';
    }
    fclose(read_file);

    int count = 0;

    for (int row = 0; row < XY_LENGTH; row++) {
        count += countLeftToRightOccurances(data[row]);
        char* pReversed_row = reverseString(data[row]);
        count += countLeftToRightOccurances(pReversed_row);
        free(pReversed_row);
    }

    char** rotated_grid_data = mirrorGridDiagonally(data);
    for (int row = 0; row < XY_LENGTH; row++) {
        count += countLeftToRightOccurances(rotated_grid_data[row]);
        free(rotated_grid_data[row]);
    }
    free(rotated_grid_data);

    char** diagonals  = getDiagonalsArrays(data);
    int max_diagonals = XY_LENGTH * 4 - 2;
    for (int i = 0; i < max_diagonals; i++) {
        if (diagonals[i] != NULL) {
            count += countLeftToRightOccurances(diagonals[i]);
            char* pReversed_diag = reverseString(diagonals[i]);
            count += countLeftToRightOccurances(pReversed_diag);
            free(pReversed_diag);
            free(diagonals[i]);
        }
    }
    free(diagonals);

    printf("count: %d\n", count);

    return 0;
}
