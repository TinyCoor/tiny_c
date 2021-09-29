cmake_minimum_required(VERSION 3.12)

project(tiny_c C)

set(CMAKE_C_STANDARD 11)

aux_source_directory(./src TINY_C_SOURCE)

set(TINY_C_HEADER ./src/include/lexer.h
        ./src/include/tag.h
        ./src/include/token.h
        ./src/include/ast.h
        ./src/include/types.h
        ./src/include/as_frontend.h
        src/include/visitor.h
        src/include/tiny_c_builtins.h src/include/utils.h src/utils.c)

add_executable(tiny_c ${TINY_C_SOURCE}  ${TINY_C_HEADER})

#该命令会在构建完成生成tiny_c 可执行文件时 执行tiny_c main.tag 命令
add_custom_command(
#        OUTPUT
        TARGET tiny_c
        POST_BUILD
        COMMAND
            tiny_c main.tag
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/examples
)
