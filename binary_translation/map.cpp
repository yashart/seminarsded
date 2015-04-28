//
// Created by yashart on 29.03.15.
//

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "map.h"

//MAP
const int MAX_MAP_KEY_LEN = 20;

errors map_OK(map* mp)
{
    if(!mp)
        return BAD_FILE;
    if(!mp->key)
        return NULL_PTR;
    return OK;
}

errors map_constructor(map* mp)
{
    mp->key = (char*) calloc(MAX_MAP_KEY_LEN, sizeof(*mp->key));
    if(!mp->key)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);

    mp->value = 0;

    if(map_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_OK(mp));
    return OK;
}

errors map_destructor(map* mp)
{
    if(map_OK(mp))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_OK(mp));

    free(mp->key);
    mp->key = NULL;
    return OK;
}

void map_dump(map* mp)
{
    printf("map [%d] = %d\n", mp->key[0], mp->value);
}

//MAP HEADER
errors map_header_OK(map_header* mp_head)
{
    if(!mp_head)
        return BAD_FILE;
    if((!mp_head->mp)&&(mp_head->quantity_element != 0))
        return NULL_PTR;
    if(mp_head->quantity_element < 0)
        return BAD_SIZE;
    return OK;
}

errors map_header_constructor(map_header* mp_head)
{
    mp_head->quantity_element = 0;
    mp_head->mp               = NULL;

    if(map_header_OK(mp_head))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp_head));
    return OK;
}

errors map_header_destructor(map_header* mp_head)
{
    if(map_header_OK(mp_head))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp_head));

    for(int i = 0; i < mp_head->quantity_element; i++)
        map_destructor(&mp_head->mp[i]);

    free(mp_head->mp);
    mp_head->mp = NULL;

    return OK;
}

void map_header_dump(map_header* mp_head)
{
    printf("map quantity elements = %d\n", mp_head->quantity_element);
    for(int i = 0; i < mp_head->quantity_element; i++)
        map_dump(&mp_head->mp[i]);
}

errors map_header_add_elem (map_header* mp_head, const char* key, int value)
{
    if(map_header_OK(mp_head))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp_head));

    mp_head->mp = (map*) realloc(mp_head->mp, (mp_head->quantity_element + 1)*sizeof(*mp_head));
    if(!mp_head->mp)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);

    map_constructor(&mp_head->mp[mp_head->quantity_element]);

    mp_head->mp[mp_head->quantity_element].key   = strcpy(mp_head->mp[mp_head->quantity_element].key, key);
    //mp_head->mp[mp_head->quantity_element].key[strlen(mp_head->mp[mp_head->quantity_element].key) - 1] = '\0';
    mp_head->mp[mp_head->quantity_element].value = value;

    mp_head->quantity_element++;

    if(map_header_OK(mp_head))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp_head));

    return OK;
}

int map_header_search(map_header* mp_head, char* key)
{
    if(map_header_OK(mp_head))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp_head));

    for(int i = 0; i < mp_head->quantity_element; i++)
    {
        if(!strcmp(mp_head->mp[i].key, key))
            return mp_head->mp[i].value;
    }

    if(map_header_OK(mp_head))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(map_header_OK(mp_head));

    return -1;
}