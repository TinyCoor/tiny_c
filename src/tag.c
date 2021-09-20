//
// Created by y123456 on 2021/9/20.
//
#include "include/tag.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"

void tag_compile(char *src) {
    lexer_t* lexer = lexer_init(src);
    parser_t* parser = parser_init(lexer);
    ast_t* root = parser_parse(parser);
    printf("%p\n",root);
    token_t* token =0;
    while ((token = lexer_next_token(lexer))->type !=TOKEN_EOF){
        printf("%s\n", token_to_cstr(token));
    }
}

void tag_compile_file(const char *file_name) {
    char* tag_src = read_file(file_name);
    tag_compile(tag_src);
   // free(tag_src);
}
