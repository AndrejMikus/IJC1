// ppm.c
// Reseni IJC-DU1, priklad b), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// nacita subor ppm a vlozi ho do struktury

#include "error.h"
#include "ppm.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER 8

/* peeks next character: get and unget it */
int peek_c(FILE *f) {
    int c;
    c = fgetc(f);
    if (c != EOF) ungetc(c, f);

    return c;
}

/* reads int number */
unsigned read_num(FILE *f) {
    int c;
    unsigned num = 0;

    while((c = peek_c(f)) != EOF && isdigit(c)) {
        c = fgetc(f);
        num *= 10;
        num += (c - '0');
    }

    return num;
}

/* returns lenght of whitespace sequence */
int read_ws(FILE *f) {
    int ws_count = 0;
    int c;
    while((c = peek_c(f)) != EOF && isspace(c)) {
        fgetc(f);
        ws_count++;
    }

    return ws_count;
}

struct ppm * ppm_read(const char * filename) {

    FILE *file;
    unsigned x_size;
    unsigned y_size;
    int max_val;
    int bytes_read = 0;
    char variant[3];

    if ((file = fopen(filename, "r")) == NULL) {
        warning("Opening file %s failed\n");
        return NULL;
    }

    /* check file validity */
    fgets(variant, sizeof(variant), file);
    if (strcmp(variant, "P6") != 0) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if (read_ws(file) == 0) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if ((x_size = read_num(file)) == 0) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if (read_ws(file) == 0) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if ((y_size = read_num(file)) == 0) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if (read_ws(file) == 0) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if ((max_val = read_num(file)) != 255) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }

    if (read_ws(file) != 1) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }
    
    /* malloc structure */
    int image_size = 3 * x_size * y_size;
    struct ppm *image = malloc(image_size + sizeof(struct ppm));
    if (image == NULL) {
        warning("memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    image->xsize = x_size;
    image->ysize = y_size;
    
    /* read the file into the structure */
    bytes_read = fread(image->data, 1, image_size, file);
    
    if (bytes_read != image_size) {
        warning("invalid PPM format\n");
        fclose(file);
        return NULL;
    }


    fclose(file);

    return image;
}

void ppm_free(struct ppm *p) {
    free(p);
}