#include "figlet.h"
#include <stdlib.h>
#include <stdio.h>

char **get_figlet_text(int size_y, int size_x, char *inputtext) {
  static char **text = NULL;
  char command[256] = {};
  char c;
  int x,y;
  FILE *stream;

  free(text);
  text = malloc(size_y * sizeof(char*));

  for(y = 0; y < size_y; y++) {
    text[y] = calloc(size_x, sizeof(char));
  }

  // warning: %s is not secure
  snprintf(command, 256, "figlet -c -k -w %i -- '%s'", size_x, inputtext);
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
