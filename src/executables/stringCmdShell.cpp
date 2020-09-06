#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "util.h"
/**
 *
 *
 * @author <jimmy_q_programmer>
 * @email jimmy@potsdam.edu
 */


// Define a type for easy replacement
typedef char * LString;
// Program CONSTANTS
const int MAX_STRING_COUNT = 10;

// Function forward declarations
/**
 * Is the given LString index valid?
 *
 * @param ndx index to check for validity
 * @return true if in safe index range; false otherwise
 */
bool isValidStringNdx(int ndx);

/**
 * Generate and print the promt.
 *
 * @param strings array of strings; promt includes indices
 * of non-empty strings so that list is checked here
 * @note Should generate and return the prompt string;
 * a function should have exactly ONE concern.
 */
void prompt(LString strings[MAX_STRING_COUNT]);

/**
 * Read one command parameter startinng at start.
 * The parameter is the next non-blank character.
 *
 * @param start pointer into null-terminated string to
 * find command parameter in.
 * @param first REFERENCE to char pointer; will point to
 * parameter, if one is found.
 * @return true with first set if non-blank found at or
 * after start; false with first left unchanged otherwise.
 */
bool readOneMore(char * start, char * & first);

/**
 * Read two command parameter startinng at start.
 * The parameter is the next non-blank character;
 * second parameter can be an escaped character.
 *
 * @param start pointer into null-terminated string to
 * find command parameter in.
 * @param first REFERENCE to char pointer; will point to
 * first parameter, if one is found.
 * @param second REFERENCE to char pointer; will point to
 * second parameter, if one is found.
 * @return true with first set if non-blank found at or
 * after start; false with first left unchanged otherwise.
 */
bool readTwoMore(char * start, char * & first, char * & second);

/**
 * Get pointer at next non-blank character UNLESS that
 * character is '\'. In that case, return pointer at the
 * character AFTER the slash (does not translate \n, etc.).
 *
 * @param start pointer at beginning of string to search
 * @return pointer at '\0', character after '\',
 * or next non-blank, whichever is found first.
 */
char * nextCharMaybeEscaped(char * start);

/**
 * Show help text
 * FIXME !
 */
void generalHelp();
/**
 * Show specific help text.
 * FIXME !
 *
 * @param cmdForHelp the command character to provide help on.
 */
void help(char cmdForHelp);

// =========== LString Provider must rewrite these functions ==========
/**
 * Initialize the given LString, however that is done.
 *
 * @parm REFERENCE to an LString that must be initialized
 */
void init(LString & str);

/**
 * Is the LString empty?
 *
 * @param the LString to check for emptiness.
 */
bool isEmpty(LString str);

/**
 * The main function.
 *
 * @param argc - # of command-line arguments
 * @param argv - array of command-line arguments
 * @return 0 on termination
 */
