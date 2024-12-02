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

int *removeElement(int arr[], int arr_size, int ignore_idx) {
  int new_size = arr_size - (ignore_idx != -1 ? 1 : 0);
  int *new_arr = (int *)malloc(new_size * sizeof(int));
  if (!new_arr) {
    perror("Memory allocation failed");
    exit(1);
  }
  int j = 0;
  for (int i = 0; i < arr_size; i++) {
    if (i != ignore_idx) {
      new_arr[j++] = arr[i];
    }
  }
  return new_arr;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  int **data = NULL;
  int *row_lengths = NULL;
  int num_rows = 0;
  char buffer[1024];

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    int *row = NULL;
    int row_size = 0;
    int value;
    char *ptr = buffer;

    while (sscanf(ptr, "%d", &value) == 1) {
      row = realloc(row, (row_size + 1) * sizeof(int));
      if (!row) {
        perror("Memory allocation failed");
        return 1;
      }
      row[row_size++] = value;
      ptr = strchr(ptr, ' ');
      if (ptr == NULL)
        break;
      ptr++;
    }

    data = realloc(data, (num_rows + 1) * sizeof(int *));
    row_lengths = realloc(row_lengths, (num_rows + 1) * sizeof(int));
    if (!data || !row_lengths) {
      perror("Memory allocation failed");
      return 1;
    }

    data[num_rows] = row;
    row_lengths[num_rows] = row_size;
    num_rows++;
  }
  fclose(file);

  int count = 0;
  for (int i = 0; i < num_rows; i++) {
    for (int j = -1; j < row_lengths[i]; j++) {
      int *new_arr = removeElement(data[i], row_lengths[i], j);
      int len = (j == -1) ? row_lengths[i] : row_lengths[i] - 1;
      if (isUniform(new_arr, len) && isSmooth(new_arr, len)) {
        count++;
        free(new_arr);
        break;
      }
      free(new_arr);
    }
  }

  printf("%d\n", count);

  for (int i = 0; i < num_rows; i++) {
    free(data[i]);
  }
  free(data);
  free(row_lengths);

  return 0;
}

