#include "grades.h"
#include <stdlib.h>
#include <string.h>

int add_grade(Student* student, int course_id, int grade) {
    if (!student || grade < 0 || grade > 100) return 0;
    
    if (student->grade_count >= student->grade_capacity) {
        int new_capacity = student->grade_capacity == 0 ? 4 : 
                          student->grade_capacity * 2;
        
        int* new_grades = realloc(student->grades, 
                                 new_capacity * sizeof(int));
        if (!new_grades) return 0;
        
        int* new_courses = realloc(student->course_ids,
                                  new_capacity * sizeof(int));
        if (!new_courses) {
            student->grades = new_grades;
            return 0;
        }
        
        student->grades = new_grades;
        student->course_ids = new_courses;
        student->grade_capacity = new_capacity;
    }
    
    student->grades[student->grade_count] = grade;
    student->course_ids[student->grade_count] = course_id;
    student->grade_count++;
    return 1;
}

double get_average(Student* student) {
    if (!student || student->grade_count == 0) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < student->grade_count; i++) {
        sum += student->grades[i];
    }
    
    return sum / student->grade_count;
}

double get_weighted_average(Student* student, CourseList* courses) {
    if (!student || !courses || student->grade_count == 0) return 0.0;
    
    double weighted_sum = 0.0;
    int total_credits = 0;
    
    for (int i = 0; i < student->grade_count; i++) {
        // Find the course corresponding to this grade
        int course_id = student->course_ids[i];
        Course* course = courses->head;
        int course_num = 1;
        
        // Navigate to the correct course
        while (course && course_num < course_id) {
            course = course->next;
            course_num++;
        }
        
        if (course) {
            weighted_sum += student->grades[i] * course->credits;
            total_credits += course->credits;
        }
    }
    
    return total_credits > 0 ? weighted_sum / total_credits : 0.0;
}

int get_best_grade(Student* student) {
    if (!student || student->grade_count == 0) return -1;
    
    int best = student->grades[0];
    for (int i = 1; i < student->grade_count; i++) {
        if (student->grades[i] > best) {
            best = student->grades[i];
        }
    }
    return best;
}

int get_worst_grade(Student* student) {
    if (!student || student->grade_count == 0) return -1;
    
    int worst = student->grades[0];
    for (int i = 1; i < student->grade_count; i++) {
        if (student->grades[i] < worst) {
            worst = student->grades[i];
        }
    }
    return worst;
}

void calculate_grade_distribution(Student* student, int* distribution, int bins) {
    if (!student || !distribution || bins <= 0) return;
    
    memset(distribution, 0, bins * sizeof(int));
    
    for (int i = 0; i < student->grade_count; i++) {
        int bin = student->grades[i] * bins / 100;
        distribution[bin]++;
    }
}
