//
// Created by y123456 on 2021/9/21.
//

#include <stdlib.h>
#include "include/parser.h"

parser_t *parser_init(lexer_t *lexer) {
    parser_t* parser =calloc(1, sizeof(struct PARSER_STRUCT));
    parser->token= lexer_next_token(lexer);
    parser->lexer= lexer;

    return parser;
}

ast_t *parser_parse(parser_t *parser) {
    return ast_init(AST_NOOP);
}

token_t *parser_consume(parser_t *parser,int type) {
   if(parser->token->type != type){
       printf("Parser Unexpectec token: `%s` ,was expected `%s`\n",
              token_to_cstr(parser->token), token_type_to_cstr(type));
       exit(-1);
   }
   parser->token= lexer_next_token(parser->lexer);
    return parser->token;
}

ast_t *parser_parse_compound(parser_t *parser) {
   ast_t *compound = ast_init(AST_COMPOUND);
    while (parser->token->type != TOKEN_EOF){
        ast_t* child = parser_parse(parser);
    }
    return ast_init(AST_NOOP);
}



