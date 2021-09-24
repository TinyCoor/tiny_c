//
// Created by y123456 on 2021/9/21.
//
#include "include/parser.h"
#include "include/types.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

parser_t *parser_init(lexer_t *lexer) {
    parser_t* parser =calloc(1, sizeof(struct PARSER_STRUCT));
    parser->token= lexer_next_token(lexer);
    parser->lexer= lexer;

    return parser;
}

ast_t *parser_parse(parser_t *parser) {
    return parser_parse_compound(parser);
}

token_t *parser_consume(parser_t *parser,int type) {
   if(parser->token->type != type){
       printf("[Parser]: Unexpected token: `%s` ,was expected `%s`\n",
              token_to_cstr(parser->token), token_type_to_cstr(type));
       exit(-1);
   }
   parser->token= lexer_next_token(parser->lexer);
   return parser->token;
}

ast_t *parser_parse_compound(parser_t *parser) {
    unsigned int should_close = 0;

    if (parser->token->type ==TOKEN_LBRACE){
        parser_consume(parser,TOKEN_LBRACE);
        should_close = 1;
    }

   ast_t *compound = ast_init(AST_COMPOUND);
   while (parser->token->type != TOKEN_EOF && parser->token->type !=TOKEN_RBRACE){
        list_push(compound->child, parser_parse_expr(parser));
        if(parser->token->type == TOKEN_SEMI)
            parser_consume(parser,TOKEN_SEMI);
   }
   if(should_close)
       parser_consume(parser,TOKEN_RBRACE);

    return compound;
}

ast_t *parser_parse_expr(parser_t *parser) {
    switch (parser->token->type) {
        case TOKEN_ID:return parser_parse_id(parser);
        case TOKEN_LPAREN: return parser_parse_list(parser);
        case TOKEN_INT: return parser_parse_int(parser);
        default: {
            printf("[Parser]:Unexpected token `%s`\n", token_type_to_cstr(parser->token->type));
            assert(false && " Unreachable Code\n");
        }
    }
}


ast_t* parser_parse_id(parser_t* parser){
    char* value = calloc(strlen(parser->token->value) +1,sizeof(char ));
    strcpy(value,parser->token->value);
    parser_consume(parser,TOKEN_ID);

    if(parser->token->type==TOKEN_EQUALS){
        //parse assignment
        parser_consume(parser,TOKEN_EQUALS);
        ast_t* ast = ast_init(AST_ASSIGNMENT);
        ast->name =value;
        ast->value= parser_parse_expr(parser);
        return ast;
    }
    //parse variable
    ast_t * ast = ast_init(AST_VARIABLE);
    ast->name=value;

    if(parser->token->type == TOKEN_COLON)
    {
        parser_consume(parser,TOKEN_COLON);
        while (parser->token->type == TOKEN_ID){
            ast->data_type = typename_to_int(parser->token->value);
            parser_consume(parser,TOKEN_ID);
            if (parser->token->type == TOKEN_LT){
                parser_consume(parser,TOKEN_LT);
                ast->data_type += typename_to_int(parser->token->value);
                parser_consume(parser,TOKEN_ID);
                parser_consume(parser,TOKEN_GT);
            }
        }
    } else{
        if(parser->token->type == TOKEN_LPAREN){
            ast->type = AST_CALL;
            ast->value = parser_parse_list(parser);
        }
    }
    return ast;
}

ast_t* parser_parse_list(parser_t *parser) {
    parser_consume(parser,TOKEN_LPAREN);
    ast_t* ast = ast_init(AST_COMPOUND);
    list_push(ast->child, parser_parse_expr(parser));
    while (parser->token->type == TOKEN_COMMA){
        parser_consume(parser,TOKEN_COMMA);
        list_push(ast->child, parser_parse_expr(parser));
    }
    parser_consume(parser,TOKEN_RPAREN);
    if(parser->token->type == TOKEN_COLON)
    {
        parser_consume(parser,TOKEN_COLON);
        while (parser->token->type == TOKEN_ID){
            ast->data_type = typename_to_int(parser->token->value);
            parser_consume(parser,TOKEN_ID);
            if (parser->token->type == TOKEN_LT){
                parser_consume(parser,TOKEN_LT);
                ast->data_type += typename_to_int(parser->token->value);
                parser_consume(parser,TOKEN_ID);
                parser_consume(parser,TOKEN_GT);
            }
        }
    }

    if(parser->token->type==TOKEN_ARROW_RIGHT){
        parser_consume(parser,TOKEN_ARROW_RIGHT);
        ast->type = AST_FUNCTION;
        ast->value = parser_parse_compound(parser);
    }
    return ast;
}

ast_t* parser_parse_block(parser_t* parser){
    parser_consume(parser,TOKEN_LBRACE);
    ast_t* root = ast_init(AST_COMPOUND);

    while (parser->token->type!=TOKEN_RBRACE){
        list_push(root->child, parser_parse_expr(parser));
    }
    parser_consume(parser,TOKEN_RBRACE);
    return root;
}

ast_t *parser_parse_int(parser_t *parser) {
    int value = atoi(parser->token->value);
    parser_consume(parser,TOKEN_INT);
    ast_t* ast =ast_init(AST_INT);
    ast->int_value = value;
    return ast;
}


