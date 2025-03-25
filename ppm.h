// ppm.h
// Reseni IJC-DU1, priklad b), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// deklaracie funkcii pre citanie formatu ppm

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3 * xsize * ysize
 };

 /* opens filename file and writes the data into the allocated structure */
 struct ppm * ppm_read(const char * filename);

 /* free ppm structure */
 void ppm_free(struct ppm *p);