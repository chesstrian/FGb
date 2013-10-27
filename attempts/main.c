#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int main(int argc, char const *argv[]) {
  if (argc == 2) {
    char *buffer;
    char *polynomial;
    int result = get_file_content(argv[1], &buffer);

    switch (result) {
      case FILE_CONTENT_READ:
        polynomial = strtok(buffer, ",");
        while(polynomial != NULL) {
          fprintf(stdout, "%s\n", polynomial);
          polynomial = strtok(NULL, ",");
        }
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
