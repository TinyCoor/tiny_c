//
// Created by y123456 on 2021/9/27.
//

#include "include/tiny_c_builtins.h"
#include "include/utils.h"
#include <stdio.h>
#include <string.h>

struct AST_STRUCT* fptr_print(visitor_t* visitor,struct AST_STRUCT* node, list_t* list){
    printf("execute builtins function\n");
    ast_t* ast = ast_init(AST_STRING);
    ast_t* first_arg = list->size ? list->items[0]: 0;
    char* hexstr = NULL;

    char* instr = calloc(128,sizeof(char ));

    if(first_arg ){
        sprintf(instr,"%d",first_arg->int_value);
        hexstr = str_to_hex(instr);
    }

    const char* template =
            "    movl $4,%%eax\n"
            "    movl $1,%%ebx\n"
            "    pushl $0x%s\n"
            "    movl %%esp,%%ecx\n"
            "    movl $%d,%%edx\n"
            "    int $0x80\n";

    char* asmb = calloc( (hexstr? strlen(hexstr) : 0) + strlen(template) + 1, sizeof(char ));
    sprintf(asmb, template, hexstr ? hexstr : "$0", hexstr ? strlen(hexstr) : 0);
    ast->string_value= asmb;
    free(hexstr);
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