#include "bitset.h"
#include <math.h>
#include <stdio.h>

#define LIMIT 333000000

void Eratosthenes(bitset_t pole) {

    bitset_fill(pole, 1);
    bitset_setbit(pole, 0, 0); // p[0] = 0
    bitset_setbit(pole, 1, 0); // p[1] = 0

    bitset_index_t sq_root = sqrt(bitset_size(pole));

    
    for (bitset_index_t i = 2; i <= sq_root; i++) {
        
        if(bitset_getbit(pole, i)) {
            for (bitset_index_t n = i * i; n < LIMIT; n += i) {
                bitset_setbit(pole, n, 0);
            }
        }
    }


}