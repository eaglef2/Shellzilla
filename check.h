#ifndef _CHECK_H_
#define _CHECK_H_

#include <stdbool.h>

void _Check(bool res, char *expr, char *file, int line);

#define _STR2(x) #x
#define _STR(x) _STR2(x)

#define Check(expr) _Check(expr, _STR(expr), __FILE__, __LINE__)

#if defined(__GNUC__) && defined(__linux__)
#define MAX_BACKTRACE 30
#endif

#endif