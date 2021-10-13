#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int maxn = 35005, maxm = 70005;

struct edge {
    int u, v, w;
} e[maxm];

int head[maxn], to[maxm], nxt[maxm], cnte, tot;
int ufs[maxn], n, m, k, val[maxn];
int fa[maxn], top[maxn], dep[maxn], son[maxn], size[maxn];

il int find(int u) {return u == ufs[u] ? u : ufs[u] = find(ufs[u]);}

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs1(int u, int f) {
    size[u] = 1, fa[u] = f, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) v = fa[top[v]];
        else u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void kruskal() {
    std::sort(e + 1, e + m + 1, [](const edge &a, const edge &b) -> bool {return a.w < b.w;});
    FOR(i, 1, m) {
        int u = e[i].u, v = e[i].v;
        u = find(u), v = find(v);
        if (u == v) continue;
        ++tot;
        ufs[tot] = ufs[u] = ufs[v] = tot;
        add(u, tot), add(tot, u);
        add(v, tot), add(tot, v);
        val[tot] = e[i].w;
        if (tot == 2 * n - 1) break;
    }
    dfs1(tot, 0), dfs2(tot, tot);
    return;
}

int main() {
    read(n), read(m), read(k);
    FOR(i, 1, n) ufs[i] = i;
    tot = n;
    FOR(i, 1, m) read(e[i].u), read(e[i].v), read(e[i].w);
    kruskal();
    while (k--) {
        int u, v; read(u), read(v);
        print(val[LCA(u, v)], '\n');
    }
    return output(), 0;
}