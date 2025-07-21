#include <stdio.h>
#include "CONTRACT/contract.h"

int main() {
    printf("Exercise DbC\n");
    require(0, "oh no!");

    printf("done\n");
    return 0;
}
