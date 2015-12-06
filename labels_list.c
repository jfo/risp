#include <string.h>

typedef struct label {
    char * name;
    node * value;
    struct label * next;
} label;

label * labels = NULL;

void add_label(char* name, node * value){
    label * output = malloc(sizeof(label));
    output->name = name;
    output->value = value;
    output->next = labels;
    labels = output;
}

int label_exists(char* l, label* labelslist) {
    if (labelslist) {
        if (strcmp(labelslist->name, l) == 0) {
            return 1;
        } else {
            label_exists(l, labelslist->next);
        }
    }
    return 0;
}

node * find_label(char* current_label, label * labelslist) {
    if (labelslist) {
        if (strcmp(labelslist->name, current_label) == 0) {
            return labelslist->value;
        } else {
            find_label(current_label, labelslist->next);
        }
    }
    return &nil;
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
