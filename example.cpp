#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lib.hpp"


int main() {
    printf("Hello world\n");

    // ------------------------------       MY PUTS        ---------------------------------------
    enum MyStdiohErrors error = {};
    error = myPuts("i am puts");
    printf("myPuts, Error: %s\n", getErrorMessage(error));

    // ------------------------------       MY STRCHR        ---------------------------------------
    const char* result = NULL; // FIXME:
    error = myStrchr("i am puts", 'p', &result);
    printf("myStrchr, Error: %s, result: %p, %c\n\n", getErrorMessage(error), result, *result);

    // ------------------------------       MY STRLEN        ---------------------------------------
    size_t strLen = 0;
    error = myStrlen("i am puts", &strLen);
    printf("myStrlen, Error: %s, result: %zu\n\n", getErrorMessage(error), strLen);

    // ------------------------------       MY STRCPY        ---------------------------------------
    const char* srcString  = "i am src string";
    char* output = (char*)calloc(strlen(srcString) + 1, sizeof(*srcString));
    assert(output != NULL);
    error = myStrcpy(output, srcString);
    printf("myStrcpy, Error: %s, output: %s\n\n", getErrorMessage(error), output);

    // ------------------------------       MY STRNCPY        ---------------------------------------
    srcString  = "i am src string";
    output = (char*)calloc(strlen(srcString) + 2, sizeof(*srcString));
    assert(output != NULL);
    error = myStrncpy(output, srcString, 4);
    printf("myStrncpy, Error: %s, output: %s\n\n", getErrorMessage(error), output);

    // ------------------------------       MY STRCAT        ---------------------------------------
    srcString  = "i am src string";
    output = (char*)calloc(strlen(srcString) + 1, sizeof(*srcString));
    assert(output != NULL);
    strcpy(output, "dest_src");
    error = myStrcat(output, srcString);
    printf("myStrcat, Error: %s, output: %s\n\n", getErrorMessage(error), output);

    // ------------------------------       MY FGETS        ---------------------------------------
    FILE* srcFile = fopen("bruh.txt", "r");
    output = (char*)calloc(strlen(srcString) + 2, sizeof(*srcString));
    assert(output != NULL);
    error = myFgets(output, 10, srcFile);
    printf("myFgets, Error: %s, output: %s\n\n", getErrorMessage(error), output);

    // ------------------------------       MY STRDUP        ---------------------------------------
    srcString  = "i am src string";
    output = {};
    error = myStrdup(srcString, &output);
    printf("myStrdup, Error: %s, output: %s\n\n", getErrorMessage(error), output);

    // ------------------------------       MY GETLINE        ---------------------------------------
    srcString  = "i am src string";
    size_t resultLen = 0;
    error = myGetline(stdin, output, ' ', &resultLen);
    printf("myStrdup, Error: %s, output: %s, resultLen: %zu\n\n", getErrorMessage(error), output, resultLen);

    // ------------------------------       MY STRSTR        ---------------------------------------
    const char* tmpStr = "bca";
    const char* srcStr = "jilszdfhlsdajfbcafhalksjd";
    error = myStrstr(tmpStr, srcStr);
    printf("myStrstr, Error: %s\n\n", getErrorMessage(error));

    // ------------------------------       MY STRSPN       ----------------------------------------
    const char* string = "1 + 38 * (4 + 5)";
    const char* good   = "+*() ";
    size_t      res    = {};
    error = myStrspn(string + 1, good, &res);
    printf("myStrspn, Error: %s, result: %zu\n\n", getErrorMessage(error), res);

    // ------------------------------       MY STRCSPN       ----------------------------------------
    string = "1 + 38 * (4 + 5)";
    good   = "+*() ";
    res    = {};
    error   = myStrcspn(string + 4, good, &res);
    printf("myStrcspn, Error: %s, result: %zu\n\n", getErrorMessage(error), res);

    // ------------------------------       MY STRTOK       ----------------------------------------
    //const char* string = "1 + 38 * (4 + 5)";
    output = "123 + 38 * (94 + 535)";
    printf("output : %s\n", output);
    good   = "+*() ";
    res    = {};
    char* token = (char*)calloc(20, sizeof(char));
    error = myStrtok(&output, good, &token);
    int i = 0;
    while (token && i < 7) {
        printf("myStrtok, Error: %s, token: %s\n", getErrorMessage(error), token);
        error = myStrtok(NULL, good, &token);
        ++i;
    }
    printf("\n");
    free(token);

    //free(output);
    output = NULL;
    return 0;
}

// strtok
