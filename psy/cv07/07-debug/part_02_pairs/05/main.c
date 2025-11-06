// Task 05
//
// Ověřte funkčnost binárního vyhledávání.
//
// Princip binárního vyhledávání je následující:
// 1. Najděte prostřední prvek seřazeného pole.
// 2. Pokud je tento prvek cílová hodnota, vraťte jeho index.
// 3. Pokud je cílová hodnota menší než prostřední prvek,
//   opakujte hledání v levé polovině pole.
// 4. Pokud je cílová hodnota větší než prostřední prvek,
//   opakujte hledání v pravé polovině pole.
//


#include <stdio.h>

int binary_search_recursive(int arr[], int target, int left, int right) {
    if (left > right) {
        return -1;
    }
    
    int mid = (left + right) / 2;
    
    if (arr[mid] == target) {
        return mid;
    }
    
    if (arr[mid] > target) {
        return binary_search_recursive(arr, target, left, mid);
    } else {
        return binary_search_recursive(arr, target, mid, right);
    }
}

int main() {
    int sorted[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int size = 11;
    
    printf("Searching in: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n\n");
    
    int tests[] = {2, 23, 67, 99, 8, 45};
    int expected[] = {0, 5, 9, -1, 2, 7};
    
    for (int i = 0; i < 6; i++) {
        int result = binary_search_recursive(sorted, tests[i], 0, size - 1);
        printf("Search %d: found at index %d (expected: %d) %s\n", 
               tests[i], result, expected[i],
               result == expected[i] ? "✓" : "✗");
    }
    
    return 0;
}
