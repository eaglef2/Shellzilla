#ifndef _CHECK_H_
#define _CHECK_H_

#include <stdbool.h>
#include <stdlib.h>

void _Check(bool res, char const *expr, char const *file, int line);

#define _STR2(x) #x
#define _STR(x) _STR2(x)

#define Check(expr) _Check(expr, _STR(expr), __FILE__, __LINE__)

#if defined(__GNUC__) && defined(__linux__)
#define MAX_BACKTRACE 30
#endif

#define NEW(type, num) (type *) _New(num, sizeof(type))
void *_New(size_t Num, size_t size);

#define GrowArray(arr, len) _GrowArray((void **) &arr, &len, sizeof(arr[0]))
void _GrowArray(void **Arr, size_t *Len, size_t Size);

#define VA_ARGS(...) , ##__VA_ARGS__
#define Log(msg, ...) _Log(msg, __LINE__, __func__, __FILE__ VA_ARGS(__VA_ARGS__))
void _Log(const char *Msg, int Line, const char *Function, const char *File, ...);
void CloseLog(void);

#endif