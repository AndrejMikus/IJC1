CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -O2
LDFLAGS=-lm

all: primes steg-decode

primes: primes.o error.o
	$(CC) $(CFLAGS) -o primes primes.o error.o $(LDFLAGS)

primes.o: primes.c bitset.h error.h
	$(CC) $(CFLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

steg-decode: steg-decode.o ppm.o error.o
	$(CC) $(CFLAGS) -o steg-decode steg-decode.o ppm.o error.o $(LDFLAGS)

steg-decode.o: steg-decode.c ppm.h error.h
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

clean:
	rm -f primes steg-decode *.o
