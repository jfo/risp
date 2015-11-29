node* quote(node* n) {
    return n;
}

int atom(node* n) {
    if ((n->type == ATOM && n->cdr->type == TERM)|| (n->type == LIST && n->car.list->type == TERM)) {
        return TRUE;
    } else {
        return FALSE;
    }
}
