//
// Created by y123456 on 2021/9/20.
//
#include <stdio.h>
#include "include/tag.h"

int main(int argc,char *argv[]) {
    if (argc < 2){
        printf("Please specify input file\n");
        return 1;
    }

    tag_compile_file(argv[1]);

    return 0;
}

