#include <stdio.h>
#include <stdlib.h>

#define MIN -10000
#define MAX 10000
#define ERROR_RANGE 100

int nacti_cisla(int *count, int *sum, int *pos, int *neg, int *even, int *odd, int *max, int *min);
int checkni_cisla(int num);
int do_stats(int *count, int *sum, int *pos, int *neg, int *even, int *odd, int *max, int *min);

int main(void) {
    int count = 0, sum = 0, pos = 0, neg = 0;
    int even = 0, odd = 0, max = -10000, min = 10000;
    return do_stats(&count, &sum, &pos, &neg, &even, &odd, &max, &min); 
}

int nacti_cisla(int *count, int *sum, int *pos, int *neg, int *even, int *odd, int *max, int *min) {
    int num;
    int first = 1;

    while (scanf("%d", &num) == 1) {
        if (checkni_cisla(num) != 0) {
            printf("\nError: Vstup je mimo interval!\n");
            return ERROR_RANGE;
        }
        if (!first) printf(", ");
        printf("%d", num);
        first = 0;
        (*count)++;
        *sum += num;
        if (num > 0) (*pos)++;
        if (num < 0) (*neg)++;
        if (num % 2 == 0) (*even)++;
        else (*odd)++;
        if (num > *max) *max = num;
        if (num < *min) *min = num;
    }
    return 0;
}

int checkni_cisla(int num) {
    if (num < MIN || num > MAX) {
        return 1;
    } else {
        return 0;
    }
}

int do_stats(int *count, int *sum, int *pos, int *neg, int *even, int *odd, int *max, int *min) {
    int result = nacti_cisla(count, sum, pos, neg, even, odd, max, min);
    if (result != 0) {
        return result;
    }
    if (*count == 0) {
        printf("No numbers entered.\n");
        return 0;
    }
    printf("\nPocet cisel: %d\n", *count);
    printf("Pocet kladnych: %d\n", *pos);
    printf("Pocet zapornych: %d\n", *neg);
    printf("Procento kladnych: %.2f\n", (double)*pos/(*count)*100);
    printf("Procento zapornych: %.2f\n", (double)*neg/(*count)*100);
    printf("Pocet sudych: %d\n", *even);
    printf("Pocet lichych: %d\n", *odd);
    printf("Procento sudych: %.2f\n", (double)*even/(*count)*100);
    printf("Procento lichych: %.2f\n", (double)*odd/(*count)*100);
    printf("Prumer: %.2f\n", (double)*sum/(*count));
    printf("Maximum: %d\n", *max);
    printf("Minimum: %d\n", *min);
    return 0;
}
