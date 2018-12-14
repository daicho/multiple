#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c, d;

    srandom(time(NULL));

    setRnd(&a, 2);
    printf("a = "); dispNumber(&a);
    setRnd(&b, 1);
    printf("b = "); dispNumber(&b);

    divide(&a, &b, &c, &d);
    printf("c = "); dispNumber(&c);
    printf("d = "); dispNumber(&d);

    return 0;
}
