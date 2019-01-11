#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c;

    srand(time(NULL));

    setRnd(&a, KETA);
    printf("a = "); dispNumber(&a);
    setRnd(&b, KETA);
    printf("b = "); dispNumber(&b);

    return 0;
}
