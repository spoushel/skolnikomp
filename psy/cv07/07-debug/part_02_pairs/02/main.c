// Task 02
//
// Nalezněte chybu v logice obrácení pole.
//
// Odkrokujte program pomocí debuggeru a zjistěte, proč nefunguje správně.

#include <stdio.h>

void reverse_array(int arr[], int size) {
    int temp;
    for (int i = 0; i <= size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void print_array(const char* label, int arr[], int size) {
    printf("%s: ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int even[] = {1, 2, 3, 4, 5, 6};
    print_array("Original even", even, 6);
    reverse_array(even, 6);
    print_array("Reversed even", even, 6);
    
    printf("\n");
    
    int odd[] = {10, 20, 30, 40, 50};
    print_array("Original odd", odd, 5);
    reverse_array(odd, 5);
    print_array("Reversed odd", odd, 5);
    
    return 0;
}
