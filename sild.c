#include "parser.c"
#include "debugging.c"
#include "sevenfunctions.c"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char* readfile(char* filename) {
    char * buffer = 0;
    long length;
    FILE * f = fopen (filename, "rb");

    if (f) {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }

    return buffer;
}

int main(){

    char* test = readfile("test.sld");
    node* testlist = makelist(test);
    printf("\n");
    debuglist(testlist, 0);

    return 0;
}
