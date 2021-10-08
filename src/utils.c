//
// Created by y123456 on 2021/9/28.
//
#include "include/utils.h"
#include "include/macros.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* str_to_hex(const char* instr){
    unsigned int length= strlen(instr);
    char* hexstr = calloc(1,sizeof(char ));

    for (unsigned int idx = 0;idx < length + 1 ;idx++){
        char *new_str = calloc(4,sizeof(char ));
        sprintf(new_str,"%x",instr[length - idx]);
        hexstr = realloc(hexstr, (strlen(hexstr) + strlen(new_str) + 1 ) * sizeof(char));
        strcat(hexstr,new_str);
        free(new_str);
    }
    return hexstr;
}

char* mkstr(const char* str){
    char* outstr = calloc(strlen(str)+1,sizeof(char));
    strcpy(outstr,str);
    return outstr;
}

char ** string_to_hex_chunks(const char *instr, int* nr_chunks) {
    unsigned int length= strlen(instr);
    unsigned int nChunks = (length/4) + 1;
    *nr_chunks =(int)nChunks;
    char** strlist = calloc(nChunks * 5 ,sizeof(char*));

    for (int i = 0; i < (length/4) + 1; ++i) {
        char* chunk_str = mkstr(instr +(i * 4));
        chunk_str = realloc(chunk_str,4);
        chunk_str[4] = 0;
        char* hex_str = str_to_hex(chunk_str);
        strlist[i] = hex_str;
    }
    return strlist;
}

char str_to_escape_seq(const char *instr) {
    assert_not_null((void*)instr);
    if(strlen(instr) <=1) return 0;
    if(instr[0] !='\\') return 0;
    char in_c = instr[1];

    switch (in_c) {
        case 'n': return '\n';
        case 't': return '\t';
        case '\\':return in_c;
        default: return in_c;
    }
    return in_c;
}

void assert_not_null(void *str) {
    if(str)
        return;
    printf("[ASSERT FAILURE]: %p\n",str);
}

char *str_format(char *instr) {
    char* new_str = calloc(1, sizeof(char ));
    unsigned int len = strlen(instr);
    int i =0;
    while (instr[i] !='\0'){
        new_str = realloc(new_str, (strlen(new_str) + 2) * sizeof(char ));
        if(instr[i] =='\\'){
            char escape = str_to_escape_seq((char[]){instr[i],instr[MIN(i+1,len)],0});
            strcat(new_str,(char[]){escape,0});
            i += 2;
        } else{
            strcat(new_str,(char[]){instr[i],0});
            i += 1;
        }
    }
    return new_str;
}
