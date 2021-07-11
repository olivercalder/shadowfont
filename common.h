#ifndef __COMMON_H
#define __COMMON_H

#define TERM_WIDTH      132
#define FALLBACK_WIDTH  16536
#define FONT_WIDTH      4
#define BUFSIZE         (TERM_WIDTH / FONT_WIDTH)

#define FMT_RAW         0
#define FMT_UINT        1
#define FMT_TXT_HEX     2
#define FMT_TXT_LOWER   3
#define FMT_TXT_UPPER   4

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;
typedef unsigned long   long uint64_t;

int min_int(int a, int b);

int max_int(int a, int b);

#endif
