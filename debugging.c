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
    char ** values = (char *[]){
    "(quote arbitrary_thing)",
    "(atom (quote arbitrary_thing))",
    "(atom (quote ()))",
    "(atom (quote (thingy)))",
    "(car (quote (thing thang thung)))",
    "(cdr (quote (thing thang thung)))",
    "(cons (quote thing) (quote (thang thung)))",
    "(cond ((eq (quote 2) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))",
    "(cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))",
    "(cond ((eq (quote 1) (quote 2)) (quote first)) ((eq (quote 2) (quote 2)) (quote second)))",
    "(label my_label (quote yayyyy))",
    "(eq my_label (quote yayyyy))",
    "(eq my_label (quote noooo))",
    "(eq my_label (quote noooo))",
    "(cons (quote a) (cons (quote b) (cons (quote c) (quote ()))))",
    "derr"
    };

    printf("%lu\n", sizeof(values));
    for (int i = 0; strcmp(values[i], "derr") ; i++) {
        printf("%s\n%p\n", values[i], &values[i]);
    }
}
