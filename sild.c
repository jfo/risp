#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* readfile() {
    char * buffer = 0;
    long length;
    FILE * f = fopen ("./test.ri", "rb");

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

void parenthesize(char * input ) {
    char* form[1048];
    for(int i = 0; i < strlen(input); i++) {
        printf("%c", input[i]);
    }
}

int main() {

    char * thingy = readfile();
    if (thingy) {
          parenthesize(thingy);
    }

    /* char c; */
    /* while ((c = getchar()) != EOF) { */
    /*     if (c == '\(') { */
    /*         printf("%c%c", '\\','t'); */
    /*     } else if (c == '\\') { */
    /*         printf("%c%c",'\\','\\'); */
    /*     } else { */
    /*         putchar(c); */
    /*     } */
    /* } */
    return 0;
}
