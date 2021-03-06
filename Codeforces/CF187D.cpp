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
const int maxn = 1e5 + 5;

struct Node {
    int ch[2], mn;
    Node() {mn = 1e9;}
} t[maxn * 50];
int n, tot, root;
ll g, r, s[maxn], f[maxn];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

void modify(int &k, int i, int j, int x, int v) {
    if (!k) k = ++tot;
    if (i == j) return t[k].mn = v, void();
    if (x <= M) modify(ls(k), i, M, x, v);
    else modify(rs(k), M + 1, j, x, v);
    t[k].mn = min(t[ls(k)].mn, t[rs(k)].mn);
    return;
}

int query(int k, int i, int j, int x, int y) {
    if (!k) return 1e9;
    if (x <= i && y >= j) return t[k].mn;
    int ret = 1e9;
    if (x <= M) chkmin(ret, query(ls(k), i, M, x, y));
    if (y > M) chkmin(ret, query(rs(k), M + 1, j, x, y));
    return ret;
}

int main() {
    read(n, g, r);
    FOR(i, 1, n + 1) read(s[i]), s[i] += s[i - 1];
    ll p = (g + r);
    DEC(i, n, 1) {
        int l = (g + s[i]) % p, r = (p - 1 + s[i]) % p;
        int k = 1e9;
        if (l <= r) chkmin(k, query(root, 0, p - 1, l, r));
        else chkmin(k, min(query(root, 0, p - 1, 0, r), query(root, 0, p - 1, l, p - 1)));
        if (k > n) f[i] = s[n + 1] - s[i];
        else f[i] = s[k] - s[i] + (p - (s[k] - s[i]) % p) + f[k];
        modify(root, 0, p - 1, s[i] % p, i);
    }
    int q; read(q);
    while (q--) {
        ll t0, ans; read(t0);
        int t = t0 % p;
        int l = (g - t + p) % p, r = (p - t - 1 + p) % p, k = 1e9;
        if (l <= r) chkmin(k, query(root, 0, p - 1, l, r));
        else chkmin(k, min(query(root, 0, p - 1, 0, r), query(root, 0, p - 1, l, p - 1)));
        if (k > n) ans = s[n + 1] + t0;
        else ans = f[k] + t0 + s[k] + (p - (s[k] + t0) % p);
        print(ans);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}