#include <malloc.h>
#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/macros.h"
#include "include/utils.h"

lexer_t* lexer_init(char* src){
    lexer_t* lexer = calloc (1,sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer-> c = src[lexer->i];

    return lexer;
}

token_t *lexer_next_token(lexer_t *lexer) {
    while (lexer->c !='\0'){
        lexer_skip_whitespace(lexer);

        if(isalpha(lexer->c)){
            return lexer_parse_id(lexer);
        }

        if(isdigit(lexer->c))
            return lexer_parse_number(lexer);

        switch (lexer->c) {
            case '=':{
                if(lexer_peek(lexer,1) == '>')
                    return lexer_advance_with(lexer, lexer_advance_with(lexer, token_init("=>",TOKEN_ARROW_RIGHT)));
                return lexer_advance_with(lexer, token_init("=", TOKEN_EQUALS));
            }
            case '(':{return lexer_advance_current(lexer,TOKEN_LPAREN);}
            case ')':{return lexer_advance_current(lexer,TOKEN_RPAREN);}
            case '{':{return lexer_advance_current(lexer,TOKEN_LBRACE);}
            case '}':{return lexer_advance_current(lexer,TOKEN_RBRACE);}
            case '[':{return lexer_advance_current(lexer,TOKEN_LBRACKET);}
            case ']':{return lexer_advance_current(lexer,TOKEN_RBRACKET);}
            case ':':{return lexer_advance_current(lexer,TOKEN_COLON);}
            case ',':{return lexer_advance_current(lexer,TOKEN_COMMA);}
            case '<':{return lexer_advance_current(lexer,TOKEN_LT);}
            case '>':{return lexer_advance_current(lexer,TOKEN_GT);}
            case ';':{return lexer_advance_current(lexer,TOKEN_SEMI);}
            case '"':{return lexer_parse_string(lexer);}
            case '\0':{break;}
            default:{
                printf("[Lexer]: Unexpected character '%c'\n",lexer->c);
                exit(1);
            }
        }
    }
    return token_init(0,TOKEN_EOF);
}

void lexer_advance(lexer_t *lexer) {
    if(lexer->i < lexer->src_size && lexer->c !='\0'){
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_t *lexer) {
    while (lexer->c== 13 || lexer->c == 10 || lexer->c ==' '||
    lexer->c == '\t'){
        lexer_advance(lexer);
    }
}

token_t *lexer_parse_id(lexer_t *lexer) {
    char* value = calloc(1,sizeof(char));
    while (isalpha(lexer->c)){
        value = realloc(value, (strlen(value)+ 2) *sizeof(char ));
        strcat(value,(char[]){lexer->c,0});
        lexer_advance(lexer);
    }
    return token_init(value,TOKEN_ID);
}

token_t *lexer_parse_number(lexer_t *lexer) {
    char* value = calloc(1,sizeof(char));
    while (isdigit(lexer->c)){
        value = realloc(value, (strlen(value)+ 2) * sizeof(char ));
        strcat(value,(char[]){lexer->c,0});
        lexer_advance(lexer);
    }
    return token_init(value,TOKEN_INT);
}

token_t *lexer_advance_with(lexer_t *lexer,token_t* token) {
    lexer_advance(lexer);
    return token;
}

char lexer_peek(lexer_t *lexer,int offset) {
    return lexer->src[MIN( lexer->i + offset,lexer->src_size)];
}

token_t *lexer_advance_current(lexer_t *lexer, int type) {
    char* value = calloc(2,sizeof(char ));
    value[0] = lexer->c;
    value[1] ='\0';
    token_t* token= token_init(value,type);
    lexer_advance(lexer);
    return token;
}

token_t *lexer_parse_string(lexer_t *lexer) {
    char *value= calloc(1,sizeof(char ));

    lexer_advance(lexer);
    while (lexer->c !='"'){
        value = realloc(value,(strlen(value) + 2) *sizeof(char ));
        strcat(value,(char[]){lexer->c,0});
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    char *format = str_format(value);
    free(value);
    return token_init(format,TOKEN_STRING);
}




