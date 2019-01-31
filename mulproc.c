#include "mulproc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct NUMBER ONE = {{1}, PLUS};
struct NUMBER TWO = {{2}, PLUS};

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
        a->n[i] = rand() % 10;

    // ゼロだったら符号をプラスにセット
    if (isZero(a) == 0)
        setSign(a, PLUS);
    else
        setSign(a, (rand() % 2) ? PLUS : MINUS);
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
        printf("%6d", a->n[i]);
    putchar('\n');
}

//
// シンプルに値を表示
//
void simpleDispNumber(const struct NUMBER *a)
{
    int i;

    if (getSign(a) == MINUS)
        printf("-");

    for (i = KETA - 1; i >= 0; i--)
        if (a->n[i]) break;

    for (; i >= 0; i--)
        printf("%d", a->n[i]);

    putchar('\n');
}

//
// ファイルに値を保存
//
void saveNumber(FILE *fp, const struct NUMBER *a)
{
    int i;

    if (getSign(a) == MINUS)
        fprintf(fp, "-");

    for (i = KETA - 1; i >= 0; i--)
        if (a->n[i]) break;

    for (; i >= 0; i--)
        fprintf(fp, "%d", a->n[i]);

    fputc('\n', fp);
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
        // 上位桁から順番に比較
        for (i = KETA - 1; i >= 0; i--) {
            if (a->n[i] > b->n[i])
                return 1;
            else if (a->n[i] < b->n[i])
                return -1;
        }
        return 0;
    }

    if (getSign(a) == MINUS && getSign(b) == MINUS) {
        // 絶対値を比較した結果を反転
        struct NUMBER c, d;
        getAbs(a, &c);
        getAbs(b, &d);
        return numComp(&c, &d) * -1;
    }

    return 0;
}

//
// aが素数かどうか判定する
// 戻り値：
//   0 ... 素数でない
//   1 ... 素数
//
int isPrime(const struct NUMBER *a)
{
    struct NUMBER i;
    struct NUMBER b, c, d, e, f, g;

    // 2より小さければ素数でない
    if (numComp(a, &TWO) == -1)
        return 0;

    // 2は素数
    if (numComp(a, &TWO) == 0)
        return 1;

    divide(a, &TWO, &b, &c);

    // 2で割り切れれば素数でない
    if (isZero(&c) == 0)
        return 0;
    
    squareRoot(a, &g);
    setInt(&i, 3);

    while (1) {
        // sqrt(a)を上回ったら終了
        if (numComp(&i, &g) == 1)
            break;

        // 余りが0だったら素数でない
        divide(a, &i, &d, &e);
        if (isZero(&e) == 0)
            return 0;

        // 更新
        add(&i, &TWO, &f);
        copyNumber(&f, &i);
    }

    return 1;
}

