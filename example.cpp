#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lib.hpp"


int main() {
    printf("Hello world\n");

    // ------------------------------       MY PUTS        ---------------------------------------
    enum MyStdiohErrors code = {};
    code = myPuts("i am puts");
    printf("myPuts, Error: %s\n", getErrorMessage(code));

    // ------------------------------       MY STRCHR        ---------------------------------------
    const char* result = NULL; // FIXME:
    code = myStrchr("i am puts", 'p', &result);
    printf("myStrchr, Error: %s, result: %p, %c\n\n", getErrorMessage(code), result, *result);

    // ------------------------------       MY STRLEN        ---------------------------------------
    size_t strLen = 0;
    code = myStrlen("i am puts", &strLen);
    printf("myStrlen, Error: %s, result: %zu\n\n", getErrorMessage(code), strLen);

    // ------------------------------       MY STRCPY        ---------------------------------------
    const char* srcString  = "i am src string";
    char* output = (char*)calloc(strlen(srcString) + 1, sizeof(*srcString));
    assert(output != NULL);
    code = myStrcpy(output, srcString);
    printf("myStrcpy, Error: %s, output: %s\n\n", getErrorMessage(code), output);

    // ------------------------------       MY STRNCPY        ---------------------------------------
    srcString  = "i am src string";
    output = (char*)calloc(strlen(srcString) + 2, sizeof(*srcString));
    assert(output != NULL);
    code = myStrncpy(output, srcString, 4);
    printf("myStrncpy, Error: %s, output: %s\n\n", getErrorMessage(code), output);

    // ------------------------------       MY STRCAT        ---------------------------------------
    srcString  = "i am src string";
    output = (char*)calloc(strlen(srcString) + 1, sizeof(*srcString));
    assert(output != NULL);
    strcpy(output, "dest_src");
    code = myStrcat(output, srcString);
    printf("myStrcat, Error: %s, output: %s\n\n", getErrorMessage(code), output);

    // ------------------------------       MY FGETS        ---------------------------------------
    FILE* srcFile = fopen("bruh.txt", "r");
    output = (char*)calloc(strlen(srcString) + 2, sizeof(*srcString));
    assert(output != NULL);
    code = myFgets(output, 10, srcFile);
    printf("myFgets, Error: %s, output: %s\n\n", getErrorMessage(code), output);

    // ------------------------------       MY STRDUP        ---------------------------------------
    srcString  = "i am src string";
    output = {};
    code = myStrdup(srcString, &output);
    printf("myStrdup, Error: %s, output: %s\n\n", getErrorMessage(code), output);

    // ------------------------------       MY GETLINE        ---------------------------------------
    // srcString  = "i am src string";
    // //output = {};
    // code = myGetline(stdin, output, '\n');
    // printf("myStrdup, Error: %s, output: %s\n\n", getErrorMessage(code), output);

    // ------------------------------       MY STRSTR        ---------------------------------------
    const char* tmpStr = "ab";
    const char* srcStr = "abababcab";
    code = myStrstr(tmpStr, srcStr);
    printf("myStrstr, Error: %s\n\n", getErrorMessage(code));

    free(output);
    output = NULL;
    return 0;
}

// strstr
