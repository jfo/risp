#include "parser.c"
#include "labels_list.c"
#include "builtins.c"
#include "debugging.c"

int main() {
    evals("(label thing (lambda (x) (quote (x x x x))))");
    evals("(thing (quote 7))");
    return 0;
}
