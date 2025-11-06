/*
 * Task 06
 * 
 * Nalezněte všechny memory leaky.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* name;
    double* grades;
    int grade_count;
} StudentRecord;

StudentRecord* create_student(int id, const char* name) {
    StudentRecord* student = malloc(sizeof(StudentRecord));
    student->id = id;
    student->name = malloc(strlen(name) + 1);
    strcpy(student->name, name);
    student->grades = NULL;
    student->grade_count = 0;
    return student;
}

void add_grade(StudentRecord* student, double grade) {
    double* new_grades = malloc((student->grade_count + 1) * sizeof(double));
    
    for (int i = 0; i < student->grade_count; i++) {
        new_grades[i] = student->grades[i];
    }
    
    new_grades[student->grade_count] = grade;
    
    student->grades = new_grades;
    student->grade_count++;
}

void free_student(StudentRecord* student) {
    if (student == NULL) return;
    
    free(student->name);
    free(student->grades);
    free(student);
}

int main() {
    StudentRecord* student = create_student(101, "Alice");
    
    for (int i = 0; i < 5; i++) {
        add_grade(student, 85.0 + i);
    }
    
    printf("Student %s has %d grades\n", student->name, student->grade_count);
    
    free_student(student);
    return 0;
}
