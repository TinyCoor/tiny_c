//
// Created by y123456 on 2021/9/20.
//

#ifndef TINY_C_TOKEN_H
#define TINY_C_TOKEN_H


typedef struct TOKEN_STRUCT{
    char* value;
    enum {
        TOKEN_ID,
        TOKEN_EQUALS,       //=
        TOKEN_LPAREN,       //(
        TOKEN_RPAREN,       //)
        TOKEN_LBRACE,       //{
        TOKEN_RBRACE,       //}
        TOKEN_LBRACKET,     //[
        TOKEN_RBRACKET,     //]
        TOKEN_COLON,        ///:
        TOKEN_COMMA,        ///,
        TOKEN_LT,           // <
        TOKEN_GT,           // >
        TOKEN_ARROW_RIGHT,  //=>
        TOKEN_INT,
        TOKEN_STRING,
        TOKEN_SEMI,         //;
        TOKEN_EOF,
    }type;
}token_t;

token_t* token_init(char* value,int type);

char* token_to_cstr(token_t* token);

const char* token_type_to_cstr(int type);


#endif //TINY_C_TOKEN_H