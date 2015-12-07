#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

enum { NIL, ATOM, LIST };

union node_val {
    char* atom;
    struct node* list;
};

typedef struct node {
    int type;
    union node_val value;
    struct node* next_item;
} node;

node nil = { NIL, {NULL}, NULL };
node truth = { ATOM, {"t"}, &nil };

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

void debuglist();
node * makelist(char* s) {
    if (s[0] == ' ' || s[0] == '\n' || s[0] == ',') {
        return makelist(s+1);
    } else if (s[0] == '\0' || s[0] == ')') {
        return &nil;
    } else if (s[0] == '\'' && s[1] == '(') {
        node* quote = malloc(sizeof(node));
        quote->type = ATOM;
        quote->value.atom = "quote";

        node* input = malloc(sizeof(node));
        input->type = LIST;
        input->value.list = makelist(s+2);
        input->next_item = &nil;

        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = quote;
        quote->next_item = input;
        output->next_item = makelist(s + count_list(s + 1) + 2);
        return output;
    } else if (s[0] == '\'') {
        node* quote = malloc(sizeof(node));
        quote->type = ATOM;
        quote->value.atom = "quote";

        node* input = malloc(sizeof(node));
        input->type = ATOM;
        input->value.atom = return_string(s+1);
        input->next_item = &nil;

        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = quote;
        quote->next_item = input;
        output->next_item = makelist(s + count_string_length(s));
        return output;
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

