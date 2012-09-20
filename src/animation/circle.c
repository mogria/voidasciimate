#include "circle.h"
#include <math.h>

short circle_animation(int *y, int *x, int size_y, int size_x) {
  static float angle = 0;
  static int radius = 1;
  if(*y < 0 && *x < 0) {
    *y = size_y / 2;
    *x = size_x / 2;
    angle = 0;
    return 0;
  } else {
    if(angle >= 360)  {
      angle = 0;
      radius++;
      return 0;
    } else {
      float add = radius * 2 * M_PI;
      add = add == 0 ? 360 : 360 / (add * M_PI);
      *x = size_x / 2.0 + round(sin(angle / (float) 180 * M_PI) * radius);
      *y = size_y / 2.0 + round(cos(angle / (float) 180 * M_PI) * radius);
      
      angle += add;
      return 1;
    }
  }
}
