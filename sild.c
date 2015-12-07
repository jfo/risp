#include "parser.c"
#include "labels_list.c"
#include "builtins.c"
#include "debugging.c"

int main() {
    evals("(cons '4 '(3))");
    return 0;
}
