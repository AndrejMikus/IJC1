// primes.c
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// vypise poslednych 10 prvocisel

#include "bitset.h"
#include "error.h"
#include "eratosthenes.h"


#include <stdio.h>
#include <time.h>

#define N_NUMBERS_TO_PRINT 10
#define LIMIT 333000000



int main(void) {
    clock_t start;
    /* start counting time */
    start = clock();

    
    bitset_create(pole, LIMIT);

    /* sieve the array */
    Eratosthenes(pole);

    int to_print = 0;
    bitset_index_t idx = LIMIT ;
    /* get the starting index */
    while (to_print < N_NUMBERS_TO_PRINT) {
        idx--;
        if (bitset_getbit(pole, idx)) to_print++;
    }

    /* now get last ten numbers */
    for (; idx < LIMIT; ++idx) {
        if (bitset_getbit(pole, idx)) {
            printf("%lu\n", idx);
        }
    }

    /* end time counding and return time message */
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
