#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "check.h"

typedef struct {
    char *str;     // The token string.
    int    strLen;  // The length of the string stored by str.
    size_t strSize; // The total bytes used by str.
} Token;

void InitToken(Token *Tok, char *Chars, int NumChars);
void FreeToken(Token **tok);
void FreeTokens(Token **toks, size_t *NumToks);

void AppendChars(Token *Tok, char *Chars, int NumChars);
void AppendChar(Token *Tok, char Char);

#define BASE_STR_SIZE 10


#endif