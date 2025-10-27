#include <stdio.h>
#include <stdlib.h>

int my_cat();

int main(void) {
    char str[] = "Hello World and hello again";
    char *cur = str;
    while (cur && *cur) {
        /*
        je to mezera - neni - vytisknu
            prevspace = false
        je to mezera - ano - novej radek - znova - skip
        if (!isspace)
        else if prevspace
        else putchar \n
            prevspace = true
        
        */
    }
    return EXIT_SUCCESS;
}

int my_cat() {


}
