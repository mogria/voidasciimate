#include "figlet.h"
#include <stdlib.h>
#include <stdio.h>
#include "../macros/array.h"

void get_figlet_text(char **buffer, int size_y, int size_x, char *inputtext, char *font) {
  static char **text = NULL;
  char command[256] = {};
  char c;
  int x,y;
  FILE *stream;

  // warning: %s is not secure
  snprintf(command, 256, "figlet -c -k -w %i -f '%s' -- '%s'", size_x, font, inputtext);
  stream = popen(command, "r");
  if(stream != NULL) {
    x = 0;
    y = 0;
    while(EOF != (c = fgetc(stream)) && y < size_y) {
      if(c == '\n') {
        y++;
        x = 0;
      } else {
        text[y][x] = c;
        x++;
      }
    }
    fclose(stream);
  }

  return text;
}
