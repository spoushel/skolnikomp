#include "math_utils.h"

uint64_t factorial(uint32_t n) {
    uint64_t result = 1;
    for (uint32_t i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
