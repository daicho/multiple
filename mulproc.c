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
    int mod;

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

    for (i = KETA - 1; i >= 0; i--) {
        if (a->n[i] > b->n[i])
            return 1;
        else if (a->n[i] < b->n[i])
            return -1;
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
// c <- a + b
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int add(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i;
    int carry = 0;

    clearByZero(c);

    for (i = 0; i < KETA; i++) {
        c->n[i] = a->n[i] + b->n[i] + carry;
        carry = c->n[i] / 10;
        c->n[i] %= 10;
    }

    if (carry == 0)
        return 0;
    else
        return -1;
}

//
// c <- a - b
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int sub(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i;
    int carry = 0;

    clearByZero(c);

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

    if (carry == 0)
        return 0;
    else
        return -1;
}
