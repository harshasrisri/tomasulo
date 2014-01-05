CC=gcc
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=main.c utils.c
EXECUTABLE=tomasulo

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o: header.h
		$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o tomasulo *core *stackdump &> /dev/null
