#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "file.h"
#include "helper.h"
#include "utilities.h"

void process_grobner(char const *filename, int display, int step, int block) {
  char *buffer;

  if (get_file_content(filename, &buffer) == FILE_CONTENT_READ) {
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
  }
}

