#include "check.h"

#if defined(__GNUC__) && defined(__linux__)
#include <execinfo.h>
#endif

#include <stdio.h>
#include <stdarg.h>


/* If res is false, then print what happened, and exit. */
void _Check(bool res, char const *expr, char const *file, int line)
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

void *_New(size_t Num, size_t Size)
{
    void *ret = calloc(Num, Size);
    Check(ret != NULL);
    return ret;
}

void _GrowArray(void **Arr, size_t *Len, size_t Size)
{
    int oldLen = 0;
    uint8_t *arr = NULL;
    
    Check(Arr != NULL && Len != NULL && *Len > 0 && Size > 0);
    oldLen = *Len;
    *Len *= 2;
    arr = (uint8_t *) realloc(*Arr, *Len * Size);
    Check(arr != NULL);
    /* Zero all the added bytes. */
    for (int i = oldLen  * Size; i < *Len * Size; i++)
        arr[i] = 0;
        
    *Arr = (void *) arr;
}

const char *LOG_FILE_NAME = "my_shell.log";
FILE *LogFile = NULL;
void _Log(const char *Msg, int Line, const char *Func, const char *File, ...)
{
    char buffer[1000];
    if (LogFile == NULL) {
        LogFile = fopen(LOG_FILE_NAME, "a");
        Check(LogFile != NULL);
        setbuf(LogFile, NULL);
        setbuf(stdout, NULL);
    }
    va_list argptr;
    va_start(argptr, File);
    
    int numChars = vsnprintf(buffer, 1000, Msg, argptr);
    va_end(argptr);
    if (numChars < 1000)
        buffer[numChars] = '\0';
    
    fprintf(LogFile, "%s:%d:%s: %s", File, Line, Func, buffer);
    fflush(LogFile);
}

void CloseLog(void)
{
    if (LogFile != NULL) {
        Log("Closing the log\n");
        fclose(LogFile);
    }
}