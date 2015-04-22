//
// Created by yashart on 29.03.15.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binary_file.h"

errors binary_buffer_constructor(binary_buffer* buffer)
{
    buffer->buffer = NULL;
    buffer->buffer = (char*) calloc (0, sizeof(*buffer->buffer));
    buffer->length = 0;

    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));
    return OK;
}

errors binary_buffer_destructor(binary_buffer* buffer)
{
    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));

    free(buffer->buffer);
    buffer->length = -117;
    buffer->buffer = NULL;
    return OK;
}

errors binary_buffer_OK(binary_buffer* buffer)
{
    if(!buffer)
        return BAD_FILE;
    if(!buffer->buffer)
        return NULL_PTR;
    if(buffer->length < 0)
        return BAD_SIZE;
    return OK;
}

errors bin_buffer_add_elem(binary_buffer* buffer, long value, int size)
{
    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));

    buffer->buffer = (char*) realloc(buffer->buffer, buffer->length + (size_t)size);
    if(!buffer->buffer)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);

    switch (size)
    {
        case 1:
            buffer->buffer[buffer->length]          = (char) value;
            break;
        case 2:
            *(short*)(buffer->buffer + buffer->length) = (short) value;
            break;
        case 4:
            *(int*)(buffer->buffer + buffer->length)   = (int) value;
            break;
        case 8:
            *(long*)(buffer->buffer + buffer->length)  = value;
            break;
        default:
            PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_SIZE);
    }
    buffer->length += size;

    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));
    return OK;
}

errors bin_buffer_add_str(binary_buffer *buffer, const char *str, int str_len)
{
    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));
    buffer->buffer = (char*) realloc(buffer->buffer, buffer->length + str_len);
    if(!buffer->buffer)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);

    memcpy(&buffer->buffer[buffer->length], str, str_len);
    buffer->length += str_len;

    if(binary_buffer_OK(buffer))
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(binary_buffer_OK(buffer));
    return OK;
}

void bin_buffer_dump(binary_buffer *buffer, const char* file_name)
{
    FILE* file = fopen(file_name, "wb");
    //printf("----------------------------------\n");
    printf("%d\n", binary_buffer_OK(buffer));
    fwrite(buffer->buffer, sizeof(char), buffer->length, file);
    //printf("\n----------------------------------");
    fclose(file);
}

char* bin_buffer_scan(const char *file_name, long* file_len)
{
    FILE* file = fopen(file_name, "rb");

    fseek (file, 0, SEEK_END);
    *file_len = ftell(file);
    fseek (file, 0, SEEK_SET);

    char* buffer = (char*) calloc(*file_len ,sizeof(*buffer));
    if(!buffer)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);

    for(int i = 0; i < *file_len; i++ )
    {
        if(!fscanf(file, "%c", &buffer[i]))
            PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE);
    }
    buffer[*file_len - 1] = 0;//last simbol

    fclose(file);

    if(!buffer)
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);

    return buffer;
}

int* bin_buffer_scan_hex(const char *file_name, long *file_len)
{
    FILE* file = fopen(file_name, "r");
    int* buffer = NULL;

    int scan_value = 0;
    long buffer_len = 0;
    while(fscanf(file, "%x ", &scan_value) == 1)
    {
        buffer_len ++;
        buffer = (int*) realloc(buffer, sizeof(*buffer) * buffer_len);
        if(!buffer)
            PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC);
        buffer[buffer_len - 1] = scan_value;
    }
    *file_len = buffer_len;
    fclose(file);

    return buffer;
}
