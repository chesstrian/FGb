#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "str.h"

char *remove_brakets(char const *buffer) {
  long unsigned memory = sizeof(char *) * strlen(buffer);
  char *result = malloc(memory);
  memcpy(result, buffer, memory);

  result++; // Remove first bracket.
  result[strlen(result) - 1] = '\0'; // Remove last bracket.

  return result;
}

char **str_split(char const *buffer, char const *separator, int *length) {
  char **result = malloc(sizeof(char *) * strlen(buffer));

  long unsigned memory = sizeof(char *) * strlen(buffer);
  char *string = malloc(memory);
  memcpy(string, buffer, memory);

  char *poly = strtok(string, separator);

  *length = 0;
  while (poly) {
    *(result + (*length)++) = strdup(poly);
    poly = strtok(0, separator);
  }

  return result;
}

char *str_trim(char const *string) {
  long unsigned memory = sizeof(char *) * strlen(string);
  char *end, *result = malloc(memory);
  memcpy(result, string, memory);

  // Trim leading space
  while (isspace(*result)) {
    result++;
  }

  if (*result == 0) {
    return result;
  }

  // Trim trailing space
  end = result + strlen(result) - 1;
  while (end > result && isspace(*end)) {
    end--;
  }

  // Write new null terminator
  *(end + 1) = 0;

  return result;
}
