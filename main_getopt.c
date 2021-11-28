#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mapping.h"
#include "display.h"
#include "encoder.h"

void print_usage() {
    /* TODO */
    return;
}

void exit_usage_if(char *mask, char *message) {
    if (mask) {
        fprintf(stderr, "%s\n\n", message);
        print_usage();
        exit(2);
    }
}

int main(int argc, char *argv[]) {
    int c, i, width = TERM_WIDTH, format = FMT_TXT;
    char *decode_filename = NULL, *decode_message = NULL;
    char *encode_filename = NULL, *encode_message = NULL;
    char *key_filename = NULL, *key = NULL;
    char *print_filename = NULL, *print_encoded_message = NULL;
    char *op_mask = NULL, *key_mask = NULL;
    char *output_filename = NULL, *output_key_filename = NULL;
    char *result = NULL, *result_key = NULL;
    FILE *outfile = stdout, *key_outfile = NULL;
    while ((c = getopt(argc, argv, "d:D:e:E:hk:K:o:O:p:q:rRw:")) != -1) {
        switch (c) {
            case 'd':
                /* decode message in filename given by optarg */
                exit_usage_if(op_mask, "ERROR: cannot perform multiple operations in a single invocation");
                op_mask |= optarg;
                decode_filename = optarg;
                break;
            case 'D':
                /* decode message given by optarg */
                exit_usage_if(op_mask, "ERROR: cannot perform multiple operations in a single invocation");
                op_mask |= optarg;
                decode_message = optarg;
                break;
            case 'e':
                /* encode message in filename given by optarg */
                exit_usage_if(op_mask | key_mask, "ERROR: cannot perform multiple operations in a single invocation");
                op_mask |= optarg;
                key_mask |= optarg;
                encode_filename = optarg;
                break;
            case 'E':
                /* encode message given by optarg */
                exit_usage_if(op_mask | key_mask, "ERROR: cannot perform multiple operations in a single invocation");
                op_mask |= optarg;
                key_mask |= optarg;
                encode_message = optarg;
                break;
            case 'h':
                print_usage();
                exit(0);
            case 'k':
                /* decode or encode using the key in filename given by optarg */
                exit_usage_if(key_mask, "ERROR: cannot perform multiple operations in a single invocation");
                key_mask |= optarg;
                key_filename = optarg;
                break;
            case 'K':
                /* decode using the key given by optarg */
                exit_usage_if(key_mask, "ERROR: cannot perform multiple operations in a single invocation");
                key_mask |= optarg;
                key = optarg;
                break;
            case 'o':
                /* write output to the file given by optarg, rather than stdout */
                exit_usage_if(output_filename, "ERROR: cannot write output to more than one filename");
                output_filename = optarg;
                break;
            case 'O':
                /* write key to the file given by optarg, if encoding a message */
                /* TODO: add some proper error handling if used without encoding */
                output_key_filename = optarg;
                break;
            case 'p':
                /* print the contents of the plaintext file given by optarg in shadowfont */
                exit_usage_if(op_mask | key_mask, "ERROR: cannot perform multiple operations in a single invocation");
                op_mask |= optarg;
                key_mask |= optarg;
                print_filename = optarg;
                break;
            case 'q':
                /* print the contents of the encoded file given by optarg in shadowfont */
                exit_usage_if(op_mask, "ERROR: cannot perform multiple operations in a single invocation");
                op_mask |= optarg;
                break;
            case 'r':
                /* treat input and output files as raw bits, rather than human-readable chars */
                format = FMT_RAW;
                break;
            case 'R':
                /* default
                 * treat input and output files as human-readable chars, rather than raw bits */
                format = FMT_TXT;
                break;
            case 'w':
                width = atoi(optarg);
                break;
            default:
                fprintf(stderr, "ERROR: Unrecognized option `%c`\n\n", c);
                print_usage();
                exit(1);
        }
    }
    /* Valid combinations:
     * d + k
     * D + K
     * e + o + O
     * E + o + O
     * h
     * p
     * q + k
     * r
     * R
     * NOTHING implies print args in shadowfont
     */
    if (output_filename)
        outfile = fopen(output_filename, "w");
    else
        output_filename = "-";
    if (decode_filename) {
        exit_usage_if(!key_filename, "ERROR: key file required to decrypt file");
        decode_from_files(decode_filename, key_filename, format, output_filename);
    } else if (decode_message) {
        exit_usage_if(!key_message, "ERROR: key required to decrypt message");
        exit_usage_if(format == FMT_RAW, "ERROR: key required to decrypt message");
        result = decode_from_message(decode_message, key);
        fprintf(outfile, "%s\n", result);
    } else if (encode_filename) {
        exit_usage(outfile == stdout, "ERROR: cannot output raw bits to stdout");
        close(outfile);
        encode_from_file(encode_filename, format, output_filename, output_key_filename);
        outfile = stdout;
/* TODO: FINISH THIS
    } else if (encode_message) {
        encode_from_string(encode_message, format, output_filename, output_key_filename);
    } else if (print_filename) {
        if (output_filename)
        fprint_file(print_filename, TERM_WIDTH);
*/
    } else {
        for (i = optind; i < argc; i++) {
            print_string(strlen(argv[i]), argv[i], TERM_WIDTH);
        }
    }
    return 0;
}
