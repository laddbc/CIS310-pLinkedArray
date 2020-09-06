#include <cstdlib>
#include <unistd.h>
#include "util.h"

// Is the input redirected?
bool isInputRedirected() {
  return !isatty(STDIN_FILENO);
}

// Return pointer to first character NOT matching ch OR pointing at '\0'.
char *unMatch(char *str, char ch) {
  while (*str == ch && *str != '\0')
    str++;
  return str;
}

// Return pointer to first character matching ch OR pointing at '\0'.
char *match(char *str, char ch) {
  while (*str != ch && *str != '\0')
    str++;
  return str;
}
