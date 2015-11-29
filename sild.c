#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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
    if (s[0] == ' ') {
        return make(s+1);
    } else if (s[0] == '\0') {
        node* output = malloc(sizeof(node));
        output->type = FINAL_TERM;
        output->car.list = NULL;
        output->cdr = NULL;
        return output;
    } else if (s[0] == '(') {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->car.list = make(s+1);
        output->cdr = make(s + count_list(s));
        return output;
    } else if (s[0] == ')') {
        node* output = malloc(sizeof(node));
        output->type = TERM;
        output->car.list = NULL;
        output->cdr = NULL;
        return output;
    } else {
        node* output = malloc(sizeof(node));
        output->type = ATOM;
        output->car.c = s[0];
        output->cdr = make(s + 1);
        return output;
    }
}

void debuglist(node* l) {
    if (l->type == TERM) {
        printf("TERM\n");
    } else if (l->type == LIST) {
        printf("BEGIN\n");
        debuglist(l->car.list);
        debuglist(l->cdr);
    } else if (l->type == ATOM) {
        printf(" %c \n", l->car.c);
        debuglist(l->cdr);
    }
}

void printlist(node* l) {
    if (l->type == TERM) {
        printf(")");
    } else if (l->type == LIST) {
        printf("(");
        printlist(l->car.list);
        printlist(l->cdr);
    } else if (l->type == ATOM) {
        printf(" %c ", l->car.c);
        printlist(l->cdr);
    }
}

node* quote(node* n) {
    return n;
}

int atom(node* n) {
    if ((n->type == ATOM && n->cdr->type == TERM)|| (n->type == LIST && n->car.list->type == TERM)) {
        return TRUE;
    } else {
        return FALSE;
    }
}


int main(){
    /* char * test = "(1 (2( (1 (3))3 6 )) 3 4)"; */

    printf("\n%i", (atom(make("()"))));
    printf("\n%i", (atom(make("(a)")->car)));

    return 0;
}
