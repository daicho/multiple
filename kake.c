#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c;

    srandom(time(NULL));

    setRnd(&a, 3);
    printf("a = "); dispNumber(&a);
    setRnd(&b, 3);
    printf("b = "); dispNumber(&b);

    multiple(&a, &b, &c);
    printf("c = "); dispNumber(&c);

    return 0;
}
