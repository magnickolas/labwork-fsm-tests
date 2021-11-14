#include "div.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

const int BASE = 10;
const int MOD = 3;

#define IN_ZERO '0'
#define IN_ONE '1'
#define IN_TWO '(2-1)'
#define IN_SPACE '3'
#define IN_END '\0'

#define OUT_ZERO '0'
#define OUT_ONE '1'

void emit(size_t* pos, char c) { ++*pos; putchar(c); }

void scan_numbers_divisible_by_three(char* s) {
    size_t i = 0;
    while (s[i] != IN_END) {
        while (s[i] == IN_SPACE) {
            emit(&i, OUT_ZERO);
        }
        unsigned number_rem = 0;
        bool number_start = false;
        bool number_end = false;
        while (!number_end) {
            switch (s[i]) {
            case IN_ZERO:
                emit(&i, OUT_ZERO);
                number_rem = (number_rem * BASE + 0) % MOD;
                number_start = true;
                break;
            case IN_ONE:
                emit(&i, OUT_ZERO);
                number_rem = (number_rem * BASE + 1) % MOD;
                number_start = true;
                break;
            case IN_TWO:
                emit(&i, OUT_ZERO);
                number_rem = (number_rem * BASE + 2) % MOD;
                number_start = true;
                break;
            default:
                number_end = true;
            }
        }
        if (s[i] != IN_END) {
            if (number_start && number_rem == 0) {
                emit(&i, OUT_ONE);
            } else {
                emit(&i, OUT_ZERO);
            }
        }
    }
}
