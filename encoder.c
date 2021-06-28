#include <stdlib.h>
#include "common.h"
#include "mapping.h"

int count_bits(short bits) {
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
        max = max_int(max, count_bits(char_to_short(string[i])));
    return max;
}

int find_max_pixels_from_array(int length, short *array) {
    int i, max = 0;
    for (i = 0; i < length; i++)
        max = max_int(max, count_bits(array[i]));
    return max;
}

void get_length_from_key_string(int key_length, char *key, int *output_length, int *start_position) {
    /* Assumes the key contains only '0's and '1's; performs "fold" if '1'. */
    int i, direction = 1, max = 0, min = 0, current = 0;
    for (i = 0; i < key_length; i++) {
        current += (key[i] - '1') & direction;
        max = max_int(max, current);
        min = min_int(min, current);
        direction = (('0' - key[i]) ^ direction) | 1;
    }
    *output_length = max - min + 1;
    *start_position = -min;
    return;
}

#define BIT_OF_CHAR(c) (1 << ((c) - 'a'))

short *decode_using_string(int input_length, int output_length, int start_position, char *encoded_message, char *key) {
    /* Assumes the key contains only '0's and '1's; performs "fold" if '1' */
    int i, position, direction = 1;
    short *array;
    array = malloc(sizeof(short) * output_length);
    position = start_position;
    for (i = 0; i < input_length; i++) {
        array[position] |= BIT_OF_CHAR(encoded_message[i]);
        position += (key[i] - '1') & direction;
        direction = (('0' - key[i]) ^ direction) | 1;
    }
    return array;
}
