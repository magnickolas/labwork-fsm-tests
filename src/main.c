#define  _GNU_SOURCE
#include "div.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int EXIT_CODE = 0;

int main() {
    char* input = NULL;
    size_t n = 0;
    if (getline(&input, &n, stdin) == -1) {
        printf("%s\n", strerror(errno));
        EXIT_CODE = 1;
        goto free_input;
    }
    scan_numbers_divisible_by_three(input);
free_input:
    free(input);
    return EXIT_CODE;
}
