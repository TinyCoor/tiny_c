//
// Created by y123456 on 2021/9/23.
//

#ifndef TINY_C_AS_FRONTEND_H
#define TINY_C_AS_FRONTEND_H

#include "ast.h"

char* as_root(ast_t* ast,list_t* list);

char* as(ast_t *ast,list_t* list);

#endif //TINY_C_AS_FRONTEND_H
