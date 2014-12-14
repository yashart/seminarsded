CC=g++

CFLAGS=-c

all: diff

diff: main.o lexical.o differentiation.o
	$(CC) main.o lexical.o differentiation.o -o diff

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

lexical.o: lexical.cpp
	$(CC) $(CFLAGS) lexical.cpp

differentiation.o: differentiation.cpp
	$(CC) $(CFLAGS) differentiation.cpp

clean:
	rm -rf *.o *.csv LATEX.txt diff
