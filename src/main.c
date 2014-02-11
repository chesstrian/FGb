#include <stdio.h>

#include "file.h"
#include "helper.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s file.\n", argv[0]);
    return -1;
  }

  char const *filename = argv[1];
  int result = read_data(filename);

  switch (result) {
  case FILE_CONTENT_READ:
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
