#include <stdlib.h>
#include <string.h>
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
    int i, input_length = 28;
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
    struct encoded_t auto_encoded;
    uint16_t *array;

    get_length_from_key_string(key_length, key, &computed_output_length, &computed_start_position);
    printf("Computed output length: %d", computed_output_length);
    printf("\t%s\n", computed_output_length == output_length ? "OK" : "ERROR");
    printf("Computed start position: %d", computed_start_position);
    printf("\t%s\n", computed_start_position == start_position ? "OK" : "ERROR");

    array = decode_string(FMT_TXT_LOWER, input_length, sample_encoded_ABC, key);
    print_array(output_length, array, TERM_WIDTH);
    result = array_to_string(output_length, array);
    free(array);
    printf("Result: %s", result);
    printf("\t%s\n", !strcmp(result, "ABC") ? "OK" : "ERROR");
    free(result);

    printf("\nCalling encode_simple(3, \"ABC\")...\n");
    auto_encoded = encode_simple(3, "ABC");
    printf("Used %d uint16_t entries.\n", auto_encoded.length);
    printf("Encoded string: ");
    for (i = 0; i < auto_encoded.length; i++)
        printf("%c", bit_to_char_lower(auto_encoded.message[i]));
    printf("\nDecryption key: ");
    for (i = 0; i < auto_encoded.length - 1; i++)
        printf("%c", '0' + auto_encoded.key[i]);

    get_length_from_key_array(auto_encoded.length - 1, auto_encoded.key, &computed_output_length, &computed_start_position);
    printf("\nComputed output length: %d", computed_output_length);
    printf("\t%s\n", computed_output_length == strlen("ABC") ? "OK" : "ERROR");
    printf("Computed start position: %d", computed_start_position);
    printf("\t%s\n", computed_start_position == 0 ? "OK" : "ERROR");

    printf("Decrypting message using key...\n");
    array = decode_uint(auto_encoded.length, auto_encoded.message, auto_encoded.key);
    free(auto_encoded.message);
    free(auto_encoded.key);
    print_array(computed_output_length, array, TERM_WIDTH);
    result = array_to_string(computed_output_length, array);
    free(array);
    printf("Result: %s", result);
    printf("\t%s\n", !strcmp(result, "ABC") ? "OK" : "ERROR");
    free(result);

    return 0;
}
