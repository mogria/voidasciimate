#include "figlet-info.h"

void get_figlet_default_dir(char *buffer, size_t size) {
  char ch;
  int pos = 0;
  FILE *handle = popen("figlet -I2", "r");
  if(handle != NULL) {
    while(EOF != (ch = getc(handle)) && ch != '\n' && pos < size - 1) {
      buffer[pos] = ch;
      pos++;
    }
    buffer[size - 1] = '\0';
    fclose(handle);
  }
}


