SRCS 	:= common.c display.c encoder.c mapping.c
HDRS	:= common.h display.h encoder.h mapping.h

OBJS	:= $(SRCS:.c=.o)

CC	= gcc
CFLAGS	= -Wall -Werror -O2 -std=c89

shadowfont : $(OBJS) main.c
	$(CC)  $(CFLAGS)  $^  -o $@

test : $(OBJS) main_test.c
	$(CC)  $(CFLAGS)  $^  -o $@
	./test

debug :	$(SRCS) $(HDRS) main_test.c
	$(CC)  $(CFLAGS)  -Og -g  $^  -o $@

.PHONY: clean valgrind test

clean :
	rm -f *.o vgcore.* shadowfont test debug

valgrind : debug
	valgrind ./debug --leak-check=full --track-origins=yes
	rm -f vgcore.*
