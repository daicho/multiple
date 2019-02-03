#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER a, b, c, d;

    setIntFromString(&a, "3333333331");
    setIntFromString(&b, "675");
    divide(&a, &b, &c, &d);
    dispNumber(&c);
    dispNumber(&d);

    return 0;
}
