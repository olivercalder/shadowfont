/*
 * Oliver Calder
 * June 2021
 *
 * Mapping between 16-bit encodings and the corresponding ASCII letters.
 *
 * Supports capital letters, as well as some common symbols.
 *
 * Upper left cell is 0, lower right cell is 14, row major.
 * The bit position (rightmost 0, leftmost 14) of the corresponds to the cell index.
 *
 * Thus, a pixel can be encoded using a single hexadecimal "digit";
 * that is, 0 is 0, a is 10, e is 14, etc.
 *
 * Alternatively, for better (or worse, depending on your familiarity with hex)
 * readability, a pixel can be encoded with a as 0, o as 14, etc.
 */

#ifndef __MAPPING_H
#define __MAPPING_H

char short_to_char(short bits);

short char_to_short(char c);

char *array_to_string(int length, short *array);

short *string_to_array(int length, char *str);

#endif
