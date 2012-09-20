#include <stdlib.h>
#include "random.h"

short random_animation(int *pos_y, int *pos_x, int size_y, int size_x) {
    static int n = -1;
  if(*pos_x < 0 || *pos_y < 0) {
    n = -1;
  }
  *pos_x = (rand() / (float)RAND_MAX) * size_x;
  *pos_y = (rand() / (float)RAND_MAX) * size_y;
  n++;
  if(n < 200) {
    return 1;
  } else {
    n = 0;
    return 0;
  }
}
