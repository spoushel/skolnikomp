#include <stdio.h>
#include <stdlib.h>

#define N 10
#define MIN 0
#define MAX 99

void init_rand(int n, int *array);
void print_array(int n, int *array);

int main(void) {
    int array[N]; 
    init_rand(N, *array);
    print_array(N, *array);
    return 0;
}

void init_rand(N, int *array) {
    for (int i = 0; i < N; ++i) {
        array[i] = rand() % MAX; 
    }
}

void print_array(N, int *array) {
    for (int i = 0; i < N; ++i) {
        printf("Array adress %p\n", array);
        printf("array %d\n", i);
    }
}