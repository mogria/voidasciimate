#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "figlet/figlet.h"
#include "macros/array.h"


void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE); 
}

int main() {
  int size_x, size_y;
  int x, y;
  int ch;
  char **buffer;
  char **part;

  srand(time(NULL));

  init_ncurses();

  getmaxyx(stdscr, size_y, size_x);

  // allocate place for the buffer
  ALLOC2(char, buffer, size_y, size_x);


  // welcome part
  PART2(char, part, 20, buffer, 0, 0);
  get_figlet_text(part, 20, size_x, "welcome", "doh");
  FREE1(part);

  // to the part
  PART2(char, part, 10, buffer, 22, 0);
  get_figlet_text(part, 10, size_x, "to the", "starwars");
  FREE1(part);

  // void part
  PART2(char, part, 20, buffer, 30, 0);
  get_figlet_text(part, 20, size_x, "VOID", "doh");
  FREE1(part);

 
  // fill screen with # characters
  for(y = 0; y < size_y; y++) {
    for(x = 0; x < size_x; x++) {
      mvprintw(y, x, "#");
    }
  }

  // randomly draw bytes in buffer to correct position
  while(1) {
    ch = getch();
    x = (rand() / (float)RAND_MAX) * size_x;
    y = (rand() / (float)RAND_MAX) * size_y;
    char c = buffer[y][x];
    c = c == 0 ? ' ' : c;
    mvprintw(y, x, "%c", c);

    if(ch == 'a') {
      break;
    }
  }

  endwin();

  FREE2(buffer, size_y);
  return EXIT_SUCCESS;
}
