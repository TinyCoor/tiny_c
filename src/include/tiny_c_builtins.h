//
// Created by y123456 on 2021/9/27.
//

#ifndef TINY_C_TINY_C_BUILTINS_H
#define TINY_C_TINY_C_BUILTINS_H
#include "visitor.h"

typedef struct AST_STRUCT* (*fptr)(visitor_t*,ast_t* ,list_t*);

struct AST_STRUCT* fptr_print(visitor_t* visitor,struct AST_STRUCT* node, list_t* list);

char* mkstr(const char* str);

void builtins_init(list_t* list);

void builtins_register_fptr(list_t* list,const char* name,fptr ptr);


#endif //TINY_C_TINY_C_BUILTINS_H
