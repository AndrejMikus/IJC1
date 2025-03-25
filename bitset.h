// bitset.h
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// makra a inline funkcie pre pracu s bitmi

#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error.h"

typedef unsigned long * bitset_t; // type of bit array
typedef unsigned long bitset_index_t; // index to array

#define BITS_PER_ULONG (sizeof(unsigned long) * CHAR_BIT)

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
 

#ifndef USE_INLINE
   #define bitset_free(jmeno_pole) free(jmeno_pole);
#else
   inline void bitset_free(bitset_t jmeno_pole) { free(jmeno_pole); }
#endif

#ifndef USE_INLINE
   #define bitset_size(jmeno_pole) ((jmeno_pole)[0])
#else
   inline bitset_index_t bitset_size(bitset_t jmeno_pole) { return jmeno_pole[0]; }
#endif

#ifndef USE_INLINE
   #define bitset_fill(jmeno_pole, bool_vyraz) do { \
      for (bitset_index_t idx = 1; idx <= arr_size_from_bits((jmeno_pole)[0]); ++idx) { \
         if ((bool_vyraz)) { (jmeno_pole)[idx] = ~0UL; } \
         else { (jmeno_pole)[idx] = 0UL; } \
      } \
   } while (0)
#else
   inline void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz) {
      for (bitset_index_t idx = 1; idx <= arr_size_from_bits((jmeno_pole)[0]); ++idx) {
         if ((bool_vyraz)) { (jmeno_pole)[idx] = ~0UL; }
         else { (jmeno_pole)[idx] = 0UL; }
      }
   }
#endif


#ifndef USE_INLINE
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
# else
   inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz) {
      if ((index) >= (bitset_size(jmeno_pole))) { 
         error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", 
            (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole)));
      } 
      if (bool_vyraz) {
            ((jmeno_pole)[1 + ((index) / (sizeof(unsigned long) * CHAR_BIT))]) |= (1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)));
      } else { 
            ((jmeno_pole)[1 + ((index) / (sizeof(unsigned long) * CHAR_BIT))]) &= ~(1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)));
      }
   }
#endif


#ifndef USE_INLINE
   #define bitset_getbit(jmeno_pole, index) \
   ((index) >= (bitset_size(jmeno_pole)) ? \
         (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", \
            (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole))), 0) : \
         ((( (jmeno_pole)[1 + ((index) / BITS_PER_ULONG)] ) & (1UL << ((index) % BITS_PER_ULONG))) != 0))
#else
   inline bool bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
         return ((index) >= (bitset_size(jmeno_pole)) ?
         (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
            (unsigned long)(index), (unsigned long)(bitset_size(jmeno_pole))), 0) :
         ((( (jmeno_pole)[1 + ((index) / (sizeof(unsigned long) * CHAR_BIT))] ) & (1UL << ((index) % (sizeof(unsigned long) * CHAR_BIT)))) != 0));
   }
#endif