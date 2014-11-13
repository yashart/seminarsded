#include "errors.h"

errors read_file(const char *filename, char **outputBuffer, long *length);

errors write_file(const char *filename, char **outputBuffer, long const length);

char * searchAllStr(char *text, long text_size, int *LinksQuantity);