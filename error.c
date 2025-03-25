// error.c
// Reseni IJC-DU1, priklad b), 17.3.2025
// Autor: Andrej Mikus, FIT
// Prelozeno: gcc (GCC) 14.2.1
// vypise varovanie/chybu a pripadne skonci s chybovym kodom 1

#include <stdarg.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

void warning(const char *fmt, ...) {
    va_list args;
     /* start listing */
    va_start(args, fmt);

    fprintf(stderr, "Warning: ");
    /* print arguments to stderr */
    vfprintf(stderr, fmt, args);

    va_end(args);
}


void error_exit(const char *fmt, ...) {
    va_list args;
    /* start listing */
    va_start(args, fmt);

    fprintf(stderr, "Error: ");
    /* print arguments to stderr */
    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}