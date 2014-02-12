#include <stdio.h>
#include <string.h>

#include "utilities.h"

void remove_brakets(char **buffer) {
  (*buffer)++; // Remove first bracket.
  (*buffer)[strlen(*buffer) - 3] = '\0'; // Remove last bracket.
}
