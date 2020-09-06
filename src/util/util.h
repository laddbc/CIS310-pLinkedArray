#ifndef UTIL_H
#define UTIL_H

/**
 * Is the input redirected?
 *
 * @return true if input is redirected.
 */
bool isInputRedirected();

/**
 * Return pointer to first character NOT matching ch OR pointing at '\0'.
 *
 * @param str string to search; cannot be NULL!
 * @param ch character to unmatch
 */
char * unMatch(char * str, char ch);

/**
 * Return pointer to first character matching ch OR pointing at '\0'.
 *
 * @param str string to search; cannot be NULL!
 * @param ch character to match
 */
char * match(char * str, char ch);

#endif /* UTIL_H */
