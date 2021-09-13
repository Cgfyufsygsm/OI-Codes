#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

typedef long long ll;

const int maxn = 2e5 + 5;

int val[maxn];

struct node {
    int l, r;
    ll ans, lenl, lenr;
    bool isone;
    node() {l = r = ans = lenl = lenr = 0; isone = 0;}
    il friend node operator+(const node &a, const node &b) {
        node ret;
        ret.ans = a.ans + b.ans;
        if (val[a.r] <= val[b.l]) ret.ans += a.lenr * b.lenl;
        ret.l = a.l, ret.r = b.r, ret.lenl = a.lenl, ret.lenr = b.lenr;
        if (a.isone && val[a.r] <= val[b.l]) ret.lenl += b.lenl;
        if (b.isone && val[a.r] <= val[b.l]) ret.lenr += a.lenr;
        ret.isone = a.isone && b.isone && (val[a.r] <= val[b.l]);
        return ret;
    }
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    t[k].l = i, t[k].r = j;
    if (i == j) {
        read(val[i]);
        t[k].lenl = t[k].lenr = t[k].isone = t[k].ans = 1;
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    t[k] = t[L] + t[R];
    return;
}

void modify(int i, int j, int k, int x, int v) {
    if (i == j) {
        val[i] = v;
        t[k].lenl = t[k].lenr = t[k].isone = t[k].ans = 1;
        return;
    }
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    t[k] = t[L] + t[R];
    return;
}

node query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    if (y <= M) return query(i, M, L, x, y);
    if (x > M) return query(M + 1, j, R, x, y);
    return query(i, M, L, x, y) + query(M + 1, j, R, x, y);
}

int main() {
    int n, q; read(n), read(q);
    build(1, n, 1);
    while (q--) {
        int op, x, y;
        read(op), read(x), read(y);
        if (op == 1) modify(1, n, 1, x, y);
        else print(query(1, n, 1, x, y).ans), putchar('\n');
    }
    return output(), 0;
}