#include <stdio.h>
#include <stdlib.h>

int my_compare(const void *a, const void *b);
size_t PartOneSolver(const size_t *l, const size_t *r, int n);
size_t PartTwoSolver(const size_t *l, const size_t *r, int n);

void pairs(const size_t *left, const size_t *right, int n);

int main(void) {
  size_t part_one = 0;
  size_t part_two = 0;
  // FILE *fp = fopen("test.txt", "r");
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL) {
    fprintf(stderr, "Unable to open file.\n");
    exit(EXIT_FAILURE);
  }

  char buffer[1000];
  size_t *left = malloc(sizeof(size_t) * 2000);
  size_t *right = malloc(sizeof(size_t) * 2000);
  size_t line = 0;

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (sscanf(buffer, "%lu %lu", &left[line], &right[line]) != 2) {
      fprintf(stderr, "Line formatting error.\n");
      exit(EXIT_FAILURE);
    }
    ++line;
  }

  fclose(fp);

  qsort(left, line, sizeof(size_t), my_compare);
  qsort(right, line, sizeof(size_t), my_compare);

  // pairs(left, right, line);

  size_t res_one = PartOneSolver(left, right, line);
  printf("Part one result: %lu\n", res_one);

  size_t res_two = PartTwoSolver(left, right, line);
  printf("Part two result: %lu\n", res_two);

  return 0;
}

int my_compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void pairs(const size_t *left, const size_t *right, int n) {
  printf("Sorted array:\n");
  for (int i = 0; i < n; i++) {
    printf("%lu %lu\n", left[i], right[i]);
  }
}

size_t PartOneSolver(const size_t *l, const size_t *r, int n) {
  size_t result = 0;

  for (int k = 0; k < n; k++) {
    if (l[k] > r[k]) {
      result += l[k] - r[k];
    } else if (l[k] < r[k]) {
      result += r[k] - l[k];
    }
  }

  return result;
}

size_t PartTwoSolver(const size_t *l, const size_t *r, int n) {
  size_t result = 0;
  size_t freq = 0;

  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) {
      if (l[i] == r[k]) {
        freq++;
      }
      result += l[i] * freq;
      freq = 0;
    }
  }
  return result;
}
