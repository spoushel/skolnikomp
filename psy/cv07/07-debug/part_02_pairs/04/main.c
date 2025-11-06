// Task 04
//
// Očekávaný výstup:
// ```
// Found: Bob with score 92.0
// Not found
// ```
//
// Zjistěte, jaký je skutečný výstup programu a proč tomu tak je.

#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double score;
} Student;

int find_student(Student students[], int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return i;
        }
    }
}

int main() {
    Student class[] = {
        {101, "Alice", 85.5},
        {102, "Bob", 92.0},
        {103, "Charlie", 78.5},
        {104, "Diana", 95.0},
        {105, "Eve", 88.0}
    };
    
    int idx = find_student(class, 5, "Bob");
    if (idx >= 0) {
        printf("Found: %s with score %.1f\n", 
               class[idx].name, class[idx].score);
    }
    
    idx = find_student(class, 5, "Frank");
    if (idx >= 0) {
        printf("Found: %s with score %.1f\n", 
               class[idx].name, class[idx].score);
    }
    
    return 0;
}
