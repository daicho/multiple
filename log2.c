#include <stdio.h>
#include <math.h>

#define LOOP_NUM 1000

int main(void)
{
    int k;
    long long ans = 0;
    int y = 3;

    for (k = 0; k < LOOP_NUM; k++) {
        ans += 2 / (2 * k + 1) * pow((y - 1) / (y + 1), 2 * k + 1) * 1000000;
    }

    printf("ans = %.20f\n", ans);
    printf("log = %.20f\n", log(y));

    return 0;
}