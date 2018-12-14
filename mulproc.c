#include "mulproc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//
// すべての桁を0で初期化
//
void clearByZero(struct NUMBER *a)
{
    int i;

    for (i = 0; i < KETA; i++)
        a->n[i] = 0;
    setSign(a, PLUS);
}

//
// 下位k桁にランダムな値をセット
//
void setRnd(struct NUMBER *a, int k)
{
    int i;

    clearByZero(a);
    for (i = 0; i < k; i++)
        a->n[i] = random() % 10;

    // ゼロだったら符号をプラスにセット
    if (isZero(a) == 0)
        setSign(a, PLUS);
    else
        setSign(a, (random() % 2) ? PLUS : MINUS);
}

//
// aをbにコピーする
//
void copyNumber(const struct NUMBER *a, struct NUMBER *b)
{
    *b = *a;
}

//
// aとbを交換する
//
void swap(struct NUMBER *a, struct NUMBER *b)
{
    struct NUMBER temp;

    copyNumber(a, &temp);
    copyNumber(b, a);
    copyNumber(&temp, b);
}

//
// 値を表示
//
void dispNumber(const struct NUMBER *a)
{
    int i;

    if (getSign(a) == PLUS)
        printf("+");
    else if (getSign(a) == MINUS)
        printf("-");

    for (i = KETA - 1; i >= 0; i--)
        printf("%2d", a->n[i]);
    putchar('\n');
}

//
// 値が0か判別する
// 戻り値：
//    0 ... a == 0
//   -1 ... a != 0
//
int isZero(const struct NUMBER *a)
{
    int i;

    for (i = 0; i < KETA; i++) {
        if (a->n[i] != 0)
            return -1;
    }
    return 0;
}

//
// a, bの大小を比較する
// 戻り地：
//    0 ... a == b
//    1 ... a > b
//   -1 ... a < b
//
int numComp(const struct NUMBER *a, const struct NUMBER *b)
{
    int i;

    if (getSign(a) == PLUS && getSign(b) == MINUS)
        return 1;
    if (getSign(a) == MINUS && getSign(b) == PLUS)
        return -1;

    if (getSign(a) == PLUS && getSign(b) == PLUS) {
        for (i = KETA - 1; i >= 0; i--) {
            if (a->n[i] > b->n[i])
                return 1;
            else if (a->n[i] < b->n[i])
                return -1;
        }
        return 0;
    }

    if (getSign(a) == MINUS && getSign(b) == MINUS) {
        struct NUMBER c, d;
        getAbs(a, &c);
        getAbs(b, &d);
        return numComp(&c, &d) * -1;
    }

    return 0;
}

//
// aの絶対値をbに返す
//
void getAbs(const struct NUMBER *a, struct NUMBER *b)
{
    copyNumber(a, b);
    setSign(b, PLUS);
}

//
// 多倍長変数aにint型変数xの値を設定する
// 戻り値：
//    0 ... 正常終了
//   -1 ... xの値がaに設定しきれなかった
//
int setInt(struct NUMBER *a, int x)
{
    int i;

    clearByZero(a);

    // 符号の設定
    if (x >= 0) {
        setSign(a, PLUS);
    } else {
        setSign(a, MINUS);
        x = -x;
    }

    for (i = 0; i < KETA; i++) {
        if (x == 0)
            return 0;

        a->n[i] = x % 10;
        x /= 10;
    }
    return -1;
}

//
// 多倍長変数aに文字列型変数xの値を設定する
// 戻り値：
//    0 ... 正常終了
//   -1 ... xの値がaに設定しきれなかった
//
int setIntFromString(struct NUMBER *a, char *x)
{
    int i, l;

    clearByZero(a);

    // 符号の設定
    if (*x == '-') {
        setSign(a, MINUS);
        x++;
    } else {
        setSign(a, PLUS);
    }

    if ((l = strlen(x)) > KETA)
        return -1;

    for (i = l - 1; i >= 0; i--) {
        if (*x < '0' || '9' < *x)
            return -1;

        a->n[i] = *x - '0';
        x++;
    }
    return 0;
}

//
// 符号を設定する
// 戻り値：
//    0 ... 正常終了
//   -1 ... sの値が異常だった場合
//
int setSign(struct NUMBER *a, int s)
{
    if (s != PLUS && s != MINUS) {
        return -1;
    } else {
        a->sign = s;
        return 0;
    }
}

//
// 符号を取得する
//
int getSign(const struct NUMBER *a)
{
    return a->sign;
}

