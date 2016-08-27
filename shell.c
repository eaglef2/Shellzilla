#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

char *Line = NULL;
size_t  LineSize = 0;

char **SplitString(char *String, int StrLen, char *Delims, int *Num);

int main(int argc, char *argv[])
{
    printf("> ");
    while (getline(&Line, &LineSize, stdin) != -1) {
        int NumTokens = 0;
        char **Tokens = SplitString(Line, LineSize, " ", &NumTokens);

        for (int i = 0; i < NumTokens; i++)
            printf("%s\n", Tokens[i]);


        free(Tokens);
        free(Line);
        Line = NULL;
        LineSize = 0;
        printf("> ");
    }
    free(Line);
    Line = NULL;
    return 0;
}

char **SplitString(char *String, int StrLen, char *Delims, int *Num)
{
    int len = 10;
    char **ret = NULL;
    char *curString = NULL;

    if (Num == NULL || String == NULL)
        return NULL;
    
    *Num = 0;
    ret = (char **) calloc(len, sizeof(char **));

    curString = strtok(String, Delims);
    if (curString == NULL) {
        ret[(*Num)++] = String;
        return ret;
    } else {
        ret[(*Num)++] = curString;
    }

    while ((curString = strtok(NULL, Delims)) != NULL) {
        if (*Num == len) {
            int oldLen = len;
            len *= 2;
            ret = (char **) realloc(ret, len);
            assert(ret != NULL);
            for (int i = oldLen; i < len; i++)
                ret[i] = NULL;
        }

        ret[(*Num)++] = curString;
    }

    return ret;
}
