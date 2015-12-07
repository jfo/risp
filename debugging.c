void printtabs(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|   ");
    }
}

void debuglistinner(node* l, int depth) {
    if (l == &nil) {
        printtabs(depth);
        printf("NIL: addr:%p, value=%p, next_item=%p  \n", l, l->value.list, l->next_item);
        printtabs(depth - 1);
        printf("-----------------------------\n");
    } else if (l->type == LIST) {
        printtabs(depth);
        printf("-----------------------------\n");
        printtabs(depth);
        printf("LIST: addr:%p, value=%p, next_item=%p  \n", l, l->value.list, l->next_item);
        debuglistinner(l->value.list, depth + 1);
        debuglistinner(l->next_item, depth);
    } else if (l->type == ATOM) {
        printtabs(depth);
        printf("ATOM: addr:%p, value=%s, next_item=%p  \n", l, l->value.atom, l->next_item);
        debuglistinner(l->next_item, depth++);
    }
}

void printlist(node* l) {
    if (l == &nil) {
        printf(")");
    } else if (l->type == LIST) {
        printf("(");
        printlist(l->value.list);
        printlist(l->next_item);
    } else if (l->type == ATOM) {
        printf(" %s ", l->value.atom);
        printlist(l->next_item);
    }
}

void debuglist(node* l) {
    printlist(l);
    printf("\n");
    debuglistinner(l, 0);
}


void print_labels(label * l) {
    if (l) {
        printf("%s\n", l->name);
        printf("%p\n", l->value);
        debuglist(l->value);
        printf("\n\n");
        print_labels(l->next);
    }
}

void prints(char * s) {
    debuglist(makelist(s));
    printf("\n");
}
void evals(char * s) {
    printf("%s\n", s);
    debuglist(eval(makelist(s)));
    printf("\n");
}
void test_all() {
    evals("(quote arbitrary_thing)");

    evals("(atom (quote arbitrary_thing))");
    evals("(atom (quote ()))");
    evals("(atom (quote (thingy)))");

    evals("(car (quote (thing thang thung)))");
    evals("(cdr (quote (thing thang thung)))");

    evals("(cons (quote thing) (quote (thang thung)))");

    evals("(cond ((eq (quote 2) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))");
    evals("(cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))");
    evals("(cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))");

    evals("(label my_label (quote yayyyy))");

    printf("You will find the truth at: %p\n", &truth);
    evals("(eq my_label (quote yayyyy))");
    printf("nil lives here: ");
    debuglist(&nil);
    evals("(eq my_label (quote noooo))");

    evals("(eq my_label (quote noooo))");
    evals("(cons (quote a) (cons (quote b) (cons (quote c) (quote ()))))");
}
