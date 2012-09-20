#include "lines.h"

short lines_animation(int *y, int *x, int size_y, int size_x) {
  static int diff;
  if(*x < 0 && *y < 0) {
    diff = 0;
    *y = -1;
  }
  *y += 1;
  
  *x = *y % 2 ? size_x - diff - 1 : diff; 

  if(*y < size_y) {
    return 1;
  } else {
    *y = -1;
    diff++;
    return 0;
  }
}
