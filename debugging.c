void printtabs(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("|   ");
    }
}

void debuglistinner(node* l, int depth) {
    if (l->type == TERM) {
        printtabs(depth);
        printf("TERM: addr:%p, value=%p, next_item=%p  \n", l, l->value.list, l->next_item);
        printtabs(depth - 1);
        printf("-----------------------------\n");
    } else if (l->type == FINAL_TERM) {
        printf("FINAL_TERM: addr:%p, value=%p, next_item=%p  \n", l, l->value.list, l->next_item);
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

void debuglist(node* l) {
    debuglistinner(l, 0);
}

void printlist(node* l) {
    if (l->type == TERM) {
        printf(")");
    } else if (l->type == FINAL_TERM) {
    } else if (l->type == LIST) {
        printf("(");
        printlist(l->value.list);
        printlist(l->next_item);
    } else if (l->type == ATOM) {
        printf(" %s ", l->value.atom);
        printlist(l->next_item);
    }
}
