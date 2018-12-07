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

    printf("%d\n", numComp(&a, &b));

    return 0;
}
