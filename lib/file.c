#include <stdio.h>
#include <stdlib.h>

#include "file.h"

int get_file_content(char const *filename, char **buffer) {
  FILE *file = fopen(filename, "r");

  if (!file) {
    return CANNOT_OPEN_FILE;
  }

  fseek(file, 0, SEEK_END);

  long length;
  length = ftell(file);

  fseek(file, 0, SEEK_SET);

  *buffer = malloc(length);

  if (*buffer) {
    fread(*buffer, 1, length, file);
  }

  fclose(file);

  if (*buffer) {
    return FILE_CONTENT_READ;
  } else {
    return FILE_CONTENT_UNREAD;
  }
}
