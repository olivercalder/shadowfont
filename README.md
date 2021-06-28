# shadowfont
Encoding messages using folding and shadows

## Usage

Just run `make test`, for now.

If you pass a filename as an argument, it will print the contents of that file using the shadow font.

## TODO:

- Decide on `{en,de}code` vs `{en,de}crypt` verbiage
- Switch to using `#define` statements for the pixel masks for characters, so they are consistent in both `char_to_short` and `short_to_char` and can be easily modified
- Store keys as bits, rather than char strings of '1's and '0's
  - Create helper program to convert between char strings and binary files
- Store messages as nibbles, rather than human-readable chars
  - Create helper program to convert between human-readable chars and packed nibbles
- Create helper program to display a string in the shadow font
- Build encoder
  - Figure out default strategy
- Build multithreaded brute-force decoder

## Things to optimize for:
- Fewest folds
  - Likely number of folds equal to max number of pixels shadowed in a single letter (varies by message, but usually around 13?
  - Lots of overlaps where the same pixel is shadowed multiple times
  - Easy to decode
- Fewest overlaps
  - Produces the shortest messages
  - Likely n-1 folds for each letter containing n shaded pixels
    - ...Unless the number of pixels is even... then some cleverness is needed
  - Easy to decode, unless the cleverness means that means that the masks for a single character are split into multiple sequences
- Most secure
  - Can one of the above optimizations be in place without compromising security?
  - Perhaps randomize the order in which pixels for a given character are masked?
  - Pad message with redundant bits to maximize the number of other valid messages (ie. no invalid output characters) which can be built using the same encoded message but different key
    - This seems the most promising, and the most challenging
