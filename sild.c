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

node* copy_single_node(node* n) {
    if (n->type == LIST) {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = copy_node(n->value.list);
        output->next_item = &empty_list;
        return output;
    } else if (n->type == ATOM) {
        node* output = malloc(sizeof(node));
        output->type = ATOM;
        output->value.atom = n->value.atom;
        output->next_item = &empty_list;
        return output;
    }
    return &empty_list;
}

node* quote(node* operand) {
    if (operand->next_item == &empty_list) {
        return copy_node(operand);
    } else {
        syntax_error("'quote' accepts only one argument.\n\n");
        return &empty_list;
    }
}

node* atom(node* operand) {
    if (
            (operand->type == ATOM && operand->next_item == &empty_list)
            ||
            (operand->type == LIST && operand->value.list == &empty_list)
       ){
        return &truth;
    } else {
        return &empty_list;
    }
}

node* eq(node* operand) {
    if (
            (
             (operand->type == LIST && operand->value.list == &empty_list)
             &&
             (operand->next_item->type == LIST && operand->next_item->value.list == &empty_list)
             &&
             operand->next_item->next_item == &empty_list
            )
            ||
            (
             operand->type == ATOM
             &&
             operand->next_item->type == ATOM
             &&
             strcmp(operand->value.atom, operand->next_item->value.atom) == 0
             &&
             operand->next_item->next_item == &empty_list
            )
       )
    {
        return &truth;
    } else if (operand->next_item->next_item != &empty_list) {
        syntax_error("'eq' accepts only two arguments.\n\n");
        return &empty_list;
    } else {
        syntax_error("thingy");
        return &empty_list;
    }
}

node* car(node* operand) {
    if (operand->type == LIST && operand->next_item == &empty_list) {
        return copy_single_node(operand->value.list);
    } else {
        return &empty_list;
    }
}

node* cdr(node* operand) {
    if (operand->type == LIST && operand->next_item == &empty_list) {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = copy_node(operand->value.list->next_item);
        output->next_item = &empty_list;
        return output;
    } else {
        return &empty_list;
    }
}

node* eval(node* n) {
    node* operator = n->value.list;
    node* operands = n->value.list->next_item;

    if (strcmp(operator->value.atom, "quote") == 0) {
        return quote(operands);
    } else if (strcmp(operator->value.atom, "atom") == 0) {
        return atom(operands);
    } else if (strcmp(operator->value.atom, "eq") == 0) {
        return eq(operands);
    } else if (strcmp(operator->value.atom, "car") == 0) {
        return car(operands);
    } else if (strcmp(operator->value.atom, "cdr") == 0) {
        return cdr(operands);
    }

    return &empty_list;
}


int main(){
    node* test = makelist("(cdr (3 4 3 7 7 7))");
    debuglist(test);
    printf("\n\n\n");
    debuglist(eval(test));

    /* debuglist(eval(test)); */
    /* printf("\n\n\n"); */
    /* debuglist(quote(test)); */
    return 0;
}
