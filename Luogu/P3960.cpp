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

const int maxn = 3e5 + 5;
using ll = long long;

mt19937 rnd(20041031);
struct Node {
    int ch[2], key;
    ll l, r, size;
} t[maxn * 50];
int root[maxn], tot, n, m, q;

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]

int newnode(ll l, ll r) {
    t[++tot].l = l, t[tot].r = r;
    t[tot].key = rnd();
    t[tot].size = r - l + 1;
    ls(tot) = rs(tot) = 0;
    return tot;
}

il void pushup(int u) {
    t[u].size = t[ls(u)].size + t[rs(u)].size + t[u].r - t[u].l + 1;
    return;
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (t[x].key < t[y].key) return rs(x) = merge(rs(x), y), pushup(x), x;
    else return ls(y) = merge(x, ls(y)), pushup(y), y;
}

void split(int u, ll k) {
    if (k >= t[u].r - t[u].l + 1) return;
    ll want = t[u].l + k - 1;
    int v = newnode(want + 1, t[u].r);
    t[u].r = want;
    rs(u) = merge(v, rs(u));
    return pushup(u);
}

void split(int u, ll sz, int &x, int &y) {
    if (!u) return x = 0, y = 0, void();
    if (t[ls(u)].size >= sz) y = u, split(ls(u), sz, x, ls(u));
    else {
        split(u, sz - t[ls(u)].size);
        x = u, split(rs(u), sz - t[ls(u)].size - (t[u].r - t[u].l + 1), rs(u), y);
    }
    return pushup(u);
}

int main() {
    read(n, m, q);
    if (m > 1) FOR(i, 1, n) root[i] = newnode(1ll * (i - 1) * m + 1, 1ll * i * m - 1);
    FOR(i, 1, n) root[n + 1] = merge(root[n + 1], newnode(1ll * i * m, 1ll * i * m));
    while (q--) {
        int x, y; read(x, y);
        if (y == m) {
            int a, b, c;
            split(root[n + 1], x - 1, a, b);
            split(b, 1, b, c);
            print(t[b].l);
            root[n + 1] = merge(merge(a, c), b);
        } else {
            int a, b, c;
            split(root[x], y, a, b);
            split(a, y - 1, a, c);
            print(t[c].l);
            int d, e, f;
            split(root[n + 1], x, d, e);
            split(d, x - 1, d, f);
            root[x] = merge(merge(a, b), f);
            root[n + 1] = merge(merge(d, e), c);
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}