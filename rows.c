#include "color.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <time.h>
#include <unistd.h> // STDIN_FILENO

static char *patterns[] = {
    // piano-like patterns, improves general agility and speed
    "uiop[poi",
    "uiopoi",
    "jkl;';lk",
    "jkl;lk",
    "nm,./.,m",
    // my right hand nightmare
    "jumki,lo.;p/",
    // make your pinky sweat a little
    "/jpl; ",
};

static int patterns_count = sizeof(patterns) / sizeof(patterns[0]);

int main(int argc, char **argv) {
  setup_keyboard();
  srand(time(NULL));

  char *set;
  if (argc > 1) {
    set = argv[1];
  } else {
    int n = rand() % patterns_count;
    set = patterns[n];
  }
  size_t set_sz = strlen(set);

  int limit = 500;
  if (argc > 2) {
    limit = atoi(argv[2]);
  }

  clear();
  printf("pattern: `%s` | limit %d\n", set, limit);

  size_t i = 0;
  int c;
  int pressed = 0;
  int missed = 0;
  while ((c = getchar()) != EOF) {
    if (c == '!') {
      break;
    }

    if (c != set[i]) {
      // print as error
      errch(c);
      missed++;
    } else {
      // print as just ok
      putchar(c);
      if (++i == set_sz) {
        i = 0;
      }
    }
    if (++pressed >= limit) {
      break;
    }
  }

  float errp = (float)missed / (float)limit * 100;
  printf("\nlimit of %d is done, %d errors (%f%%).\n", limit, missed,
         (double)errp);
}
