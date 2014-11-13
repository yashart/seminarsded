CC=g++

CFLAGS=-c -Wall

all: list

list: main.o errors.o fileworking.o list.o hash.o
	$(CC) main.o errors.o fileworking.o list.o hash.o -o list

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

errors.o: errors.cpp
	$(CC) $(CFLAGS) errors.cpp

fileworking.o: fileworking.cpp
	$(CC) $(CFLAGS) fileworking.cpp

list.o: list.cpp
	$(CC) $(CFLAGS) list.cpp

hash.o: hash.cpp
	$(CC) $(CFLAGS) hash.cpp

clean:
	rm -rf *.o *.csv list
