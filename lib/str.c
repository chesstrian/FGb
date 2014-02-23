#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "str.h"

char **str_split(char *split, char const *separator, int *length) {
  *length = 0;
  char **result = malloc(sizeof(char *) * strlen(split));

  char *poly = strtok(split, separator);

  while (poly) {
    *(result + (*length)++) = strdup(poly);
    poly = strtok(0, separator);
  }

  return result;
}

char *str_trim(char *str) {
  char *end;

  // Trim leading space
  while (isspace(*str)) {
    str++;
  }

  if (*str == 0) {
    return str;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace(*end)) {
    end--;
  }

  // Write new null terminator
  *(end + 1) = 0;

  return str;
}
