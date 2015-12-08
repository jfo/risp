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

void debuglist();
node * find_labelin(char* current_label, label* labelslist) {
    if (labelslist) {
        if (strcmp(labelslist->name, current_label) == 0) {
            return labelslist->value;
        } else {
            return find_labelin(current_label, labelslist->next);
        }
    }

    printf("%s", current_label);
    printf("ERROR: variable %s unbound", current_label);
    exit(1);
}

node * find_label(char* current_label) {
    return find_labelin(current_label, labels);
}

