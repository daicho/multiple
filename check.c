#include <stdio.h>
#include <sys/time.h>
#include "mulproc.h"

int main(void)
{
    char str[KETA + 1];
    struct NUMBER p;
    struct NUMBER a, b;
    struct NUMBER one, two;
    FILE *fp;

    if ((fp = fopen("sophie.txt", "r")) == NULL) {
        printf("Error\n");
        return -1;
    }

    setInt(&one, 1);
    setInt(&two, 2);

    // ファイルを1行ずつ読み込み
    while(fscanf(fp, "%s\n", str) != EOF) {
        if (setString(&p, str) == -1)
            continue;

        if (isPrime(&p)) {
            // b <- 2p + 1
            multiple(&p, &two, &a);
            add(&a, &one, &b);

            if (!isPrime(&b))
                simpleDispNumber(&p);
        } else {
            simpleDispNumber(&p);
        }
    }

    return 0;
}
