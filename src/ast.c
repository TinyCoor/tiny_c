//
// Created by y123456 on 2021/9/21.
//

#include "include/ast.h"
#include <stdlib.h>
ast_t *ast_init(int type) {
    ast_t* root = calloc(1,sizeof(struct AST_STRUCT));
    root->type = type;
    if(type == AST_COMPOUND)
        root->child = list_init(sizeof(struct AST_STRUCT));


    return root;
}
