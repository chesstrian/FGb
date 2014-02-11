#include <stdio.h>

#include "file.h"

#include "helper.h"
#include "utilities.h"

int read_data(char const *filename) {
  char *buffer;

  // Read data from filename.
  int read_file = get_file_content(filename, &buffer);
  if (read_file != FILE_CONTENT_READ) {
    return read_file;
  }

  parse_data(buffer);

  return FILE_CONTENT_READ;
}

int parse_data(char *buffer) {
  // TODO : Implement.
  remove_brakets(buffer);
  fprintf(stdout, "%s", buffer);

  return 0;
}
