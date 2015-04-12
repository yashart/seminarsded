//
// Created by yashart on 29.03.15.
//

#ifndef _BINARY_TRANSLATION_MAP_H_
#define _BINARY_TRANSLATION_MAP_H_

#include "errors.h"

struct map
{
    char* key;
    int   value;
};

errors map_OK           (map* mp);
errors map_constructor  (map* mp);
errors map_destructor   (map* mp);
void map_dump           (map* mp);

struct map_header
{
    int quantity_element;
    map* mp;
};

errors map_header_OK            (map_header* mp_head);
errors map_header_constructor   (map_header* mp_head);
errors map_header_destructor    (map_header* mp_head);
void   map_header_dump          (map_header* mp_head);
errors map_header_add_elem      (map_header* mp_head, const char* key, int value);
int    map_header_search        (map_header* mp_head, char* key);

#endif //_BINARY_TRANSLATION_MAP_H_
