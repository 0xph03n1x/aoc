#include <stddef.h>
#include <stdio.h>
#include <string.h>

const char *words[] = {"one", "two",   "three", "four", "five",
                       "six", "seven", "eight", "nine"};
const size_t string_lengths[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};

int getDigit(char buff[], int first, int use_words) {
  int words_idx[9] = {0};

  size_t idx = first ? 0 : strlen(buff) - 1;
  while (buff[idx] != '\0' && idx >= 0) {
    char c = buff[idx];
    idx += first ? 1 : -1;
    if (c >= 48 && c <= 57) {
      return c - 48;
    }

    if (use_words) {
      for (int i = 0; i <= 8; i++) {
        const char *word = words[i];
        int w_idx = words_idx[i];
        if (!first) {
          w_idx = string_lengths[i] - 1 - w_idx;
        }
        if (word[w_idx] == c) {
          words_idx[i]++;

          if (first && word[w_idx + 1] == '\0' || !first && w_idx == 0) {
            // first match
            return i + 1;
          }
        } else {
          if (first) {
            words_idx[i] = word[0] == c ? 1 : 0;
          } else {
            words_idx[i] = word[string_lengths[i] - 1] == c ? 1 : 0;
          }
        }
      }
    }
  }
  return 0;
}

int solve(int use_words) {
  FILE *fp = fopen("input", "r");
  int sum = 0;

  char line[255];
  while (fgets(line, 255, fp)) {
    int first_digit = getDigit(line, 1, use_words);
    int last_digit = getDigit(line, 0, use_words);

    sum += first_digit * 10 + last_digit;
  }

  fclose(fp);

  return sum;
}

int main() {
  printf("part1: %d\n", solve(0));
  printf("part2: %d\n", solve(1));
}
