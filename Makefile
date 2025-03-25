# Makefile
# Reseni IJC-DU1, priklad a), b), 17.3.2025
# Autor: Andrej Mikus, FIT
# Prelozeno: gcc (GCC) 14.2.1
#

CC=gcc
CFLAGS=-std=c11 -g -Wall -Wextra -pedantic -O2
LDFLAGS=-lm
INL_FLAGS = -DUSE_INLINE


TARGS = primes primes-i steg-decode

LIBS = bitset.h eratosthenes.h error.h ppm.h

O_STEG = bitset.o eratosthenes.o ppm.o steg-decode.o error.o
O_PRIMES = bitset.o eratosthenes.o primes.o error.o
O_PRIMES_I = bitset-i.o eratosthenes.o primes-i.o error.o

all: $(TARGS)

primes: $(O_PRIMES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

primes-i: $(O_PRIMES_I)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

steg-decode: $(O_STEG)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(LIBS)
	$(CC) $(CFLAGS) -c $< -o $@

primes-i.o: primes.c $(LIBS)
	$(CC) $(CFLAGS) $(INL_FLAGS) -c $< -o $@

bitset-i.o: bitset.c bitset.h
	$(CC) $(CFLAGS) $(INL_FLAGS) -c $< -o $@

run: all
	ulimit -s 120000 && ./primes && ./primes-i

clean:
	rm -f *.o $(TARGS) xmikus19.zip

zip:
	zip xmikus19.zip *.c *.h Makefile