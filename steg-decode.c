// steg-decode.c
// Reseni IJC-DU1, priklad b), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
//


#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"

#include <stdio.h>
#include <stdlib.h>

#define START_PRIME 101

#define MAX_MESSAGE_BUFF 6000

/**
 *  from:
 *  https://www.cl.cam.ac.uk/~mgk25/ucs/utf8_check.c
 */
unsigned char *utf8_check(unsigned char *s)
{
  while (*s) {
    if (*s < 0x80)
      /*  0xxxxxxx */
      s++;
    else if ((s[0] & 0xe0) == 0xc0) {
      /* 110XXXXx 10xxxxxx  */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[0] & 0xfe) == 0xc0)                        /*  overlong? */
	return s;
      else
	s += 2;
    } else if ((s[0] & 0xf0) == 0xe0) {
      /* 1110XXXX 10Xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||    /*  overlong? */
	  (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||    /* surrogate?  */
	  (s[0] == 0xef && s[1] == 0xbf &&
	   (s[2] & 0xfe) == 0xbe))                      /*  U+FFFE or U+FFFF? */
	return s;
      else
	s += 3; 
    } else if ((s[0] & 0xf8) == 0xf0) {
      /*  11110XXX 10XXxxxx 10xxxxxx 10xxxxxx  */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[3] & 0xc0) != 0x80 ||
	  (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
	return s;
      else
	s += 4;
    } else
      return s;
  }

  return NULL;
}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        warning("usage: ./steg-decode <file>");
        return 1;
    }
    
    /* read ppm structure */
    struct ppm *img = ppm_read(argv[1]);
    
    if (img == NULL) {
        error_exit("loading image structure failure");
    }

    bitset_t arr;
    /* size of message is ((R+G+B) * bits in a byte) */
    size_t size_btst = 3*img->xsize*img->ysize * CHAR_BIT;
    bitset_alloc(arr, size_btst);

    Eratosthenes(arr);
    bitset_index_t idx = START_PRIME;
    
    /* extra buffer for checking utf-8 message */
    char *msg = malloc(MAX_MESSAGE_BUFF);
    if (msg == NULL) {
        error_exit("memory allocation fail");
    }

    char element = 0;
    int loop = 0;
    int found_null = 0;
    size_t msg_idx = 0;

    
    for(size_t pos = START_PRIME; pos < size_btst; pos++) {
        /* if prime on idx, write the bit from file to element */
        if (bitset_getbit(arr, idx)) {
            /* write bit on position 0-7 in byte (element)
             according to loop*/
            element |= ((img->data[pos] & 0x01) << loop);
            loop++;
        }
        if (loop == CHAR_BIT) {
            if (element == '\0'){
                /* found null terminator, end writing */
                found_null = 1;
                break;
            } 

            /* write in auxiliary buffer for checking message*/
            if (msg_idx < MAX_MESSAGE_BUFF - 1) {
                msg[msg_idx++] = element;
            } else {
                free(msg);
                error_exit("message is too long");
            }
            putchar(element);
            element = 0;
            loop = 0;
        }
        
        idx++;
    }

    /* error: no ending null terminator found in the message*/
    if (!found_null) {
        free(msg);
        error_exit("missing null terminaror");
    }

    msg[msg_idx] = '\0';
    /* check correct utf-8 encoding */
    if (utf8_check((unsigned char *) msg)) {
        free(msg);
        error_exit("not valid UTF-8 message");
    }

    free(msg);


    bitset_free(arr);
    ppm_free(img);

    return 0;

}