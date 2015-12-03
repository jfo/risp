#include "parser.c"
#include "debugging.c"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void syntax_error(char* err) {
    printf("\nSyntax Error: %s", err);
}


node* copy_node(node* n) {
    if (n->type == LIST) {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = copy_node(n->value.list);
        output->next_item = copy_node(n->next_item);
        return output;
    } else if (n->type == ATOM) {
        node* output = malloc(sizeof(node));
        output->type = ATOM;
        output->value.atom = n->value.atom;
        output->next_item = copy_node(n->next_item);
        return output;
    } else {
        return &empty_list;
    }
}

node* quote(node* operand) {
    if (operand->next_item == &empty_list) {
        return copy_node(operand);
    } else {
        syntax_error("quote accepts only one argument.\n\n");
        return &empty_list;
    }
}

node* eval(node* n) {
    node* operator = n->value.list;
    node* operands = n->value.list->next_item;

    if (strcmp(operator->value.atom, "quote") == 0) {
        return quote(operands);
    }

    return &empty_list;
}


int main(){
    node* test = makelist("(quote 1 3)");
    debuglist(test);
    debuglist(eval(test));

    /* debuglist(test); */
    /* printf("\n\n\n"); */
    /* debuglist(eval(test)); */
    /* printf("\n\n\n"); */
    /* debuglist(quote(test)); */
    return 0;
}
