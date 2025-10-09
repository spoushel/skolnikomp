#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int ret = EXIT_SUCCESS;
    int num;
    scanf("%d", &num);
    int i;
    for (i = 0; i < num + 1; i++) {
        if (i % 2 == 0 ) {
            printf("%d\n", i);
        } else {
            continue;
        }
    }
    
    return ret;
}

// shuf -i1-99 -n 10 > in.txt