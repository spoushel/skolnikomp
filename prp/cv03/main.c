#include <stdio.h>
#include <stdlib.h>

/*
int main(void)
{
    int ret = EXIT_SUCCESS;
    int i = 0;
    for (i = 1; i <= 10; i++) {
        printf("%d\n", i);
    }
    return ret;
}
*/

int main(void) {
    int ret = EXIT_SUCCESS;
    int i = 0;
    while (i <= 10) {
        ++i;
        printf("%d\n", i);
        if (i == 5) {
            break;
        }
    }
    return ret;
}
