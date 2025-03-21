// bitset.h
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc
//

#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long * bitset_t; // type of bit array

typedef unsigned long bitset_index_t;

/**
 * @brief includes one field for size
 * 
 */
#define arr_size_from_bits(bits) \
   ((bits) % sizeof(unsigned long)) ? \
   ((bits) / sizeof(unsigned long) * CHAR_BIT  + 1) : \
   ((bits) / sizeof(unsigned long) * CHAR_BIT)


#define bitset_create(jmeno_pole, velikost) \
   static_assert((velikost) > 0, "Error: size of array must be positive");\
   unsigned long (jmeno_pole)[arr_size_from_bits((velikost)) + 1] = {(unsigned long) (velikost), 0, };

 /* malloc allocates memory only in full bytes (CHAR_BITS)*/
 #define bitset_alloc(jmeno_pole, velikost) do { \
   static_assert((velikost) > 0, "Error: size of array must be positive");\
   static_assert((velikost) < ULONG_MAX, "Error: size of array exceeded"); \
    (jmeno_pole) = calloc(arr_size_from_bits((velikost)) + 1, sizeof(unsigned long)); \
    if (!(jmeno_pole)) { fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n"); exit(1); } \
    (jmeno_pole)[0] = ((unsigned long) velikost); \
 } while (0)

