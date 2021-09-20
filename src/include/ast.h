//
// Created by y123456 on 2021/9/21.
//

#ifndef TINY_C_AST_H
#define TINY_C_AST_H

typedef struct AST_STRUCT{
enum {
    AST_COMPOUND,
    AST_FUNCTION_DEFINITION,
    AST_DEFINITION_TYPE,
    AST_VARIABLE,
    AST_STATEMENT,
    AST_NOOP,
}type;
}ast_t;

ast_t* ast_init(int type);

#endif //TINY_C_AST_H
