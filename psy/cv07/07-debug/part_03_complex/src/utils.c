#include "utils.h"
#include <string.h>
#include <stdlib.h>

int compare_students_by_name(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    
    int last_cmp = strcmp(s1->last_name, s2->last_name);
    if (last_cmp != 0) return last_cmp;
    
    return strcmp(s1->first_name, s2->first_name);
}

int compare_students_by_id(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    return s1->id - s2->id;
}

int compare_students_by_gpa(const void* a, const void* b) {
    const Student* s1 = (const Student*)a;
    const Student* s2 = (const Student*)b;
    
    if (s1->gpa > s2->gpa) return -1;
    if (s1->gpa < s2->gpa) return 1;
    return 0;
}

int binary_search_student(StudentDB* db, int id) {
    if (!db || db->count == 0) return -1;
    
    int left = 0;
    int right = db->count - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (db->students[mid].id == id) {
            return mid;
        }
        if (db->students[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int validate_grade(int grade) {
    return grade >= 0 && grade <= 100;
}

int validate_id(int id) {
    return id > 0 && id < 1000000;
}

int validate_year(int year) {
    return year >= 1 && year <= 6;
}

char* trim_whitespace(char* str) {
    if (!str) return NULL;
    
    while (*str == ' ' || *str == '\t' || *str == '\n') str++;
    
    char* end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end = '\0';
        end--;
    }
    
    return str;
}

int get_student_year_category(int year) {
    if (year <= 2) {
        return 0;
    } else if (year <= 4) {
        return 1;
    } else {
        return 2;
    }
}
