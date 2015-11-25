#include <stdio.h>
#include <stdlib.h>

enum { ATOM, LIST };
typedef struct list {
    int value_type;
    char atom_value;
    struct list* list_value;
    struct list* next_item;
} list;

list* make_list_from_string(char* s) {
    list* out = malloc(sizeof(list));
    out->value_type = ATOM;
    out->atom_value = s[0];
    if (s[1] == '\0') {
        out->next_item = NULL;
        return out;
    } else {
        out->next_item = make_list_from_string(s + 1);
    }
    return out;
}

void printlist(list* l) {
    printf("%c", l->atom_value);
    if (l->next_item == NULL) {return;}
    printlist(l->next_item);
}

int main(){
    printlist(make_list_from_string("to"));
    return 0;
}
