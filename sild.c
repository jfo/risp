#include "parser.c"
#include "labels_list.c"
#include "builtins.c"
#include "debugging.c"

int main() {

    debuglist(makelist("(eq '() (quote ()))"));
    evals("(eq '1 '1)");

    return 0;
}