//
// aがソフィー・ジェルマン素数かどうか判定する
// 戻り値：
//   0 ... ソフィー・ジェルマン素数でない
//   1 ... ソフィー・ジェルマン素数
//
int isSophie(const struct NUMBER *a) {
    struct NUMBER b, c;

    if (isPrime(a)) {
        // c <- 2a + 1
        if (multiple(a, &TWO, &b)) return 0;
        if (add(&b, &ONE, &c))     return 0;

        if (isPrime(&c))
            return 1;
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
// aをN倍してbに返す
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int mulByN(const struct NUMBER *a, struct NUMBER *b)
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
// aを1/N倍してbに返す
// 戻り値：
//   aをNで割った余り
//
int divByN(const struct NUMBER *a, struct NUMBER *b)
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
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int add(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i;
    int carry = 0;

    clearByZero(c);

    if (getSign(a) == PLUS && getSign(b) == PLUS) {
        setSign(c, PLUS);

        for (i = 0; i < KETA; i++) {
            c->n[i] = a->n[i] + b->n[i] + carry;
            carry = c->n[i] / 10;
            c->n[i] %= 10;
        }

        // すべての計算が終わっても桁上りがあったらオーバーフロー
        if (carry == 0)
            return 0;
        else
            return -1;
    }

    // (-a) + (-b) = -((+a) + (+b))
    if (getSign(a) == MINUS && getSign(b) == MINUS) {
        struct NUMBER d, e;
        getAbs(a, &d);
        getAbs(b, &e);

        if (add(&d, &e, c) == 0) {
            setSign(c, MINUS);
            return 0;
        } else {
            return -1;
        }
    }

    // (+a) + (-b) = (+a) - (+b)
    if (getSign(a) == PLUS && getSign(b) == MINUS) {
        struct NUMBER d;
        getAbs(b, &d);
        return sub(a, &d, c);
    }

    // (-a) + (+b) = (+b) - (+a)
    if (getSign(a) == MINUS && getSign(b) == PLUS) {
        struct NUMBER d;
        getAbs(a, &d);
        return sub(b, &d, c);
    }

    return 0;
}

//
// c <- a - b
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int sub(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i;
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

        // すべての計算が終わっても桁借りがあったらオーバーフロー
        if (carry == 0)
            return 0;
        else
            return -1;
    }

    // (-a) - (+b) = -((+a) + (+b))
    if (getSign(a) == MINUS && getSign(b) == PLUS) {
        struct NUMBER d;
        getAbs(a, &d);

        if (add(&d, b, c) == 0) {
            setSign(c, MINUS);
            return 0;
        } else {
            return -1;
        }
    }

    // a - (-b) = a + (+b)
    if (getSign(b) == MINUS) {
        struct NUMBER d;
        getAbs(b, &d);
        return add(a, &d, c);
    }

    return 0;
}

//
// c <- a * b
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int multiple(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    int i, j;
    int carry;

    clearByZero(c);

    if (getSign(a) == getSign(b)) {
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

            // すべての計算が終わっても桁上りがあったらオーバーフロー
            if (carry)
                return -1;

            // 加算時のオーバーフロー
            if (add(c, &d, &e))
                return -1;

            copyNumber(&e, c);
        }

        return 0;
    } else {
        struct NUMBER d, e;

        // 異符号ならば絶対値同士の計算結果の符号を反転する
        getAbs(a, &d);
        getAbs(b, &e);

        if (multiple(&d, &e, c)) {
            setSign(c, MINUS);
            return 0;
        } else {
            return -1;
        }
    }
}

//
// c <- a / b の商
// d <- a / b の剰余
// 戻り値：
//    0 ... 正常終了
//   -1 ... ゼロで除算
//
int divide(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c, struct NUMBER *d)
{
    struct NUMBER e, f, g;

    if (isZero(b) == 0)
        return -1;

    copyNumber(a, d);
    clearByZero(c);

    while (numComp(d, b) != -1) {
        copyNumber(b, &f);
        setInt(&g, 1);

        while (1) {
            mulByN(&f, &e);
            if (numComp(d, &e) != 1)
                break;

            copyNumber(&e, &f);

            mulByN(&g, &e);
            copyNumber(&e, &g);
        }

        sub(d, &f, &e);
        copyNumber(&e, d);

        add(c, &g, &e);
        copyNumber(&e, c);
    }

    return 0;
}

//
// b <- a + 1
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int increment(const struct NUMBER *a, struct NUMBER *b)
{
    return add(a, &ONE, b);
}

//
// b <- a - 1
// 戻り値：
//    0 ... 正常終了
//   -1 ... オーバーフロー
//
int decrement(const struct NUMBER *a, struct NUMBER *b)
{
    return sub(a, &ONE, b);
}

//
// b <- sqrt(a)
// 戻り値：
//   0 ... 正常終了
//
int squareRoot(const struct NUMBER *a, struct NUMBER *b)
{
    struct NUMBER c, d, e, f, g;

    copyNumber(a, &c);
    clearByZero(b);
    setInt(&d, 1);

    while (1) {
        if (numComp(&c, &d) == -1)
            break;

        sub(&c, &d, &e);
        copyNumber(&e, &c);

        // 更新
        increment(b, &g);
        copyNumber(&g, b);

        add(&d, &TWO, &f);
        copyNumber(&f, &d);
    }

    return 0;
}

/*
//
// c <- a^b
//
int power(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b % 2 == 0) return power(a * a, b / 2);
    return a * power(a, b - 1);
}

//
// c <- aとbの最大公約数
//
int gcd(const struct NUMBER *a, const struct NUMBER *b, struct NUMBER *c)
{
    struct NUMBER d;
    div(a, b, NULL, &d);
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b % 2 == 0) return power(a * a, b / 2);
    return a * power(a, b - 1);
}
*/
