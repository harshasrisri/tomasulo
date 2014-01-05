CC=gcc
CC_OPTIONS=-Wall -g

all: header.h utils
	$(CC) $(CC_OPTIONS) utils.o -o tomasulo

utils:header.h
	$(CC) $(CC_OPTIONS) -c utils.c

clean:
	@rm *.o core *.stackdump tomasulo

