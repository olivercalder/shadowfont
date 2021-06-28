#ifndef __ENCODER_H
#define __ENCODER_H

int find_max_pixels_from_string(int length, char *string);

int find_max_pixels_from_array(int length, short *array);

void get_length_from_key_string(int key_length, char *key, int *output_length, int *start_position);

short *decode_using_string(int input_length, int output_length, int start_position, char *encoded_message, char *key);

#endif
