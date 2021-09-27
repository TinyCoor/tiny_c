//
// Created by y123456 on 2021/9/27.
//

#include "include/tiny_c_builtins.h"
#include <stdio.h>
#include <string.h>

struct AST_STRUCT* fptr_print(visitor_t* visitor,struct AST_STRUCT* node, list_t* list){
    printf("execute builtins function\n");
    ast_t* ast = ast_init(AST_STRING);
    const char* template =
            "    movl $4,%eax\n"
            "    movl $0,%ebx\n"
            "    movl $0,%ecx\n"
            "    int $0x80\n";
    ast->string_value= mkstr(template);
    return ast;
}

void builtins_register_fptr(list_t* list,const char* name,fptr ptr){
    ast_t* fptr_print_var = ast_init(AST_VARIABLE);
    fptr_print_var->name= mkstr(name);
    fptr_print_var->fptr= ptr;
    list_push(list,fptr_print_var);
}

void builtins_init(list_t* list){
    builtins_register_fptr(list,"print",fptr_print);
}


char* mkstr(const char* str){
    char* outstr = calloc(strlen(str)+1,sizeof(char));
    strcpy(outstr,str);
    return outstr;
}