#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "str.h"

void remove_brakets(char **buffer) {
  (*buffer)++; // Remove first bracket.

  int i = 0, len = strlen(*buffer);

  while ((*buffer)[len - ++i] != ']')
    ;

  (*buffer)[len - i] = '\0'; // Remove last bracket.
}

void str_trim(char **string) {
  while (isspace(**string)) {
    (*string)++;
  }

  if (**string == 0) {
    return;
  }

  char *end = *string + strlen(*string) - 1;
  while (end > *string && isspace(*end)) {
    end--;
  }

  *(end + 1) = 0;
}

char **str_split(char *buffer, char const *separator, int *length) {
  char **result = malloc(sizeof(char *) * strlen(buffer));
  char *poly = strtok(buffer, separator);

  *length = 0;
  while (poly) {
    *(result + (*length)++) = strdup(poly);
    poly = strtok(0, separator);
  }

  return result;
}
