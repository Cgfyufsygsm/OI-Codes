#include <cstdio>
#include <cctype>
#include <vector>
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
using ll = long long;
const int maxn = 2e5 + 5;

struct edge {
    int to;
    ll w;
    edge(int v = 0, ll c = 0) : to(v), w(c) {}
};
std::vector<edge> G[maxn];
int son[maxn], n;
ll f[maxn], g[maxn], h[maxn], D[maxn];

void dfs1(int u, int fa) {
    for (auto &e : G[u]) {
        int v = e.to;
        ll c = e.w;
        if (v == fa) continue;
        dfs1(v, u);
        ll tmp = max(f[v], D[v]) + c;
        if (tmp > f[u]) g[u] = f[u], f[u] = tmp, son[u] = v;
        else if (tmp > g[u]) g[u] = tmp;
    }
    return;
}

void dfs2(int u, int fa) {
    for (auto &e : G[u]) {
        int v = e.to;
        ll c = e.w;
        if (v == fa) continue;
        if (son[u] == v) h[v] = max(max(g[u], h[u]), D[u]) + c;
        else h[v] = max(max(f[u], h[u]), D[u]) + c;
        dfs2(v, u);
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n - 1) {
        int a, b; ll c;
        read(a), read(b), read(c);
        G[a].push_back(edge(b, c));
        G[b].push_back(edge(a, c));
    }
    FOR(i, 1, n) read(D[i]);
    dfs1(1, 0);
    dfs2(1, 0);
    FOR(i, 1, n) print(max(h[i], f[i]), '\n');
    return output(), 0;
}