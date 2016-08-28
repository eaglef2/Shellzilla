#include "check.h"

#if defined(__GNUC__) && defined(__linux__)
#include <execinfo.h>
#endif

#include <stdio.h>
#include <stdlib.h>

void _Check(bool res, char *expr, char *file, int line)
{
    if (res)
        return;
    
    fprintf(stderr, "%s %d: %s is false\n", file, line, expr);
#if defined(__GNUC__) && defined(__linux__)
    void  *array[MAX_BACKTRACE];
    size_t size    = 0;
    char **strings = NULL;
    
    size = backtrace(array, MAX_BACKTRACE);
    strings = backtrace_symbols(array, size);
    fprintf(stderr, "Stack Trace:\n");
    for (int i = 0; i < size; i++)
        fprintf(stderr, "\t%d: %s\n", i, strings[i]);
#endif

    exit(1);
}