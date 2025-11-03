#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100
#define ERROR_AMOUNT 101
#define MAX_LENGTH 500 // 26*9 = 235
#define MAX_LENGTH_ALPHABET 26

int load_check_input(char arr_sentence[], int arr_alphabet[]);
int print_chars(void);
int print_nums(int arr_alphabet[]);
int evaluate_input(char current_char, int arr_alphabet[]);

int main(void) {
    int arr_alphabet[MAX_LENGTH_ALPHABET] = {0};
    char arr_sentence[MAX_LENGTH];

    int result = load_check_input(arr_sentence, arr_alphabet);
    if (result != 0)
        return result;

    print_chars();
    print_nums(arr_alphabet);
    return EXIT_SUCCESS;
}

int load_check_input(char arr_sentence[], int arr_alphabet[]) {
    int i = 0;
    int ch;
    while ((ch = getchar()) != EOF && i < MAX_LENGTH)
    {
        if (ch == '\n')
            break;
        if (ch == '.')
            break;
        if (!isalpha(ch) && ch != ' ')
        {
            fprintf(stderr, "Chyba vstupu!\n");
            return ERROR_INPUT;
        }
        arr_sentence[i] = (char)ch;
        int result = evaluate_input(ch, arr_alphabet);
        if (result != 0)
            return result;
        ++i;
    }
    arr_sentence[i] = '\0';
    return EXIT_SUCCESS;
}

int print_chars(void) {
    for (int l = 0; l < MAX_LENGTH_ALPHABET; ++l)
    {
        char letter = 'a' + l;
        printf(" %c", letter);
    }
    printf("\n");
    return 0;
}

int evaluate_input(char current_char, int arr_alphabet[]) {
    if (current_char == ' ')
        return 0;

    int index = tolower(current_char) - 'a';
    arr_alphabet[index]++;

    if (arr_alphabet[index] > 9)
    {
        fprintf(stderr, "Error: Prilis mnoho stejnych znaku!\n");
        return ERROR_AMOUNT;
    }
    return EXIT_SUCCESS;
}

int print_nums(int arr_alphabet[]) {
    for (int i = 0; i < MAX_LENGTH_ALPHABET; ++i)
    {
        printf(" %d", arr_alphabet[i]);

    }
    printf("\n");
    return EXIT_SUCCESS;
}
