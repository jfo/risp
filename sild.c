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

node** parse_string(char* s) {
    node **output = malloc(sizeof(node) * 100);
    int output_i = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            char* temp_list = &s[i];
            temp_list[count_list(temp_list)] = '\0';
            output[output_i] = makelist(temp_list);
            output_i++;
            i += count_list(s + i);
        }
    }
    return output;
}

int main(){

    char* input = readfile("test.sld");
    node** thing = parse_string(input);

    for (int i = 0; i < 9; i++) {
        printlist(thing[i]);
        getchar();
    }

    for (int i = 0; i < 9; i++) {
        debuglist(thing[i]);
        getchar();
    }

    return 0;
}
