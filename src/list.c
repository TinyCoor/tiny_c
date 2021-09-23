//
// Created by y123456 on 2021/9/21.
//

#include "include/list.h"

list_t *list_init(size_t item_size) {
    list_t* list = calloc(1,sizeof(struct LIST_STRUCT));
    list->size = 0;
    list->item_size = item_size;
    list->items = NULL;

    return list;
}

void list_push(list_t *list, void *item) {
    list->size +=1;
    if(!list->items)
        list->items = calloc(1,list->item_size);
    else
        list->items = realloc(list->items,(list->size * list->item_size));

    list->items[list->size] = item;
}

