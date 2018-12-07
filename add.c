#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    int i, j, k, n;
    struct NUMBER a, b, c, d;

    srandom(time(NULL));

    for (n = 0; n < 1000; n++) {
        i = random() % 20000 - 10000;
        j = random() % 20000 - 10000;
        k = i - j;

        setInt(&a, i);
        setInt(&b, j);
        setInt(&c, k);
        sub(&a, &b, &d);

        if (numComp(&c, &d) != 0) {
            printf("a = "); dispNumber(&a);
            printf("b = "); dispNumber(&b);
            printf("c = "); dispNumber(&c);
            printf("d = "); dispNumber(&d);
        }
    }

    return 0;
}
