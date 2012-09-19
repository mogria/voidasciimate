#include <stdlib.h>
#include "random.h"

void random_animation(int *pos_y, int *pos_x, int size_y, int size_x) {
  *pos_x = (rand() / (float)RAND_MAX) * size_x;
  *pos_y = (rand() / (float)RAND_MAX) * size_y;
}
