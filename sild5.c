#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

enum { TERM, ATOM, LIST };

union NodeVal {
    char atom;
    struct node* list;
};

typedef struct node {
    int node_type;
    union NodeVal value;
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


node* makenode(char* s) {
    node* current_node = malloc(sizeof(node));

    if (s[0] == '\0') { return current_node; }

    if (s[0] == '(') {
        current_node->node_type = LIST;
        current_node->value.list = makenode(s + 1);
        current_node->next_item = makenode(s + count_list(s));
    } else if (s[0] == ')') {
        current_node->node_type = TERM;
    } else {
        current_node->node_type = ATOM;
        current_node->value.atom = s[0];
        current_node->next_item = makenode(s + 1);
    }

    return current_node;
}

void printlist(node* l) {
    if (l == NULL) {
        return;
    } else if (l->node_type == TERM) {
        printf("TERM\n");
    } else if (l->node_type == LIST) {
        printlist(l->value.list);
        printlist(l->next_item);
    } else if (l->node_type == ATOM) {
        printf("%c", l->value.atom);
        printlist(l->next_item);
    }
}

int main(){
    char * test = "(1(2))";
    printlist(makenode(test));
    /* printf("%i\n",count_list(test)); */
    /* printf("%c",test[count_list(test)]); */
    return 0;
}
