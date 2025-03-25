// error.h
// Reseni IJC-DU1, priklad b), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// deklaracie funkcii s varovaniami

/* prints warning */
void warning(const char *fmt, ...);

/* prints error */
void error_exit(const char *fmt, ...);