#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdio.h>
#include "common.h"

void fprint_array(FILE *outfile, int length, uint16_t *array, int width);

void print_array(int length, uint16_t *array, int width);

void fprint_string(FILE *outfile, int length, char *string, int width);

void print_string(int length, char *string, int width);

void fdisplay_string(FILE *outfile, format_t format, int length, char *string, int width);

void display_string(format_t format, int length, char *string, int width);

void fprint_file(FILE *outfile, FILE *infile, int width);

void print_file(FILE *infile, int width);

void fprint_filename(FILE *outfile, char *filename, int width);

void print_filename(char *filename, int width);

void fdisplay_file(FILE *outfile, format_t format, FILE *infile, int width);

void display_file(format_t format, FILE *infile, int width);

void fdisplay_filename(FILE *outfile, format_t format, char *filename, int width);

void display_filename(format_t format, char *filename, int width);

#endif
