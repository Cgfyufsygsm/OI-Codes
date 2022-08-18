#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 5e4 + 5, mod = 201314;
vector<int> G[maxn];
int fa[maxn], size[maxn], son[maxn], dep[maxn];
int top[maxn], dfn[maxn], nfd[maxn], dfnTot;
int n, m, ans[maxn];
struct Query {
    int op, x, z, id;
} q[maxn << 1];

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
    dfn[u] = ++dfnTot;
    if (son[u]) dfs2(son[u], topf);
    for (int v : G[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
    return;
}

struct Node {
    int sum, tag;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushTag(int i, int j, int k, int v) {
    t[k].sum = (t[k].sum + (j - i + 1ll) * v) % mod;
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
    is >> n >> m;
    FOR(i, 2, n) is >> fa[i], ++fa[i], G[fa[i]].emplace_back(i);
    FOR(i, 1, m) {
        int l, r, z; is >> l >> r >> z;
        ++r, ++z;
        q[2 * i - 1] = {mod - 1, l, z, i};
        q[2 * i] = {1, r, z, i};
    }
    dfs1(1), dfs2(1, 1);
    m <<= 1;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return a.x < b.x;});
    int cur = 0;
    FOR(i, 1, m) {
        while (cur < q[i].x)
            modify(1, ++cur);
        ans[q[i].id] = (ans[q[i].id] + 1ll * q[i].op * query(1, q[i].z) % mod) % mod;
    }
    FOR(i, 1, m >> 1) os << ans[i] << '\n';
    return 0;
}