#ifndef STATS_H
#define STATS_H

#include "student.h"

typedef struct {
    double mean;
    double median;
    double std_dev;
    int min;
    int max;
    int histogram[GRADE_HISTOGRAM_BINS];
} Statistics;

Statistics* calculate_statistics(StudentDB* db);
double calculate_class_average(StudentDB* db);
double calculate_std_deviation(StudentDB* db);
void generate_histogram(StudentDB* db, int* histogram, int bins);
int count_passing(StudentDB* db, int pass_grade);
int count_failing(StudentDB* db, int pass_grade);

#endif
