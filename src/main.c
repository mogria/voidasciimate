#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "figlet/figlet.h"

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


  srand(time(NULL));

  init_ncurses();

  getmaxyx(stdscr, size_y, size_x);

  ALLOC2(char, buffer, size_y, size_x);
  get_figlet_text(buffer, size_y, size_x, "VOID", "doh");

 
  for(y = 0; y < size_y; y++) {
    for(x = 0; x < size_x; x++) {
      mvprintw(y, x, "#");
    }
  }
  while(1) {
    ch = getch();
    x = (rand() / (float)RAND_MAX) * size_x;
    y = (rand() / (float)RAND_MAX) * size_y;
    char c = text[y][x];
    c = c == 0 ? ' ' : c;
    mvprintw(y, x, "%c", c);

    if(ch == 'a') {
      break;
    }
  }

  endwin();
  return 0;
}
