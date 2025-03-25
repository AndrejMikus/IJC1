// bitset.c
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// deklaracie inline funkcii

#include "bitset.h"
#ifdef USE_INLINE
    extern inline void bitset_free(bitset_t jmeno_pole);

    extern inline bitset_index_t bitset_size(bitset_t jmeno_pole);

    extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz);

    extern inline void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz);

    extern inline bool bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
#endif