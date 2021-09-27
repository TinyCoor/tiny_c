//
// Created by y123456 on 2021/9/27.
//
#include "include/visitor.h"
#include "include/tiny_c_builtins.h"
#include <assert.h>
#include <string.h>

static ast_t *var_lookup(list_t* list,const char* name){
    for (int i = 0; i <list->size ; ++i) {
        ast_t *child_ast = list->items[i];

        if(child_ast->type != AST_VARIABLE || ! child_ast->name)
            continue;
        if(strcmp(child_ast->name,name) ==0)
            return child_ast;
    }
    return NULL;
}

visitor_t *visitor_init() {
    visitor_t * visitor = calloc(1,sizeof(struct VISITOR_STRUCT));
    visitor->object = ast_init(AST_COMPOUND);
    builtins_init(visitor->object->child);
    return visitor;
}

ast_t *visitor_visit(visitor_t *visitor, ast_t *node, list_t *list) {
    switch (node->type) {
        case AST_COMPOUND:{return visitor_visit_compound(visitor,node,list);}
        case AST_VARIABLE:{return visitor_visit_variable(visitor,node,list);}
        case AST_ASSIGNMENT:{return visitor_visit_assignment(visitor,node,list);}
        case AST_CALL:{return visitor_visit_call(visitor,node,list);}
        case AST_INT: {return visitor_visit_int(visitor,node,list);}
        case AST_ACCESS:{return visitor_visit_access(visitor,node,list);}
        case AST_FUNCTION:{return visitor_visit_function(visitor,node,list);}
        case AST_STRING:{return visitor_visit_string(visitor,node,list);}
        default:{assert(0&& "Unreached Code\n");}
    }
    return node;
}

ast_t *visitor_visit_compound(visitor_t *visitor, ast_t *node, list_t *list) {
    ast_t* compound = ast_init(AST_COMPOUND);
    for (int i = 0; i <node->child->size ; ++i) {
        list_push(compound->child, visitor_visit(visitor,node->child->items[i],list));
    }
    return compound;
}

ast_t *visitor_visit_assignment(visitor_t *visitor, ast_t *node, list_t *list) {
    ast_t *new_var= ast_init(AST_ASSIGNMENT);
    new_var->name = node->name;
    new_var->value = visitor_visit(visitor,node->value,list);
    list_push(list,new_var);

    //TODO FIX BUG in
    return new_var;
}

ast_t *visitor_visit_variable(visitor_t *visitor, ast_t *node, list_t *list) {
    ast_t* var = var_lookup(visitor->object->child,node->name);
    if(var)
        return var;
    return node;
}

ast_t * visitor_visit_call(visitor_t *visitor, ast_t *node, list_t *list) {
    ast_t* var= var_lookup(visitor->object->child,node->name);

    if(var){
        if(var->fptr){
            return visitor_visit(visitor, var->fptr(visitor,var,node->value->child),list);
        }
    }
    return node;
}

ast_t *visitor_visit_int(visitor_t *visitor, ast_t *node, list_t *list) {
    return node;
}

ast_t *visitor_visit_access(visitor_t *visitor, ast_t *node, list_t *list) {
    return node;
}

ast_t *visitor_visit_function(visitor_t *visitor, ast_t *node, list_t *list) {
    ast_t* func = ast_init(AST_FUNCTION);
    func->child = list_init(sizeof(list_t*));
    func->value = visitor_visit(visitor,node->value,list);

    for (int i = 0; i <node->child->size ; ++i) {
        list_push(func->child, visitor_visit(visitor,node->child->items[i],list));
    }

    return func;
}

ast_t *visitor_visit_string(visitor_t *visitor, ast_t *node, list_t *list) {
    return node;
}
