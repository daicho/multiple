#pragma once

#define PLUS  1
#define MINUS -1
#define KETA  30

struct NUMBER {
    int n[KETA];
    int sign;
};

void clearByZero(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(const struct NUMBER *, struct NUMBER *);
void swap(struct NUMBER *, struct NUMBER *);
void dispNumber(const struct NUMBER *);

int  mulBy10(const struct NUMBER *, struct NUMBER *);
int  divBy10(const struct NUMBER *, struct NUMBER *);
int  simpleMultiple(int a, int b, int *c);
int  isZero(const struct NUMBER *);
int  numComp(const struct NUMBER *, const struct NUMBER *);

void getAbs(const struct NUMBER *, struct NUMBER *);
int  setInt(struct NUMBER *, int);
int  setIntFromString(struct NUMBER *, char *);
int  setSign(struct NUMBER *, int);
int  getSign(const struct NUMBER *);

int  add(const struct NUMBER *, const struct NUMBER *, struct NUMBER *);
int  sub(const struct NUMBER *, const struct NUMBER *, struct NUMBER *);
