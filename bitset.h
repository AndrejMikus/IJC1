// bitset.h
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc
//

#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error.h"

typedef unsigned long * bitset_t; // type of bit array

typedef unsigned long bitset_index_t;


/**
 * @brief includes one field for size
 * 
 */
#define arr_size_from_bits(bits) (((bits) / (CHAR_BIT * sizeof(unsigned long))) + \
   (((bits) % (CHAR_BIT * sizeof(unsigned long))) ? 1 : 0))



#define bitset_create(jmeno_pole, velikost) \
   static_assert((velikost) > 0, "Error: size of array must be positive"); \
   unsigned long (jmeno_pole)[arr_size_from_bits((velikost)) + 1] = { (unsigned long) (velikost), 0 };


 /* malloc allocates memory only in full bytes (CHAR_BITS)*/
 #define bitset_alloc(jmeno_pole, velikost) do { \
   assert((velikost) > 0 && "Error: size of array must be positive");\
   assert((velikost) <= ULONG_MAX && "Error: size of array exceeded"); \
    (jmeno_pole) = calloc(arr_size_from_bits((velikost)) + 1, sizeof(unsigned long)); \
    if (!(jmeno_pole)) { error_exit("bitset_alloc: Chyba alokace paměti"); } \
    (jmeno_pole)[0] = ((unsigned long) velikost); \
 } while (0)


 #define bitset_free(jmeno_pole) free(jmeno_pole);


 #define bitset_size(jmeno_pole) ((jmeno_pole)[0])


 #define bitset_fill(jmeno_pole, bool_vyraz) do { \
   for (bitset_index_t idx = 1; idx <= arr_size_from_bits((jmeno_pole)[0]); ++idx) { \
      if ((bool_vyraz)) { (jmeno_pole)[idx] = ~0UL; } \
      else { (jmeno_pole)[idx] = 0UL; } \
   } \
 } while (0)



 #define BITS_PER_ULONG (sizeof(unsigned long) * CHAR_BIT)

 /* ================================================== */
/* inspired from https://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#bitManipulation */
#define bitset_setbit(jmeno_pole, index, bool_vyraz) do { \
   if ((index) >= (bitset_size(jmeno_pole))) { \
       error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", \
           (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole))); \
   } \
   if (bool_vyraz) { \
       ((jmeno_pole)[1 + ((index) / BITS_PER_ULONG)]) |= (1UL << ((index) % BITS_PER_ULONG)); \
   } else { \
       ((jmeno_pole)[1 + ((index) / BITS_PER_ULONG)]) &= ~(1UL << ((index) % BITS_PER_ULONG)); \
   } \
} while (0)



#define bitset_getbit(jmeno_pole, index) \
((index) >= (bitset_size(jmeno_pole)) ? \
      (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", \
         (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole))), 0) : \
      ((( (jmeno_pole)[1 + ((index) / BITS_PER_ULONG)] ) & (1UL << ((index) % BITS_PER_ULONG))) != 0))


/* ================================================== */

inline void bitset_free(bitset_t *pole) { free(pole); }

inline bitset_index_t bitset_size(bitset_t jmeno_pole) { return jmeno_pole[0]; }



