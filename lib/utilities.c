#include <string.h>

#include "utilities.h"

void remove_brakets(char *buffer) {
  buffer++; // Remove first bracket.
  buffer[strlen(buffer) - 1] = '\0'; // Remove last bracket.
}
