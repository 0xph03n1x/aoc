#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PartOneSolver(char *line);
int PartTwoSolver(char *line);
int FindWord(char *substring);

const char *words[] = {"zero", "one", "two",   "three", "four",
                       "five", "six", "seven", "eight", "nine"};

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  char line[100];
  int part_one = 0;
  int part_two = 0;

  while (fgets(line, sizeof(line), fp)) {
    part_one += PartOneSolver(line);
  }
  printf("Part one solution - %d\n", part_one);

  rewind(fp);

  while (fgets(line, sizeof(line), fp)) {
    part_two += PartTwoSolver(line);
  }
  printf("Part two solution - %d\n", part_two);

  fclose(fp);
  return 0;
}

int PartOneSolver(char *line) {
  int solution = 0;
  int first_number = 0;
  int second_number = 0;
  int i = 0;

  // printf("Word: %s", line);
  while (true) {
    char c = line[i];

    if (c == '\0' || c == '\n' || c == '\r') {
      break;
    }

    if (c >= 48 && c <= 57) {
      first_number = atoi(&c);
      break;
    }
    i++;
  }

  int j = strlen(line) - 1;

  while (j >= 0) {
    char c = line[j];

    if (c >= 48 && c <= 57) {
      second_number = atoi(&c);
      break;
    }
    j--;
  }

  if (second_number > 0) {
    solution += (first_number * 10) + second_number;
  } else {
    solution += first_number + second_number;
  }

  // printf("F-%d, L-%d, S-%d\n", first_number, second_number, solution);
  return solution;
}

int PartTwoSolver(char *line) {
  printf("Word: %s", line);
  int solution = 0;
  int first_number = 0;
  int second_number = 0;
  int i = 0;

  while (true) {
    char c = line[i];

    if (c == '\0' || c == '\n' || c == '\r') {
      break;
    }
    if (c >= 48 && c <= 57) {
      first_number = atoi(&c);
      break;
    } else {
      char *substring = malloc(i + 2);
      strncpy(substring, line, i + 1);
      substring[i + 1] = '\0';
      int wordnum = FindWord(substring);
      if (wordnum != -1) {
        first_number = wordnum;
        break;
      }
      free(substring);
    }
    i++;
  }
  int j = strlen(line) - 1;

  while (j >= 0) {
    char c = line[j];

    if (c >= 48 && c <= 57) {
      second_number = atoi(&c);
      break;
    } else {
      char *substr = malloc(strlen(line) - j + 1);
      strncpy(substr, line + j, strlen(line) - j + 1);
      int wordnum = FindWord(substr);
      if (wordnum != -1) {
        second_number = wordnum;
        break;
      }
      free(substr);
    }
    j--;
  }

  if (second_number > 0) {
    solution += (first_number * 10) + second_number;
  } else {
    solution += first_number + second_number;
  }
  printf("F-%d, L-%d, S-%d\n", first_number, second_number, solution);
  return solution;
}

int FindWord(char *substring) {
  for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
    if (strstr(substring, words[i]) != NULL) {
      return i;
    }
  }
  return -1;
}
