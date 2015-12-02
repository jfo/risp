#include "parser.c"
#include "debugging.c"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node* quote(node* n) {
    node* output = malloc(sizeof(node));
    output->type = n->next_item->type;
    output->value = n->value;
    output->next_item = n->next_item;
    return &empty_list;
}


int main(){
    node* test = makelist("(quote 1)");
    node* test2 = makelist("1");
    debuglist(test);
    debuglist(test2);
    return 0;
}
