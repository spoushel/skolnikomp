#ifndef COURSE_H
#define COURSE_H

#include "config.h"
#include "student.h"

typedef struct Course {
    char code[MAX_COURSE_CODE_LEN];
    char* name;
    int* enrolled_students;
    int enrolled_count;
    int capacity;
    int credits;
    struct Course* next;
} Course;

typedef struct {
    Course* head;
    int count;
} CourseList;

CourseList* course_list_create(void);
Course* course_add(CourseList* list, const char* code, const char* name, int credits);
int course_enroll_student(Course* course, int student_id);
Course* course_find(CourseList* list, const char* code);
void course_list_destroy(CourseList* list);
void course_print_roster(Course* course, StudentDB* db);

#endif
