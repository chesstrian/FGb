#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

char *output_filename(int q, int n) {
  char *filename = malloc(sizeof(char *) * 20);

  sprintf(filename, "%s_q%d_n%d", "solution", q, n);

  return filename;
}

char *stats_filename(int q, int n) {
  char *filename = malloc(sizeof(char *) * 20);

  sprintf(filename, "%s_q%d_n%d", "output", q, n);

  return filename;
}
