#ifndef _MYSTDIOH_LIB_
#define _MYSTDIOH_LIB_


enum MyStdiohErrors {
    STDIO_ERROR_OK,
    STDIO_ERROR_INVALID_ARG,
    STDIO_ERROR_BUFFER_TOO_SMALL,
};

const char* getErrorMessage(enum MyStdiohErrors error);

MyStdiohErrors myPuts(const char* string);

MyStdiohErrors myStrchr(const char* string, char charToSearch, const char* result);

MyStdiohErrors myStrchr(char* string, char charToSearch, char* result);

MyStdiohErrors myStrlen(const char* string, size_t* result);

MyStdiohErrors myStrcpy(char* dest, const char* src);

#endif
