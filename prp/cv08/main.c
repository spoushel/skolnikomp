#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INIT_CAPACITY //muzu nastavit pri kompilaci ale fallback je 4, "if not defined init..."
#define INIT_CAPACITY 4
#endif

#ifndef INIT_SIZE
#define INIT_SIZE 64
#endif

typedef struct lines {
    int n; //pocet radku
    char **lines; //pole ukazatelu na retezce
    int capacity;
} lines;

struct lines* init(int capacity); //lol i give up :3
void clean(struct lines *lines) {
    if (lines != NULL) {
        for (int i = 0; i < lines ->n; ++i) {

        }
        free(lines->lines);
}

}

char *read_line(void); //permut
char *arr_enlarge(char *str, int size) {
    char *tmp = realloc(str, size);
    if (!tmp) {
        fprintf(stderr, "chyba rip");
        exit(-1);
    }
}

int main(void) {

    int ret = EXIT_SUCCESS;
    struct lines lines = init(INIT_CAPACITY);
    char *l = NULL;
    while ((l = read_line())) {
        printf("%s\n", l);
        free(l);
    }
    free(l);
    return ret;

}

char *read_line(void) {
    int size = INIT_SIZE;
    char *str = calloc((size +1), sizeof *str); //muze byt sizeof *str , chlivek na 0 navic
    int n = 0; //kolik jsem nacetl znaku
    int r;
    while (str && (r = getchar()) != "\n" && r != EOF) { //\n nebude soucasti
        if (n == size){
            size += INIT_SIZE;
            str = arr_enlarge(str, size + 1); // dam tu zvetsenou
            arr_enlarge(str, size);
        }
        str[n++] = r;

    }
    if (str == NULL) {
        fprintf(stderr, "chyba twin");
        exit(-1);

    }
    str[n] = '\0';
    if (n == 0 && r == EOF) {

    }
}


//nacte vstup o neznamem poctu radku o nahodnem poctu znaku vypsat v nahodnem poradi
//funkce permute na promichani, pole pocet a pole cisel - funkce rand
/*
char* read_line(void) 
    getchar() az po \n
make_arr
    malloc() - fixni velikost
    enlarge() = realloc() 
store_lines
rand_lines - permutace
    rand() - random cislo
print_rlines
*/
//

/* MINULY CVIKA

void write(char *arr);
char* make_arr(void);


int main() {
    printf("\n");
    char* pole = make_arr();
    write(pole);
    free(pole);

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
*/