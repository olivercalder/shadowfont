SRCS 	:= common.c display.c encoder.c mapping.c main.c
HDRS	:= common.h display.h encoder.h mapping.h

OBJS	:= $(SRCS:.c=.o)

CC	= gcc
CFLAGS	= -Wall -Werror -O2 -std=c89

main : $(OBJS)
	$(CC)  $(CFLAGS)  $(OBJS) -o $@

debug :	$(SRCS) $(HDRS)
	$(CC)  $(CFLAGS)  -Og -g *.c -o $@

.PHONY: clean test

clean :
	rm -f *.o main debug

test : main
	./main
