#ifndef GRADES_H
#define GRADES_H

#include "student.h"
#include "course.h"

int add_grade(Student* student, int course_id, int grade);
double get_average(Student* student);
double get_weighted_average(Student* student, CourseList* courses);
int get_best_grade(Student* student);
int get_worst_grade(Student* student);
void calculate_grade_distribution(Student* student, int* distribution, int bins);

#endif
