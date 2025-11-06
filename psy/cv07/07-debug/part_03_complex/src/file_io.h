#ifndef FILE_IO_H
#define FILE_IO_H

#include "student.h"
#include "course.h"

int load_students(StudentDB* db, const char* filename);
int save_students(StudentDB* db, const char* filename);
int export_report(StudentDB* db, CourseList* courses, const char* filename);

#endif
