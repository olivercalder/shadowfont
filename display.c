#include <stdio.h>
#include "common.h"

void fprint_array(FILE *fd, int length, short *array, int width) {
    int char_index = 0, pixel_row, pixel_col, filled, row_start, row_end, char_limit = width / 4;
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

void print_array(int length, short *array, int width) {
    fprint_array(stdout, length, array, width);
}
