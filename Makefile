CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -O2

all: bitset_test

bitset_test: bitset.o
	$(CC) $(CFLAGS) -o bitset_test bitset.o

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

clean:
	rm -f bitset_test bitset.o