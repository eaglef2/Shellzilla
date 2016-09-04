#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "check.h"
#include "token.h"

#define INIT_SIZE 10

void ProcessTokens(Token *Tokens, int NumTokens);

int main(int argc, char *argv[])
{
    size_t numTokens = 0;
    size_t sizeTokens = INIT_SIZE;
    int    state   = 0;
    char   curChar = '\0';
    bool   changed = false;
    bool   lineIsEmpty = true;
    Token *tokens  = NEW(Token, sizeTokens);
    
    printf("> ");
    Log("Starting program\n");
    
    while (true) {
        if (numTokens >= sizeTokens) {
            GrowArray(tokens, sizeTokens);
        }
        curChar = getchar();
        Log("State %d: Got char '%c' (%d)\n", state, curChar, curChar);
        if (state == 0) {
            if (curChar == '\n') {
                if (changed)
                    numTokens += 1;
                ProcessTokens(tokens, numTokens);
                FreeTokens(&tokens, &sizeTokens);
                numTokens = 0;
                sizeTokens = INIT_SIZE;
                tokens = NEW(Token, sizeTokens);
                printf("> ");
                changed = false;
                changed = false;
                lineIsEmpty = true;
                continue;
            } else if (isspace(curChar)) {
                if (changed) {
                    numTokens+= 1;
                    changed = false;
                }
                lineIsEmpty = false;
                continue;
            } else if (curChar == EOF) {
                if (lineIsEmpty)
                    break;
                else
                    continue;
            }
            
            lineIsEmpty = false;
            changed = true;
            if (curChar == '\'')
                state = 1;
            else if (curChar == '"')
                state = 2;
            else 
                AppendChar(&tokens[numTokens], curChar);
        } else if (state == 1) {
            if (curChar == '\'') {
                state = 0;
            } else
                AppendChar(&tokens[numTokens], curChar);
        } else if (state == 2) {
            if (curChar == '"')
                state = 0;
            else if (curChar == '\\') {
                curChar = getchar();
                AppendChar(&tokens[numTokens], curChar);
            } else
                AppendChar(&tokens[numTokens], curChar);
        }
    }
    
    FreeTokens(&tokens, &sizeTokens);
    CloseLog();
    
    return 0;
}

void ProcessTokens(Token *Tokens, int NumTokens)
{
    Log("ProcessTokens: %d\n", NumTokens);
    if (NumTokens == 0)
        return;
    printf("[");
    for (int i = 0; i < NumTokens; i++) {
        printf("\"");
        for (int j = 0; j < Tokens[i].strLen; j++)
            printf("%c", Tokens[i].str[j]);
        if (i < NumTokens - 1)
            printf("\",");
        else 
            printf("\"");
    }
    printf("]\n");
}