#ifndef _MYSTDIOH_LIB_
#define _MYSTDIOH_LIB_


enum MyStdiohErrors {
    STDIO_ERROR_OK,
    STDIO_ERROR_INVALID_ARG,
    STDIO_ERROR_BUFFER_TOO_SMALL,
    STDIO_ERROR_ALLOCATION,
    STDIO_ERROR_NULL_PTR,
};

const char* getErrorMessage(enum MyStdiohErrors error);

MyStdiohErrors myPuts(const char* string);

MyStdiohErrors myStrchr(const char* string, char charToSearch, const char** result);

MyStdiohErrors myStrchr(char* string, char charToSearch, char** result);

MyStdiohErrors myStrlen(const char* string, size_t* result);

MyStdiohErrors myStrcpy(char* dest, const char* src);

MyStdiohErrors myStrncpy(char* dest, const char* src, size_t count);

MyStdiohErrors myStrcat(char* dest, const char* src);

MyStdiohErrors myFgets(char* str, int count, FILE* stream);

MyStdiohErrors myStrdup(const char* src, char** result);

MyStdiohErrors myGetline(FILE* stream, char* result, char delim);

MyStdiohErrors myStrstr(const char* tmp, const char* src);

#endif
