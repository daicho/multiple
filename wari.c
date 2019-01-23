#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    int i;
    struct NUMBER p;
    struct NUMBER a, b, c, d;

    for (i = -2; i <= 120; i++) {
        setInt(&a, i);
        printf("%3d : %d\n", i, isPrime(&a));
    }

    return 0;
}
