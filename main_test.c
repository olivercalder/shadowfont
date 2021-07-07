#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "common.h"
#include "mapping.h"
#include "display.h"
#include "encoder.h"

int main(int argc, char *argv[]) {
    /* Check that decoding "ABC" using a key works.
     * Start from the B to test the get_length_from_key_string() function.
     *
     * Encodings for A, B, and C:
     * A: "bdfghijlmo"
     * B: "abdfghjlmn"
     * C: "bcdgjno"
     *
     * Remember that pixel columns are flipped after an odd number of folds
     */
    int input_length = 28;
    int key_length = input_length - 1;
                        /* flipped 0011100011100110100110001100
                            orig: "abcbbdddgffgghhijljlmomjnnao" */
    char *sample_encoded_ABC    = "ababbdddiddgghhilljjoomjnnao";
                                /* BCCBAABCCBAABBAAAABBAABCCBBC */
    char *key                   = "010010010010101110101001010";
    int output_length = 3;
    int start_position = 1;
    int computed_output_length, computed_start_position;
    char *result;
    uint16_t *array = decode_using_string(
            input_length,
            output_length,
            start_position,
            sample_encoded_ABC,
            key);
    print_array(output_length, array, TERM_WIDTH);
    result = array_to_string(output_length, array);
    free(array);
    printf("Result: %s", result);
    printf("\t%s\n", !strcmp(result, "ABC") ? "OK" : "ERROR");
    free(result);
    get_length_from_key_string(key_length, key, &computed_output_length, &computed_start_position);
    printf("Computed output length: %d", computed_output_length);
    printf("\t%s\n", computed_output_length == output_length ? "OK" : "ERROR");
    printf("Computed start position: %d", computed_start_position);
    printf("\t%s\n", computed_start_position == start_position ? "OK" : "ERROR");

    return 0;
}