//
// aを10倍してbに返す
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int mulBy10(const struct NUMBER *a, struct NUMBER *b)
{
    int i;

    if (a->n[KETA - 1])
        return -1;

    for (i = 0; i < KETA - 1; i++)
        b->n[i + 1] = a->n[i];
    b->n[0] = 0;
    setSign(b, getSign(a));

    return 0;
}

//
// aを1/10倍してbに返す
// 戻り値：
//   aを10で割った余り
//
int divBy10(const struct NUMBER *a, struct NUMBER *b)
{
    int i;

    for (i = 0; i < KETA - 1; i++)
        b->n[i] = a->n[i + 1];
    b->n[KETA - 1] = 0;

    // ゼロだったら符号をプラスにセット
    if (isZero(b) == 0)
        setSign(b, PLUS);
    else
        setSign(b, getSign(a));

    return a->n[0];
}

//
// c <- a + b
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int add(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i;
    int ret;
    int carry = 0;

    clearByZero(c);

    if (getSign(a) == PLUS && getSign(b) == PLUS) {
        setSign(c, PLUS);

        for (i = 0; i < KETA; i++) {
            c->n[i] = a->n[i] + b->n[i] + carry;
            carry = c->n[i] / 10;
            c->n[i] %= 10;
        }

        if (carry == 0)
            ret = 0;
        else
            ret = -1;
    }

    if (getSign(a) == MINUS && getSign(b) == MINUS) {
        struct NUMBER d, e;
        getAbs(a, &d);
        getAbs(b, &e);

        ret = add(&d, &e, c);
        setSign(c, MINUS);
    }

    if (getSign(a) == PLUS && getSign(b) == MINUS) {
        struct NUMBER d;
        getAbs(b, &d);
        ret = sub(a, &d, c);
    }

    if (getSign(a) == MINUS && getSign(b) == PLUS) {
        struct NUMBER d;
        getAbs(a, &d);
        ret = sub(b, &d, c);
    }

    return ret;
}

//
// c <- a - b
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int sub(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i;
    int ret;
    int carry = 0;

    clearByZero(c);

    if (getSign(a) == PLUS && getSign(b) == PLUS) {
        if (numComp(a, b) != -1) {
            setSign(c, PLUS);

            for (i = 0; i < KETA; i++) {
                int digit_a = a->n[i] - carry;
                int digit_b = b->n[i];

                if (digit_a >= digit_b) {
                    c->n[i] = digit_a - digit_b;
                    carry = 0;
                } else {
                    c->n[i] = 10 + digit_a - digit_b;
                    carry = 1;
                }
            }
        } else {
            sub(b, a, c);
            setSign(c, MINUS);
        }

        if (carry == 0)
            ret = 0;
        else
            ret = -1;
    }

    if (getSign(a) == MINUS && getSign(b) == PLUS) {
        struct NUMBER d;
        getAbs(a, &d);
        ret = add(&d, b, c);
        setSign(c, MINUS);
    }

    if (getSign(b) == MINUS) {
        struct NUMBER d;
        getAbs(b, &d);
        ret = add(a, &d, c);
    }

    return ret;
}

//
// c <- a * b
//
int multiple(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i, j;
    int ret;
    int carry;

    clearByZero(c);

    if (getSign(a) == PLUS && getSign(b) == PLUS) {
        for (i = 0; i < KETA ; i++) {
            struct NUMBER d;
            struct NUMBER e;

            clearByZero(&d);

            carry = 0;
            for (j = 0; j + i < KETA; j++) {
                d.n[j + i] = a->n[j] * b->n[i] + carry;
                carry = d.n[i] / 10;
                d.n[i] %= 10;
            }

            if (carry)
                return -1;

            if (add(c, &d, &e))
                return -1;

            copyNumber(&e, c);
        }

        ret = 0;
    } else {
        struct NUMBER d;
        struct NUMBER e;
        getAbs(a, &d);
        getAbs(b, &e);

        ret = multiple(&d, &e, c);

        if (getSign(a) == PLUS && getSign(b) == MINUS)
            setSign(c, MINUS);

        if (getSign(a) == MINUS && getSign(b) == PLUS)
            setSign(c, MINUS);

        if (getSign(a) == MINUS && getSign(b) == MINUS)
            setSign(c, PLUS);
    }

    return ret;
}

//
// c <- a / b の商
// d <- a / b の剰余
//
int divide(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c, struct NUMBER *d)
{
    int i;

    clearByZero(c);
    clearByZero(d);

    if (isZero(b) == 0)
        return -1;

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
