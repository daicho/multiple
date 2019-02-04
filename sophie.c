#include <stdio.h>
#include <sys/time.h>
#include "mulproc.h"

// 算出するソフィー・ジェルマン素数の数
#define NUM_COUNT 10000

int main(void)
{
    int cnt;
    struct NUMBER a, p;
    struct NUMBER one;
    struct timeval tv;
    double tstart, tend;

    // 開始時刻を記録
    gettimeofday(&tv, NULL);
    tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;

    setInt(&one, 1);
    setInt(&p, 1);

    cnt = 0;
    while (cnt < NUM_COUNT) {
        // ソフィー・ジェルマン素数だったら値を表示
        if (isSophie(&p)) {
            simpleDispNumber(&p);
            cnt++;
        }

        // 更新
        add(&p, &one, &a);
        copyNumber(&a, &p);
    }

    gettimeofday(&tv, NULL);
    tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
    printf("Time : %f\n", tend - tstart);

    return 0;
}
