CC=g++
CFLAGS=-c -g3 -Wall
LDFLAGS=
SOURCES=main.cpp errors.cpp binary_file.cpp map.cpp source_file.cpp assembler.cpp translator.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin_trans

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o bin_trans
