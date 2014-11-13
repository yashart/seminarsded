#include "list.h"
#include <stdio.h>
#include <stdlib.h>

errors listHeaderConstructor (listHeader* header)
{
    header->quantityElements = 0;
    header->firstList        = (list*) calloc(1, sizeof(*header->firstList));
    listConstructor(header->firstList);
    return OK;
}

errors listConstructor(list* list)
{
    //list->data = 0; //<- some types of listData can haven't value 0
    list->nextList = NULL;
    list->previousList = NULL;
    return OK;
}

errors listOK(listHeader* header)
{
    #ifdef DEBUG
    list* pointer = header->firstList;
    for(int i = 0; i < header->quantityElements; i++)
    {
        if(pointer == NULL)
        {
            return BAD_LIST_SIZE;
        }
        if((i + 1) < header->quantityElements)
        {
            if ((pointer->nextList != NULL) && (pointer != pointer->nextList->previousList))
            {
                return BAD_LIST;
            }
            pointer = pointer->nextList;
        }
    }
    for(int i = header->quantityElements - 1; i >= 0; i--)
    {
        if(pointer == NULL)
        {
            return BAD_LIST_SIZE;
        }
        if(i != 0)
        {
            if (pointer != pointer->previousList->nextList)
            {
                return BAD_LIST;
            }
            pointer = pointer->previousList;
        }
    }
    #endif
    return OK;
}

void listDump(listHeader *header, errors ERROR)
{
    list* pointer = header->firstList;
    printf("List(%d)\n", ERROR);
    if(pointer != NULL)
    {
        while (pointer->nextList != NULL)
        {
            if (pointer == pointer->nextList->previousList)
            {
                printf("<-(");
            }
            printf("%s)->", pointer->data);
            pointer = pointer->nextList;
        }
        printf("(%s)->", pointer->data);
    }
}

errors addNewList(listHeader *header, list *pointer, listData data)
{
    if(listOK(header))
    {
        listDump(header, listOK(header));
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(listOK(header));
    }

    list* newList = (list*) calloc(1, sizeof(*newList));
    listConstructor(newList);
    newList->nextList         = pointer;
    newList->previousList     = pointer->previousList;
    pointer->previousList     = newList;
    newList->data             = data;
    header->firstList         = newList;
    if(listOK(header))
    {
        listDump(header, listOK(header));
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(listOK(header));
    }
    header->quantityElements ++;
    return OK;
}

errors deleteList(listHeader *header, list **pointer)
{
    if (listOK(header))
    {
        listDump(header, listOK(header));
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(listOK(header));
    }

    list *newPointerPosition = NULL;

    header->quantityElements--;
    if ((*pointer)->nextList != NULL)
    {
        (*pointer)->nextList->previousList = (*pointer)->previousList;
        newPointerPosition = (*pointer)->nextList;
    }
    if ((*pointer)->previousList != NULL)
    {
        (*pointer)->previousList->nextList = (*pointer)->nextList;
        newPointerPosition = (*pointer)->previousList;
    }

    free(*pointer);
    *pointer = newPointerPosition;

    if(listOK(header))
    {
        listDump(header, listOK(header));
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(listOK(header));
    }
    return OK;
}


list* nextList(const list *list)
{
    return list->nextList;
}

list* previousList(const list* list)
{
    return list->previousList;
}
