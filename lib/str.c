#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

char **str_split(char *split, char const *separator) {
  size_t index = 0;
  char **result = malloc(sizeof(char*) * strlen(split));

  char *poly = strtok(split, separator);

  while (poly) {
    *(result + index++) = strdup(poly);
    poly = strtok(0, separator);
  }

  return result;
}
