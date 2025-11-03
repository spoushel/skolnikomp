#include <stdio.h>
#include <stdlib.h>

void write(char *arr);
char* make_arr(void);

int main() {
    printf("\n");
    char* pole = make_arr();
    write(pole);
    free(pole);

    // 1 nacist vstup na 20 znaku getchar
    // 2 vypsat pole znaku
    // 3 izolovat vypis znaku do funkce
    // 4 izolovagt uzivatelske nacteni a vytvoreni pole
    return 0;
}

void write(char *arr) {
    printf("%s\n", arr);
}

char* make_arr(void) {
    int arrayLength = 20;
    char* arr = (char *) malloc(arrayLength * sizeof(char));
    if (arr == NULL) {
        printf("Error allocation memory.");
        exit(1);
    }
    int i = 0;
    for (int ch; (ch = getchar()) != EOF; ++i) {
        if (i > arrayLength - 1) {
            char* list = realloc(ch, arrayLength * 2);
        }
        arr[i] = (char)ch;
    }
    arr[i] = '\0';
    write(arr);
    return arr;
}

//promenna na stacku ma omezenou zivotnost, chceme heap
//valgrind pozoruje program a praci s pameti
