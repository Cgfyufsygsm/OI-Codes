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
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using db = double;
const int maxn = 5e5 + 5;
int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
db q[maxn << 1], p[maxn];

db f[maxn], g[maxn], h[maxn], ans;

il void add(int u, int v, db pr) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    q[cnte] = pr;
    head[u] = cnte;
    return;
}

void dfs1(int u, int fa) {
    f[u] = 1 - p[u];
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        f[u] *= (f[v] + (1 - f[v]) * (1 - q[i]));
    }
    return;
}

void dfs2(int u, int fa, int pre) {
    if (fa) {
        db h;
        h = (f[u] + (1 - f[u]) * (1 - q[pre])) > 1e-6 ? g[fa] * f[fa] / (f[u] + (1 - f[u]) * (1 - q[pre])) : 0;
        g[u] = h + (1 - h) * (1 - q[pre]);
    } else g[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        dfs2(v, u, i);
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n - 1) {
        int u, v, p;
        read(u), read(v), read(p);
        add(u, v, p * 0.01), add(v, u, p * 0.01);
    }
    FOR(i, 1, n) {
        int pr; read(pr);
        p[i] = pr * 0.01;
    }
    dfs1(1, 0);
    dfs2(1, 0, 0);
    FOR(i, 1, n) ans += 1 - f[i] * g[i];
    printf("%.6lf\n", ans);
    return output(), 0;
}