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
const int maxn = 1e6 + 5;
int n, to[maxn], w[maxn], deg[maxn];
int q[maxn], head, tail;
ll f[maxn], g[maxn];

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

ll work(int rt) {
    int u = rt;
    ll f1 = f[u], f2 = f[u], pre = w[u], r1 = g[u], r2 = -1e18;
    u = to[u];
    while (u != rt) {
        deg[u] = 0;
        r1 = max(r1, f[u] + pre + f2);
        r2 = max(r2, f[u] - pre + f1);
        r1 = max(r1, g[u]);
        f1 = max(f1, f[u] + pre);
        f2 = max(f2, f[u] - pre);
        pre += w[u];
        u = to[u];
    }
    return max(r1, r2 + pre);
}

int main() {
    read(n);
    FOR(i, 1, n) read(to[i]), read(w[i]), ++deg[to[i]];
    head = 1, tail = 0;
    FOR(i, 1, n) if (!deg[i]) q[++tail] = i;
    while (head <= tail) {
        int u = q[head++];
        g[to[u]] = max(g[to[u]], f[to[u]] + f[u] + w[u]);
        g[to[u]] = max(g[to[u]], g[u]);
        f[to[u]] = max(f[to[u]], f[u] + w[u]);
        if (!--deg[to[u]]) q[++tail] = to[u];
    }
    ll ans = 0;
    FOR(i, 1, n) if (deg[i]) ans += work(i);
    print(ans);
    return output(), 0;
}