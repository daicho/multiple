#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c, d;

    setIntFromString(&a, "333333333333333331");
    printf("%d", isPrime(&a));

    return 0;
}
