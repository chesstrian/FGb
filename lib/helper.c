#include <stdio.h>
#include <stdlib.h>

#include "str.h"
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
  char *poly = NULL;
  char **polys = NULL;
  char const *separator = ",";

  remove_brakets(&buffer);
  polys = str_split(buffer, separator);

  if (polys) {
    for (int i = 0; *(polys + i); ++i) {
      poly = str_trim(*(polys + i));
      fprintf(stdout, "Super poly: %s.\n", poly);
    }
  }

  return 0;
}
