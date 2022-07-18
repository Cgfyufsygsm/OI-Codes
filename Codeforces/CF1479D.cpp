#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
using ull = unsigned long long;
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
const int maxn = 3e5 + 5;
int n, m, a[maxn];
ull val[maxn];
vector<int> G[maxn];
int fa[maxn], dep[maxn], size[maxn], son[maxn], top[maxn];

void dfs1(int u, int pre) {
    fa[u] = pre, dep[u] = dep[pre] + 1, size[u] = 1;
    for (auto &v : G[u]) if (v != pre) {
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf;
    if (son[u]) dfs2(son[u], topf);
    for (auto &v : G[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
    return;
}

int getLCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

struct Node {
    int ch[2];
    ull val;
} t[maxn * 50];
int root[maxn], tot;

il int clone(int u) {
    t[++tot] = t[u];
    return tot;
}

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

void modify(int &u, int i, int j, int x, ull v) {
    u = clone(u);
    t[u].val ^= v;
    if (i == j) return;
    if (x <= M) modify(ls(u), i, M, x, v);
    else modify(rs(u), M + 1, j, x, v);
    return;
}

void dfs(int u) {
    modify(root[u] = root[fa[u]], 1, n, a[u], val[a[u]]);
    for (auto &v : G[u]) if (v != fa[u]) dfs(v);
    return;
}

int ans;

void query(int u1, int u2, int u3, int u4, int i, int j) {
    if (i == j) {
        ans = i;
        return;
    }
    if (t[ls(u1)].val ^ t[ls(u2)].val ^ t[ls(u3)].val ^ t[ls(u4)].val)
        query(ls(u1), ls(u2), ls(u3), ls(u4), i, M);
    else query(rs(u1), rs(u2), rs(u3), rs(u4), M + 1, j);
}

void query(int u1, int u2, int u3, int u4, int i, int j, int a, int b) {
    if (a <= i && b >= j) {
        if (t[u1].val ^ t[u2].val ^ t[u3].val ^ t[u4].val)
            query(u1, u2, u3, u4, i, j);
        return;
    }
    if (a <= M) query(ls(u1), ls(u2), ls(u3), ls(u4), i, M, a, b);
    if (b > M && ans == -1) query(rs(u1), rs(u2), rs(u3), rs(u4), M + 1, j, a, b);
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], val[i] = rnd();
    FOR(i, 2, n) {
        int u, v; is >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    dfs(1);
    while (m--) {
        int u, v, a, b; is >> u >> v >> a >> b;
        int lca = getLCA(u, v);
        ans = -1;
        query(root[u], root[v], root[lca], root[fa[lca]], 1, n, a, b);
        os << ans << '\n';
    }
    return 0;
}