#ifndef __COMMON_H
#define __COMMON_H

#define TERM_WIDTH      132
#define FALLBACK_WIDTH  16536
#define FONT_WIDTH      4
#define BUFSIZE         (TERM_WIDTH / FONT_WIDTH)

#define FMT_TXT         0
#define FMT_RAW         1

int min_int(int a, int b);

int max_int(int a, int b);

#endif
