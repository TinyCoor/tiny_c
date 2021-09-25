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
                               "%s:\n"
                               "    pushl %%ebp\n"
                               "    movl %%esp,%%ebp\n";


        s = realloc(s,(strlen(template)+ (strlen(ast->name) * 2) + 1)*sizeof(char));
        sprintf(s,template,ast->name, ast->name);

        ast_t* as_val = ast->value;
        char* as_val_val = as(as_val->value);
        s = realloc(s, ( strlen(s)+ strlen(as_val_val) +1 ) * sizeof(char));
        strcat(s,as_val_val);


    }
   return s;
}

char* as_variable(ast_t* ast,int id){
    char* s = calloc(1,sizeof(char));
    if(ast->type == AST_INT){
        const char* template = "$%d";
        s = realloc(s,(strlen(template) +256 )* sizeof(char));
        sprintf(s,template,ast->int_value);
    } else{
        const char* template = "%d(%%esp)";
        s = realloc(s,(strlen(template) +8) * sizeof(char));
        sprintf(s,template,id);
    }
    return s;
}

char* as_call(ast_t* ast){
    char *s = calloc(1,sizeof(char));
    if(strcmp(ast->name,"return") == 0){
        ast_t* first_arg = ast->value->child->size ? ast->value->child->items[0] : 0;
        char* var_s= calloc(3,sizeof(char));
        var_s[0]='$';
        var_s[1] ='0';
        var_s[2] = '\0';

        if(first_arg && first_arg->type == AST_VARIABLE){
            char* as_var = as_variable(first_arg,8);
            var_s = realloc(var_s, (strlen(as_var) + 1 ) * sizeof(char));
            strcpy(var_s,as_var);
            free(as_var);
        }
        const char* template=   "    movl %s,%%eax\n"
                                "    movl %%ebp,%%esp\n"
                                "    popl %%ebp\n"
                                "    ret\n";
        char* ret_s = calloc(strlen(template) + 128,sizeof(char));
        sprintf(ret_s,template,var_s);
        s = realloc(s, ( strlen(ret_s) + 1 ) * sizeof(char));
        strcat(s,ret_s);
    }
    return s;
}

char* as_int(ast_t* ast){
    return "";
}

char* as_access(ast_t* ast){
    char* s = calloc(1,sizeof(char));
//    ast_t* first_arg =  ast->value->child->size ? ast->value->child->items[0] : 0;
//    printf("%d\n",first_arg->int_value);

    return s;
}


char *as_root(ast_t* ast){
    const char* section = ".section .text\n"
                          ".global _start\n"
                          "_start:\n"
                          "    pushl 0(%esp)\n"
                          "    pushl 4(%esp)\n"
                          "    call main\n"
                          "    addl $4,%esp\n"
                          "    movl %eax,%ebx\n"
                          "    movl $1,%eax\n"
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
            next_value = as_variable(ast,0);
        }break;
        case AST_CALL:{
            next_value = as_call(ast);
        }break;
        case AST_INT:{
            next_value = as_int(ast);
        }break;
        case AST_ACESS:{
            next_value = as_access(ast);
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
