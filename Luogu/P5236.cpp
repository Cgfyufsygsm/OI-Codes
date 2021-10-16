#include <cstdio>
#include <cctype>
#include <utility>
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

const int maxn = 2e4 + 5, maxm = 4e4 + 5;

struct edge {
    int to, nxt, w;
} e0[maxm], e[maxn << 1];

int head0[maxn], head[maxn], cnte0, cnte;
int n, m, fang, q;

void add0(int u, int v, int w) {
    e0[++cnte0].to = v;
    e0[cnte0].w = w;
    e0[cnte0].nxt = head0[u];
    head0[u] = cnte0;
    return;
}

void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

int dfn[maxn], low[maxn], dfnClock, stk[maxn], top;
int dis0[maxn], val[maxn], r[maxn];

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u;
    for (int i = head0[u]; i; i = e0[i].nxt) {
        int &v = e0[i].to;
        if (!dfn[v]) {
            val[v] = e0[i].w;
            dis0[v] = dis0[u] + e0[i].w;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                ++fang;
                r[fang] = val[stk[top]] + dis0[stk[top]] - dis0[u];
                while (true) {
                    int x = stk[top--], tmp = dis0[x] - dis0[u];
                    tmp = min(tmp, r[fang] - tmp);
                    add(fang, x, tmp), add(x, fang, tmp);
                    if (x == v) break;
                }
                add(fang, u, 0), add(u, fang, 0);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
            if (v != fa && dfn[v] < dfn[u]) val[u] = e0[i].w;
        }
    }
    return;
}

int dis[maxn], fa[maxn][20], dep[maxn];

void dfs(int u, int pre) {
    fa[u][0] = pre;
    for (int i = 1; fa[fa[u][i - 1]][i - 1]; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == pre) continue;
        dis[v] = dis[u] + e[i].w;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    return;
}

using pii = std::pair<int, int>;

pii LCA(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    for (int delta = dep[u] - dep[v], i = 0; delta; delta >>= 1, ++i)
        if (delta & 1) u = fa[u][i];
    if (u == v) return pii(u, -1);
    DEC(i, 15, 0)
        if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    if (fa[u][0] <= n) return pii(fa[u][0], -1);
    else return pii(u, v);
}

int main() {
    read(n), read(m), read(q);
    FOR(i, 1, m) {
        int u, v, w;
        read(u), read(v), read(w);
        add0(u, v, w), add0(v, u, w);
    }
    fang = n, tarjan(1, 0);
    dfs(1, 0);
    while (q--) {
        int u, v; read(u), read(v);
        auto p = LCA(u, v);
        if (~p.second)  {
            int tmp = myabs(dis0[p.first] - dis0[p.second]);
            tmp = min(tmp, r[fa[p.first][0]] - tmp);
            print(dis[u] + dis[v] - dis[p.first] - dis[p.second] + tmp, '\n');
        } else print(dis[u] + dis[v] - 2 * dis[p.first], '\n');
    }
    return output(), 0;
}