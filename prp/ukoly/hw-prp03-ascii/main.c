#include <stdio.h>
#include <stdlib.h>

#define MIN 3
#define MAX 69
#define ERROR_INPUT 100
#define ERROR_RANGE 101
#define ERROR_ODD 102
#define ERROR_FENCE_HEIGHT 103

int load_check_nums(int *width, int *height, int *fencesize, int input);
int print_house(int *width, int *height, int fencesize);
void print_body(int *width, int *height, int fencesize);
void print_roof(int *width);
void print_single_fence(int fencesize, int rowtype);

int main(void) {
    int height = 0, width = 0, fencesize = 0;
    int input = scanf("%d %d", &width, &height);

    if (input == 2 && width == height) {
        if (scanf("%d", &fencesize) == 1) {
            input = 3;
        } else {
            input = -1;
        }
    }
    int result = load_check_nums(&width, &height, &fencesize, input);
    if (result != 0) {
        return result;
    } else {
        return print_house(&width, &height, fencesize);
    }
}

int load_check_nums(int *width, int *height, int *fencesize, int input) {
    if (input != 2 && input != 3) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return ERROR_INPUT;
    }
    if (*width < MIN || *width > MAX || *height > MAX || *height < MIN) {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        return ERROR_RANGE;
    }
    if (*width % 2 == 0) {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        return ERROR_ODD;
    }
    if (input == 3) {
        if (*fencesize <= 0) {
            fprintf(stderr, "Error: Neplatna velikost plotu!\n");
            return ERROR_FENCE_HEIGHT;
        }
        if (*fencesize >= *height) {
            fprintf(stderr, "Error: Neplatna velikost plotu!\n");
            return ERROR_FENCE_HEIGHT;
        }
    }
    return EXIT_SUCCESS;
}

int print_house(int *width, int *height, int fencesize) {
    print_roof(width);
    print_body(width, height, fencesize);
    return 0;
}

void print_body(int *width, int *height, int fencesize) {
    // top row
    for (int i = 0; i < *width; ++i) {
        printf("X");
    }
    printf("\n");

    //middle rows
    for (int i = 0; i < *height - 2; ++i) {
        printf("X");
        //vnitrek prostredku

        for (int j = 0; j < *width - 2; ++j) {
            if (fencesize > 0) {
                if ((i+j) % 2 == 0) {
                printf("o");
                } else {
                printf("*");
                }
            } else {
                printf(" ");
            }
            
        }
        printf("X");

        if (fencesize > 0 && i >= (*height - 1 - fencesize)) {
            int fence_row = i - (*height - fencesize -1);
            print_single_fence(fencesize, fence_row);
        }
        printf("\n");
    }
    //bottom
    for (int i = 0; i < *width; ++i) {
        printf("X");
    }
    if (fencesize > 0) {
        print_single_fence(fencesize, 0);
    }
    printf("\n"); 
}

void print_roof(int *width) {
    int roof_height = (*width + 1) / 2;
    for (int i = 0; i < (roof_height - 1); ++i) {
        int front_spaces = roof_height - 1 - i;
        int middle_spaces = (i == 0) ? 0 : 2 * i - 1;
        printf("%*s", front_spaces, "");
        printf("X");
        if (i > 0) {
            printf("%*s", middle_spaces, "");
            printf("X");
        }
        printf("\n");
    }
}

void print_single_fence(int fencesize, int row_type) {
    for (int i = 0; i < fencesize; ++i) {
        if (row_type == 0) {
            if ((fencesize - i) % 2 != 0) {
                printf("|");
            } else {
                printf("-");
            }
        } else {
            if ((fencesize - i) % 2 != 0) {
                printf("|");
            } else {
                printf(" ");
            }
        }
    }
}
