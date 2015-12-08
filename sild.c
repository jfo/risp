#include "parser.c"
#include "labels_list.c"
#include "builtins.c"
#include "debugging.c"

int main() {

evals("\
        ((lambda (x) x) '1)\
");
    /* evals("\ */
  /* (thing1 '1)\ */
/* "); */
    return 0;
}
