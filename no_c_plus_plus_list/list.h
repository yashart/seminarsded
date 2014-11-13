#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "errors.h"
typedef char* listData;

struct list
{
    listData data;
    list* previousList;
    list* nextList;
};

struct listHeader
{
    int quantityElements;
    list* firstList;
};

errors listHeaderConstructor (listHeader* header);

errors listConstructor(list* list);

errors listOK(listHeader* header);

void listDump(listHeader* header, errors ERROR);

list* nextList(const list* list);

list* previousList(const list* list);

errors addNewList(listHeader *header, list *pointer, listData data);

errors deleteList(listHeader *header, list **pointer);

#endif