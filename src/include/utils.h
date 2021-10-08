//
// Created by y123456 on 2021/9/28.
//

#ifndef TINY_C_UTILS_H
#define TINY_C_UTILS_H

char* str_to_hex(const char* instr);

char** string_to_hex_chunks(const char* instr,int* nr_chunks);

char* mkstr(const char* str);

char str_to_escape_seq(const char* instr);

char* str_format(char *instr);

void assert_not_null(void* str);



#endif //TINY_C_UTILS_H
