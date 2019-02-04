#include <stdio.h>
#include <sys/time.h>
#include "mulproc.h"

// 計算する時間
#define PROC_TIME 43200

int main(void)
{
    struct NUMBER p;
    struct NUMBER a;
    struct NUMBER one;
    struct timeval tv;
    double tstart, tend;
    FILE *fp;

    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    if ((fp = fopen("sophie.txt", "w")) == NULL) {
        printf("Error\n");
        return -1;
    }

    setInt(&one, 1);
    setInt(&p, 1);

    while (1) {
        // 一定時間で終了
        gettimeofday(&tv, NULL);
        if ((double)tv.tv_sec + (double)tv.tv_usec * 1.e-6 - tstart >= PROC_TIME)
            break;

        // ソフィー・ジェルマン素数だったら値を保存
        if (isSophie(&p))
            saveNumber(fp, &p);

        // 更新
        add(&p, &one, &a);
        copyNumber(&a, &p);
    }

    return 0;
}
