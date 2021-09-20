//
// Created by y123456 on 2021/9/20.
//

#ifndef TINY_C_LEXER_H
#define TINY_C_LEXER_H
#include "token.h"
#include <stdio.h>

typedef struct LEXER_STRUCT{
    char* src;
    size_t src_size;
    char c;
    unsigned int i;
}lexer_t;

lexer_t* lexer_init(char* src);

char lexer_peek(lexer_t* lexer,int offset);

void lexer_advance(lexer_t* lexer);

token_t *lexer_advance_current(lexer_t* lexer,int type);

void lexer_skip_whitespace(lexer_t* lexer);

token_t* lexer_advance_with(lexer_t* lexer,token_t* token);

token_t* lexer_parse_id(lexer_t* lexer);

token_t *lexer_parse_number(lexer_t *pStruct);

token_t* lexer_next_token(lexer_t* lexer);



#endif //TINY_C_LEXER_H
