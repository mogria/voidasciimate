#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "figlet/figlet.h"
#include "animation/random.h"
#include "animation/top-down.h"
#include "macros/array.h"

struct textline {
  char *text;
  char *fontname;
  int offset_y;
  int offset_x;
  int size_y;
};


void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE); 
}

#define NUM_TEXTLINES 3

int main() {
  int size_x, size_y;
  int x, y;
  int ch;
  char **buffer;
  char **part;
  struct textline texts[NUM_TEXTLINES] = {
    {
      "welcome",
      "doh",
      0,
      0,
      20
    },
    {
      "to the",
      "starwars",
      20,
      0,
      10
    },
    {
      "VOID",
      "doh",
      30,
      0,
      20
    },
  };

  void (*animator_func)(int *, int*, int, int) = top_down_animation;

  srand(time(NULL));

  init_ncurses();

  getmaxyx(stdscr, size_y, size_x);

  // allocate place for the buffer
  ALLOC2(char, buffer, size_y, size_x);

  for(x = 0; x < NUM_TEXTLINES; x++) {
    // welcome part
    PART2(char, part, texts[x].size_y, buffer, texts[x].offset_y, 0);
    get_figlet_text(part, texts[x].size_y, size_x, texts[x].text, texts[x].fontname);
    FREE1(part);
  }

  // fill screen with # characters
  for(y = 0; y < size_y; y++) {
    for(x = 0; x < size_x; x++) {
      mvprintw(y, x, "#");
    }
  }

  // randomly draw bytes in buffer to correct position
  x = -1; y = -1;
  while(1) {
    ch = getch();
    animator_func(&y, &x, size_y, size_x);

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
