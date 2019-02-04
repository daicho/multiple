#include <stdio.h>
#include <sys/time.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER p;
    struct NUMBER a, b;
    struct NUMBER two;
    struct timeval tv;
    double tstart, tend;
    FILE *fp;

    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    if ((fp = fopen("sophie.txt", "w")) == NULL) {
        printf("Error\n");
        return -1;
    }

    setInt(&two, 2);
    //setIntFromString(&a, "100000");
    setIntFromString(&p, "3");

    // 2はソフィー・ジェルマン素数
    //simpleDispNumber(&two);
    saveNumber(fp, &two);

    while (1) {
        gettimeofday(&tv, NULL);
        if ((double)tv.tv_sec + (double)tv.tv_usec * 1.e-6 - tstart >= 43200)
            break;

        if (isSophie(&p)) {
            //simpleDispNumber(&p);
            saveNumber(fp, &p);
        }

        // 更新
        add(&p, &two, &b);
        copyNumber(&b, &p);
    }

    //gettimeofday(&tv, NULL);
    //tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    //printf("Time : %f\n", tend - tstart);

    return 0;
}
