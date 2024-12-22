#include "color.c"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define ALPHA "~`!@#$%^&*()=_+-[]{}1234567890/\\|"
#define SET_SIZE 10
#define LIMIT 30 * SET_SIZE
#define PROMPT "set: %s\ntry: "

void mixer(char *dest) {
  int r;
  for (int i = 0; i < SET_SIZE; i++) {
    r = rand() % (sizeof(ALPHA) - 1);
    dest[i] = ALPHA[r];
  }
}

int main() {
  setup_keyboard();
  srand(time(NULL));

  int c;
  int i = 0;
  int n = 0;

  char *set = malloc(sizeof(char) * SET_SIZE);
  bzero(set, SET_SIZE);

  clear();
  mixer(set);
  printf(PROMPT, set);

  while ((c = getchar()) != EOF) {
    if (c == 'Q') {
      break;
    }

    if (c == set[i]) {
      putchar(c);
      i++;
    } else {
      errch(c);
    }

    if (i == SET_SIZE) {
      i = 0;
      clear();
      mixer(set);
      printf(PROMPT, set);
    }

    if (++n == LIMIT) {
      break;
    }
  }
}
