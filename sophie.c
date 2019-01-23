#include <stdio.h>
#include "mulproc.h"

int main(void)
{
    int i;
    struct NUMBER a, b, c, d;
    struct NUMBER p;
    struct NUMBER one, two;

    setInt(&one, 1);
    setInt(&two, 2);

    setIntFromString(&a, "1000");
    setInt(&p, 2);

    while (1) {
        // 終了条件
        if (numComp(&p, &a) == 1)
            break;

        // 余りが0だったら素数でない
        if (isPrime(&p) == 0)
            goto update;
        
        multiple(&p, &two, &b);
        add(&b, &one, &c);
        
        if (isPrime(&c) != 0)
            dispNumber(&c);

update:
        // 更新
        add(&b, &one, &d);
        copyNumber(&d, &b);
    }

    return 0;
}
