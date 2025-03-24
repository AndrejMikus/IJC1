// steg-decode.c
// Reseni IJC-DU1, priklad a), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc
//



#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.c"

#include <stdio.h>

#define START_PRIME 101

int main(int argc, char *argv[]) {
    if (argc != 2) {
        warning("usage: ./steg-decode <file>");
        return 1;
    }
    
    struct ppm *img = ppm_read(argv[1]);
    
    if (img == NULL) {
        error_exit("loading image structure failure");
    }

    bitset_t arr;
    size_t size_btst = 3*img->xsize*img->ysize * CHAR_BIT;
    bitset_alloc(arr, size_btst);

    Eratosthenes(arr);
    bitset_index_t idx = START_PRIME;
    

    char element = 0;
    int loop = 0;
    int found_null = 0;

    for(size_t pos = START_PRIME; pos < size_btst; pos++) {
        if (bitset_getbit(arr, idx)) {
            element |= ((img->data[pos] & 0x01) << loop);
            loop++;
        }
        if (loop == CHAR_BIT) {
            if (element == '\0'){
                found_null = 1;
                break;
            } 
            putchar(element);
            element = 0;
            loop = 0;
        }
        
        idx++;
    }

    if (!found_null) {
        error_exit("missing null terminaror");
    }


    bitset_free(arr);
    ppm_free(img);

    return 0;

}