#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 1e5 + 5;

struct node {
    int val, ch[2];
    node() {val = 1e9;}
} t[maxn << 5];
int tot, root, n, q;
ll s[maxn], g, r, f[maxn];

#define ls(k) t[k].ch[0]
#define rs(k) t[k].ch[1]
#define M ((i + j) >> 1)

void modify(int &k, int i, int j, int x, int v) {
    if (!k) k = ++tot;
    if (i == j) {
        chkmin(t[k].val, v);
        return;
    }
    if (x <= M) modify(ls(k), i, M, x, v), chkmin(t[k].val, t[ls(k)].val);
    else modify(rs(k), M + 1, j, x, v), chkmin(t[k].val, t[rs(k)].val);
    return;
}

int query(int k, int i, int j, int x, int y) {
    if (!k) return 1e9;
    if (x <= i && y >= j) return t[k].val;
    int res = 1e9;
    if (x <= M) chkmin(res, query(ls(k), i, M, x, y));
    if (y > M) chkmin(res, query(rs(k), M + 1, j, x, y));
    return res;
}

int main() {
    read(n), read(g), read(r);
    ll p = g + r;
    FOR(i, 1, n + 1) read(s[i]), s[i] += s[i - 1];
    DEC(i, n, 1) {
        ll _t = (p - s[i] % p) % p;
        int k = query(root, 0, p - 1, max(0ll, g - _t), p - _t - 1);
        if (g - _t < 0) chkmin(k, query(root, 0, p - 1, g - _t + p, p - 1));
        if (k > n) f[i] = s[n + 1] - s[i];
        else f[i] = s[k] - s[i] + (p - (s[k] - s[i]) % p) + f[k];
        modify(root, 0, p - 1, s[i] % p, i);
    }
    read(q);
    while (q--) {
        ll t0, ans;
        read(t0);
        ll t = t0 % p;
        int k = query(root, 0, p - 1, max(0ll, g - t), p - t - 1);
        if (g - t < 0) chkmin(k, query(root, 0, p - 1, g - t + p, p - 1));
        if (k > n) ans = s[n + 1] + t0;
        else ans = s[k] + t0 + (p - (s[k] + t0) % p) + f[k];
        print(ans, '\n');
    }
    return output(), 0;
}