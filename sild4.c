#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

enum { TERM, ATOM, LIST };
typedef struct node {
    int value_type;
    char atom_value;
    struct node* list_value;
    struct node* next_item;
} node;

int count_list(char* s) {
    int depth = 1;
    int count = 0;
    for (int i = 1; depth != 0; i++) {
        if (s[i] == '(') {
            depth++;
        } else if (s[i] == ')') {
            depth--;
        }
        count++;
    }
    return count + 1;
}

node * make_node(char* s) {
    node* out = malloc(sizeof(node));

    if (s[0] == '\0') {
        out->value_type = TERM;
    } else if (s[0] == '(') {
        out->value_type = LIST;
        out->list_value = make_node(s + 1);
        out->next_item = make_node(s + count_list(s));
    } else if (s[0] == ')') {
    } else if (s[1] == ')') {
        out->value_type = ATOM;
        out->atom_value = s[0];
    } else {
        out->value_type = ATOM;
        out->atom_value = s[0];
        out->next_item = make_node(s + 1);
    }

    return out;
}

void print_list(node* n) {
    if (n == NULL) {
        printf("CLOSE LIST\n");
        return;
    } else if (n->value_type == TERM) {
        printf("TERM\n");
        return;
    } else if (n->value_type == LIST) {
        printf("OPEN LIST ===");
        printf("LIST: %p\n", n->list_value);
        print_list(n->list_value);
        print_list(n->next_item);
    } else if (n->value_type == ATOM) {
        printf("ATOM: %c\n", n->atom_value);
        print_list(n->next_item);
    }
}

int main(){
    print_list(make_node("(1(23))"));
    /* printf("%i", count_list("(thing)")); */
    return 0;
}
