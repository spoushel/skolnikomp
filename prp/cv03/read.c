#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int ret = EXIT_SUCCESS;
    int input;
    input = scanf("%d");
    int i = 0;
    for (i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
    return ret;
}

