/*
 * Oliver Calder
 * July 2021
 *
 * Mapping between 16-bit encodings and the corresponding ASCII letters.
 *
 * Supports capital letters, as well as some common symbols.
 *
 * Upper left cell is 0, lower right cell is 14, row major.
 * The bit position (rightmost 0, leftmost 14) corresponds to the cell index.
 *
 * A 1 in bit position 15 is a placeholder which does not correspond to any
 * pixel, and is necessary when encoding spaces.
 *
 * Thus, a pixel can be encoded using a single hexadecimal "digit";
 * that is, 0 is 0, a is 10, e is 14, etc.
 *
 * Alternatively, for better (or worse, depending on your familiarity with hex)
 * readability, a pixel can be encoded with a as 0, o as 14, etc.
 */

#include <stdlib.h>
#include "mapping.h"
#include "common.h"

#define BITS_A              0b101101111101010
#define BITS_B              0b011101011101011
#define BITS_C              0b110001001001110
#define BITS_D              0b011101101101011
#define BITS_E              0b111001111001111
#define BITS_F              0b001001111001111
#define BITS_G              0b110101101001110
#define BITS_H              0b101101111101101
#define BITS_I              0b111010010010111
#define BITS_J              0b010101100100100
#define BITS_K              0b101101011101101
#define BITS_L              0b111001001001001
#define BITS_M              0b101101111111101
#define BITS_N              0b101111111111101
#define BITS_O              0b010101101101010
#define BITS_P              0b001001111101011
#define BITS_Q              0b110111101101010
#define BITS_R              0b101101011101011
#define BITS_S              0b011100111001110
#define BITS_T              0b010010010010111
#define BITS_U              0b111101101101101
#define BITS_V              0b010101101101101
#define BITS_W              0b101111111101101
#define BITS_X              0b101101010101101
#define BITS_Y              0b010010010101101
#define BITS_Z              0b111001010100111
#define BITS_0              0b111101101101111
#define BITS_1              0b010010010010011
#define BITS_2              0b111001010100011
#define BITS_3              0b011100011100011
#define BITS_4              0b100100111101101
#define BITS_5              0b011100011001111
#define BITS_6              0b011101111001110
#define BITS_7              0b100100100100111
#define BITS_8              0b111101010101110
#define BITS_9              0b100100110101111
#define BITS_PERIOD         0b010000000000000
#define BITS_COMMA          0b010010000000000
#define BITS_SINGLEQUOTE    0b000000000010010
#define BITS_DOUBLEQUOTE    0b000000000101101
#define BITS_COLON          0b000010000010000
#define BITS_SEMICOLON      0b010010000010000
#define BITS_EXCLAMATION    0b010000010010010
#define BITS_QUESTION       0b010000010100011
#define BITS_PLUS           0b000010111010000
#define BITS_MINUS          0b000000111000000
#define BITS_STAR           0b000101010101000
#define BITS_SLASH          0b001001010100100
#define BITS_PIPE           0b010010010010010
#define BITS_BACKSLASH      0b100100010001001
#define BITS_PERCENT        0b101001010100101
#define BITS_CARET          0b000000000101010
#define BITS_TILDE          0b000000001111000
#define BITS_AMPERSAND      0b110101110101010
#define BITS_OPENPAREN      0b100010010010100
#define BITS_CLOSEPAREN     0b001010010010001
#define BITS_OPENBRACKET    0b110010010010110
#define BITS_CLOSEBRACKET   0b011010010010011
#define BITS_OPENBRACE      0b110010011010110
#define BITS_CLOSEBRACE     0b011010110010011
#define BITS_LT             0b000100011100000
#define BITS_GT             0b000001110001000
#define BITS_LEQ            0b111000100011100
#define BITS_GEQ            0b111000001110001
#define BITS_EQUAL          0b000111000111000
#define BITS_UNDERSCORE     0b111000000000000
#define BITS_SPACE          0b000000000000000
#define BITS_UNKNOWN        0b111111111111111

char uint16_to_char(uint16_t bits) {
    switch (bits & 077777) {
        case BITS_A:
            return 'A';
        case BITS_B:
            return 'B';
        case BITS_C:
            return 'C';
        case BITS_D:
            return 'D';
        case BITS_E:
            return 'E';
        case BITS_F:
            return 'F';
        case BITS_G:
            return 'G';
        case BITS_H:
            return 'H';
        case BITS_I:
            return 'I';
        case BITS_J:
            return 'J';
        case BITS_K:
            return 'K';
        case BITS_L:
            return 'L';
        case BITS_M:
            return 'M';
        case BITS_N:
            return 'N';
        case BITS_O:
            return 'O';
        case BITS_P:
            return 'P';
        case BITS_Q:
            return 'Q';
        case BITS_R:
            return 'R';
        case BITS_S:
            return 'S';
        case BITS_T:
            return 'T';
        case BITS_U:
            return 'U';
        case BITS_V:
            return 'V';
        case BITS_W:
            return 'W';
        case BITS_X:
            return 'X';
        case BITS_Y:
            return 'Y';
        case BITS_Z:
            return 'Z';
        case BITS_0:
            return '0';
        case BITS_1:
            return '1';
        case BITS_2:
            return '2';
        case BITS_3:
            return '3';
        case BITS_4:
            return '4';
        case BITS_5:
            return '5';
        case BITS_6:
            return '6';
        case BITS_7:
            return '7';
        case BITS_8:
            return '8';
        case BITS_9:
            return '9';
        case BITS_PERIOD:
            return '.';
        case BITS_COMMA:
            return ',';
        case BITS_SINGLEQUOTE:
            return '\'';
        case BITS_DOUBLEQUOTE:
            return '"';
        case BITS_COLON:
            return ':';
        case BITS_SEMICOLON:
            return ';';
        case BITS_EXCLAMATION:
            return '!';
        case BITS_QUESTION:
            return '?';
        case BITS_PLUS:
            return '+';
        case BITS_MINUS:
            return '-';
        case BITS_STAR:
            return '*';
        case BITS_SLASH:
            return '/';
        case BITS_PIPE:
            return '|';
        case BITS_BACKSLASH:
            return '\\';
        case BITS_PERCENT:
            return '%';
        case BITS_CARET:
            return '^';
        case BITS_TILDE:
            return '~';
        case BITS_AMPERSAND:
            return '&';           /* this one is rather questionable */
        case BITS_OPENPAREN:
            return '(';
        case BITS_CLOSEPAREN:
            return ')';
        case BITS_OPENBRACKET:
            return '[';
        case BITS_CLOSEBRACKET:
            return ']';
        case BITS_OPENBRACE:
            return '{';
        case BITS_CLOSEBRACE:
            return '}';
        case BITS_LT:
            return '<';
        case BITS_GT:
            return '>';
        /* case BITS_LEQ:
         *     return '<=';
         * case BITS_GEQ:
         *     return '>=';
         */
        case BITS_EQUAL:
            return '=';
        case BITS_UNDERSCORE:
            return '_';
        case BITS_SPACE:
            return ' ';
        default:
            return '#';         /* unknown symbol */
    }
}

