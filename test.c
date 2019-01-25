#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c;

    srand(time(NULL));

    setInt(&a, 100000);
    squareRoot(&a, &b);

    return 0;
}
