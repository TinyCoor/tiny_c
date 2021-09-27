//
// Created by y123456 on 2021/9/20.
//
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "include/io.h"

char *read_file(const char *file_name) {
    int pos =0;
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }
    if (fseek(file, 0, SEEK_END) < 0) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n", file_name, strerror(errno));
        exit(-1);
    }
    pos = ftell(file);
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

    char *buffer =(char*) malloc((size_t)pos * sizeof(char));
    memset(buffer,0,pos);
    size_t n = fread(buffer, 1, (size_t)pos, file);
    if (ferror(file)) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }
    //TODO 增加 0避免垃圾
    memset(buffer+pos,0,1);
    fclose(file);
    return buffer;
}

void write_file(const char *file_name, char *output_buffer) {
    FILE *file = fopen(file_name, "wb");
    if (file == NULL) {
        fprintf(stderr, "ERROR:Could not open file %s :%s\n",
                file_name, strerror(errno));
        exit(-1);
    }

    if(!fwrite(output_buffer, sizeof(char), strlen(output_buffer),file)){
        fclose(file);
        printf("Could not write file\n");
        exit(-1);
    }
    fclose(file);
}