uint16_t char_to_uint16(char c) {
    switch (c) {
        case 'A':
        case 'a':
            return BITS_A;
        case 'B':
        case 'b':
            return BITS_B;
        case 'C':
        case 'c':
            return BITS_C;
        case 'D':
        case 'd':
            return BITS_D;
        case 'E':
        case 'e':
            return BITS_E;
        case 'F':
        case 'f':
            return BITS_F;
        case 'G':
        case 'g':
            return BITS_G;
        case 'H':
        case 'h':
            return BITS_H;
        case 'I':
        case 'i':
            return BITS_I;
        case 'J':
        case 'j':
            return BITS_J;
        case 'K':
        case 'k':
            return BITS_K;
        case 'L':
        case 'l':
            return BITS_L;
        case 'M':
        case 'm':
            return BITS_M;
        case 'N':
        case 'n':
            return BITS_N;
        case 'O':
        case 'o':
            return BITS_O;
        case 'P':
        case 'p':
            return BITS_P;
        case 'Q':
        case 'q':
            return BITS_Q;
        case 'R':
        case 'r':
            return BITS_R;
        case 'S':
        case 's':
            return BITS_S;
        case 'T':
        case 't':
            return BITS_T;
        case 'U':
        case 'u':
            return BITS_U;
        case 'V':
        case 'v':
            return BITS_V;
        case 'W':
        case 'w':
            return BITS_W;
        case 'X':
        case 'x':
            return BITS_X;
        case 'Y':
        case 'y':
            return BITS_Y;
        case 'Z':
        case 'z':
            return BITS_Z;
        case '0':
            return BITS_0;
        case '1':
            return BITS_1;
        case '2':
            return BITS_2;
        case '3':
            return BITS_3;
        case '4':
            return BITS_4;
        case '5':
            return BITS_5;
        case '6':
            return BITS_6;
        case '7':
            return BITS_7;
        case '8':
            return BITS_8;
        case '9':
            return BITS_9;
        case '.':
            return BITS_PERIOD;
        case ',':
            return BITS_COMMA;
        case '\'':
            return BITS_SINGLEQUOTE;
        case '"':
            return BITS_DOUBLEQUOTE;
        case ':':
            return BITS_COLON;
        case ';':
            return BITS_SEMICOLON;
        case '!':
            return BITS_EXCLAMATION;
        case '?':
            return BITS_QUESTION;
        case '+':
            return BITS_PLUS;
        case '-':
            return BITS_MINUS;
        case '*':
            return BITS_STAR;
        case '/':
            return BITS_SLASH;
        case '|':
            return BITS_PIPE;
        case '\\':
            return BITS_BACKSLASH;
        case '%':
            return BITS_PERCENT;
        case '^':
            return BITS_CARET;
        case '~':
            return BITS_TILDE;
        case '&':
            return BITS_AMPERSAND;  /* this one is rather questionable */
        case '(':
            return BITS_OPENPAREN;
        case ')':
            return BITS_CLOSEPAREN;
        case '[':
            return BITS_OPENBRACKET;
        case ']':
            return BITS_CLOSEBRACKET;
        case '{':
            return BITS_OPENBRACE;
        case '}':
            return BITS_CLOSEBRACE;
        case '<':
            return BITS_LT;
        case '>':
            return BITS_GT;
        /* case '<=':
         *     return BITS_LEQ;
         * case '>=':
         *     return BITS_GEQ;
         */
        case '=':
            return BITS_EQUAL;
        case '_':
            return BITS_UNDERSCORE;
        case ' ':
        case '\0':
        case '\n':
            return BITS_SPACE;
        default:
            return BITS_UNKNOWN;    /* unknown symbol */
    }
}

char *array_to_string(int length, uint16_t *array) {
    int i;
    char *str = malloc(sizeof(char) * length);
    for (i = 0; i < length; i++)
        str[i] = uint16_to_char(array[i]);
    return str;
}

uint16_t *string_to_array(int length, char *str) {
    int i;
    uint16_t *arr = malloc(sizeof(uint16_t) * length);
    for (i = 0; i < length; i++)
        arr[i] = char_to_uint16(str[i]);
    return arr;
}
