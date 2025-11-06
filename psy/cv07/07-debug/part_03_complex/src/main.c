#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "student.h"
#include "course.h"
#include "grades.h"
#include "stats.h"
#include "file_io.h"
#include "utils.h"

void print_menu() {
    printf("\n=== Systém správy studentských známek ===\n");
    printf("1. Načíst studenty ze souboru\n");
    printf("2. Přidat nového studenta\n");
    printf("3. Odebrat studenta\n");
    printf("4. Přidat kurz\n");
    printf("5. Zapsat studenta do kurzu\n");
    printf("6. Přidat známku\n");
    printf("7. Najít studenta (binary search)\n");
    printf("8. Zobrazit všechny studenty\n");
    printf("9. Zobrazit seznam kurzu\n");
    printf("10. Vypočítat statistiky\n");
    printf("11. Exportovat report\n");
    printf("12. Uložit a ukončit\n");
    printf("Volba: ");
}

int main() {
    StudentDB* db = db_create();
    CourseList* courses = course_list_create();
    
    if (!db || !courses) {
        fprintf(stderr, "Failed to initialize system\n");
        return 1;
    }
    
    course_add(courses, "B0B36PSY", "Programování v C/C++", 6);
    course_add(courses, "B0B36PRP", "Procedurální programování", 6);
    course_add(courses, "B0B01LAG", "Lineární algebra", 7);
    
    bool running = true;
    while (running) {
        print_menu();
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1: {
                printf("Enter filename: ");

                char filename[100];
                if (fgets(filename, sizeof(filename), stdin)) {
                    char *newline = strchr(filename, '\n');
                    if (newline) *newline = '\0';
                    
                    if (load_students(db, filename)) {
                        printf("Students loaded successfully\n");
                    } else {
                        printf("Failed to load students\n");
                    }
                }
                break;
            }
            
            case 2: {
                int id, year;
                char first[256], last[256];
                printf("Enter student ID: ");
                scanf("%d", &id);
                getchar();
                
                printf("Enter first name: ");
                fgets(first, sizeof(first), stdin);
                char *newline = strchr(first, '\n');
                if (newline) *newline = '\0';
                
                printf("Enter last name: ");
                fgets(last, sizeof(last), stdin);
                newline = strchr(last, '\n');
                if (newline) *newline = '\0';
                
                printf("Enter year: ");
                scanf("%d", &year);
                
                if (db_add_student(db, id, first, last, year)) {
                    printf("Student added successfully\n");
                } else {
                    printf("Failed to add student\n");
                }
                break;
            }
            
            case 3: {
                int id;
                printf("Enter student ID to remove: ");
                scanf("%d", &id);
                
                if (db_remove_student(db, id)) {
                    printf("Student removed successfully\n");
                } else {
                    printf("Failed to remove student\n");
                }
                break;
            }
            
            case 4: {
                char code[MAX_COURSE_CODE_LEN];
                char name[100];
                int credits;
                printf("Enter course code: ");
                fgets(code, MAX_COURSE_CODE_LEN, stdin);
                char *newline = strchr(code, '\n');
                if (newline) *newline = '\0';
                
                printf("Enter course name: ");
                fgets(name, 100, stdin);
                newline = strchr(name, '\n');
                if (newline) *newline = '\0';
                
                printf("Enter credits: ");
                scanf("%d", &credits);
                
                if (course_add(courses, code, name, credits)) {
                    printf("Course added successfully\n");
                } else {
                    printf("Failed to add course\n");
                }
                break;
            }
            
            case 5: {
                int student_id, course_id;
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                printf("Enter course ID (1-3): ");
                scanf("%d", &course_id);
                
                Course* course = courses->head;
                for (int i = 1; i < course_id && course; i++) {
                    course = course->next;
                }
                
                if (course && course_enroll_student(course, student_id)) {
                    printf("Student enrolled successfully\n");
                } else {
                    printf("Failed to enroll student\n");
                }
                break;
            }
            
            case 6: {
                int id, course_id, grade;
                printf("Enter student ID: ");
                scanf("%d", &id);
                printf("Enter course ID: ");
                scanf("%d", &course_id);
                printf("Enter grade: ");
                scanf("%d", &grade);
                
                Student* s = db_find_student(db, id);
                if (s && add_grade(s, course_id, grade)) {
                    printf("Grade added successfully\n");
                } else {
                    printf("Failed to add grade\n");
                }
                break;
            }
            
            case 7: {
                int search_id;
                printf("Enter student ID to search: ");
                scanf("%d", &search_id);
                
                int index = binary_search_student(db, search_id);
                if (index >= 0) {
                    Student* s = &db->students[index];
                    printf("Found: %s (ID: %d, Year: %d, GPA: %.2f)\n",
                           s->full_name, s->id, s->year, s->gpa);
                } else {
                    printf("Student with ID %d not found.\n", search_id);
                }
                break;
            }
            
            case 8:
                db_calculate_gpas(db);
                db_print(db);
                break;
            
            case 9: {
                Course* c = courses->head;
                int i = 1;
                while (c) {
                    printf("\nCourse %d:\n", i++);
                    course_print_roster(c, db);
                    c = c->next;
                }
                break;
            }
            
            case 10: {
                Statistics* stats = calculate_statistics(db);
                if (stats) {
                    printf("\n=== Statistics ===\n");
                    printf("Class Average: %.2f\n", stats->mean);
                    printf("Standard Deviation: %.2f\n", stats->std_dev);
                    printf("Min Grade: %d\n", stats->min);
                    printf("Max Grade: %d\n", stats->max);
                    printf("\nGrade Distribution:\n");
                    for (int i = 0; i < GRADE_HISTOGRAM_BINS; i++) {
                        if (i == GRADE_HISTOGRAM_BINS - 1) {
                            printf("[ 100]: %d\n", stats->histogram[i]);
                        } else {
                            printf("[%2d-%2d]: %d\n", i * 10, (i + 1) * 10 - 1, stats->histogram[i]);
                        }
                    }
                    free(stats);
                } else {
                    printf("No data available for statistics.\n");
                }
                break;
            }
            
            case 11: {
                printf("Enter output filename: ");
                char filename[100];
                if (fgets(filename, sizeof(filename), stdin)) {
                    char *newline = strchr(filename, '\n');
                    if (newline) *newline = '\0';
                    
                    if (export_report(db, courses, filename)) {
                        printf("Report exported successfully\n");
                    } else {
                        printf("Failed to export report\n");
                    }
                }
                break;
            }
            
            case 12:
                running = false;
                break;
            
            default:
                printf("Not implemented yet\n");
        }
    }
    
    db_destroy(db);
    course_list_destroy(courses);
    
    return 0;
}
