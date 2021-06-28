/*
 * Oliver Calder
 * June 2021
 *
 * Mapping between 16-bit encodings and the corresponding ASCII letters.
 *
 * Supports capital letters, as well as some common symbols.
 *
 * Upper left cell is 0, lower right cell is 14, row major.
 * The bit position (rightmost 0, leftmost 14) of the corresponds to the cell index.
 *
 * Thus, a pixel can be encoded using a single hexadecimal "digit";
 * that is, 0 is 0, a is 10, e is 14, etc.
 *
 * Alternatively, for better (or worse, depending on your familiarity with hex)
 * readability, a pixel can be encoded with a as 0, o as 14, etc.
 */

#include <stdlib.h>

char short_to_char(short bits) {
    switch (bits) {
        case 0b101101111101010:
            return 'A';
        case 0b011101011101011:
            return 'B';
        case 0b110001001001110:
            return 'C';
        case 0b011101101101011:
            return 'D';
        case 0b111001111001111:
            return 'E';
        case 0b001001111001111:
            return 'F';
        case 0b110101101001110:
            return 'G';
        case 0b101101111101101:
            return 'H';
        case 0b111010010010111:
            return 'I';
        case 0b010101100100100:
            return 'J';
        case 0b101101011101101:
            return 'K';
        case 0b111001001001001:
            return 'L';
        case 0b101101111111101:
            return 'M';         /* this one is rather questionable */
        case 0b101111111111101:
            return 'N';         /* this one is rather questionable */
        case 0b010101101101010:
            return 'O';
        case 0b001001111101011:
            return 'P';
        case 0b110111101101010:
            return 'Q';
        case 0b101101011101011:
            return 'R';
        case 0b011100111001110:
            return 'S';
        case 0b010010010010111:
            return 'T';
        case 0b111101101101101:
            return 'U';
        case 0b010101101101101:
            return 'V';
        case 0b101111111101101:
            return 'W';
        case 0b101101010101101:
            return 'X';
        case 0b010010010101101:
            return 'Y';
        case 0b111001010100111:
            return 'Z';
        case 0b010010010010011:
            return '1';
        case 0b111001010100011:
            return '2';
        case 0b011100011100011:
            return '3';
        case 0b100100111101101:
            return '4';
        case 0b011100011001111:
            return '5';
        case 0b011101111001110:
            return '6';
        case 0b100100100100111:
            return '7';
        case 0b111101010101110:
            return '8';
        case 0b100100110101111:
            return '9';
        case 0b010000000000000:
            return '.';
        case 0b010010000000000:
            return ',';
        case 0b000000000010010:
            return '\'';
        case 0b000000000101101:
            return '"';
        case 0b000010000010000:
            return ':';
        case 0b010010000010000:
            return ';';
        case 0b010000010010010:
            return '!';
        case 0b010000010100011:
            return '?';
        case 0b000010111010000:
            return '+';
        case 0b000000111000000:
            return '-';
        case 0b000101010101000:
            return '*';
        case 0b001001010100100:
            return '/';
        case 0b010010010010010:
            return '|';
        case 0b100100010001001:
            return '\\';
        case 0b101001010100101:
            return '%';
        case 0b000000000101010:
            return '^';
        case 0b000000001111000:
            return '~';
        case 0b110101110101010:
            return '&';           /* this one is rather questionable */
        case 0b100010010010100:
            return '(';
        case 0b001010010010001:
            return ')';
        case 0b110010010010110:
            return '[';
        case 0b011010010010011:
            return ']';
        case 0b110010011010110:
            return '{';
        case 0b011010110010011:
            return '}';
        case 0b000100011100000:
            return '<';
        case 0b000001110001000:
            return '>';
        /* case 0b111000100011100:
         *     return '<=';
         * case 0b111000001110001:
         *     return '>=';
         */
        case 0b000111000111000:
            return '=';
        case 0b111000000000000:
            return '_';
        case 0b000000000000000:
            return ' ';
        default:
            return '#';         /* unknown symbol */
    }
}

