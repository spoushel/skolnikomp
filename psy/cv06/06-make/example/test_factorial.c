#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "./utils/math_utils.h"

int main() {
    struct { uint32_t n; uint64_t expect; } cases[] = {
        {0, 1},
        {1, 1},
        {5, 120},
        {10, 3628800}
    };

    bool failed = false;
    for (size_t i = 0; i < sizeof(cases)/sizeof(cases[0]); ++i) {
        uint64_t r = factorial(cases[i].n);
        if (r != cases[i].expect) {
            fprintf(stderr, "Test failed: %d -> %ld (expected %ld)\n", cases[i].n, r, cases[i].expect);
            failed = true;
        }
    }

    if (!failed) {
        fprintf(stderr, "All tests passed.\n");
        return 0;
    } else {
        return 1;
    }
}
