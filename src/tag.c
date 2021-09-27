//
// Created by y123456 on 2021/9/20.
//
#include "include/tag.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/as_frontend.h"
#include "include/visitor.h"
#include <string.h>


static char* sh(char* cmd){
    char* output = calloc(1,sizeof(char));
    output[0] ='\0';
    FILE *file;
    char path[1035]={0};
    file =popen(cmd,"r");
    if(file ==NULL){
        printf("Could not run cmd\n");
        exit(-1);
    }
    while (fgets(path,sizeof(path),file) !=NULL){
        output = realloc(output,strlen(output) + strlen(path) +1 *sizeof(char ));
        strcat(output,path);
    }
    pclose(file);
    return output;
}

void tag_compile(char *src) {
    lexer_t* lexer = lexer_init(src);
    parser_t* parser = parser_init(lexer);
    ast_t* root = parser_parse(parser);

    visitor_t* visitor = visitor_init();
    ast_t* optimized_root = visitor_visit(visitor,root, list_init(sizeof (struct AST_STRUCT)));

    char* s = as_root(optimized_root, list_init(sizeof(struct AST_STRUCT*)));

    write_file("test.s",s);
    sh("as --32 test.s -o test.o");
    sh("ld test.o -o test.exe -m i386pe");
//    printf("%s\n",s);
}

void tag_compile_file(const char *file_name) {
    char* tag_src = read_file(file_name);
    tag_compile(tag_src);
   // free(tag_src);
}
