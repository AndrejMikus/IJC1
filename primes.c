#include "bitset.h"
#include "eratosthenes.c"
#include <stdio.h>

#define N_NUMBERS_TO_PRINT 10

int main(void) {
    bitset_t pole;
    bitset_alloc(pole, LIMIT);

    Eratosthenes(pole);

    int to_print = 0;
    bitset_index_t idx = LIMIT ;

    while (to_print < 10) {
        idx--;
        if (bitset_getbit(pole, idx)) to_print++;
    }

    for (; idx < LIMIT; ++idx) {
        if (bitset_getbit(pole, idx)) {
            printf("%lu\n", idx);
        }
    }

    return 0;
}
