//
// Created by y123456 on 2021/9/21.
//

#ifndef TINY_C_LIST_H
#define TINY_C_LIST_H
#include <stdlib.h>
typedef struct LIST_STRUCT{
    void** items;
    size_t item_size;
    size_t size;
}list_t;

list_t* list_init(size_t item_size);

void list_push(list_t* list,void* item);


#endif //TINY_C_LIST_H
