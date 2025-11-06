#include "stats.h"
#include "grades.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

Statistics* calculate_statistics(StudentDB* db) {
    if (!db || db->count == 0) return NULL;
    
    Statistics* stats = malloc(sizeof(Statistics));
    if (!stats) return NULL;
    
    stats->mean = calculate_class_average(db);
    stats->std_dev = calculate_std_deviation(db);
    
    stats->min = 100;
    stats->max = 0;
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        for (int j = 0; j < s->grade_count; j++) {
            if (s->grades[j] < stats->min) stats->min = s->grades[j];
            if (s->grades[j] > stats->max) stats->max = s->grades[j];
        }
    }
    
    generate_histogram(db, stats->histogram, GRADE_HISTOGRAM_BINS);
    
    return stats;
}

double calculate_class_average(StudentDB* db) {
    if (!db || db->count == 0) return 0.0;
    
    double sum = 0.0;
    int total_grades = 0;
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        for (int j = 0; j < s->grade_count; j++) {
            sum += s->grades[j];
            total_grades++;
        }
    }
    
    return total_grades > 0 ? sum / total_grades : 0.0;
}

double calculate_std_deviation(StudentDB* db) {
    if (!db || db->count == 0) return 0.0;
    
    double mean = calculate_class_average(db);
    double sum_squared_diff;
    int total_grades = 0;
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        for (int j = 0; j < s->grade_count; j++) {
            double diff = s->grades[j] - mean;
            sum_squared_diff += diff * diff;
            total_grades++;
        }
    }
    
    if (total_grades <= 1) return 0.0;
    
    return sqrt(sum_squared_diff / total_grades);
}

void generate_histogram(StudentDB* db, int* histogram, int bins) {
    if (!db || !histogram || bins <= 0) return;
    
    for (int i = 0; i < bins; i++) {
        histogram[i] = 0;
    }
    
    for (int i = 0; i < db->count; i++) {
        Student* s = &db->students[i];
        int distribution[GRADE_HISTOGRAM_BINS] = {0};
        calculate_grade_distribution(s, distribution, bins);
        for (int j = 0; j < bins; j++) {
            histogram[j] += distribution[j];
        }
    }
}

int count_passing(StudentDB* db, int pass_grade) {
    if (!db) return 0;
    
    int passing = 0;
    for (int i = 0; i < db->count; i++) {
        double avg = get_average(&db->students[i]);
        if (avg >= pass_grade) {
            passing++;
        }
    }
    return passing;
}

int count_failing(StudentDB* db, int pass_grade) {
    if (!db) return 0;
    
    int failing = 0;
    for (int i = 0; i < db->count; i++) {
        double avg = get_average(&db->students[i]);
        if (avg < pass_grade) {
            failing++;
        }
    }
    return failing;
}
