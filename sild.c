#include "parser.c"
#include "debugging.c"
#include "sevenfunctions.c"


int main(){
    node*test = makelist("(1 (2( (1 (3))3 6 )) 3 4)");
    printlist(test);
    printf("\n");
    debuglist(test, 0);

    return 0;
}
