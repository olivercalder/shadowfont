#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "display.h"
#include "mapping.h"

void fprint_array(FILE *outfile, int length, uint16_t *array, int width) {
    int char_index = 0, pixel_row, pixel_col, filled, row_start, row_end, char_limit;
    if (width < 0)
        width = FALLBACK_WIDTH;
    char_limit = width / 4;
    if (char_limit < 1)
        char_limit = length;
    while (char_index < length) {
        /* new row */
        row_start = char_index;
        row_end = min_int(length, char_index + char_limit);
        for (pixel_row = 0; pixel_row < 5; pixel_row++) {
            for (char_index = row_start; char_index < row_end; char_index++) {
                for (pixel_col = 0; pixel_col < 3; pixel_col++) {
                    filled = (array[char_index] >> ((pixel_row * 3) + pixel_col)) & 1;
                    fprintf(outfile, "%c", filled * '#' + !filled * ' ');
                }
                fprintf(outfile, " ");
            }
            fprintf(outfile, "\n");
        }
        fprintf(outfile, "\n");
    }
}

void print_array(int length, uint16_t *array, int width) {
    fprint_array(stdout, length, array, width);
}

void fprint_string(FILE *outfile, int length, char *string, int width) {
    uint16_t *array;
    array = string_to_array(length, string);
    print_array(length, array, width);
    free(array);
}

void print_string(int length, char *string, int width) {
    fprint_string(stdout, length, string, width);
}

void fdisplay_string(FILE *outfile, format_t format, int length, char *string, int width) {
    uint16_t *array;
    array = string_to_bits(format, length, string);
    print_array(length, array, width);
    free(array);
}

void display_string(format_t format, int length, char *string, int width) {
    fdisplay_string(stdout, format, length, string, width);
}

void fprint_file(FILE *outfile, FILE *infile, int width) {
    char *buf;
    int bufsize;
    if (width < 0)
        width = FALLBACK_WIDTH;
    bufsize = sizeof(char) * width / FONT_WIDTH;
    buf = malloc(bufsize);
    while (fgets(buf, bufsize, infile) != NULL)
        fprint_string(outfile, strlen(buf), buf, width);
    free(buf);
}

void print_file(FILE *infile, int width) {
    fprint_file(stdout, infile, width);
}

void fprint_filename(FILE *outfile, char *filename, int width) {
    FILE *infile;
    infile = fopen(filename, "r");
    fprint_file(outfile, infile, width);
    fclose(infile);
}

void print_filename(char *filename, int width) {
    fprint_filename(stdout, filename, width);
}

void fdisplay_file(FILE *outfile, format_t format, FILE *infile, int width) {
    char *buf;
    int bufsize;
    if (width < 0)
        width = FALLBACK_WIDTH;
    bufsize = sizeof(char) * width / FONT_WIDTH;
    buf = malloc(bufsize);
    while (fgets(buf, bufsize, infile) != NULL)
        fdisplay_string(outfile, format, strlen(buf), buf, width);
    free(buf);
}

void display_file(format_t format, FILE *infile, int width) {
    fdisplay_file(stdout, format, infile, width);
}

void fdisplay_filename(FILE *outfile, format_t format, char *filename, int width) {
    FILE *infile;
    infile = fopen(filename, "r");
    fdisplay_file(outfile, format, infile, width);
    fclose(infile);
}

void display_filename(format_t format, char *filename, int width) {
    fdisplay_filename(stdout, format, filename, width);
}
