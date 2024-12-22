#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define clear() printf("\033[H\033[J")

void errch(int c) {
  if (c == ' ') {
    c = '_'; // sadly we can't color the whitespace...
  };
  printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, c);
}

// switch terminal into a raw mode,
// so keypresses are delivered immediately, without pressing ENTER
// (I've chatGPTed this, sorry).
void setup_keyboard() {
  struct termios term_io;

  // Get the current terminal attributes and store them in orig_termios
  tcgetattr(STDIN_FILENO, &term_io);

  // Disable canonical mode and echo
  term_io.c_lflag &= ~(ICANON | ECHO);

  // Set the terminal attributes with the modified settings
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_io);
}
