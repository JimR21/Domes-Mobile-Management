CC=gcc
CFLAGS=-g -Wall
SOURCES=CDCpointer.c MobileCallManagement.c TStoixeiouOuraPlus.c
OBJECTS=$(SOURCES:.c=.o)
DEPS=OuraPlus.h TStoixeiouOuraPlus.h
EXECUTABLE=manage.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(SOURCES) $(DEPS)
	$(CC) $(OBJECTS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *.gch
