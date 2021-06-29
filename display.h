#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdio.h>

void fprint_array(FILE *fd, int length, short *array, int width);

void print_array(int length, short *array, int width);

void fprint_string(FILE *fd, int length, char *string, int width);

void print_string(int length, char *string, int width);

void fprint_file(FILE *fd, char *filename, int width);

void print_file(char *filename, int width);

#endif
