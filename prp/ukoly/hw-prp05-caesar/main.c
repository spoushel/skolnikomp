#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100
#define ERROR_LENGTH 101
#define INITIAL_LENGTH 50
#define SHIFT_NUM 52

char* arr_orig = NULL;
char* arr_noise = NULL; 
int arr_orig_size = INITIAL_LENGTH;
int arr_noise_size = INITIAL_LENGTH;
int current_length = 0;
int noise_length = 0;

void load_input(void);
int shift_letter(int shift, int letter);
void make_choose_options(void);

static int is_ascii_letter(int ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int main(void) {
    arr_orig = malloc(arr_orig_size * sizeof(char));
    arr_noise = malloc(arr_noise_size * sizeof(char));
    if (!arr_orig || !arr_noise) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        free(arr_orig);
        free(arr_noise);
        return ERROR_INPUT;
    }

    load_input();

    if (current_length != noise_length) {
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        free(arr_orig);
        free(arr_noise);
        return ERROR_LENGTH;
    }
    make_choose_options();

    free(arr_orig);
    free(arr_noise);
    return 0;
}

void load_input(void) {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (!is_ascii_letter(ch)) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(ERROR_INPUT);
        }
        if (current_length >= arr_orig_size) {
            arr_orig_size *= 2;
            char* tmp = realloc(arr_orig, arr_orig_size * sizeof(char));
            if (!tmp) {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(ERROR_INPUT);
            }
            arr_orig = tmp;
        }
        arr_orig[current_length++] = (char)ch;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (!is_ascii_letter(ch)) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(ERROR_INPUT);
        }
        if (noise_length >= arr_noise_size) {
            arr_noise_size *= 2;
            char* tmp = realloc(arr_noise, arr_noise_size * sizeof(char));
            if (!tmp) {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(ERROR_INPUT);
            }
            arr_noise = tmp;
        }
        arr_noise[noise_length++] = (char)ch;
    }
}

int shift_letter(int shift, int letter) {  
    int pos;
    if (letter >= 'A' && letter <= 'Z') {
        pos = letter - 'A';
    } else {
        pos = letter - 'a' + SHIFT_NUM / 2;
    }
    int shifted_pos = (pos + (shift % SHIFT_NUM)) % SHIFT_NUM;
    if (shifted_pos < 0) shifted_pos += SHIFT_NUM;

    if (shifted_pos < SHIFT_NUM / 2) {
        return 'A' + shifted_pos;
    } else {
        return 'a' + (shifted_pos - SHIFT_NUM / 2);
    }
}

void make_choose_options(void) { 
    int best_score = -1, best_shift = 0;
    for (int offset = 0; offset < SHIFT_NUM; offset++) {
        int score = 0;
        for (int i = 0; i < current_length; i++) {
            if (shift_letter(offset, arr_orig[i]) == arr_noise[i]) score++;
        }
        if (score > best_score) {
            best_score = score;
            best_shift = offset;
        }
    }
    
    for (int i = 0; i < current_length; i++) {
        putchar(shift_letter(best_shift, arr_orig[i]));
    }
    putchar('\n');
}
