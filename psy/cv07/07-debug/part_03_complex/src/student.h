#ifndef STUDENT_H
#define STUDENT_H

#include "config.h"

typedef struct {
    int id;
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    char full_name[MAX_NAME_LEN * 2];
    int* grades;
    int* course_ids;
    int grade_count;
    int grade_capacity;
    double gpa;
    int year;
} Student;

typedef struct {
    Student* students;
    int count;
    int capacity;
} StudentDB;

StudentDB* db_create(void);
int db_add_student(StudentDB* db, int id, const char* first, const char* last, int year);
int db_remove_student(StudentDB* db, int id);
Student* db_find_student(StudentDB* db, int id);
Student* db_find_by_name(StudentDB* db, const char* last_name);
void db_update_full_names(StudentDB* db);
void db_calculate_gpas(StudentDB* db);
void db_destroy(StudentDB* db);
void db_print(StudentDB* db);

#endif
