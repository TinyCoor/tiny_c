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


