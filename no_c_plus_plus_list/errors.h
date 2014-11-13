#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED
enum errors
{
    OK              = 0,
    BAD_LIST        = 1,
    BAD_LIST_SIZE   = 2,
    BAD_MALLOC      = 3,
    BAD_FILE        = 4
};

void dump(const errors ERROR, const char *FUNCTION_NAME, const int LINE, const char *FILE, const bool kill);

#define PLEASE_KILL_MY_VERY_BAD_FUNCTION(MY_ERRNO) dump(MY_ERRNO, __PRETTY_FUNCTION__, __LINE__, __FILE__, true);
#define PLEASE_DONT_KILL_MY_VERY_BAD_FUNCTION(MY_ERRNO) dump(MY_ERRNO, __PRETTY_FUNCTION__, __LINE__, __FILE__, false);
#endif