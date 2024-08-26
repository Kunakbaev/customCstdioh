#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

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

// FIXME: return as was
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

    return strictStrCopy(dest, src, count);
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
// FIXME: return strlen of resutl

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

// O(strlen(tmp) + strlen(src))
MyStdiohErrors myStrstr(const char* tmp, const char* src) {
    if (tmp == NULL || src == NULL)
        return STDIO_ERROR_INVALID_ARG;

    size_t len1 = 0;
    size_t len2 = 0;

    MyStdiohErrors error = STDIO_ERROR_OK;
    error = myStrlen(tmp, &len1);
    if (error != STDIO_ERROR_OK)
        return error;
    error = myStrlen(src, &len2);
    if (error != STDIO_ERROR_OK)
        return error;

    if (!len1 || !len2)
        return STDIO_ERROR_INVALID_ARG;


    size_t arrLen = len1 + 1 + len2;
    char* concatString = (char*)calloc(arrLen + 1, sizeof(char));
    error = myStrcat(concatString, tmp);
    if (error != STDIO_ERROR_OK)
        return error;

    concatString[len1] = DELIM;
    concatString[len1 + 1] = '\0';
    //printf("s : %s\n", s);
    //return STDIO_ERROR_OK;

    error = myStrcat(concatString, src);
    if (error != STDIO_ERROR_OK)
        return error;

    printf("s : %s\n", concatString);
    printf("arrLen : %zu\n", arrLen);

    int* prefFunc = (int*)calloc(arrLen, sizeof(int));
    if (prefFunc == NULL)
        return STDIO_ERROR_ALLOCATION;

    prefFunc[0] = 0;
    // ab#ab
    for (int i = 1; i < arrLen; ++i) {
        int* ptr = &prefFunc[i];
        *ptr = prefFunc[i - 1];
        while (concatString[*ptr] != concatString[i] && *ptr != 0)
            *ptr = prefFunc[*ptr];
        if (concatString[*ptr] == concatString[i])
            *ptr = *ptr + 1;
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

    free(concatString);
    free(prefFunc);
    return STDIO_ERROR_OK;
}



// mega bruh
bool isInDelims[256] = {}; // 256 - number of chars

static MyStdiohErrors helpterStrspnFunc(const char* string, const char* good, size_t* res, bool shouldBeIn) {
    if (string == NULL || good == NULL || res == NULL)
        return STDIO_ERROR_INVALID_ARG;

    memset(isInDelims, 0, 256 * sizeof(bool));
    const char* ptr = good;
    do {
        isInDelims[*ptr] = 1;
    } while(*ptr != '\0');

    ptr = string;
    do {
        *res = *res + 1;
    } while (*ptr != '\0' &&
        ((shouldBeIn && isInDelims[*ptr]) ||
        (!shouldBeIn && !isInDelims[*ptr])));
    *res = *res - 1;
    return STDIO_ERROR_OK;
}

static MyStdiohErrors myStrspn(const char* string, const char* good, size_t* res) {
    if (string == NULL || good == NULL || res == NULL)
        return STDIO_ERROR_INVALID_ARG;

    return helpterStrspnFunc(string, good, res, true);
}

static MyStdiohErrors myStrcspn(const char* string, const char* bad, size_t* res) {
    if (string == NULL || bad == NULL || res == NULL)
        return STDIO_ERROR_INVALID_ARG;

    return helpterStrspnFunc(string, bad, res, false);
}
