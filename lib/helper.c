#include <stdio.h>

#include "file.h"

#include "helper.h"

int read_data(char const *filename) {
  char *buffer;

  // Read data from filename.
  int read_file = get_file_content(filename, &buffer);
  if (read_file != FILE_CONTENT_READ) {
    return read_file;
  }

  fprintf(stdout, "%s", buffer);

  return FILE_CONTENT_READ;
}
