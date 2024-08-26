#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "lib.hpp"

const int INF = 1'000'000'000;

// some symbol that doesn't occur in out strings
const char DELIM = '#';

const char* getErrorMessage(enum MyStdiohErrors error) {
    switch (error) {
        case STDIO_ERROR_OK:
            return "No errors, everythings fine\n";
        case STDIO_ERROR_INVALID_ARG:
            return "Error: invalid argument (possibly set to NULL)\n";
        case STDIO_ERROR_BUFFER_TOO_SMALL:
            return "Error: buffer is too small\n";
        case STDIO_ERROR_ALLOCATION:
            return "Error: couldn't allocate memory\n";
        case STDIO_ERROR_NULL_PTR:
            return "Error: trying to take value of NULL pointer\n";
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
        if (ptr == NULL)
            return STDIO_ERROR_NULL_PTR;
        putc(*ptr, stdout);
        ++ptr;
    }

    putc('\n', stdout);
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strchr
MyStdiohErrors myStrchr(const char* string, char charToSearch, const char** result) {
    if (string == NULL) // error
        return STDIO_ERROR_INVALID_ARG;

    const char* ptr = string;
    while (*ptr != '\0') {
        if (ptr == NULL)
            return STDIO_ERROR_NULL_PTR;
        if (*ptr == charToSearch) {
            *result = ptr;
            return STDIO_ERROR_OK;
        }
        ++ptr;
    }

    result = NULL;
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strchr
MyStdiohErrors myStrchr(char* string, char charToSearch, const char** result) {
    return myStrchr(string, charToSearch, result);
}

// https://en.cppreference.com/w/cpp/string/byte/strlen
MyStdiohErrors myStrlen(const char* string, size_t* result) {
    if (string == NULL || result == NULL)
        return STDIO_ERROR_INVALID_ARG;

    const char* ptr = string;
    while (*ptr != '\0') {
        if (ptr == NULL)
            return STDIO_ERROR_NULL_PTR;
        ++ptr;
    }
    *result = ptr - string;
    return STDIO_ERROR_OK;
}

// copies min(count, strlen(src)) symbols to dest
static MyStdiohErrors strictStrCopy(char* dest, const char* src, size_t count) {
    if (dest == NULL || src == NULL || count <= 0)
        return STDIO_ERROR_INVALID_ARG;

    char* ptr_dest       = dest;
    const char* ptr_src  = src;
    while (count--) {
        //printf("%d %c %c\n", count, *ptr_dest, *ptr_src);
        if (ptr_dest == NULL || ptr_src == NULL)
            return STDIO_ERROR_NULL_PTR;
        if (count != 0)
            *ptr_dest = *ptr_src;
        if (*ptr_src == '\0')
            break;
        ++ptr_dest;
        ++ptr_src;
    };

    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strcpy
MyStdiohErrors myStrcpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL)
        return STDIO_ERROR_INVALID_ARG;

    return strictStrCopy(dest, src, INF);
}

//https://en.cppreference.com/w/c/string/byte/strncpy
MyStdiohErrors myStrncpy(char* dest, const char* src, size_t count) {
    if (dest == NULL || src == NULL || count <= 0)
        return STDIO_ERROR_INVALID_ARG;

    char* ptr_dest       = dest;
    const char* ptr_src  = src;
    while (count--) {
        if (ptr_dest == NULL || ptr_src == NULL)
            return STDIO_ERROR_NULL_PTR;
        //printf("%d %c %c\n", count, *ptr_dest, *ptr_src);
        if (count != 0)
            *ptr_dest = *ptr_src;
        ++ptr_dest;
        if (*ptr_src != '\0')
            ++ptr_src;
    };

    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strcat
MyStdiohErrors myStrcat(char* dest, const char* src) {
    if (dest == NULL || src == NULL)
        return STDIO_ERROR_INVALID_ARG;

    size_t len = 0;
    MyStdiohErrors error = myStrlen(dest, &len);
    if (error != STDIO_ERROR_OK) {
        dest[0] = '\0';
        return error;
    }

    char* ptr_dest       = dest + len;
    const char* ptr_src  = src;
    do {
        if (ptr_dest == NULL || ptr_src == NULL)
            return STDIO_ERROR_NULL_PTR;
        *ptr_dest = *ptr_src;
        ++ptr_dest;
        ++ptr_src;
    } while (*ptr_src != '\0');

    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/io/fgets
MyStdiohErrors myFgets(char* str, int count, FILE* stream) {
    if (str == NULL || count <= 1 || stream == NULL)
        return STDIO_ERROR_INVALID_ARG;

    char* ptr = str;
    char ch = '?';
    // reads count - 1 chars from stream (or until new line or terminate symbol)
    while ((ch = getc(stream)) != EOF && (--count)) {
        if (ch == '\0' || ch == '\n')
            break;
        if (ptr == NULL)
            return STDIO_ERROR_NULL_PTR;

        *ptr = ch;
        ++ptr;
    }

    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/c/string/byte/strdup
MyStdiohErrors myStrdup(const char* src, char** result) {
    if (src == NULL || result == NULL)
        return STDIO_ERROR_INVALID_ARG;

    size_t len = 0;
    MyStdiohErrors error = myStrlen(src, &len);
    if (error != STDIO_ERROR_OK)
        return error;
    *result = (char*)calloc(len + 1, sizeof(char));
    if (*result == NULL)
        return STDIO_ERROR_ALLOCATION;

    myStrcpy(*result, src);
    return STDIO_ERROR_OK;
}

// https://en.cppreference.com/w/cpp/string/basic_string/getline
MyStdiohErrors myGetline(FILE* stream, char* result, char delim) {
    if (stream == NULL || result == NULL)
        return STDIO_ERROR_INVALID_ARG;

    char ch = '?';
    char* ptr = result;
    while ((ch = getc(stream)) != EOF) {
        if (ch == delim) break;
        if (ptr == NULL)
            return STDIO_ERROR_NULL_PTR;
        *ptr = ch;
        ++ptr;
    }
    if (ptr == NULL)
        return STDIO_ERROR_NULL_PTR;
    *ptr = '\0';

    return STDIO_ERROR_OK;
}

MyStdiohErrors myStrstr(const char* tmp, const char* src) {
    size_t len1 = 0;
    size_t len2 = 0;

    MyStdiohErrors error = {};
    error = myStrlen(tmp, &len1);
    if (error != STDIO_ERROR_OK)
        return error;
    error = myStrlen(src, &len2);
    if (error != STDIO_ERROR_OK)
        return error;

    size_t arrLen = len1 + 1 + len2;

    char* s = (char*)calloc(arrLen + 1, sizeof(char));
    error = myStrcat(s, tmp);
    if (error != STDIO_ERROR_OK)
        return error;

    const char* delim = "#";
    error = myStrcat(s, delim);
    if (error != STDIO_ERROR_OK)
        return error;
    printf("s : %s\n", s);
    //return STDIO_ERROR_OK;

    error = myStrcat(s, src);
    if (error != STDIO_ERROR_OK)
        return error;

    printf("s : %s\n", s);
    printf("arrLen : %zu\n", arrLen);

    int* prefFunc = (int*)calloc(arrLen * 2 + 10, sizeof(int));
    if (prefFunc == NULL)
        return STDIO_ERROR_ALLOCATION;

    prefFunc[0] = 0;
    // ab#ab
    for (int i = 1; i < arrLen; ++i) {
        int* ptr = &prefFunc[i];
        *ptr = prefFunc[i - 1];
        while (s[*ptr] != s[i] && *ptr != 0)
            *ptr = prefFunc[*ptr];

        //printf("i : %d, ptr : %d\n", i, *ptr);
        if (s[*ptr] == s[i])
            *ptr = *ptr + 1;
        //printf("i : %d, ptr : %d\n", i, prefFunc[i]);
        //if (i == 0) break;
    }

    printf("prefFunc : ");
    for (int i = 0; i < arrLen; ++i)
        printf("%d ", prefFunc[i]);
    printf("\n");

    printf("Occurences: ");
    for (size_t i = 0; i < arrLen; ++i)
        if (prefFunc[i] == len1)
            printf("%zu ", i - len1 - 2);
    printf("\n");

    free(prefFunc);
    free(s);
    return STDIO_ERROR_OK;
}
