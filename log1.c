#include <stdio.h>
#include <math.h>

#define LOOP_NUM 1000

int main(void)
{
    int k;
    double ans = 0;
    int y = 2;

    for (k = 0; k < LOOP_NUM; k++) {
        ans += (double)2 / (2 * k + 1) * pow((double)(y - 1) / (y + 1), 2 * k + 1);
    }

    printf("ans = %.20f\n", ans);
    printf("log = %.20f\n", log(y));

    return 0;
}