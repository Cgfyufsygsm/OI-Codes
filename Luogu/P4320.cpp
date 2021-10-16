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

const int maxn = 5e5 + 5, maxm = 1e6 + 5;
int n, m;

struct YFS {
    static const int maxn = ::maxn << 1;
    int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, fang;
    int dfn[maxn], top[maxn], dep[maxn], son[maxn], fa[maxn], size[maxn], dfnClock;
    int t[maxn << 2];

    il void add(int u, int v) {
        to[++cnte] = v;
        nxt[cnte] = head[u];
        head[u] = cnte;
        return;
    }

    void dfs1(int u, int pre) {
        dep[u] = dep[pre] + 1, fa[u] = pre, size[u] = 1;
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            if (v == pre) continue;
            dfs1(v, u);
            size[u] += size[v];
            if (size[v] > size[son[u]]) son[u] = v;
        }
        return;
    }

    void dfs2(int u, int topf) {
        top[u] = topf;
        dfn[u] = ++dfnClock;
        if (son[u]) dfs2(son[u], topf);
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }

    int LCA(int u, int v) {
        while (top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) v = fa[top[v]];
            else u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int query(int u, int v) {return (dep[u] + dep[v] - 2 * dep[LCA(u, v)]) / 2 + 1;}
} G;

struct Graph {
    int head[maxn], to[maxm << 1], nxt[maxm << 1], cnte;
    int dfn[maxn], low[maxn], stk[maxn], top, dfnClock;

    il void add(int u, int v) {
        to[++cnte] = v;
        nxt[cnte] = head[u];
        head[u] = cnte;
        return;
    }

    void tarjan(int u, YFS &G) {
        stk[++top] = u;
        dfn[u] = low[u] = ++dfnClock;
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            if (!dfn[v]) {
                tarjan(v, G);
                low[u] = min(low[u], low[v]);
                if (dfn[u] == low[v]) {
                    ++G.fang;
                    while (true) {
                        int x = stk[top--];
                        G.add(G.fang, x), G.add(x, G.fang);
                        if (x == v) break;
                    }
                    G.add(G.fang, u), G.add(u, G.fang);
                }
            } else low[u] = min(low[u], dfn[v]);
        }
        return;
    }
} G0;

int main() {
    read(n), read(m);
    G.fang = n;
    FOR(i, 1, m) {
        int u, v; read(u), read(v);
        G0.add(u, v), G0.add(v, u);
    }
    G0.tarjan(1, G);
    G.dfs1(1, 0);
    G.dfs2(1, 1);
    int q; read(q);
    while (q--) {
        int u, v; read(u), read(v);
        print(G.query(u, v), '\n');
    }
    return output(), 0;
}