
#include "token.h"


void AppendChars(Token *Tok, char *Chars, int NumChars)
{    
    Check(Tok != NULL);
    if (Chars == NULL || NumChars <= 0)
        return;

    if (Tok->str == NULL) {
        InitToken(Tok, Chars, NumChars);
        return;
    }
    
    for (int i = 0; i < NumChars; i++) {
        if (Chars[i] == '\0')
            break;
        if (Tok->strLen >= Tok->strSize)
            GrowArray(Tok->str, Tok->strSize);
        
        Tok->str[Tok->strLen] = Chars[i];
        Tok->strLen += 1;
    }
}

void AppendChar(Token *Tok, char Char)
{
    Check(Tok != NULL && Char != '\0');
    if (Tok->str == NULL)
        InitToken(Tok, &Char, 1);
    else
        AppendChars(Tok, &Char, 1);
}

void InitToken(Token *Tok, char *Chars, int NumChars)
{
    Check(Tok != NULL && Chars != NULL && NumChars > 0);
    if (Tok->str != NULL)
        free(Tok->str);
    Tok->strSize = BASE_STR_SIZE;
    Tok->str = NEW(char, Tok->strSize);
    
    AppendChars(Tok, Chars, NumChars);
}

void FreeToken(Token **tok)
{
    if (tok == NULL || *tok == NULL)
        return;
    if ((*tok)->str != NULL)
        free((*tok)->str);
    (*tok)->str = NULL;
    (*tok)->strLen = 0;
    (*tok)->strSize = 0;
    free(*tok);
    *tok = NULL;
}

void FreeTokens(Token **Toks, size_t *NumTokens)
{
    Token *toks = *Toks;
    Check(NumTokens != NULL);
    for (size_t i = 0; i < *NumTokens; i++) {
        if (toks[i].str != NULL)
            free(toks[i].str);
        toks[i].str = NULL;
        toks[i].strLen = 0;
        toks[i].strSize = 0;
    }
    free(toks);
    *Toks = NULL;
    *NumTokens = 0;
}