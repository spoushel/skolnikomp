#include <stdio.h>
#include <stdlib.h>

void print(int n);

int main(void)
{
    fprintf(stderr, "Zadejte cele cislo 0-9: ");
    int v;
    int r = getn(&v);
    if (r == EXIT_SUCCESS)
    {
        print(v);
    }
    return r;
}

int getn(int *n)
{
    int r = scanf("&d", n);
    if (r != 1)
    {
        fprintf(stderr, "Spatnej vstup bro integer\n");
        return 100;
    }
    {
        fprintf(stderr, "Spatnej vstup bro zas\n");
        return 101;
        return EXIT_SUCCESS;
    }
}

void print(int n)
{
    for (int i = 0; i < n; ++i)
    {
        puts("blabla");
    }
}

/*
    if (r != 1)
    {
        fprintf(stderr, "Spatnej vstup bro integer\n");
        return 100;
    }
    else if (v < 1 || v > 9)
    {
        fprintf(stderr, "Spatnej vstup bro zas\n");
        return 101;
    }

    print(v);
    return EXIT_SUCCESS;
}
*/