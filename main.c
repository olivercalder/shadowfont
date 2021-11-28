#include <string.h>
#include "common.h"
#include "mapping.h"
#include "encoder.h"
#include "display.h"

const char *USAGE = "usage: %s <command> [<args>]\n"
                    "\n"
                    "Available commands:\n"
                    "\n"
                    "    display <format> <filename> [<filename> ...]\n"
                    "        <format> is the format of the input file, and must be one of the following:\n"
                    "            txt     treat as plaintext -- all other options treat as encoded text\n"
                    "            hex\n"
                    "            lower\n"
                    "            upper\n"
                    "            bin     both message and key stored as bits, otherwise key is '0's and '1's\n"
                    "        if <filename> is '-', reads from stdin\n"
                    "\n"
                    "    encode <format> <infile> <messagefile> [<keyfile>]\n"
                    "        <format> is the format of the encoded message file, and must be one of the following:\n"
                    "            hex\n"
                    "            lower\n"
                    "            upper\n"
                    "            bin     both message and key stored as bits, otherwise key is '0's and '1's\n"
                    "        if <infile> is '-', reads from stdin\n"
                    "        if <keyfile> is not given, defaults to <messagefile>.key\n"
                    "\n"
                    "    decode <format> <messagefile> <keyfile> [<outfile>]\n"
                    "        <format> is the format of the encoded message file, and must be one of the following:\n"
                    "            hex\n"
                    "            lower\n"
                    "            upper\n"
                    "            bin     both message and key stored as bits, otherwise key is '0's and '1's\n"
                    "        if <outfile> is not given, writes to stdout\n"
                    "\n"
                    "    print [<text> ...]\n"
                    "        if no <text> given, reads from stdin\n"
                    "\n";

void print_usage(char *argv[]) {
    fprintf(stderr, USAGE, argv[0]);
}

int get_format(char *fmt_str) {
    if (!strcmp(fmt_str, "txt")) {
        return FMT_TXT;
    } else if (!strcmp(fmt_str, "hex")) {
        return FMT_TXT_HEX;
    } else if (!strcmp(fmt_str, "lower")) {
        return FMT_TXT_LOWER;
    } else if (!strcmp(fmt_str, "upper")) {
        return FMT_TXT_UPPER;
    } else if (!strcmp(fmt_str, "bin")) {
        return FMT_BIN;
    }
    return -1;
}

int main_display(int argc, char *argv[]) {
    int i, format;
    if (argc <= 2) {
        fprintf(stderr, "ERROR: %s %s\t -- missing required arguments <format> and <filename>\n\n", argv[0], argv[1]);
        return 1;
    } else if (argc == 3) {
        fprintf(stderr, "ERROR: %s %s %s\t -- missing required argument <filename>\n\n", argv[0], argv[1], argv[2]);
        return 1;
    }
    format = get_format(argv[2]);
    switch (format) {
        case FMT_TXT:
            for (i = 3; i < argc; i++)
                print_filename(argv[i], TERM_WIDTH);
            return 0;
        case FMT_TXT_HEX:
        case FMT_TXT_LOWER:
        case FMT_TXT_UPPER:
            break;
        case FMT_BIN:
            /* TODO */
            fprintf(stderr, "ERROR: bin format currently unimplemented");
        default:
            fprintf(stderr, "ERROR: %s: unknown format '%s'\n\n", argv[1], argv[2]);
            return 1;
    }
    for (i = 3; i < argc; i++)
        display_filename(format, argv[i], TERM_WIDTH);
    return 0;
}

int main_encode(int argc, char *argv[]) {
    /* TODO */
    return 0;
}

int main_decode(int argc, char *argv[]) {
    /* TODO */
    return 0;
}

int main_print(int argc, char *argv[]) {
    int i;
    char buf[BUFSIZE];
    if (argc > 2) {
        for (i = 2; i < argc; i++)
            print_string(strlen(argv[i]), argv[i], TERM_WIDTH);
    } else {
        while (fgets(buf, BUFSIZE, stdin))
            print_string(strlen(buf), buf, TERM_WIDTH);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    if (argc <= 1) {
        ret = 1;
    } else if (!strcmp(argv[1], "display")) {
        ret = main_display(argc, argv);
    } else if (!strcmp(argv[1], "encode")) {
        ret = main_encode(argc, argv);
    } else if (!strcmp(argv[1], "decode")) {
        ret = main_decode(argc, argv);
    } else if (!strcmp(argv[1], "print")) {
        ret = main_print(argc, argv);
    }
    if (ret)
        print_usage(argv);
    return ret;
}
