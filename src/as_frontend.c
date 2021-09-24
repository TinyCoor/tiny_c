//
// Created by y123456 on 2021/9/23.
//
#include "include/ast.h"
#include "include/as_frontend.h"
#include <string.h>
#include <stdio.h>

char* as_compound(ast_t* ast){
    char* value = calloc(1,sizeof(char));
    for (int i = 0; i < ast->child->size; ++i) {
        ast_t* child_ast = (ast_t*) ast->child->items[i];
        char* next_value = as(child_ast);
        value = realloc(value,(strlen(next_value) +1)*sizeof(char));
        strcat(value,next_value);
    }
    return value;
}

char* as_assignment(ast_t* ast){
    char *s = calloc(1,sizeof(char));
    if(ast->value->type == AST_FUNCTION){
        const char* template = ".global %s\n"
                               "%s:\n";
        s = realloc(s,(strlen(template)+ (strlen(ast->name) * 2) + 1)*sizeof(char));
        sprintf(s,template,ast->name, ast->name);

        ast_t* as_val = ast->value;
        char* as_val_val = as(as_val->value);
        s = realloc(s, ( strlen(s)+ strlen(as_val_val) +1 ) * sizeof(char));
        strcat(s,as_val_val);
    }
   return s;
}
char* as_variable(ast_t* ast){

}

char* as_call(ast_t* ast){
    char *s = calloc(1,sizeof(char));
    if(strcmp(ast->name,"return") == 0){
        ast_t* first_arg = ast->value->child->size ? ast->value->child->items[0] : 0;
        const char* template= "    mov $%d,%%eax\n"
                              "    ret\n";
        char* ret_s = calloc(strlen(template) + 128,sizeof(char));
        sprintf(ret_s,template,first_arg ? first_arg->int_value: 0);
        s = realloc(s, ( strlen(ret_s) + 1 ) * sizeof(char));
        strcat(s,ret_s);
    }
    return s;
}

char* as_int(ast_t* ast){

}


char *as_root(ast_t* ast){
    const char* section = ".section .text\n"
                          ".global _start\n"
                          "_start:\n"
                          "    call main\n"
                          "    mov %eax,%ebx\n"
                          "    mov $1,%eax\n"
                          "    int $0x80\n\n";
    char* value = calloc( (strlen(section) + 128) , sizeof(char ));
    strcpy(value,section);

    char* next_value = as(ast);
    value = realloc(value,(strlen(next_value) + strlen(value) +1) *sizeof(char));
    strcat(value,next_value);
    return value;
}



char* as(ast_t *ast) {

    char* value = calloc(1, sizeof(char ));
    char * next_value = NULL;
    switch (ast->type) {
        case AST_COMPOUND:{
            next_value = as_compound(ast);
        }break;
        case AST_ASSIGNMENT :{
            next_value = as_assignment(ast);
        }break;
        case AST_VARIABLE:{
            next_value = as_variable(ast);
        }break;
        case AST_CALL:{
            next_value = as_call(ast);
        }break;
        case AST_INT:{
            next_value = as_int(ast);
        }break;
        default:{
            printf("[as fronted]: No fronted for ast of type '%d'\n",ast->type);
            exit(-1);
        }
    }

    value = realloc(value,(strlen(next_value) +1)*sizeof(char));
    strcat(value,next_value);
    return value;
}
