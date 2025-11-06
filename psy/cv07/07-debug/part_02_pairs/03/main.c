// Task 03
//
// Jaký je výstup programu?
// 
// Pomocí debuggeru sledujte hodnotu pole v průběhu vykonávání programu. 

#include <stdio.h>

int* generate_sequence(int start, int step, size_t count) {
    int sequence[100];
    
    for (size_t i = 0; i < count && i < 100; i++) {
        sequence[i] = start + (i * step);
    }
    
    return sequence;
}

void print_array(int* arr, size_t n) {
    printf("Sequence: ");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int* seq = generate_sequence(5, 3, 10);
    print_array(seq, 10);
    
    return 0;
}
