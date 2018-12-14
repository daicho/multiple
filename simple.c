int  simpleMultiple(int, int, int *);
int  simpleDivide(int, int, int *, int *);

//
// 加算しか使わない乗算
//
int simpleMultiple(int a, int b, int *c)
{
    int i;
    int temp;

    // 大きい数に小さい数をかける
    if (a < b) {
        temp = a;
        a = b;
        b = temp;
    }

    // 負の数に対応
    if (b < 0) {
        a *= -1;
        b *= -1;
    }

    *c = 0;

    i = 0;
    while (1) {
        if (i >= b)
            break;
        *c += a;
        i++;
    }

    return 0;
}

//
// 加算と減算しか使わない除算
//
int simpleDivide(int a, int b, int *c, int *d)
{
    int i;
    int sign_a = 1;
    int sign_b = 1;

    if (b == 0)
        return -1;

    if (a < 0) {
        a *= -1;
        sign_a = -1;
    }

    if (b < 0) {
        b *= -1;
        sign_b = -1;
    }

    i = 0;
    while (1) {
        if (a < b)
            break;
        a -= b;
        i++;
    }

    *c = i * sign_a * sign_b;
    *d = a * sign_a;

    return 0;
}
