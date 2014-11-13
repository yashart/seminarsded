#include "fileworking.h"
#include <stdio.h>
#include <stdlib.h>

errors read_file(const char *filename, char **outputBuffer, long *length)
{
    FILE* file = NULL;
    file = fopen(filename, "r");
    if (!file)
    {
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE)
    }
    fseek (file, 0, SEEK_SET);
    *length = 0;
    fseek (file, 0, SEEK_END);
    *length = ftell(file);
    fseek (file, 0, SEEK_SET);
    if (!*length)
    {
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE)
    }
    *outputBuffer = (char*) calloc(*length, sizeof(*outputBuffer));
    if (!*outputBuffer)
    {
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_MALLOC)
    }
    if(fread (*outputBuffer, 1, *length, file) != *length)
    {
        PLEASE_DONT_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE)
    }
    fclose(file);
    return OK;
}

errors write_file(const char *filename, char **outputBuffer, long const length)
{
    FILE* file = NULL;
    file = fopen(filename, "w");
    if (!file)
    {
        PLEASE_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE)
    }

    if(fwrite (*outputBuffer, 1, length, file) != length)
    {
        PLEASE_DONT_KILL_MY_VERY_BAD_FUNCTION(BAD_FILE)
    }

    fclose(file);
    return OK;
}

char * searchAllStr(char *text, long text_size, int *LinksQuantity) {
    char** linksArray = NULL;
    linksArray = (char**) realloc((char*)linksArray, sizeof(*linksArray));
    linksArray[0] = (char*)&text[0];
    int numberString = 1;
    for(int i = 1; i < text_size; i++)
    {
        if ((text[i] == '\0') || (text[i] == '\n') || (text[i] == ' '))
        {
            text[i] = '\0';
        }
    }

    for(int i = 1; i < text_size; i++)
    {
        if((text[i] == '\0')&&(text[i+1] != '\0'))
        {
            linksArray = (char**) realloc((char*)linksArray, (numberString + 1)*sizeof(*linksArray));
            linksArray[numberString] = (char*) &text[i+1];
            numberString++;
        }
    }
    *LinksQuantity = numberString;
    return *linksArray;
}