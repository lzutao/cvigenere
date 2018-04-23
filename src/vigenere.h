/**
 * Program: vigenere.h
 * Function: encode and decode a vigenere string with given key
 * Supported charset: [a-z]
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> // getopt()
#include <stdarg.h> // va_start

/**
 * Function: encode a string to vigenere string
 * @key    : array of shifted value to int.
 *           Example: bacon to {1, 0, 2, 14, 13}
 * @source : [a-zA-Z]
 * @result : a returned string with len >= source string
 */
extern int
vigenereEncode(char *result, char const *source, char const *shiftarray, size_t shift_size);

/**
 * Function: encode a string to vigenere string
 * @key    : array of shifted value to int.
 *           Example: bacon to {1, 0, 2, 14, 13}
 * @source : [a-zA-Z]
 * @result : a returned string with len >= source string
 */
extern int
vigenereDecode(char *result, char const *source, char const *shiftarray, size_t shift_size);

/**
 * Function: shift shift_th a token char
 * return: shifted character
 ****************************************
 * Usage: char ch = caesarEncode('a', 2);
 */
extern char
caesarEncode(char token, char shift);

/**
 * Function: extend modular function to signed number
 * return: modular of dividend and divisor
 ****************************************************
 * Usage: int modular = mod(9, -7);
 * Note: Rename from mod to pmod because of error when gcc compiles
 */
int
pmod( int dividend, int divisor );
