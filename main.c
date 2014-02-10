#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "UtilsWrapper.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file.\n", argv[0]);
    return -1;
  }

  // Variables.
  char *buffer;
  char *polynomial;
//  CUtils *u = NULL;

  char const *filename = argv[1];
  int result = get_file_content(filename, &buffer);

  switch (result) {
  case FILE_CONTENT_READ:
//    u = str_new(buffer);
//    str_print(u);
    break;
  case FILE_CONTENT_UNREAD:
    fprintf(stderr, "Could not read file's content.\n");
    break;
  case CANNOT_OPEN_FILE:
    fprintf(stderr, "Could not open file.\n");
    break;
  default:
    break;
  }

  return 0;
}
