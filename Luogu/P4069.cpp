#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define GO(u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

template<typename T> il void swap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

typedef long long ll;
const int maxn = 100000 + 5;
const ll INF = 123456789123456789;

il ll min(ll a, ll b) {return a < b ? a : b;}
il ll max(ll a, ll b) {return a > b ? a : b;}

int n, m, head[maxn], cnte;

struct edge {
    int to, nxt;
    ll dist;
} e[maxn << 1];

void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].dist = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

int fa[maxn], son[maxn], size[maxn], dep[maxn];
int dfn[maxn], nfd[maxn], top[maxn], cntDfn;
ll dis[maxn];

void dfs1(int u, int f) {
    fa[u] = f, size[u] = 1, dep[u] = dep[f] + 1;
    GO(u) {
        if (v == f) continue;
        dis[v] = dis[u] + e[i].dist;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]])
            son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    dfn[u] = ++cntDfn, top[u] = topf, nfd[dfn[u]] = u;
    if (son[u]) dfs2(son[u], topf);
    GO(u) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
    return;
}

int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

ll t[maxn << 2], minv[maxn << 2];
ll K[maxn], B[maxn];
int tot;

il ll calc(int x, int id) {return K[id] * dis[nfd[x]] + B[id];}
il void pushup(int k) {minv[k] = min(minv[k], min(minv[L], minv[R]));}

void build(int i, int j, int k) {
    minv[k] = INF, t[k] = 1;
    if (i == j) return;
    build(i, M, L);
    build(M + 1, j, R);
    return;
}

void modify(int i, int j, int k, int x, int y, int u) {
    if (x <= i && y >= j) {
        if (calc(i, u) <= calc(i, t[k]) && calc(j, u) <= calc(j, t[k])) {
            t[k] = u;
            minv[k] = min(minv[k], min(calc(i, u), calc(j, u)));
            return;
        }
        if (calc(i, u) >= calc(i, t[k]) && calc(j, u) >= calc(j, t[k])) return;
        if (K[u] < K[t[k]]) {
            if (calc(M, u) <= calc(M, t[k]))
                modify(i, M, L, x, y, t[k]), t[k] = u;
            else modify(M + 1, j, R, x, y, u);
        } else {
            if (calc(M, u) <= calc(M, t[k]))
                modify(M + 1, j, R, x, y, t[k]), t[k] = u;
            else modify(i, M, L, x, y, u);
        }
        return minv[k] = min(minv[k], min(calc(i, u), calc(j, u))), pushup(k);
    }
    if (x <= M) modify(i, M, L, x, y, u);
    if (y > M) modify(M + 1, j, R, x, y, u);
    pushup(k);
    return;
}

ll query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return minv[k];
    ll ret = INF;
    if (B[t[k]] != INF) ret = min(ret, min(calc(max(i, x), t[k]), calc(min(j, y), t[k])));
    if (x <= M) ret = min(ret, query(i, M, L, x, y));
    if (y > M) ret = min(ret, query(M + 1, j, R, x, y));
    return ret;
}

void modify(int u, int v) {
    while (top[u] != top[v])
        modify(1, n, 1, dfn[top[u]], dfn[u], tot), u = fa[top[u]];
    modify(1, n, 1, dfn[v], dfn[u], tot);
    return;
}

void modify(int s, int t, ll a, ll b) {
    int lca = LCA(s, t);
    K[++tot] = -a, B[tot] = a * dis[s] + b;
    modify(s, lca);
    K[++tot] = a, B[tot] = a * (dis[s] - 2 * dis[lca]) + b;
    modify(t, lca);
    return;
}

ll query(int s, int t) {
    ll ret = INF;
    while (top[s] != top[t]) {
        if (dep[top[s]] < dep[top[t]]) swap(s, t);
        ret = min(ret, query(1, n, 1, dfn[top[s]], dfn[s]));
        s = fa[top[s]];
    }
    if (dep[s] > dep[t]) swap(s, t);
    return min(ret, query(1, n, 1, dfn[s], dfn[t]));
}

int main() {
    n = read(), m = read();
    FOR(i, 1, n - 1) {
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    B[tot = 1] = INF;
    build(1, n, 1);
    while (m--) {
        int op = read(), s = read(), t = read();
        if (op == 1) {
            ll a = read(), b = read();
            modify(s, t, a, b);
        } else printf("%lld\n", query(s, t));
    }
    return 0;
}