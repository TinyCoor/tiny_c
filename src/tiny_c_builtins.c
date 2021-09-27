//
// Created by y123456 on 2021/9/27.
//

#include "include/builtins.h"
#include <stdio.h>


struct AST_STRUCT* fptr_print(visitor_t* visitor,struct AST_STRUCT* node, list_t* list){
    printf("%d\n",list->size);
    return node;
}

void builtins_register(list_t* list,const char* name,fptr ptr){
    ast_t* fptr_print_var = ast_init(AST_VARIABLE);
    fptr_print_var->name= mkstr(name);
    fptr_print_var->fptr= ptr;
    list_push(list,fptr_print_var);
}

void builtins_init(list_t* list){
    builtins_register_fptr(list,"print",fptr_print);
}


static char* mkstr(const char* str){
    char* outstr = calloc(strlen(str)+1,sizeof(char));
    strcpy(outstr,str);
    return outstr;
}