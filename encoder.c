#include <stdlib.h>
#include "common.h"
#include "encoder.h"
#include "mapping.h"

int count_bits(uint16_t bits) {
    int ones = 0;
    while (bits) {
        bits &= (bits - 1);
        ones++;
    }
    return ones;
}

int find_max_pixels_from_string(int length, char *string) {
    int i, max = 0;
    for (i = 0; i < length; i++)
        max = max_int(max, count_bits(char_to_uint16(string[i])));
    return max;
}

int find_max_pixels_from_array(int length, uint16_t *array) {
    int i, max = 0;
    for (i = 0; i < length; i++)
        max = max_int(max, count_bits(array[i]));
    return max;
}

void get_length_from_key_array(int key_length, uint8_t *key, int *output_length, int *start_position) {
    /* Assumes the key contains only 0s and 1s; performs "fold" if 1 */
    int i, direction = 1, max = 0, min = 0, current = 0;
    for (i = 0; i < key_length; i++) {
        current += (key[i] - 1) & direction;
        max = max_int(max, current);
        min = min_int(min, current);
        direction = ((-key[i]) ^ direction) | 1;
    }
    *output_length = max - min + 1;
    *start_position = -min;
    return;
}

void get_length_from_key_string(int key_length, char *key, int *output_length, int *start_position) {
    /* Assumes the key contains only '0's and '1's; performs "fold" if '1' */
    int i;
    uint8_t *key_arr = malloc(sizeof(uint8_t) * key_length);
    for (i = 0; i < key_length; i++) {
        key_arr[i] = key[i] - '0';
    }
    get_length_from_key_array(key_length, key_arr, output_length, start_position);
    free(key_arr);
    return;
}

/* If direction is -1, mirrors bits about the middle column of a 3-column
 * array of pixels representing a character.  Thus, pixels in the 0 mod 3
 * column flip with those in the 2 mod 3 column.
 * The given direction must be either 1 or -1 */
uint16_t mirror_bits(uint16_t bits, int direction) {
    return ((((bits) & 011111) << (1 - (direction))) | ((bits) & 0122222) | (((bits) & 044444) >> (1 - (direction))));
}

uint16_t get_bit_from_char_hex(char c, int direction) {
    char buf[2] = {c, '\0'};
    return mirror_bits(1 << (strtoul(buf, NULL, 16)), direction);
}

uint16_t get_bit_from_char_lower(char c, int direction) {
    return mirror_bits(1 << (c - 'a'), direction);
}

uint16_t get_bit_from_char_upper(char c, int direction) {
    return mirror_bits(1 << (c - 'A'), direction);
}

uint16_t get_bit_from_char(int format, char c, int direction) {
    switch (format) {
        case FMT_TXT_HEX:
            return get_bit_from_char_hex(c, direction);
        case FMT_TXT_LOWER:
            return get_bit_from_char_lower(c, direction);
        case FMT_TXT_UPPER:
            return get_bit_from_char_upper(c, direction);
        default:
            return ~0;
    }
}

uint16_t *decode_string(int format, int input_length, char *encoded_message, char *key) {
    /* Assumes the key contains only '0's and '1's; performs "fold" if '1' */
    int i, position, output_length, direction = 1;
    uint16_t *array;
    uint16_t (*bit_fn)(char, int);
    switch (format) {
        case FMT_TXT_HEX:
            bit_fn = get_bit_from_char_hex;
            break;
        case FMT_TXT_LOWER:
            bit_fn = get_bit_from_char_lower;
            break;
        case FMT_TXT_UPPER:
            bit_fn = get_bit_from_char_upper;
            break;
        default:
            return (uint16_t *)-1;  /* should probably throw a more informative error */
    }
    get_length_from_key_string(input_length - 1, key, &output_length, &position);
    array = malloc(sizeof(uint16_t) * output_length);
    for (i = 0; i < output_length; i++)
        array[i] = 0;
    for (i = 0; i < input_length; i++) {
        array[position] |= bit_fn(encoded_message[i], direction);
        position += (key[i] - '1') & direction;
        direction = (('0' - key[i]) ^ direction) | 1;
    }
    return array;
}

uint16_t *decode_uint(int input_length, uint16_t *encoded_message, uint8_t *key) {
    int i, position, output_length, direction = 1;
    uint16_t *array;
    get_length_from_key_array(input_length - 1, key, &output_length, &position);
    array = malloc(sizeof(uint16_t) * output_length);
    for (i = 0; i < output_length; i++)
        array[i] = 0;
    for (i = 0; i < input_length; i++) {
        array[position] |= mirror_bits(encoded_message[i], direction);
        position += (key[i] - 1) & direction;
        direction = ((0 - key[i]) ^ direction) | 1;
    }
    return array;
}

/* Encrypts the given string into shadowfont, storing the pixel mappings and the
 * decryption key in a struct encoded_t.  The message and key are both
 * uncompressed, ready to be displayed or compressed and written to files.
 *
 * The encryption scheme used is to complete each character before moving on to
 * the next.  Thus, there is an empty pixel for any character which requires an
 * even number of pixels (including space characters), and there is a flip after
 * every pixel except those which are the final pixel for a given character. */
struct encoded_t encode_simple(int length, char *message) {
    struct encoded_t ret;
    uint16_t *source, *array,  tmp, tmp2;
    uint8_t *key;
    int i, j, direction, tmp_length, total_length = 0;
    source = string_to_array(length, message);
    for (i = 0; i < length; i++) {
        tmp = source[i];
        tmp_length = 0;
        while (tmp) {
            tmp_length++;
            tmp = (tmp & (tmp - 1));
        }
        tmp_length |= 1;
        total_length += tmp_length;
    }
    array = malloc(sizeof(uint16_t) * total_length);
    key = malloc(sizeof(uint8_t) * (total_length));
    ret.message = array;
    ret.key = key;
    ret.length = total_length;
    j = 0;
    for (i = 0; i < length; i++) {
        tmp = source[i];
        tmp_length = 0;
        direction = 1;  /* direction will only be correct in first while loop */
        while (tmp) {
            tmp2 = tmp;
            tmp = tmp & (tmp - 1);
            array[j] = mirror_bits(tmp ^ tmp2, direction);
            key[j] = 1;
            direction = (~direction) | 1;
            j++;
            tmp_length++;
        }
        if (!(tmp_length & 1)) {   /* handles both even-pixeled chars and spaces */
            array[j] = 0100000;
            j++;
        }
        key[j - 1] = 0;
    }
    return ret;
}

struct encoded_t encode_fewest_folds(int length, char *message) {
    struct encoded_t ret;
    ret.length = 0;
    ret.message = NULL;
    ret.key = NULL;
    return ret;
    /* TODO */
}
