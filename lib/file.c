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

char *output_filename() {
  int i = 1;
  char filenumber[3];
  char *fileprefix = malloc(sizeof(char *) * 10);
  char *filename = malloc(sizeof(char *) * 20);

  do {
    sprintf(fileprefix, "%s", "output.");
    sprintf(filenumber, "%d", i++);
    filename = strcat(fileprefix, filenumber);
  } while (access(filename, F_OK) != -1);

  return filename;
}
