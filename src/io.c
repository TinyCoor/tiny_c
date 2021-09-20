//
// Created by y123456 on 2021/9/20.
//
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/io.h"

char *read_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }
    if (fseek(file, 0, SEEK_END) < 0) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n", file_name, strerror(errno));
        exit(-1);
    }
    int pos = ftell(file);
    if (pos < 0) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }
    if (fseek(file, 0, SEEK_SET) < 0) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }

    char *buffer =(char*)malloc((size_t)pos);
    memset(buffer,0,pos);
    size_t n = fread(buffer, 1, (size_t)pos, file);
    if (ferror(file)) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }
    fclose(file);
    return buffer;
}



