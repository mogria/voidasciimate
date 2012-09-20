#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "figlet/figlet.h"
#include "animation/random.h"
#include "animation/top-down.h"
#include "animation/circle.h"
#include "animation/lines.h"
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
  int c = 0,ch = 0;
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

  short (*animator_func)(int *, int*, int, int) = random_animation;

  struct timespec last_frame_time;
  struct timespec current_time;

  clock_gettime(CLOCK_REALTIME, &last_frame_time);

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
    c = getch();
    if(c != ERR) {
      ch = c;
    }

    // update current time
    clock_gettime(CLOCK_REALTIME, &current_time);

    // calculate diffrence
    unsigned long long timediff = (((unsigned long long)current_time.tv_sec) << sizeof(time_t)) + current_time.tv_nsec;
    timediff -= (((unsigned long long)last_frame_time.tv_sec) << sizeof(time_t)) + last_frame_time.tv_nsec;
    
     // check if diffrence is more or = 100ms
    if(timediff >= 10000000) {
      // store time of last frame
      last_frame_time.tv_sec = current_time.tv_sec;
      last_frame_time.tv_nsec = current_time.tv_nsec;

      short again;
      do {
        again = animator_func(&y, &x, size_y, size_x);
        if(y >= 0 && y < size_y && x >= 0 && x < size_x) {
          char c = buffer[y][x];
          c = c == 0 ? ' ' : c;
          mvprintw(y, x, "%c", c);
        }
      } while (again);

      if(ch == 'a') {
        break;
      }
    }
  }

  endwin();

  FREE2(buffer, size_y);
  return EXIT_SUCCESS;
}
