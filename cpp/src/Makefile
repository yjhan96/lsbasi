CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=-std=c++11 -Wall
SOURCES=token.cpp lexer.cpp parser.cpp interpreter.cpp main.cpp
ODIR=obj
_OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJECTS))
EXECUTABLE=comp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(ODIR)/$@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EXECUTABLE)
