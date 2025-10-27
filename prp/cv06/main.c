#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 10

int my_strlen(const char *str);
int my_strcmp(const char *str1, const char *str2, int n);

int main(void) {

    char str[] = "Everybody likes PRP";

    //printf("%s\n", strstr(str, " "));
    char *cur = str;
    while (cur && *cur && *cur != ' ') {
        cur += 1;
    }
    printf("%s\n", cur);

    char *str2 = "Tom";
    printf("T");
    return EXIT_SUCCESS; 
    /*
    const char *str = "blablabla";
    const char *str1 = "mimimimi";
    const char *str2 = "mimi";
    int n = 10;
    printf("strlen je %d \n", my_strlen(str));
    printf("stdcmp je %d \n", my_strcmp(str1, str2, n));
    return EXIT_SUCCESS; */
}

int my_strlen(const char *str) {
    int len = 0;
    while (str && *str) {
        str += 1;
        len += 1;
    }

    return len;
}


int my_strcmp(const char *str1, const char *str2, int n) {
    int ret = 0;
    for ( int i = 0; 
        i < n && str1 && str2 && ret == 0
        && (str1[i] != '\0' || str2[i] != '\0'); 
        ++i) {
        if (str1[i] < (str2[i])) {
            ret = -1;
        } else if (str1[i] > str2[i]) {
            ret = 1;
        }
    }
    return ret;
}
