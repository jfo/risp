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
        return &nil;
    }
}

node* copy_single_node(node* n) {
    if (n->type == LIST) {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = copy_node(n->value.list);
        output->next_item = &nil;
        return output;
    } else if (n->type == ATOM) {
        node* output = malloc(sizeof(node));
        output->type = ATOM;
        output->value.atom = n->value.atom;
        output->next_item = &nil;
        return output;
    }
    return &nil;
}


node* quote(node* operand) {
    if (operand->next_item == &nil) {
        return copy_node(operand);
    } else {
        syntax_error("'quote' accepts only one argument.\n\n");
        return &nil;
    }
}

node* atom(node* operand) {
    if (
            (operand->type == ATOM && operand->next_item == &nil)
            ||
            (operand->type == LIST && operand->value.list == &nil)
       ){
        return &truth;
    } else {
        return &nil;
    }
}

node* eq(node* operand) {

    node* first = eval(operand);
    node* second = eval(operand->next_item);

    if (
            (first->type == LIST && first->value.list == &nil)
            &&
            (second->type == LIST && second->value.list == &nil)
            &&
            operand->next_item->next_item == &nil
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
            operand->next_item->next_item == &nil
            )
    {
        return &truth;
    } else if (operand->next_item->next_item != &nil) {
        syntax_error("'eq' accepts only two arguments.\n\n");
        return &nil;
    } else {
        return &nil;
    }
}

node* car(node* operand) {
    node * first = eval(operand);
    if (first->type == LIST && operand->next_item == &nil) {
        return copy_single_node(first->value.list);
    } else {
        return &nil;
    }
}

node* cdr(node* operand) {
    node* first = eval(operand);

    if (first->type == LIST && operand->next_item == &nil) {
        node* output = malloc(sizeof(node));
        output->type = LIST;
        output->value.list = copy_node(first->value.list->next_item);
        output->next_item = &nil;
        return output;
    } else {
        return &nil;
    }
}

node* cons(node* operands) {
    node* first = eval(operands);
    node* second = eval(operands->next_item);

    node* output = malloc(sizeof(node));
    output->type = LIST;
    output->value.list = first;
    output->value.list->next_item = copy_node(second->value.list);
    output->next_item = &nil;
    return output;
}

node* cond(node* operands) {
    if (operands == &nil) {
        return &nil;
    }

    if (eval(operands->value.list) == &truth) {
        return copy_node(eval(operands->value.list->next_item));
    } else {
        return cond(operands->next_item);
    }
}

node* eval(node* n) {
    if (n->type == ATOM) {
        return find_label(n->value.atom);
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
    } else if (strcmp(operator->value.atom, "label") == 0) {
        add_label(first_operand->value.atom, copy_node(eval(first_operand->next_item)));
        return find_label(first_operand->value.atom);
    } else {
        operator = find_label(operator->value.atom);
        eval(operator);
    }

    printf("Did you forget to add that function? - %s\n", operator->value.atom);
    return &nil;
}

