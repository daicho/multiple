#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    int a, b;

    srandom(time(NULL));

    simpleDivide(7, -3, &a, &b);
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