int main(int argc, char *argv[]) {
  LString theStrings[MAX_STRING_COUNT];
  for (int n = 0; n < MAX_STRING_COUNT; ++n)
    init(theStrings[n]);

  bool done = false;
  while (!done) {
    // Input line from the user
    char line[80];

    // prompt and read line
    prompt(theStrings);
    done = (fgets(line, 80, stdin) == NULL);

    if (done)
      continue;

    // echo input if input is redirected from a file
    if (isInputRedirected())
      printf("%s", line);

    line[strlen(line) - 1] = '\0'; // chop EOLN with NULL (make line shorter)
    char * cmdChar = unMatch(line, ' ');
    if (*cmdChar == '\0')
      continue; // line contains only spaces

    if (*cmdChar == 'q') {
      done = true;
    } else if (*cmdChar == 'a') {
      char * list;
      char * ch;
      if (!readTwoMore(cmdChar + 1, list, ch)) {
        // FIXME error messagee
        continue;
      }
      int ndx = *list - '0';
      if (!isValidStringNdx(ndx)) {
        // FIXME error message
        continue;
      }
      printf("%c %c %c - Command not implemented.\n", *cmdChar, *list, *ch);
    } else if (*cmdChar == 'r') {
      char * list;
      char * ch;
      if (!readTwoMore(cmdChar + 1, list, ch)) {
        // FIXME error messagee
        continue;
      }
      int ndx = *list - '0';
      if (!isValidStringNdx(ndx)) {
        // FIXME error message
        continue;
      }
      printf("%c %c %c - Command not implemented.\n", *cmdChar, *list, *ch);
    } else if (*cmdChar == 'e') {
      char * list;
      if (!readOneMore(cmdChar + 1, list)) {
        // FIXME error messagee
        continue;
      }
      int ndx = *list - '0';
      if (!isValidStringNdx(ndx)) {
        // FIXME error message
        continue;
      }
      printf("%c %c - Command not implemented.\n", *cmdChar, *list);
    } else if (*cmdChar == 'c') {
      char * listA;
      char * listB;
      if (!readTwoMore(cmdChar + 1, listA, listB)) {
        // FIXME error messagee
        continue;
      }
      int ndxA = *listA - '0';
      if (!isValidStringNdx(ndxA)) {
        // FIXME error message
        continue;
      }
      int ndxB = *listB - '0';
      if (!isValidStringNdx(ndxB)) {
        // FIXME error message
        continue;
      }
      printf("%c %c %c - Command not implemented.\n", *cmdChar, *listA, *listB);
    } else if (*cmdChar == 'l') {
      printf("%c - Command not implemented.\n", *cmdChar);
    } else if (*cmdChar == 'f') {
      printf("%c - Command not implemented.\n", *cmdChar);
    } else if (*cmdChar == 'h') {
      char * aboutChar = unMatch(cmdChar+1, ' ');
      if (*aboutChar == '\0' ) {
        generalHelp();
      } else {
        help(*aboutChar);
      }
    } else {
      printf("Unrecognized command character, \"%c\". \"h\" for help.\n", *cmdChar);
    }
  }
}

// ----- LString Provider Update! -----
// initialize an LString
void init(LString & str) {
  str = NULL;
}

// check whether LString is empty
bool isEmpty(LString str) {
  return str == nullptr;
}

// ----- Help Functions (FIXME) -----
// display general help
void generalHelp() {
  printf("<<< HELP TEXT >>>\n");
}

// display command-specific help (or error message)
void help(char cmdForHelp) {
  printf("<<< SPECIALIZED HELP TEXT (%c) >>>\n", cmdForHelp);
}

// ----- Utility Functions -----
// is ndx valid string index?
bool isValidStringNdx(int ndx) {
  return (0 <= ndx) && (ndx < MAX_STRING_COUNT);
}

// generate and display a prompt w/ list of non-empty LString
void prompt(LString strings[MAX_STRING_COUNT]) {
  printf("Non-empty Lists :: ");
  bool anyNonEmpty = false;
  for (int i = 0; i < MAX_STRING_COUNT; ++i) {
    if (!isEmpty(strings[i])) {
      printf("%d", i);
      anyNonEmpty = true;
    }
  }
  if (anyNonEmpty)
    printf(" ");

  printf(":: cmd? ");
}

// ----- I/O Routines -----
// read a possibly escaped space or other char. NOT \n,\r,\t, etc.
char * nextCharMaybeEscaped(char * start) {
  char * ch = unMatch(start, ' ');
  if (*ch == '\\')
    ch++;
  return ch;
}

// could we read (and store) one more character parameter?
bool readOneMore(char * start, char * & first) {
  first = unMatch(start, ' ');
  return *first;
}

// could we read (and store) two more character parameters? Second might be escaped.
bool readTwoMore(char * start, char * & first, char * & second) {
  first = unMatch(start, ' ');
  if (*first != '\0')
    second = nextCharMaybeEscaped(first+1);
  return *first && *second;
}
