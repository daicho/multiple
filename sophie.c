#include <stdio.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER p;
    struct NUMBER a, b;
    struct NUMBER two;

    setInt(&two, 2);
    setIntFromString(&a, "1000");
    setInt(&p, 3);

    while (1) {
        // 終了条件
        if (numComp(&p, &a) == 1)
            break;

        if (isSophie(&p))
            dispNumber(&p);

        // 更新
        add(&p, &two, &b);
        copyNumber(&b, &p);
    }

    return 0;
}
