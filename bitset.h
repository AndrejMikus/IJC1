// bitset.h
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc
//

#include <limits.h>
#include <assert.h>

typedef unsigned long * bitset_t; // type of bit array

typedef unsigned long bitset_index_t;

#define bitset_create(jmeno_pole, velikost) do { \
    static_assert(((velikost) > 0), "Error: size of array must be positive");\
    static_assert(((velikost) < ULONG_MAX), "Error: size of array exceeded")
     (unsigned long jmeno_pole[(velikost) / CHAR_BIT + 1]) = { (velikost) }; \
     while(0) }

