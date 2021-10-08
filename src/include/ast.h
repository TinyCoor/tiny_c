//
// Created by y123456 on 2021/9/21.
//

#ifndef TINY_C_AST_H
#define TINY_C_AST_H
#include "list.h"
struct VISITOR_STRUCT;

typedef struct AST_STRUCT{
enum {
    AST_COMPOUND,
    AST_FUNCTION,
    AST_ASSIGNMENT,
    AST_ACCESS,
    AST_CALL,
    AST_INT,
    AST_STRING,
    AST_DEFINITION_TYPE,
    AST_VARIABLE,
    AST_STATEMENT,
    AST_NOOP,
}type;
list_t * child;
char* name;
char* string_value;
struct AST_STRUCT* value;
int int_value;
int data_type;

struct AST_STRUCT*( *fptr)(struct VISITOR_STRUCT* visitor,struct AST_STRUCT* node,list_t*);


}ast_t;

ast_t* ast_init(int type);

#endif //TINY_C_AST_H
