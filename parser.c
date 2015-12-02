#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

enum { FINAL_TERM, TERM, ATOM, LIST };

union node_val {
    char* atom;
    struct node* list;
};

typedef struct node {
    int type;
    union node_val value;
    struct node* next_item;
} node;

node empty_list = {TERM, {NULL}, NULL};

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

int count_string_length(char* s){
    int i;
    for (i = 0;
            (
             s[i] != '\0'
             &&
             s[i] != ')'
             &&
             s[i] != '('
             &&
             s[i] != ' '
             &&
             s[i] != '\n'
             &&
             s[i] != ','
             &&
             s[i] != ';'
             );
            i++) {
    }
    return i;
}
char* return_string(char* s){
    char* out = malloc(count_string_length(s));
    int i;
    for (i = 0;
            (
             s[i] != '\0'
             &&
             s[i] != ')'
             &&
             s[i] != '('
             &&
             s[i] != ' '
             &&
             s[i] != '\n'
             &&
             s[i] != ','
             &&
             s[i] != ';'
             );
            i++) {
        out[i] = s[i];
    }
    out[i] = '\0';
    return out;
}

node * makelist(char* s) {
    if (s[0] == ' ' || s[0] == '\n' || s[0] == ',') {
        return makelist(s+1);
    } else if (s[0] == '\0' || s[0] == ')') {
        return &empty_list;
    } else if (s[0] == '(') {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = makelist(s+1);
        output->next_item = makelist(s + count_list(s));
        return output;
    } else {
        node* output = malloc(sizeof(node));
        output->type = ATOM;
        output->value.atom = return_string(s);
        output->next_item = makelist(s + count_string_length(s));
        return output;
    }
}
