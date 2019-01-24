#include <stdio.h>
#include <time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER p;
    struct NUMBER a, b;
    struct NUMBER two;
    time_t start = time(NULL);

    setInt(&two, 2);
    setIntFromString(&a, "100000");
    setIntFromString(&p, "3");

    // 2はソフィー・ジェルマン素数
    simpleDispNumber(&two);

    while (numComp(&p, &a) == -1) {
        if (isSophie(&p))
            simpleDispNumber(&p);

        // 更新
        add(&p, &two, &b);
        copyNumber(&b, &p);
    }

    printf("Time : %lld\n", time(NULL) - start);

    return 0;
}
