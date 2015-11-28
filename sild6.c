#include <stdio.h>
#include <stdlib.h>

enum { FINAL_TERM, TERM, ATOM, LIST };

/* forward declaration */
struct node;

/* a node_val can either be a char or a pointer to a new list */
union node_val {
    char c;
    struct node* list;
};

/* lol why not? car is a node_val (either a char or a new list) and cdr is a pointer to another node. */
/* if cdr is NULL? */
typedef struct node {
    int type;
    union node_val car;
    struct node* cdr;
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

node * make(char* s) {
    node* output = malloc(sizeof(node));

    if (s[0] == '(') {
        output->type = LIST;
        output->car.list = make(s+1);
        output->cdr = make(s + count_list(s));
    } else if (s[0] == ')') {
        output->type = TERM;
        output->car.list = NULL;
        output->cdr = NULL;
    } else {
        output->type = ATOM;
        output->car.c = s[0];
        output->cdr = make(s + 1);
    }

    if (s[0] == '\0') {
        output->type = FINAL_TERM;
        output->car.list = NULL;
        output->cdr = NULL;
    }

    return output;
}

void printlist(node* l) {
    if (l == NULL) {
        return;
    } else if (l->type == TERM) {
        printf(")");
    } else if (l->type == LIST) {
        printf("(");
        printlist(l->car.list);
        printlist(l->cdr);
    } else if (l->type == ATOM) {
        printf("%c", l->car.c);
        printlist(l->cdr);
    }
}

int main(){
    char * test = "(1 (2 (3 6)) 3 4)";
    printlist(make(test));
    return 0;
}
