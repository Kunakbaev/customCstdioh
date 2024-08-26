#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lib.hpp"


int main() {
    printf("Hello world\n");

    enum MyStdiohErrors code = {};
    code = myPuts("i am puts");
    printf("Error: %s\n", getErrorMessage(code));

    const char* result = {};
    code = myStrchr("i am puts", 'p', result);
    printf("Error: %s, result: %p\n\n", getErrorMessage(code), result);

    size_t strLen = 0;
    code = myStrlen("i am puts", &strLen);
    printf("Error: %s, result: %zu\n\n", getErrorMessage(code), strLen);

    const char* srcString  = "i am src string";
    char* output = (char*)calloc(strlen(srcString) + 2, sizeof(*srcString));

    assert(output != NULL);
    code = myStrcpy(output, srcString);
    printf("Error: %s, output: %s\n\n", getErrorMessage(code), output);
    free(output);



    return 0;
}
