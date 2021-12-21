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
    while (!isspace(c)) s[p++] = c, c = getchar();
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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 5e5 + 5;

int a[maxn], b[maxn];

struct node {
    int maxa, minb, val1, val2, ans;
    node() {maxa = val1 = val2 = ans = -1e9, minb = 1e9;}
} t[maxn << 2];

//val1  : max(ai - bj) i < j
// val2 : max(ai - bj) i > j

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

node operator+(const node &a, const node &b) {
    node res;
    res.maxa = max(a.maxa, b.maxa);
    res.minb = min(a.minb, b.minb);
    res.val1 = max(a.val1, b.val1, a.maxa - b.minb);
    res.val2 = max(a.val2, b.val2, b.maxa - a.minb);
    res.ans = max(a.ans, b.ans, a.maxa + b.val2, b.maxa + a.val1);
    return res;
}

void build(int i, int j, int k) {
    if (i == j) {
        t[k].maxa = a[i], t[k].minb = b[i];
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    t[k] = t[L] + t[R];
    return;
}

void modify1(int i, int j, int k, int x, int v) {
    if (i == j) {
        t[k].maxa = v;
        return;
    }
    if (x <= M) modify1(i, M, L, x, v);
    else modify1(M + 1, j, R, x, v);
    t[k] = t[L] + t[R];
    return;
}

void modify2(int i, int j, int k, int x, int v) {
    if (i == j) {
        t[k].minb = v;
        return;
    }
    if (x <= M) modify2(i, M, L, x, v);
    else modify2(M + 1, j, R, x, v);
    t[k] = t[L] + t[R];
    return;
}

node query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) {
        return t[k];
    }
    if (y <= M) return query(i, M, L, x, y);
    if (x > M) return query(M + 1, j, R, x, y);
    return query(i, M, L, x, y) + query(M + 1, j, R, x, y);
}

int main() {
    int n, m; read(n, m);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]);
    build(1, n, 1);
    while (m--) {
        int op, x, y; read(op, x, y);
        if (op == 1) modify1(1, n, 1, x, y);
        else if (op == 2) modify2(1, n, 1, x, y);
        else print(query(1, n, 1, x, y).ans);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}