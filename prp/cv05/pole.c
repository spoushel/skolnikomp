// pole je vlastne jen pointer
// vsechny adresy jsou stejny 

#include <stdio.h>

int main(void) {
    char c = 10;    // Definice proměnné c typu char
    int x = 10;     // Definice proměnné x typu int
    int *px = &x;   // Definice proměnné px typu ukazatel na proměnnou typu int
    char *pc = &c;  // Definice proměnné pc typu ukazatel na proměnnou typu char 
    printf("sizeof(c) = %ld (%ld)\n", sizeof(c), sizeof(char));  // Tisk paměťové velikosti proměnné c a typu char
    printf("sizeof(x) = %ld (%ld)\n", sizeof(x), sizeof(int));   // Tisk paměťové velikosti proměnné x a typu int
    printf("sizeof(px) = %ld (%ld)\n", sizeof(px), sizeof(int*)); // Tisk paměťové velikosti proměnné px a typu int*
    printf("sizeof(pc) = %ld (%ld)\n", sizeof(pc), sizeof(char*)); // Tisk paměťoé velikosti proměnné pc a typu char*
    printf("px: %p\n", px); // hodnota ukazatele px (adresa x)
    printf("pc: %p\n", pc); // hodnota ukazatele pc (adresa c)
    printf("(pc - px) = %ld\n", (pc - (char*)px)); // rozdíl adress 
    return 0;
}

/*
int main(void) {
    int x = 10;   // Celočíselná proměnná x
    int *px = &x; // Proměnná typu ukazatel na proměnnou typu int, inicializovaná na 
    printf("px = %p\n", px); // Tisk hodnoty ukazatele 
    printf("*px = %d\n", *px); // Tisk hodnoty uložené na adrese, kterou ukazatel obsahuje
    return 0;
} */
