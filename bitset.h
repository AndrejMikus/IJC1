// bitset.h
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc
//

#include <limits.h>

typedef unsigned long * bitset_t; // type of bit array

typedef unsigned long bitset_index_t;

#define bitset_create(jmeno_pole, velikost) (unsigned long jmeno_pole[(velikost) / CHAR_BIT + 1]) = { (velikost) }