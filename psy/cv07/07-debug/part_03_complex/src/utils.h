#ifndef UTILS_H
#define UTILS_H

#include "student.h"

int compare_students_by_name(const void* a, const void* b);
int compare_students_by_id(const void* a, const void* b);
int compare_students_by_gpa(const void* a, const void* b);
int binary_search_student(StudentDB* db, int id);
int validate_grade(int grade);
int validate_id(int id);
int validate_year(int year);
char* trim_whitespace(char* str);
int get_student_year_category(int year);

#endif
