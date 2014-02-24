#include <stdio.h>
#include <stdlib.h>

#include "file.h"

char *get_file_content(char const *filename) {
  char *buffer;

  FILE *file = fopen(filename, "r");

  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);

  long length;
  length = ftell(file);

  fseek(file, 0, SEEK_SET);

  buffer = malloc(length);

  if (buffer) {
    fread(buffer, 1, length, file);
  }

  fclose(file);

  if (buffer) {
    return buffer;
  } else {
    return NULL;
  }
}
