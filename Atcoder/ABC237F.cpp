#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 2e5 + 5;
int n, q, p[maxn], x;

struct SegmentTree {
    int sum[maxn << 2], tag[maxn << 2];
    SegmentTree() {
        memset(sum, 0, sizeof sum);
        memset(tag, -1, sizeof tag);
    }
#define M ((i + j) >> 1)
#define L (k << 1)
#define R (L | 1)
    void pushup(int k) {
        sum[k] = sum[L] + sum[R];
        return;
    }
    void build(int i, int j, int k, int x) {
        if (i == j) {
            sum[k] = (p[i] >= x);
            return;
        }
        build(i, M, L, x), build(M + 1, j, R, x);
        pushup(k);
    }
    void pushdown(int i, int j, int k) {
        if (tag[k] == -1) return;
        tag[L] = tag[R] = tag[k];
        sum[L] = (M - i + 1) * tag[k];
        sum[R] = (j - M) * tag[k];
        tag[k] = -1;
        return;
    }
    int query(int i, int j, int k, int x, int y) {
        if (x <= i && y >= j) return sum[k];
        pushdown(i, j, k);
        int ret = 0;
        if (x <= M) ret += query(i, M, L, x, y);
        if (y > M) ret += query(M + 1, j, R, x, y);
        return ret;
    }
    void modify(int i, int j, int k, int x, int y, int v) {
        if (x > y) return;
        if (x <= i && y >= j) {
            sum[k] = (j - i + 1) * v;
            tag[k] = v;
            return;
        }
        pushdown(i, j, k);
        if (x <= M) modify(i, M, L, x, y, v);
        if (y > M) modify(M + 1, j, R, x, y, v);
        pushup(k);
        return;
    }
    void sort(int c, int l, int r) {
        int s = query(1, n, 1, l, r);
        if (c == 1) {
            modify(1, n, 1, l, r - s, 0);
            modify(1, n, 1, r - s + 1, r, 1);
        } else {
            modify(1, n, 1, l, l + s - 1, 1);
            modify(1, n, 1, l + s, r, 0);
        }
        return;
    }
#undef M
#undef L
#undef R
} t1, t2;

int fin1[maxn], fin2[maxn];

int main() {
    read(n, q, x);
    FOR(i, 1, n) read(p[i]);
    t1.build(1, n, 1, x + 1);
    t2.build(1, n, 1, x);
    FOR(i, 1, q) {
        int c, l, r; read(c, l, r);
        t1.sort(c, l, r), t2.sort(c, l, r);
    }
    FOR(i, 1, n) {
        if (t1.query(1, n, 1, i, i) != t2.query(1, n, 1, i, i)) {
            print(i);
            break;
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}