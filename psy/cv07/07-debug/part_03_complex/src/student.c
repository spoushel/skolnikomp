#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StudentDB* db_create(void) {
    StudentDB* db = malloc(sizeof(StudentDB));
    if (!db) return NULL;
    
    db->capacity = 10;
    db->count = 0;
    db->students = calloc(db->capacity, sizeof(Student));
    if (!db->students) {
        free(db);
        return NULL;
    }
    
    for (int i = 0; i < db->capacity; i++) {
        db->students[i].grades = NULL;
        db->students[i].course_ids = NULL;
        db->students[i].grade_count = 0;
        db->students[i].grade_capacity = 0;
    }
    
    return db;
}

int db_add_student(StudentDB* db, int id, const char* first, const char* last, int year) {
    if (!db || !first || !last) return 0;
    
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) return 0;
    }
    
    if (db->count >= db->capacity) {
        int new_capacity = db->capacity * 2;
        Student* new_students = realloc(db->students, 
                                       new_capacity * sizeof(Student));
        if (!new_students) return 0;
        
        db->students = new_students;
        for (int i = db->capacity; i < new_capacity; i++) {
            db->students[i].grades = NULL;
            db->students[i].course_ids = NULL;
            db->students[i].grade_count = 0;
            db->students[i].grade_capacity = 0;
        }
        db->capacity = new_capacity;
    }
    
    int insert_index = db->count;
    while (insert_index > 0 && db->students[insert_index - 1].id > id) {
        insert_index--;
    }

    if (insert_index < db->count) {
        memmove(&db->students[insert_index + 1],
                &db->students[insert_index],
                (db->count - insert_index) * sizeof(Student));
    }

    Student* s = &db->students[insert_index];
    s->id = id;
    s->year = year;
    s->gpa = 0.0;

    strcpy(s->first_name, first);
    strcpy(s->last_name, last);

    strcpy(s->full_name, s->first_name);
    strcat(s->full_name, " ");
    strcat(s->full_name, s->last_name);

    s->grades = NULL;
    s->course_ids = NULL;
    s->grade_count = 0;
    s->grade_capacity = 0;

    db->count++;
    return 1;
}

Student* db_find_student(StudentDB* db, int id) {
    if (!db) return NULL;
    
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            return &db->students[i];
        }
    }
    return NULL;
}

Student* db_find_by_name(StudentDB* db, const char* last_name) {
    if (!db || !last_name) return NULL;
    
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->students[i].last_name, last_name) == 0) {
            return &db->students[i];
        }
    }
    return NULL;
}

int db_remove_student(StudentDB* db, int id) {
    if (!db) return 0;
    
    int index = -1;
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return 0;
    
    Student* s = &db->students[index];
    free(s->grades);
    free(s->course_ids);
    
    for (int i = index; i < db->count - 1; i++) {
        db->students[i] = db->students[i + 1];
    }
    
    db->count--;
    return 1;
}

void db_update_full_names(StudentDB* db) {
    if (!db) return;
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        strcpy(s->full_name, s->first_name);
        strcat(s->full_name, " ");
        strcat(s->full_name, s->last_name);
    }
}

void db_calculate_gpas(StudentDB* db) {
    if (!db) return;
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        if (s->grade_count == 0) {
            s->gpa = 0.0;
            continue;
        }
        
        double sum = 0.0;
        for (int j = 0; j < s->grade_count; j++) {
            sum += s->grades[j];
        }
        s->gpa = sum / s->grade_count;
    }
}

void db_destroy(StudentDB* db) {
    if (!db) return;
    
    for (int i = 0; i < db->count; i++) {
        free(db->students[i].grades);
        free(db->students[i].course_ids);
    }
    free(db->students);
    free(db);
}

void db_print(StudentDB* db) {
    if (!db) return;
    
    printf("\n=== Student Database (%d students) ===\n", db->count);
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        printf("[%03d] %s (Year %d, GPA: %.2f)\n", 
               s->id, s->full_name, s->year, s->gpa);
    }
    printf("\n");
}
