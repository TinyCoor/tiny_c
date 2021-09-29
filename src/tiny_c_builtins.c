//
// Created by y123456 on 2021/9/27.
//

#include "include/tiny_c_builtins.h"
#include "include/utils.h"
#include <stdio.h>
#include <string.h>

struct AST_STRUCT* fptr_print(visitor_t* visitor, struct AST_STRUCT* node, list_t* list){
    printf("execute builtins function\n");
    ast_t* ast = ast_init(AST_STRING);
    ast_t* first_arg = list->size ? list->items[0]: 0;
    char* hexstr = NULL;
    char* instr = NULL;
    int nr_chunks = 0;

    if(first_arg ){
        if(first_arg->type == AST_STRING){
            instr = first_arg->string_value;
        } else if(first_arg->type == AST_INT){
            instr = calloc(128, sizeof(char));
            sprintf(instr,"%d",first_arg->int_value);
        }


        char** chunks = string_to_hex_chunks(instr,&nr_chunks);
        char * str_push = calloc(1,sizeof(char ));
        char* push_template = "    pushl $0x%s\n";
        for (int i = 0; i <nr_chunks ; ++i) {
            char* push_hex= chunks[nr_chunks - i -1];
            char* push = calloc(strlen(push_hex) + strlen(push_template) + 1, sizeof(char ));
            sprintf(push,push_template,push_hex);
            str_push = realloc(str_push, (strlen(str_push)+ strlen(push) +1) *sizeof(char ));
            strcat(str_push,push);
        }
        hexstr = str_push;
    }

    const char* template =
            "    movl $4,%%eax\n"
            "    movl $1,%%ebx\n"
            "%s\n"
            "    addl $%d,%%esp\n"
            "    movl %%esp,%%ecx\n"
            "    movl $%d,%%edx\n"
            "    int $0x80\n";

    char* asmb = calloc( (hexstr? strlen(hexstr) : 0) + strlen(template) + 1, sizeof(char ));
    sprintf(asmb, template, hexstr ? hexstr : "$0", strlen(instr) * 2,nr_chunks * 4);
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


