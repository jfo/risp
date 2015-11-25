#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    char value;
    struct list* next;
} list;

list make(char* s) {
    list* out = malloc(sizeof(list));
    if (s[0] == '\0') {
        out->next = NULL;
    } else {
        out->value = s[0];
        list next = make(s+1);
        out->next = &next;
    }
    return *out;
}

void printlist(list* l) {
    if (l->next == NULL) { 
        return;
    }
    printf("%c", l->value);
    printlist(l->next);
}

int main(){
    char* teststring = "(jadsfiojaoids)";

    list thing = make(teststring);

    printlist(&thing);

    return 0;
}
