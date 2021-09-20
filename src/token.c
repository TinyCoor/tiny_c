//
// Created by y123456 on 2021/9/20.
//
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "include/token.h"

token_t *token_init(char *value, int type) {
    token_t* token = calloc(1,sizeof(struct TOKEN_STRUCT));
    token->value= value;
    token->type = type;
    return token;
}
 const char* token_type_to_cstr(int type){
    switch (type) {
        case TOKEN_ID:    return "TOKEN_ID";
        case TOKEN_EQUALS:return "TOKEN_EQUALS";//=
        case TOKEN_LPAREN:return "TOKEN_LPAREN";//(
        case TOKEN_RPAREN:return "TOKEN_RPAREN";//)
        case TOKEN_LBRACE:return "TOKEN_LBRACE";//{
        case TOKEN_RBRACE:return "TOKEN_RBRACE";//}
        case TOKEN_COMMA: return "TOKEN_COMMA" ; ///,
        case TOKEN_COLON: return "TOKEN_COLON";  ///:
        case TOKEN_LT:return "TOKEN_LT" ;    // <
        case TOKEN_GT:return "TOKEN_GT";     // >
        case TOKEN_ARROW_RIGHT: return "TOKEN_ARROW_RIGHT";//=>
        case TOKEN_SEMI:return "TOKEN_SEMI"; //;
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_EOF: return "TOKEN_EOF";
        default:return "";
    }
    return "not_stringable";
}

char *token_to_cstr(token_t *token) {
    const char * type_str = token_type_to_cstr(token->type);
    const char* template = "<type=`%s`, int_type=`%d`, value=`%s`>";
    char*str = calloc(strlen(type_str) + strlen(template) + 8,sizeof(char ));
    sprintf(str,template,type_str, token->type,token->value);
    return str;
}

