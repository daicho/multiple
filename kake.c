#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c;

    srandom(time(NULL));

    setRnd(&a, KETA / 2);
    printf("a = "); dispNumber(&a);
    setRnd(&b, KETA / 2 + 1);
    printf("b = "); dispNumber(&b);

    if (multiple(&a, &b, &c))
        printf("over flow\n");
    printf("c = "); dispNumber(&c);

    return 0;
}