short char_to_short(char c) {
    switch (c) {
        case 'A':
        case 'a':
            return 0b101101111101010;
        case 'B':
        case 'b':
            return 0b011101011101011;
        case 'C':
        case 'c':
            return 0b110001001001110;
        case 'D':
        case 'd':
            return 0b011101101101011;
        case 'E':
        case 'e':
            return 0b111001111001111;
        case 'F':
        case 'f':
            return 0b001001111001111;
        case 'G':
        case 'g':
            return 0b110101101001110;
        case 'H':
        case 'h':
            return 0b101101111101101;
        case 'I':
        case 'i':
            return 0b111010010010111;
        case 'J':
        case 'j':
            return 0b010101100100100;
        case 'K':
        case 'k':
            return 0b101101011101101;
        case 'L':
        case 'l':
            return 0b111001001001001;
        case 'M':         /* this one is rather questionable */
        case 'm':
            return 0b101101111111101;
        case 'N':         /* this one is rather questionable */
        case 'n':
            return 0b101111111111101;
        case 'O':
        case 'o':
            return 0b010101101101010;
        case 'P':
        case 'p':
            return 0b001001111101011;
        case 'Q':
        case 'q':
            return 0b110111101101010;
        case 'R':
        case 'r':
            return 0b101101011101011;
        case 'S':
        case 's':
            return 0b011100111001110;
        case 'T':
        case 't':
            return 0b010010010010111;
        case 'U':
        case 'u':
            return 0b111101101101101;
        case 'V':
        case 'v':
            return 0b010101101101101;
        case 'W':
        case 'w':
            return 0b101111111101101;
        case 'X':
        case 'x':
            return 0b101101010101101;
        case 'Y':
        case 'y':
            return 0b010010010101101;
        case 'Z':
        case 'z':
            return 0b111001010100111;
        case '1':
            return 0b010010010010011;
        case '2':
            return 0b111001010100011;
        case '3':
            return 0b011100011100011;
        case '4':
            return 0b100100111101101;
        case '5':
            return 0b011100011001111;
        case '6':
            return 0b011101111001110;
        case '7':
            return 0b100100100100111;
        case '8':
            return 0b111101010101110;
        case '9':
            return 0b100100110101111;
        case '.':
            return 0b010000000000000;
        case ',':
            return 0b010010000000000;
        case '\'':
            return 0b000000000010010;
        case '"':
            return 0b000000000101101;
        case ':':
            return 0b000010000010000;
        case ';':
            return 0b010010000010000;
        case '!':
            return 0b010000010010010;
        case '?':
            return 0b010000010100011;
        case '+':
            return 0b000010111010000;
        case '-':
            return 0b000000111000000;
        case '*':
            return 0b000101010101000;
        case '/':
            return 0b001001010100100;
        case '|':
            return 0b010010010010010;
        case '\\':
            return 0b100100010001001;
        case '%':
            return 0b101001010100101;
        case '^':
            return 0b000000000101010;
        case '~':
            return 0b000000001111000;
        case '&':
            return 0b110101110101010;   /* this one is rather questionable */
        case '(':
            return 0b100010010010100;
        case ')':
            return 0b001010010010001;
        case '[':
            return 0b110010010010110;
        case ']':
            return 0b011010010010011;
        case '{':
            return 0b110010011010110;
        case '}':
            return 0b011010110010011;
        case '<':
            return 0b000100011100000;
        case '>':
            return 0b000001110001000;
        /* case '<=':
         *     return 0b111000100011100;
         * case '>=':
         *     return 0b111000001110001;
         */
        case '=':
            return 0b000111000111000;
        case '_':
            return 0b111000000000000;
        case ' ':
        case '\0':
        case '\n':
            return 0b000000000000000;
        default:
            return 0b111111111111111;   /* unknown symbol */
    }
}

char *array_to_string(int length, short *array) {
    int i;
    char *str = malloc(sizeof(char) * length);
    for (i = 0; i < length; i++)
        str[i] = short_to_char(array[i]);
    return str;
}

short *string_to_array(int length, char *str) {
    int i;
    short *arr = malloc(sizeof(short) * length);
    for (i = 0; i < length; i++)
        arr[i] = char_to_short(str[i]);
    return arr;
}
