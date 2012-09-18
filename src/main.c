#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "figlet/figlet.h"

int main() {
  int size_x, size_y;
  int x, y;
  int ch;
  char **text;
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE); 

  srand(time(NULL));

  getmaxyx(stdscr, size_y, size_x);

  text = get_figlet_text(size_y, size_x, "\n\nWelcome\nto the\nVOID");

 
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
