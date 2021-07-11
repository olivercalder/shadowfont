#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "display.h"
#include "mapping.h"

void fprint_array(FILE *fd, int length, uint16_t *array, int width) {
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
                    fprintf(fd, "%c", filled * '#' + !filled * ' ');
                }
                fprintf(fd, " ");
            }
            fprintf(fd, "\n");
        }
        fprintf(fd, "\n");
    }
}

void print_array(int length, uint16_t *array, int width) {
    fprint_array(stdout, length, array, width);
}

void fprint_string(FILE *fd, int length, char *string, int width) {
    uint16_t *array = malloc(sizeof(uint16_t) * length);
    if (width < 0)
        width = FALLBACK_WIDTH;
    array = string_to_array(length, string);
    print_array(length, array, width);
    free(array);
}

void print_string(int length, char *string, int width) {
    fprint_string(stdout, length, string, width);
}

void fprint_file(FILE *fd, char *filename, int width) {
    FILE *infile;
    char *buf;
    int bufsize;
    if (width < 0)
        width = FALLBACK_WIDTH;
    bufsize = sizeof(char) * width / FONT_WIDTH;
    buf = malloc(bufsize);
    infile = fopen(filename, "r");
    while (fgets(buf, bufsize, infile) != NULL)
        fprint_string(fd, strlen(buf), buf, width);
    fclose(infile);
}

void print_file(char *filename, int width) {
    fprint_file(stdout, filename, width);
}
