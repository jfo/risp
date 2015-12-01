void printtabs(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|   ");
    }
}

void debuglistinner(node* l, int depth) {
    if (l->type == TERM) {
        printtabs(depth);
        printf("TERM: addr:%p, car=%p, cdr=%p  \n", l, l->car.list, l->cdr);
        printtabs(depth - 1);
        printf("-----------------------------\n");
    } else if (l->type == FINAL_TERM) {
        printf("FINAL_TERM: addr:%p, car=%p, cdr=%p  \n", l, l->car.list, l->cdr);
        printf("-----------------------------\n");
    } else if (l->type == LIST) {
        printtabs(depth);
        printf("-----------------------------\n");
        printtabs(depth);
        printf("LIST: addr:%p, car=%p, cdr=%p  \n", l, l->car.list, l->cdr);
        debuglistinner(l->car.list, depth + 1);
        debuglistinner(l->cdr, depth);
    } else if (l->type == ATOM) {
        printtabs(depth);
        printf("ATOM: addr:%p, car=%s, cdr=%p  \n", l, l->car.c, l->cdr);
        debuglistinner(l->cdr, depth++);
    }
}

void debuglist(node* l) {
    debuglistinner(l, 0);
}

void printlist(node* l) {
    if (l->type == TERM) {
        printf(")");
    } else if (l->type == FINAL_TERM) {
    } else if (l->type == LIST) {
        printf("(");
        printlist(l->car.list);
        printlist(l->cdr);
    } else if (l->type == ATOM) {
        printf(" %s ", l->car.c);
        printlist(l->cdr);
    }
}
