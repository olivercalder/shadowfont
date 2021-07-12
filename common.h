#ifndef __COMMON_H
#define __COMMON_H

#define TERM_WIDTH      132
#define FALLBACK_WIDTH  16536
#define FONT_WIDTH      4
#define BUFSIZE         (TERM_WIDTH / FONT_WIDTH)

typedef enum {
    FMT_TXT,
    FMT_UINT,
    FMT_TXT_HEX,
    FMT_TXT_LOWER,
    FMT_TXT_UPPER,
    FMT_BIN,
} format_t;

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef unsigned long   long uint64_t;

int min_int(int a, int b);

int max_int(int a, int b);

#endif
