CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=

SOURCES=tomasulo.c utils.c parser.c
EXECUTABLE=tomasulo

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

$(OBJECTS): *.h

clean:
	@rm -f *.o tomasulo *core *stackdump
