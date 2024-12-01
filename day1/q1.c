#include <stdio.h>
#include <stdlib.h>

int left_number;
int right_number;

int left_numbers[1000];
int right_numbers[1000];

int diffs[1000];

FILE *read_file;

int comp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {
  read_file = fopen("input.txt", "r");

  int i;
  for (i = 0; i < 1000; i++) {
    fscanf(read_file, "%d %d", &left_number, &right_number);
    left_numbers[i] = left_number;
    right_numbers[i] = right_number;
  }

  qsort(left_numbers, 1000, sizeof(int), comp);
  qsort(right_numbers, 1000, sizeof(int), comp);

  for (i = 0; i < 1000; i++) {
    int diff = left_numbers[i] - right_numbers[i];
    diff = abs(diff);
    diffs[i] = diff;
  }

  int total = 0;

  for (i = 0; i < 1000; i++) {
    total += diffs[i];
  }
  printf("total: %d\n", total);
}
