#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char *input=NULL;
    size_t len=0;
    printf("db > ");
    while (getline(&input, &len, stdin) != -1) {
        if (!strncmp(input, ".exit", 4)) {
            break;
        }

        free(input);
        input = NULL;
        len = 0;
        printf("db > ");
    }
    return 0;
}
