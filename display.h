#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdio.h>
#include "common.h"

void fprint_array(FILE *fd, int length, uint16_t *array, int width);

void print_array(int length, uint16_t *array, int width);

void fprint_string(FILE *fd, int length, char *string, int width);

void print_string(int length, char *string, int width);

void fprint_file(FILE *fd, char *filename, int width);

void print_file(char *filename, int width);

#endif
