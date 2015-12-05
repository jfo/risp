#include "parser.c"
#include "debugging.c"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node* eval();

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

    node* first = eval(operand);
    node* second = eval(operand->next_item);

    if (
            (first->type == LIST && first->value.list == &empty_list)
            &&
            (second->type == LIST && second->value.list == &empty_list)
            &&
            operand->next_item->next_item == &empty_list
       )
    {
        return &truth;
    } else if (
            first->type == ATOM
            &&
            second->type == ATOM
            &&
            strcmp(first->value.atom, second->value.atom) == 0
            &&
            operand->next_item->next_item == &empty_list
            )
    {
        return &truth;
    } else if (operand->next_item->next_item != &empty_list) {
        syntax_error("'eq' accepts only two arguments.\n\n");
        return &empty_list;
    } else {
        return &empty_list;
    }
}

node* car(node* operand) {
    node * first = eval(operand);
    if (first->type == LIST && operand->next_item == &empty_list) {
        return copy_single_node(first->value.list);
    } else {
        return &empty_list;
    }
}

node* cdr(node* operand) {
    node* first = eval(operand);

    if (first->type == LIST && operand->next_item == &empty_list) {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = copy_node(first->value.list->next_item);
        output->next_item = &empty_list;
        return output;
    } else {
        return &empty_list;
    }
}

node* cons(node* operands) {
    node* first = eval(operands);
    node* second = eval(operands->next_item);

    node* output = malloc(sizeof(node));
    output->type = LIST;
    output->value.list = first;
    output->value.list->next_item = copy_node(second->value.list);
    output->next_item = &empty_list;
    return output;
}

node* cond(node* operands) {
    if (operands->value.list->type == ATOM) {
        return &truth;
    } else if (operands->value.list->type == LIST) {
        return eval(operands->value.list);
    }
    return &empty_list;
}


node* eval(node* n) {
    if (n->type == ATOM) {
        return copy_single_node(n);
    }

    node* operator = n->value.list;
    node* first_operand = n->value.list->next_item;

    if (strcmp(operator->value.atom, "quote") == 0) {
        return quote(first_operand);
    } else if (strcmp(operator->value.atom, "atom") == 0) {
        return atom(eval(first_operand));

    } else if (strcmp(operator->value.atom, "eq") == 0) {
        return eq(first_operand);

    } else if (strcmp(operator->value.atom, "car") == 0) {
        return car(first_operand);
    } else if (strcmp(operator->value.atom, "cdr") == 0) {
        return cdr(first_operand);
    } else if (strcmp(operator->value.atom, "cons") == 0) {
        return cons(first_operand);

    } else if (strcmp(operator->value.atom, "cond") == 0) {
        return cond(first_operand);
    }

    syntax_error("Did you forget to add that function?\n");
    return &empty_list;
}

void evals(char * s) {
    printf("\n");
    debuglist(eval(makelist(s)));
    printf("\n");
}


int main(){
printf("\n\
int main(){\n\
    evals(\"(eq (atom (car (cons 4 (cdr (quote (1 2 3)))))) t)\");\n\
    return 0;\n\
}\n");
    evals("(eq (atom (car (cons 4 (cdr (quote (1 2 3)))))) t)");
    return 0;
}
