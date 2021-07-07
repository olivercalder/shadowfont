#ifndef __ENCODER_H
#define __ENCODER_H

#include <stdint.h>

struct encoded_t {
    uint16_t *message;
    uint8_t *key;
    int length;
};

int find_max_pixels_from_string(int length, char *string);

int find_max_pixels_from_array(int length, uint16_t *array);

void get_length_from_key_string(int key_length, char *key, int *output_length, int *start_position);

uint16_t *decode_using_string(int input_length, int output_length, int start_position, char *encoded_message, char *key);

struct encoded_t encode_shortest(int length, char *message);

struct encoded_t encode_fewest_folds(int length, char *message);

#endif
