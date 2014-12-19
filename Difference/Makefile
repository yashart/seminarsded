CC=g++

CFLAGS=-c

all: diff

diff: main.o lexical.o differentiation.o fileworking.o
	$(CC) main.o lexical.o differentiation.o fileworking.o -o diff

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

lexical.o: lexical.cpp
	$(CC) $(CFLAGS) lexical.cpp

differentiation.o: differentiation.cpp
	$(CC) $(CFLAGS) differentiation.cpp

fileworking.o: fileworking.cpp
	$(CC) $(CFLAGS) fileworking.cpp

clean:
	rm -rf *.o *.csv LATEX.txt diff
