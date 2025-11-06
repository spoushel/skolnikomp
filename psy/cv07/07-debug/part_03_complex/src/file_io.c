#include "file_io.h"
#include "grades.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_students(StudentDB* db, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    
    char line[256];
    int in_grades_section = 0;
    
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline
        
        if (strcmp(line, "GRADES") == 0) {
            in_grades_section = 1;
            continue;
        }
        
        if (strcmp(line, "END") == 0) {
            break;
        }
        
        if (!in_grades_section) {
            // Parse student line
            int id, year;
            char first[MAX_NAME_LEN], last[MAX_NAME_LEN];
            
            // Use field width to prevent buffer overflow
            if (sscanf(line, "%d %49s %49s %d", &id, first, last, &year) == 4) {
                db_add_student(db, id, first, last, year);
            }
        } else {
            // Parse grade line
            int student_id, course_id, grade;
            if (sscanf(line, "%d %d %d", &student_id, &course_id, &grade) == 3) {
                Student* s = db_find_student(db, student_id);
                if (s) {
                    add_grade(s, course_id, grade);
                }
            }
        }
    }
    
    fclose(f);
    return 1;
}

int save_students(StudentDB* db, const char* filename) {
    if (!db) return 0;
    
    FILE* f = fopen(filename, "w");
    if (!f) return 0;
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        fprintf(f, "%d %s %s %d\n", 
                s->id, s->first_name, s->last_name, s->year);
        
        fprintf(f, "%d\n", s->grade_count);
        for (int j = 0; j < s->grade_count; j++) {
            fprintf(f, "%d %d\n", s->course_ids[j], s->grades[j]);
        }
    }
    
    fclose(f);
    return 1;
}

int export_report(StudentDB* db, CourseList* courses, const char* filename) {
    if (!db || !courses) return 0;
    
    FILE* f = fopen(filename, "w");
    if (!f) return 0;
    
    fprintf(f, "=== Grade Report ===\n");
    fprintf(f, "Total Students: %d\n", db->count);
    fprintf(f, "Total Courses: %d\n\n", courses->count);
    
    double overall_avg = calculate_class_average(db);
    fprintf(f, "Overall Class Average: %.2f\n", overall_avg);
    fprintf(f, "Passing Students: %d\n", count_passing(db, 60));
    fprintf(f, "Failing Students: %d\n\n", count_failing(db, 60));
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        fprintf(f, "Student: %s (ID: %d, Year: %d)\n", 
                s->full_name, s->id, s->year);
        fprintf(f, "  GPA: %.2f\n", s->gpa);
        fprintf(f, "  Best Grade: %d\n", get_best_grade(s));
        fprintf(f, "  Worst Grade: %d\n\n", get_worst_grade(s));
    }
    
    fclose(f);
    return 1;
}
