#include "bitset.h"
#include "error.h"
#include "eratosthenes.c"


#include <stdio.h>
#include <time.h>

#define N_NUMBERS_TO_PRINT 10
#define LIMIT 333000000



int main(void) {
    clock_t start;
    start = clock();

    bitset_t pole;
    bitset_alloc(pole, LIMIT);

    Eratosthenes(pole);

    int to_print = 0;
    bitset_index_t idx = LIMIT ;

    while (to_print < N_NUMBERS_TO_PRINT) {
        idx--;
        if (bitset_getbit(pole, idx)) to_print++;
    }

    for (; idx < LIMIT; ++idx) {
        if (bitset_getbit(pole, idx)) {
            printf("%lu\n", idx);
        }
    }


    bitset_free(pole);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
