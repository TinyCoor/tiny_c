cmake_minimum_required(VERSION 3.12)

project(tiny_c C)

set(CMAKE_C_STANDARD 11)

aux_source_directory(./src TINY_C_SOURCE)

set(TINY_C_HEADER ./src/include/lexer.h
        ./src/include/tag.h
        ./src/include/token.h
        )

add_executable(tiny_c ${TINY_C_SOURCE} )

add_custom_command(
        TARGET tiny_c
        POST_BUILD
        COMMAND
            tiny_c main.tag
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/examples
)
