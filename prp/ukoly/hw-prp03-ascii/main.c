#include <stdio.h>
#include <stdlib.h>

#define MIN 3
#define MAX 69
#define ERROR_VSTUP 100
#define ERROR_RANGE 101
#define ERROR_ODD 102

int nacti_checkni_cisla(int *sirka, int *vysk, int input);
int nakresli_domecek(int *sirka, int *vyska);
void nakresli_body(int *sirka, int *vyska);
void nakresli_strechu(int *sirka);

int main(void) {
    int vyska = 0, sirka = 0;
    int input = scanf("%d %d", &sirka, &vyska);
    int result = nacti_checkni_cisla(&sirka, &vyska, input);
    if (result != 0) {
        return result;
    } else {
        return nakresli_domecek(&sirka, &vyska);
    }
}

int nacti_checkni_cisla(int *sirka, int *vyska, int input) {
    if (input != 2) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return ERROR_VSTUP;
    }

    if (*sirka < MIN || *vyska > MAX || *sirka < MIN || *vyska < MIN) {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        return ERROR_RANGE;
    }
    if (*sirka % 2 == 0) {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        return ERROR_ODD;
    }
    return EXIT_SUCCESS;
}

int nakresli_domecek(int *sirka, int *vyska) {
    nakresli_strechu(sirka);
    nakresli_body(sirka, vyska);
    return 0;
}

void nakresli_body(int *sirka, int *vyska) {
    for (int i = 0; i < *sirka; ++i) {
        printf("X");
    }
    printf("\n");
    for (int i = 0; i < *vyska - 2; ++i) {
        printf("X");
        for (int i = 0; i < *sirka - 2; ++i) {
            printf(" ");
        }
        printf("X\n");
    }
    for (int i = 0; i < *sirka; ++i) {
        printf("X");
    }
    printf("\n"); 
}

void nakresli_strechu(int *sirka) {
    int roof_height = (*sirka + 1) / 2;
    for (int i = 0; i < (roof_height - 1); ++i) {
        int front_spaces = roof_height - 1 - i;
        int middle_spaces = (i == 0) ? 0 : 2 * i - 1;
        printf("%*s", front_spaces, "");
        printf("X");
        if (i > 0) {
            printf("%*s", middle_spaces, "");
            printf("X");
        }
        printf("\n");
    }

}

