#include <stdio.h>
#include "mulproc.h"

int main(void)
{
    struct NUMBER p;
    struct NUMBER a, b;
    struct NUMBER two;
    FILE *fp;

    if ((fp = fopen("sophie.txt", "w")) == NULL) {
        printf("ファイルオープンに失敗しました\n");
        return -1;
    }

    setInt(&two, 2);
    setIntFromString(&a, "1000000000");
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

    return 0;
}
