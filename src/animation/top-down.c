#include "top-down.h"

short top_down_animation(int *pos_y, int *pos_x, int size_y, int size_x) {
  if(*pos_y < 0 || *pos_x < 0) {
    *pos_y = 0; 
    *pos_x = 0; 
    return 1;
  } else {
    (*pos_x)++;
    if(*pos_x >= size_x) {
      if(*pos_y < size_y - 1)  {
        (*pos_y)++;
        *pos_x = 0;
      } else {
        (*pos_x) = size_x;
      }
      return 0;
    } else {
      return 1;
    }
  }
}
