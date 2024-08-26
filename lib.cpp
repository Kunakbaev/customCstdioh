#include <stdio.h>
#include <assert.h>

#include "lib.hpp"

const char* getErrorMessage(enum MyStdiohErrors error) {
    switch (error) {
        case STDIO_ERROR_OK:
            return "No errors, everythings fine\n";
        case STDIO_ERROR_INVALID_ARG:
            return "Error: invalid argument (possibly set to NULL)\n";
        case STDIO_ERROR_BUFFER_TOO_SMALL:
            return "Error: buffer is too small\n";
        default:
            return "Unknown error\n";
    }
}

// https://en.cppreference.com/w/cpp/io/c/puts
MyStdiohErrors myPuts(const char* string) {
    if (string == NULL) // error
        return STDIO_ERROR_INVALID_ARG;

    const char* ptr = string;
    while (*ptr != '\0') {
        putc(*ptr, stdout);
        ++ptr;
    }

    putc('\n', stdout);
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strchr
MyStdiohErrors myStrchr(const char* string, char charToSearch, const char* result) {
    if (string == NULL) // error
        return STDIO_ERROR_INVALID_ARG;

    const char* ptr = string;
    while (*ptr != '\0') {
        if (*ptr == charToSearch) {
            result = ptr;
            return STDIO_ERROR_OK;
        }
        ++ptr;
    }

    result = NULL;
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strchr
MyStdiohErrors myStrchr(char* string, char charToSearch, char* result) {
    if (string == NULL) // error
        return STDIO_ERROR_INVALID_ARG;

    char* ptr = string;
    while (*ptr != '\0') {
        if (*ptr == charToSearch) {
            result = ptr;
            return STDIO_ERROR_OK;
        }
        ++ptr;
    }

    result = NULL;
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/cpp/string/byte/strlen
MyStdiohErrors myStrlen(const char* string, size_t* result) {
    if (string == NULL || result == NULL)
        return STDIO_ERROR_INVALID_ARG;

    const char* ptr = string;
    while (*ptr != '\0')
        ++ptr;
    *result = ptr - string;
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strcpy
MyStdiohErrors myStrcpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL)
        return STDIO_ERROR_INVALID_ARG;

    char* ptr_dest = dest;
    char* ptr_src  = (char*)src;
    do {
        // dest buffer is not large enough
        if (*ptr_dest == '\0' && *ptr_src != '\0')
            return STDIO_ERROR_BUFFER_TOO_SMALL;

        *ptr_dest = *ptr_src;
        ++ptr_dest;
        ++ptr_src;
    } while (*ptr_src != '\0');

    return STDIO_ERROR_OK;
}
