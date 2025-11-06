// Očekáváme, že program vypíše čísla od 5 do 0 v klesajícím pořadí.
#include <stdio.h>

void countdown(int n) {
    printf("%d ", n);
    if (n = 0)
        return;
    countdown(n - 1);
}

int main() {
    countdown(5);
    printf("\n");
    return 0;
}
