#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CourseList* course_list_create(void) {
    CourseList* list = malloc(sizeof(CourseList));
    if (!list) return NULL;
    
    list->head = NULL;
    list->count = 0;
    return list;
}

Course* course_add(CourseList* list, const char* code, const char* name, int credits) {
    if (!list || !code || !name) return NULL;
    
    Course* existing = course_find(list, code);
    if (existing) return existing;
    
    Course* course = malloc(sizeof(Course));
    if (!course) return NULL;
    
    strncpy(course->code, code, MAX_COURSE_CODE_LEN - 1);
    course->code[MAX_COURSE_CODE_LEN - 1] = '\0';
    
    course->name = malloc(strlen(name) + 1);
    if (!course->name) {
        free(course);
        return NULL;
    }
    strcpy(course->name, name);
    
    course->capacity = 20;
    course->enrolled_students = malloc(course->capacity * sizeof(int));
    if (!course->enrolled_students) {
        free(course);
        return NULL;
    }
    
    course->enrolled_count = 0;
    course->credits = credits;
    course->next = list->head;
    list->head = course;
    list->count++;
    
    return course;
}

int course_enroll_student(Course* course, int student_id) {
    if (!course || student_id <= 0) return 0;
    
    if (course->enrolled_count >= course->capacity) {
        int new_capacity = course->capacity * 2;
        int* new_array = realloc(course->enrolled_students, 
                                new_capacity * sizeof(int));
        if (!new_array) return 0;
        course->enrolled_students = new_array;
        course->capacity = new_capacity;
    }
    
    course->enrolled_students[course->enrolled_count++] = student_id;
    return 1;
}

Course* course_find(CourseList* list, const char* code) {
    if (!list || !code) return NULL;
    
    Course* current = list->head;
    while (current) {
        if (strcmp(current->code, code) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void course_list_destroy(CourseList* list) {
    if (!list) return;
    
    Course* current = list->head;
    while (current) {
        Course* next = current->next;
        free(current->enrolled_students);
        free(current);
        current = next;
    }
    free(list);
}

void course_print_roster(Course* course, StudentDB* db) {
    if (!course || !db) return;
    
    printf("\n=== %s (%s) - %d credits ===\n", 
           course->name, course->code, course->credits);
    printf("Enrolled: %d students\n", course->enrolled_count);
    
    for (int i = 0; i < course->enrolled_count; i++) {
        Student* s = db_find_student(db, course->enrolled_students[i]);
        if (s) {
            printf("  - %s (ID: %d)\n", s->full_name, s->id);
        }
    }
}
