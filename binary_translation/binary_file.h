//
// Created by yashart on 29.03.15.
//

#ifndef _BINARY_TRANSLATION_BINARY_FILE_H_
#define _BINARY_TRANSLATION_BINARY_FILE_H_

#include "errors.h"

struct binary_buffer
{
    char* buffer;
    int length;
};

errors binary_buffer_constructor    (binary_buffer* buffer);
errors binary_buffer_destructor     (binary_buffer* buffer);
errors binary_buffer_OK             (binary_buffer* buffer);
errors bin_buffer_add_elem          (binary_buffer* buffer, long value, int size);
errors bin_buffer_add_str(binary_buffer *buffer, const char *str, int str_len);
void   bin_buffer_dump              (binary_buffer *buffer, const char *file_name);

char*  bin_buffer_scan              (const char *file_name, long* file_len);
int* bin_buffer_scan_hex(const char *file_name, long *file_len);

#endif //_BINARY_TRANSLATION_BINARY_FILE_H_