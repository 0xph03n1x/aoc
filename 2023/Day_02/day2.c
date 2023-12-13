// inputs_test.txt
// inputs.txt
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_LEN 100
#define LINE_LEN_MAX 170

// Valid game parameters
#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

void PartOneSolver(char *games[]);
void PartTwoSolver(char *games[]);

int main(void) {
  // open file
  FILE *fp = fopen("inputs.txt", "r");
  // check if file opened successfully
  if (fp == 0) {
    fprintf(stderr, "Failed to open file!");
    return EXIT_FAILURE;
  }

  char line[LINE_LEN_MAX];
  char *games[FILE_LEN];

  // for each game allocate max line len worth of memory
  for (int i = 0; i < FILE_LEN; i++) {
    games[i] = malloc(LINE_LEN_MAX);
  }

  int index = 0;

  // copy line read from the file to games[]
  while (fgets(line, sizeof(line), fp)) {
    int end_line = 0;
    for (end_line; line[end_line] != '\n'; end_line++) {
    }
    strncpy(
        games[index], &line[8],
        end_line - 8);  // remove Game n: from the string since the index is n
    index++;
  }

  // close file
  fclose(fp);

  PartOneSolver(games);
  PartTwoSolver(games);

  return 0;
}

void PartOneSolver(char *games[]) {
  int number_of_cubes = 0;
  int result = 0;
  char color;

  for (int i = 0; i < FILE_LEN; i++) {
    bool is_game_possible = true;
    for (int j = 0; j < strlen(games[i]); j++) {
      if (isdigit(games[i][j])) {
        number_of_cubes = games[i][j] - 0x30;
        color = games[i][j + 2];
        if (isdigit(games[i][j + 1])) {
          number_of_cubes *= 10;
          number_of_cubes += games[i][j + 1] - 0x30;
          color = games[i][j + 3];
        }
        switch (color) {
          case 'r':
            if (number_of_cubes > MAX_RED) {
              is_game_possible = false;
            }
          case 'g':
            if (number_of_cubes > MAX_GREEN) {
              is_game_possible = false;
            }
          case 'b':
            if (number_of_cubes > MAX_BLUE) {
              is_game_possible = false;
            }
        }
      }
    }
    if (is_game_possible == true) {
      result += i + 1;
    }
  }
  printf("Part One - result of all possible games: %d\n", result);
}

void PartTwoSolver(char *arr[]) {
  int number_of_cubes, result = 0;
  char color_of_n;
  for (int i = 0; i < FILE_LEN; i++) {
    int min_red = 0, min_green = 0, min_blue = 0;
    for (int j = 0; j < strlen(arr[i]); j++) {
      if (isdigit(arr[i][j])) {
        number_of_cubes = arr[i][j] - '0';
        color_of_n = arr[i][j + 2];
        if (isdigit(arr[i][j + 1])) {
          number_of_cubes *= 10;
          number_of_cubes += arr[i][j + 1] - '0';
          color_of_n = arr[i][j + 3];
        }
        switch (color_of_n) {
          case 'r':
            if (number_of_cubes > min_red) min_red = number_of_cubes;
            break;
          case 'g':
            if (number_of_cubes > min_green) min_green = number_of_cubes;
            break;
          case 'b':
            if (number_of_cubes > min_blue) min_blue = number_of_cubes;
            break;
        }
      }
    }
    result += (min_red * min_green * min_blue);
  }
  printf("result of power of each game: %d\n", result);
}
