/*
 * Oliver Calder
 * July 2021
 *
 * Mapping between 16-bit encodings and the corresponding ASCII letters.
 *
 * Supports capital letters, as well as some common symbols.
 *
 * Upper left cell is 0, lower right cell is 14, row major.
 * The bit position (rightmost 0, leftmost 14) corresponds to the cell index.
 *
 * A 1 in bit position 15 is a placeholder which does not correspond to any
 * pixel, and is necessary when encoding spaces.
 *
 * Thus, a pixel can be encoded using a single hexadecimal "digit";
 * that is, 0 is 0, a is 10, e is 14, etc.
 *
 * Alternatively, for better (or worse, depending on your familiarity with hex)
 * readability, a pixel can be encoded with a as 0, o as 14, etc.
 */

#ifndef __MAPPING_H
#define __MAPPING_H

#include "common.h"

char uint16_to_char(uint16_t bits);

uint16_t char_to_uint16(char c);

uint16_t char_to_bit_hex(char c);

uint16_t char_to_bit_lower(char c);

uint16_t char_to_bit_upper(char c);

uint16_t char_to_bit(format_t format, char c);

/* Returns the position of the leftmost bit, where no bits is treated as 15 */
int index_of_bit(uint16_t bit);

char bit_to_char_hex(uint16_t bit);

char bit_to_char_lower(uint16_t bit);

char bit_to_char_upper(uint16_t bit);

char bit_to_char(format_t format, uint16_t bit);

uint16_t *string_to_array(int length, char *str);

char *array_to_string(int length, uint16_t *array);

uint16_t *string_to_bits_hex(int length, char *string);

uint16_t *string_to_bits_lower(int length, char *string);

uint16_t *string_to_bits_upper(int length, char *string);

uint16_t *string_to_bits(format_t format, int length, char *string);

char *bits_to_string_hex(int length, uint16_t *bits);

char *bits_to_string_lower(int length, uint16_t *bits);

char *bits_to_string_upper(int length, uint16_t *bits);

char *bits_to_string(format_t format, int length, uint16_t *bits);

#endif
