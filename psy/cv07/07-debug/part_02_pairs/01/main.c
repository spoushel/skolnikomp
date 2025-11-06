// Task 01
//
// Program má za úkol spočítat statistiky (počet, součet a průměr) z pole celých čísel.
// Zkontrolujte, že program dává očekávané výsledky pro všechny metriky.
//
// Použijte debugger pro odkrokování výpočtu.


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint32_t count;
    double sum;
    double average;
} Statistics;

Statistics calculate_stats(int data[], size_t n) {
    Statistics stats;
    stats.count = n;
    stats.sum = 0.0;

    for (size_t i = 0; i < n; i++) {
        stats.sum += data[i];
    }
    
    if (stats.sum > 0) {
        stats.average = stats.sum / stats.count;
    } else {
        stats.average = 0;
    }
    
    return stats;
}

int main() {
    int positive[] = {10, 20, 30};
    size_t positive_size = 3;

    Statistics s1 = calculate_stats(positive, positive_size);
    printf("Positive: count=%u, sum=%.2f, avg=%.2f\n", s1.count, s1.sum, s1.average);
    
    int negative[] = {-5, -10, -15};
    size_t negative_size = 3;

    Statistics s2 = calculate_stats(negative, negative_size);
    printf("Negative: count=%u, sum=%.2f, avg=%.2f\n", s2.count, s2.sum, s2.average);
    
    return 0;
}
