#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c;

    srandom(time(NULL));

    setRnd(&a, KETA);
    printf("a = "); dispNumber(&a);
    setRnd(&b, KETA);
    printf("b = "); dispNumber(&b);

    int d;
    simpleMultiple(100, 100, &d);
    printf("%d\n", d);

    return 0;
}
