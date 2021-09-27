//
// Created by y123456 on 2021/9/27.
//

#ifndef TINY_C_VISITOR_H
#define TINY_C_VISITOR_H
#include "ast.h"
//optimize ast tree

typedef struct VISITOR_STRUCT{
    ast_t* object;
}visitor_t;

visitor_t *visitor_init();

ast_t *visitor_visit(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_compound(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_assignment(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_variable(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_call(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_int(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_access(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_function(visitor_t* visitor,ast_t* node,list_t* list);

ast_t *visitor_visit_string(visitor_t* visitor,ast_t* node,list_t* list);

#endif //TINY_C_VISITOR_H
