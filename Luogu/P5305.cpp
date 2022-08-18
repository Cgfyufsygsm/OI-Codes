#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 5e4 + 5, mod = 998244353;
vector<int> G[maxn];
int fa[maxn], size[maxn], son[maxn], dep[maxn];
int top[maxn], dfn[maxn], nfd[maxn], dfnTot;
int n, m, ans[maxn], K, powK[maxn];
struct Query {
    int x, y, id;
} q[maxn];

int qPow(int a, int b) {
    int ret = 1;
    for (a %= mod; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1) ret = 1ll * ret * a % mod;
    return ret;
}

void dfs1(int u) {
    size[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int v : G[u]) {
        dfs1(v);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    dfn[u] = ++dfnTot, nfd[dfn[u]] = u;
    if (son[u]) dfs2(son[u], topf);
    for (int v : G[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
    return;
}

struct Node {
    int sum, tag, val;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    if (i == j) {
        t[k].val = (powK[dep[nfd[i]]] - powK[dep[fa[nfd[i]]]] + mod) % mod;
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    t[k].val = (t[L].val + t[R].val) % mod;
    return;
}

il void pushTag(int i, int j, int k, int v) {
    t[k].sum = (t[k].sum + 1ll * v * t[k].val % mod) % mod;
    t[k].tag = (t[k].tag + v) % mod;
    return;
}

il void pushDown(int i, int j, int k) {
    if (!t[k].tag) return;
    pushTag(i, M, L, t[k].tag), pushTag(M + 1, j, R, t[k].tag);
    t[k].tag = 0;
    return;
}

il void pushUp(int k) {t[k].sum = (t[L].sum + t[R].sum) % mod;}

void modify(int i, int j, int k, int x, int y, int v) {
    if (x <= i && y >= j) return pushTag(i, j, k, v);
    pushDown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, v);
    if (y > M) modify(M + 1, j, R, x, y, v);
    return pushUp(k);
}

void modify(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        modify(1, n, 1, dfn[top[u]], dfn[u], 1);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    modify(1, n, 1, dfn[u], dfn[v], 1);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].sum;
    pushDown(i, j, k);
    int ret = 0;
    if (x <= M) (ret += query(i, M, L, x, y)) %= mod;
    if (y > M) (ret += query(M + 1, j, R, x, y)) %= mod;
    return ret;
}

int query(int u, int v) {
    int ret = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = (ret + query(1, n, 1, dfn[top[u]], dfn[u])) % mod;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return (ret + query(1, n, 1, dfn[u], dfn[v])) % mod;
}

int main() {
    is >> n >> m >> K;
    FOR(i, 1, n) powK[i] = qPow(i, K);
    FOR(i, 2, n) is >> fa[i], G[fa[i]].emplace_back(i);
    FOR(i, 1, m) {
        int x, y; is >> x >> y;
        q[i] = {x, y, i};
    }
    dfs1(1), dfs2(1, 1);
    build(1, n, 1);
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return a.x < b.x;});
    int cur = 0;
    FOR(i, 1, m) {
        while (cur < q[i].x)
            modify(1, ++cur);
        ans[q[i].id] = query(1, q[i].y);
    }
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}