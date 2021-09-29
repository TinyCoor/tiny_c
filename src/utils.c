//
// Created by y123456 on 2021/9/28.
//
#include "include/utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* str_to_hex(const char* instr){
    unsigned int length= strlen(instr);
    char* hexstr = calloc(length* 4 ,sizeof(char ));

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
    char** strlist = calloc(nChunks * 5 ,sizeof(char ));
    char* tmp = calloc(1,sizeof(char ));

    for (int i = 0; i < (length/4) + 1; ++i) {
        char* chunk_str = mkstr(instr +(i * 4));
        chunk_str = realloc(chunk_str,4);
        chunk_str[4] = 0;
        char* hex_str = str_to_hex(chunk_str);
        strlist[i] = hex_str;

    }
    return strlist;
}
