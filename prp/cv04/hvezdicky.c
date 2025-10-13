#include <stdio.h>
#include <stdlib.h>

#define ERR_INPUT 101
#define ERR_RANGE 102
#define MIN 1
#define MAX 10

//furt to nefunguje wtf

void print_line(int n);
int print_triangle(int n);
int check_read_input(int *n);

int main(void)
{
    int n;
    int ret;
    ret = check_read_input(&n);
    if (ret == EXIT_SUCCESS) {
        print_triangle(n);
    }
    return ret;
}

int check_read_input(int *n) {
    
    int result = scanf("%d", n);

    if (result != 1){
        return ERR_INPUT;
    }
    if (*n > MAX || *n < MIN) {
        return ERR_RANGE;
    }

    return EXIT_SUCCESS;
}

void print_line(int n) {
    for (int i = 0; i < n; ++i){
            printf("*");
        }
        printf("\n");
}

int print_triangle(int n) {
    for (int i = 0; i < n; ++i) {
        print_line(n-i);
    }
    return 0;
}
