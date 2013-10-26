#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, char *argv[]) {
  if (argc == 2) {
    char *buffer;
    int result = getFileContent(argv[1], &buffer);
    switch (result) {
      case FILE_CONTENT_READ:
        fprintf(stdout, "%s\n", buffer);
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
  } else {
    fprintf(stderr, "Usage: %s file.\n", argv[0]);
    return -1;
  }

  return 0;
}
