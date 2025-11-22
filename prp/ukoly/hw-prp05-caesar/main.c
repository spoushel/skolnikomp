#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_INPUT 100
#define ERROR_LENGTH 101
#define INITIAL_LENGTH 50
#define SHIFT_NUM 52
#define ALPHABET_SIZE 26

void load_input(char **arr_orig, int *arr_orig_size, int *current_length, char **arr_noise, int *arr_noise_size, int *noise_length);
int shift_letter(int shift, int letter);
void make_choose_options(const char *arr_orig, const char *arr_noise, int current_length);
int fancy_distance(const char *str1, const char *str2, int len1, int len2);
void make_choose_fancy_distance(const char *arr_orig, const char *arr_noise, int current_length, int noise_length);
static int is_ascii_letter(int ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int main(int argc, char *argv[]) {
    char *arr_orig = NULL;
    char *arr_noise = NULL;
    int arr_orig_size = INITIAL_LENGTH;
    int arr_noise_size = INITIAL_LENGTH;
    int current_length = 0;
    int noise_length = 0;
    int param_present = 0;
    
    if (argc > 1 && !strcmp(argv[1], "-prp-optional")) {
        param_present = 1;
    }

    arr_orig = malloc(arr_orig_size * sizeof(char));
    arr_noise = malloc(arr_noise_size * sizeof(char));

    if (!arr_orig || !arr_noise) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        free(arr_orig);
        free(arr_noise);
        return ERROR_INPUT;
    }

    load_input(&arr_orig, &arr_orig_size, &current_length, &arr_noise, &arr_noise_size, &noise_length);

    if (!param_present) {
        if (current_length != noise_length) {
            fprintf(stderr, "Error: Chybna delka vstupu!\n");
            free(arr_orig);
            free(arr_noise);
            return ERROR_LENGTH;
        }
        make_choose_options(arr_orig, arr_noise, current_length);
    } else {
        make_choose_fancy_distance(arr_orig, arr_noise, current_length, noise_length);
    }

    free(arr_orig);
    free(arr_noise);
    return 0;
}

void load_input(char **arr_orig, int *arr_orig_size, int *current_length,
                char **arr_noise, int *arr_noise_size, int *noise_length) {
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (!is_ascii_letter(ch)) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(ERROR_INPUT);
        }
        if (*current_length >= *arr_orig_size) {
            *arr_orig_size *= 2;
            char *tmp = realloc(*arr_orig, *arr_orig_size);
            if (!tmp) {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(ERROR_INPUT);
            }
            *arr_orig = tmp;
        }
        (*arr_orig)[(*current_length)++] = (char)ch;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (!is_ascii_letter(ch)) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            exit(ERROR_INPUT);
        }
        if (*noise_length >= *arr_noise_size) {
            *arr_noise_size *= 2;
            char *tmp = realloc(*arr_noise, *arr_noise_size);
            if (!tmp) {
                fprintf(stderr, "Error: Chybny vstup!\n");
                exit(ERROR_INPUT);
            }
            *arr_noise = tmp;
        }
        (*arr_noise)[(*noise_length)++] = (char)ch;
    }
}

int shift_letter(int shift, int letter) {
    // posouva pismenko o dany pocet znaku v seznamu A - z
    int pos;
    if (letter >= 'A' && letter <= 'Z') {
        pos = letter - 'A';
    } else {
        pos = letter - 'a' + ALPHABET_SIZE;
    }
    
    int shifted_pos = (pos + shift) % SHIFT_NUM;
    if (shifted_pos < 0) {
        shifted_pos += SHIFT_NUM;
    }

    if (shifted_pos < ALPHABET_SIZE) {
        return 'A' + shifted_pos;
    } else {
        return 'a' + (shifted_pos - ALPHABET_SIZE);
    }
}

void make_choose_options(const char *arr_orig, const char *arr_noise, int current_length) {
    // prochazi vsechny moznosti a uklada nejlepsi
    int best_score = -1; int best_shift = 0;
    
    for (int offset = 0; offset < SHIFT_NUM; offset++) {
        int score = 0;
        for (int i = 0; i < current_length; i++) {
            if (shift_letter(offset, arr_orig[i]) == arr_noise[i]) {
                score++;
            }
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

int fancy_distance(const char *str1, const char *str2, int len1, int len2) {
    //spocitani levenstejnovy vzdalenosti 
    int *prev = malloc((len2 + 1) * sizeof(int)); 
    int *curr = malloc((len2 + 1) * sizeof(int)); 
    if (!prev || !curr) {
        free(prev);
        free(curr);
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(ERROR_INPUT);
    }

    for (int j = 0; j <= len2; j++) {
        prev[j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        curr[0] = i;

        for (int k = 1; k <= len2; k++) {
            int subs_cost = (str1[i - 1] == str2[k - 1]) ? 0 : 1;
            
            int delete = prev[k] + 1;
            int insert = curr[k - 1] + 1;
            int substitute = prev[k - 1] + subs_cost;

            int min = delete;
            if (insert < min) {
                min = insert;
            }
            if (substitute < min) {
                min = substitute;
            }

            curr[k] = min;
        }
        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }
    int res = prev[len2];
    free(prev);
    free(curr);
    return res;
}

void make_choose_fancy_distance(const char *arr_orig, const char *arr_noise, int current_length, int noise_length) {
    //hodnoti moznosti pomoci levenstejnovy vzdalenosti, uklada nejlepsi
    char *decoded = malloc(current_length ? current_length : 1);
    if (!decoded) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(ERROR_INPUT);
    }
    int best_score = -1, best_shift = 0; 

    for (int offset = 0; offset < SHIFT_NUM; offset++) {
        for (int i = 0; i < current_length; i++) {
            decoded[i] = shift_letter(offset, arr_orig[i]);
        }
        int dist = fancy_distance(decoded, arr_noise, current_length, noise_length);
        if (best_score < 0 || dist < best_score) { 
            best_score = dist;
            best_shift = offset;
        }
    }
    for (int i = 0; i < current_length; i++) {
        putchar(shift_letter(best_shift, arr_orig[i]));
    }
    putchar('\n');
    free(decoded);
}
