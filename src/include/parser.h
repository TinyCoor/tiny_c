//
// Created by y123456 on 2021/9/21.
//

#ifndef TINY_C_PARSER_H
#define TINY_C_PARSER_H
#include "lexer.h"
#include "ast.h"
typedef struct PARSER_STRUCT{
    lexer_t* lexer;
    token_t* token;
}parser_t;

parser_t* parser_init(lexer_t* lexer);

ast_t* parser_parse(parser_t* parser);

ast_t* parser_parse_compound(parser_t* parser);

ast_t* parser_parse_expr(parser_t* parser);

ast_t* parser_parse_id(parser_t* parser);

ast_t* parser_parse_list(parser_t* parser);

ast_t* parser_parse_block(parser_t* parser);

ast_t* parser_parse_int(parser_t* parser);

token_t* parser_consume(parser_t* parser,int type);


#endif //TINY_C_PARSER_H
