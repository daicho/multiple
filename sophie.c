#include <stdio.h>
#include <sys/timeb.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER p;
    struct NUMBER a, b;
    struct NUMBER two;
    struct timeval tv;
    double tstart, tend;

    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    setInt(&two, 2);
    setIntFromString(&a, "10000");
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

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("Time : %f\n", tend - tstart);

    return 0;
}
