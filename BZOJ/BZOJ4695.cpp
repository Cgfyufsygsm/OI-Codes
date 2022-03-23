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

using ll = long long;
const int maxn = 5e5 + 5;
const int INF = 1e9;

struct Node {
    int mx1, mx2, mn1, mn2, cntmx, cntmn, tagmx, tagmn;
    ll sum, tag;
    void init(int val) {
        mx1 = mn1 = sum = val;
        mx2 = -INF, mn2 = INF;
        cntmx = cntmn = 1;
        tagmx = tagmn = tag = 0;
        return;
    }
} t[maxn << 2];

int a[maxn], n;

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushUp(int k) {
    t[k].sum = t[L].sum + t[R].sum;

    t[k].mx1 = max(t[L].mx1, t[R].mx1);
    t[k].mn1 = min(t[L].mn1, t[R].mn1);

    if (t[L].mx1 == t[R].mx1) t[k].mx2 = max(t[L].mx2, t[R].mx2), t[k].cntmx = t[L].cntmx + t[R].cntmx;
    else if (t[k].mx1 == t[L].mx1) t[k].mx2 = max(t[L].mx2, t[R].mx1), t[k].cntmx = t[L].cntmx;
    else if (t[k].mx1 == t[R].mx1) t[k].mx2 = max(t[L].mx1, t[R].mx2), t[k].cntmx = t[R].cntmx;

    if (t[L].mn1 == t[R].mn1) t[k].mn2 = min(t[L].mn2, t[R].mn2), t[k].cntmn = t[L].cntmn + t[R].cntmn;
    else if (t[k].mn1 == t[L].mn1) t[k].mn2 = min(t[L].mn2, t[R].mn1), t[k].cntmn = t[L].cntmn;
    else if (t[k].mn1 == t[R].mn1) t[k].mn2 = min(t[L].mn1, t[R].mn2), t[k].cntmn = t[R].cntmn;

    return;
}

void build(int i, int j, int k) {
    if (i == j) return t[k].init(a[i]);
    build(i, M, L), build(M + 1, j, R);
    return pushUp(k);
}

void pushTag(int i, int j, int k, int tagmx, int tagmn, int tag) {
    if (t[k].mn1 == t[k].mx1) {
        if (tagmn == tag) tagmn = tagmx;
        else tagmx = tagmn;
        t[k].sum += 1ll * tagmn * t[k].cntmn;
    }
    else t[k].sum += 1ll * tagmn * t[k].cntmn + 1ll * tagmx * t[k].cntmx
        + 1ll * tag * (j - i + 1 - t[k].cntmn - t[k].cntmx);
    if (t[k].mn2 == t[k].mx1) t[k].mn2 += tagmx;
    else if (t[k].mn2 != INF) t[k].mn2 += tag;
    if (t[k].mx2 == t[k].mn1) t[k].mx2 += tagmn;
    else if (t[k].mx2 != -INF) t[k].mx2 += tag;
    t[k].mn1 += tagmn, t[k].mx1 += tagmx;
    t[k].tagmn += tagmn, t[k].tagmx += tagmx, t[k].tag += tag;
}

void pushDown(int i, int j, int k) {
    int mn = min(t[L].mn1, t[R].mn1);
    int mx = max(t[L].mx1, t[R].mx1);
    pushTag(i, M, L, t[L].mx1 == mx ? t[k].tagmx : t[k].tag, t[L].mn1 == mn ? t[k].tagmn : t[k].tag, t[k].tag);
    pushTag(M + 1, j, R, t[R].mx1 == mx ? t[k].tagmx : t[k].tag, t[R].mn1 == mn ? t[k].tagmn : t[k].tag, t[k].tag);
    t[k].tagmn = t[k].tagmx = t[k].tag = 0;
}

void add(int i, int j, int k, int x, int y, int v) {
    if (x <= i && y >= j) return pushTag(i, j, k, v, v, v);
    pushDown(i, j, k);
    if (x <= M) add(i, M, L, x, y, v);
    if (y > M) add(M + 1, j, R, x, y, v);
    pushUp(k);
    return;
}

void toMax(int i, int j, int k, int x, int y, int v) {
    if (v <= t[k].mn1) return;
    if (x <= i && y >= j && v < t[k].mn2) return pushTag(i, j, k, 0, v - t[k].mn1, 0);
    pushDown(i, j, k);
    if (x <= M) toMax(i, M, L, x, y, v);
    if (y > M) toMax(M + 1, j, R, x, y, v);
    pushUp(k);
    return;
}

void toMin(int i, int j, int k, int x, int y, int v) {
    if (t[k].mx1 <= v) return;
    if (x <= i && y >= j && v > t[k].mx2) return pushTag(i, j, k, v - t[k].mx1, 0, 0);
    pushDown(i, j, k);
    if (x <= M) toMin(i, M, L, x, y, v);
    if (y > M) toMin(M + 1, j, R, x, y, v);
    pushUp(k);
    return;
}

ll querySum(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].sum;
    pushDown(i, j, k);
    ll ret = 0;
    if (x <= M) ret += querySum(i, M, L, x, y);
    if (y > M) ret += querySum(M + 1, j, R, x, y);
    return ret;
}

int queryMin(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].mn1;
    pushDown(i, j, k);
    int ret = 1e9;
    if (x <= M) chkmin(ret, queryMin(i, M, L, x, y));
    if (y > M) chkmin(ret, queryMin(M + 1, j, R, x, y));
    return ret;
}

int queryMax(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].mx1;
    pushDown(i, j, k);
    int ret = -1e9;
    if (x <= M) chkmax(ret, queryMax(i, M, L, x, y));
    if (y > M) chkmax(ret, queryMax(M + 1, j, R, x, y));
    return ret;
}

int main() {
    //freopen("BZOJ4695.in", "r", stdin);
    //freopen("BZOJ4695.out", "w", stdout);
    read(n);
    FOR(i, 1, n) read(a[i]);
    build(1, n, 1);
    int m; read(m);
    while (m--) {
        int op, l, r, v; read(op, l, r);
        if (op <= 3) read(v);
        if (op == 1) add(1, n, 1, l, r, v);
        else if (op == 2) toMax(1, n, 1, l, r, v);
        else if (op == 3) toMin(1, n, 1, l, r, v);
        else if (op == 4) print(querySum(1, n, 1, l, r));
        else if (op == 5) print(queryMax(1, n, 1, l, r));
        else print(queryMin(1, n, 1, l, r));
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}