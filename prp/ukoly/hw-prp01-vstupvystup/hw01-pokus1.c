#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MIN_VALUE -10000
#define MAX_VALUE 10000
#define ERROR_RANGE_EOF 100
#define ERROR_DIVISION_ZERO 101

int load_input(int *num1, int *num2);
int do_calc(void);

int main(void) {
    return do_calc();
}

int load_input(int *num1, int *num2) {
    const int min = MIN_VALUE, max = MAX_VALUE;
    int nums = scanf("%d %d", num1, num2);

    if (nums != 2) {
                fprintf(stderr, "Chyba nacitani vstupu!\n");
        return EXIT_FAILURE;
    }
 
    if (*num1 < min || *num1 > max || *num2 < min || *num2 > max) {
        fprintf(stderr, "Error: Vstup je mimo interval!\n");
        return ERROR_RANGE_EOF;
    }   
    int ch = 0;
    while ((ch = getchar()) != '\n') {
        if (ch == '.') {
            fprintf(stderr, "Chyba nacitani vstupu!\n");
            return EXIT_FAILURE;
        }
    }
    if (ch == EOF) {
        fprintf(stderr, "Chyba nacitani vstupu!\n");
        return ERROR_RANGE_EOF;
    }
    return EXIT_SUCCESS;
}

int do_calc(void) {
    int num1, num2;
    int input = load_input(&num1, &num2);
    
    if (input != EXIT_SUCCESS) {
        return input;
    }

    int soucet = num1 + num2;
    int rozdil = num1 - num2;
    int soucin = num1 * num2;
    double prumer = (double)(num1 + num2) / 2;

    printf("Desitkova soustava: %d %d\n", num1, num2);
    printf("Sestnactkova soustava: %x %x\n", num1, num2);
    printf("Soucet: %d + %d = %d\n", num1, num2, soucet);
    printf("Rozdil: %d - %d = %d\n", num1, num2, rozdil);
    printf("Soucin: %d * %d = %d\n", num1, num2, soucin);
    
    if (num2 == 0) {
        fprintf(stderr, "Error: Nedefinovany vysledek!\n");
        printf("Podil: %d / %d = NaN\n", num1, num2);
    } else {
        double podil = (double)num1 / num2;
        printf("Podil: %d / %d = %d\n", num1, num2, (int)podil);
    }
    printf("Prumer: %.1f\n", prumer);

    if (num2 == 0) {
        return ERROR_DIVISION_ZERO;
    }
    return EXIT_SUCCESS;
}