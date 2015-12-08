#include "parser.c"
#include "labels_list.c"
#include "builtins.c"
#include "debugging.c"

int main() {

evals("\
        ((lambda (x) (atom x)) '1)\
");
    return 0;
}
