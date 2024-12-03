#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "input.txt"
// #define FILE_NAME "test.txt"
#define ARRAY_LENGTH 6
#define MAX_LINE_LENGTH 4096

#define STARTING_STRING "mul("
#define CLOSING_BRACKET ")"
#define WHITESPACE " "
#define COMMA ","

char* getStringBetweenBrackets(char* pStart, char* pEnd) {
    pStart += 4;
    unsigned long length = pEnd - pStart;

    char* pInside_brackets = malloc(length + 1);
    if (!pInside_brackets) {
        return NULL;
    }

    strncpy(pInside_brackets, pStart, length);
    pInside_brackets[length] = '\0';
    return pInside_brackets;
}

char* getStringBetweenPointers(char* pStart, char* pEnd) {
    unsigned long length = pEnd - pStart;

    char* pInside_pointers = malloc(length + 1);
    if (!pInside_pointers) {
        return NULL;
    }

    strncpy(pInside_pointers, pStart, length);
    pInside_pointers[length] = '\0';
    return pInside_pointers;
}

char* findNextChar(char* pString, char* pSearchString) {
    char* pFind_search_string = pString;
    size_t length             = strlen(pString);
    int i;

    for (i = 0; i < length; i++) {
        if (strncmp(pFind_search_string, pSearchString,
                    strlen(pSearchString)) == 0) {
            return pFind_search_string;
        }
        pFind_search_string++;
    }
    return NULL;
}

int tryStringToInt(char* pString_number) {
    char* pWalk_string = pString_number;
    while (pWalk_string != pString_number + strlen(pString_number)) {
        if (*pWalk_string < '0' || *pWalk_string > '9') {
            return 0;
        }
        pWalk_string++;
    }

    long out =
        strtol(pString_number, &pString_number + strlen(pString_number), 10);
    return out;
}

int main() {
    // file parsing
    FILE* read_file = fopen(FILE_NAME, "r");
    if (!read_file) {
        perror("where file bruh err");
        return 1;
    }

    char lines[ARRAY_LENGTH][MAX_LINE_LENGTH + 1];
    char* ptr = &lines[ARRAY_LENGTH][MAX_LINE_LENGTH + 1];
    int i;

    for (i = 0; i < ARRAY_LENGTH; i++) {
        if (fgets(lines[i], MAX_LINE_LENGTH + 1, read_file) == NULL) {
            if (feof(read_file)) {
                fprintf(stderr, "fucky wucky\n");
                break;
            } else {
                perror("Error reading line");
                fclose(read_file);
                return 1;
            }
        }
    }
    fclose(read_file);

    // actual logic
    long count = 0;
    for (int j = 0; j < ARRAY_LENGTH; j++) {
        char* pWindow = lines[j];
        size_t length = strlen(pWindow);

        for (i = 0; i < length - 1; i++) {
            if (strncmp(pWindow, STARTING_STRING, strlen(STARTING_STRING)) ==
                0) {
                char* pClosing_bracket = findNextChar(pWindow, CLOSING_BRACKET);
                if (pClosing_bracket == NULL) {
                    printf("couldnt find closign bracket");
                    break;
                }

                char* pInside_brackets =
                    getStringBetweenBrackets(pWindow, pClosing_bracket);
                if (pInside_brackets == NULL) {
                    pWindow++;
                    continue;
                }
                char* pComma = findNextChar(pInside_brackets, COMMA);
                char* pFirst_number =
                    getStringBetweenPointers(pInside_brackets, pComma);
                char* pSecond_number = getStringBetweenPointers(
                    pComma + 1, pInside_brackets + strlen(pInside_brackets));

                if (pFirst_number == NULL || pSecond_number == NULL) {
                    pWindow++;
                    continue;
                }

                long first_number  = tryStringToInt(pFirst_number);
                long second_number = tryStringToInt(pSecond_number);
                if (first_number == 0 || second_number == 0) {
                    pWindow++;
                    continue;
                }
                count += first_number * second_number;

                free(pInside_brackets);
                free(pFirst_number);
                free(pSecond_number);
            }
            pWindow++;
        }
        printf("count: %ld\n\r", count);
    }
    return 0;
}
