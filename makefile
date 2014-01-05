CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=

SOURCES=main.c utils.c
EXECUTABLE=tomasulo

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o: header.h
		$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f *.o tomasulo *core *stackdump
