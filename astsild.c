#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char value;
    struct node *next;
} node;

node makelist(){
    node output;
    char c;
    if ((c = getchar()) != EOF) {
        output.value = c;
        node *next = malloc(sizeof(node));
        next2 = makelist();
        output.next = next;
    } else {
        output.value = 'H';
        output.next = NULL;
    }
    return output;
};

void printlist(node current) {
    if (current.value == 'H') {
        printf("\nmadei\n");
        return;
    } else {
        printf("%c", current.value);
        printlist(*current.next);
    }
    return;
};

int main(){
    node out = makelist();
    printlist(out);
    return 0;
}
