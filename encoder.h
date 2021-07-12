#ifndef __ENCODER_H
#define __ENCODER_H

#include "common.h"

struct encoded_t {
    uint16_t *message;
    uint8_t *key;
    int length;
};

int find_max_pixels_from_string(int length, char *string);

int find_max_pixels_from_array(int length, uint16_t *array);

void get_length_from_key_array(int key_length, uint8_t *key, int *output_length, int *start_position);

void get_length_from_key_string(int key_length, char *key, int *output_length, int *start_position);

uint16_t mirror_bits(uint16_t bits, int direction);

uint16_t get_bit_from_char_hex(char c, int direction);

uint16_t get_bit_from_char_lower(char c, int direction);

uint16_t get_bit_from_char_upper(char c, int direction);

uint16_t get_bit_from_char(format_t format, char c, int direction);

uint16_t *decode_string(format_t format, int input_length, char *encoded_message, char *key);

uint16_t *decode_uint(int input_length, uint16_t *encoded_message, uint8_t *key);

struct encoded_t encode_simple(int length, char *message);

struct encoded_t encode_fewest_folds(int length, char *message);

#endif
