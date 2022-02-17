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
const int maxn = 1e6 + 5;
int n, q;
ll tag[maxn];

struct node {
    ll add;
    int same, col, coltag;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushup(int k) {
    t[k].col = t[L].col;
    t[k].same = (t[L].same && t[R].same && t[L].col == t[R].col);
    return;
}

void build(int i, int j, int k) {
    if (i == j) {
        t[k].add = t[k].coltag = 0;
        t[k].same = t[k].col = 1;
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    pushup(k);
    return;
}

void pushdown(int i, int j, int k) {
    if (t[k].add) {
        t[L].add += t[k].add, t[R].add += t[k].add;
        t[k].add = 0;
    }
    if (t[k].coltag) {
        t[L].same = t[R].same = 1;
        t[L].col = t[L].coltag = t[R].col = t[R].coltag = t[k].coltag;
        t[k].coltag = 0;
    }
    return;
}

ll query(int i, int j, int k, int x) {
    if (i == j) return t[k].add + tag[t[k].col];
    pushdown(i, j, k);
    if (x <= M) return query(i, M, L, x);
    else return query(M + 1, j, R, x);
}

void modify(int i, int j, int k, int x, int y, int c) {
    if (x <= i && y >= j && t[k].same) {
        t[k].add += tag[t[k].col] - tag[c];
        t[k].col = t[k].coltag = c;
        t[k].same = 1;
        return;
    }
    pushdown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, c);
    if (y > M) modify(M + 1, j, R, x, y, c);
    pushup(k);
    return;
}

int main() {
    read(n, q);
    build(1, n, 1);
    char op[10];
    while (q--) {
        read(op);
        if (op[0] == 'C') {
            int x, y, c; read(x, y, c);
            modify(1, n, 1, x, y, c);
        } else if (op[0] == 'A') {
            int c, x; read(c, x);
            tag[c] += x;
        } else {
            int x; read(x);
            print(query(1, n, 1, x));
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}