#include <stdio.h>
#include <stdlib.h>

enum { TERM, ATOM, LIST };
typedef struct list {
    int value_type;
    char atom_value;
    struct list* list_value;
    struct list* next_item;
} list;

int count_list(char* s) {
    int depth = 0;
    int i;
    for (i = 0; (depth == 0 && s[i] == ')'); i++) {
        if (s[i] == '(') {
            depth++;
        } else if (s[i] == ')') {
            depth--;
        }
    }
    return i + 2;
}

list* make_list_from_string(char* s) {
    list* out = malloc(sizeof(list));

    if (s[0] == '(') {
        out->value_type = LIST;
        out->list_value = make_list_from_string(s + 1);
        out->next_item = make_list_from_string(s + 1 + (count_list(s) ));
    } else if (s[1] == ')') {
        out->value_type = ATOM;
        out->atom_value = s[0];
    } else if (s[0] == '\0') {
        out->value_type = TERM;
        return out;
    } else {
        out->value_type = ATOM;
        out->atom_value = s[0];
        out->next_item = make_list_from_string(s+1);
    }
    return out;
}

void printlist(list* l) {
    if (l->value_type == LIST) {
        printf("LIST: %p, %c\n", l->list_value, l->atom_value);
        printlist(l->list_value);
        printlist(l->next_item);
    } else if (l->value_type == ATOM) {
        printf("ATOM: %p, %c\n", l->list_value, l->atom_value);
        if (l->next_item == NULL) { return; }
        printlist(l->next_item);
    } else if (l->value_type == TERM) {
        printf("TERM");
    }
}

int main(){
    printlist(make_list_from_string("(t(l))"));
    return 0;
}
