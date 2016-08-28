#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include "check.h"

typedef enum {
    IllegalToken, /* If a Token has this value, it is the result of an 
                   * error or the Token has not been set up yet. */
    WordToken,    /* A token that is not a string or a key-word. */
    StringToken,  /* A token that is a string. */
    ForToken,     /* Tokenized form of "for". */
    WhileToken,   /* Tokenized form of "while". */
    IfToken,      /* Tokenized form of "if". */
    UnknownToken, /* We don't know what this token might be. */
    END_TOKEN,    /* Tracks the largest legal value for a TokenType. */
} TokenType;

const int HIGHEST_TOKEN = END_TOKEN - 1;

typedef struct {
    TokenType type;
    char *str;
    int strLen;
} Token;

/* A Token with an illegal type, a NULL str, and a strLen of 0. 
 * All new Tokens should be given this value to aide debugging.
 */
const Token DefaultToken;

Token *Tokenize(char *Input, int InputLen, int *NumTokens);

#endif