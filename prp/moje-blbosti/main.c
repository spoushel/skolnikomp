#include <stdio.h>
#include <stdlib.h>

int main() {

    
}


int random() {
    int i = 5, j = 5, k;
    printf("start: i je %d\n", i);
    i++;
    printf("i je %d\n", i);
    j = ++i;
    printf("j je %d\n", j);
    j = i++;
    printf("j je %d\n", j);
    k = --j + 2;
    printf("k je %d\n", k);
    return EXIT_SUCCESS;
}
