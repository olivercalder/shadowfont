#include <stdlib.h>
#include <string.h>
#include "mapping.h"
#include "display.h"
#include "encoder.h"

#define BUFSIZE 256
#define TERM_WIDTH 132

int main(int argc, char *argv[]) {
    char buf[BUFSIZE];
    FILE *infile;
    int len;

    /* Check that decoding "ABC" using a key works.
     * Start from the B to test the get_length_from_key_string() function.
     *
     * Encodings for A, B, and C:
     * A: "bdfghijlmo"
     * B: "abdfghjlmn"
     * C: "bcdgjno"
     */
    int input_length = 28;
    int key_length = input_length - 1;
    char *sample_encoded_ABC    = "abcbbdddgffgghhijljlmomjnnao";
                                /* BCCBAABCCBAABBAAAABBAABCCBBC */
    char *key                   = "010010010010101110101001010";
    int output_length = 3;
    int start_position = 1;
    int computed_output_length, computed_start_position;
    char *result;
    short *array = decode_using_string(
            input_length,
            output_length,
            start_position,
            sample_encoded_ABC,
            key);
    print_array(output_length, array, TERM_WIDTH);
    result = array_to_string(output_length, array);
    printf("%s\n", result);
    get_length_from_key_string(key_length, key, &computed_output_length, &computed_start_position);
    printf("Computed output length: %d\n", computed_output_length);
    printf("Computed start position: %d\n", computed_start_position);
    free(array);

    /* Print the given file using shadowfont. */
    if (argc > 1) {
        infile = fopen(argv[1], "r");
        while (fgets(buf, BUFSIZE, infile) != NULL) {
            len = strlen(buf);
            array = string_to_array(len, buf);
            print_array(len, array, TERM_WIDTH);
            free(array);
        }
    }
    return 0;
}
