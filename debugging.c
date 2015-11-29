void printtabs(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|   ");
    }
}

void debuglist(node* l, int depth) {
    if (l->type == TERM) {
        printtabs(depth - 1);
        printf("------------TERM------------\n");
    } else if (l->type == LIST) {
        printtabs(depth);
        printf("LIST: car=%p, cdr=%p  \n", l->car.list, l->cdr);
        debuglist(l->car.list, depth + 1);
        debuglist(l->cdr, depth);
    } else if (l->type == ATOM) {
        printtabs(depth);
        printf("ATOM: car=%c, cdr=%p  \n", l->car.c, l->cdr);
        debuglist(l->cdr, depth++);
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
