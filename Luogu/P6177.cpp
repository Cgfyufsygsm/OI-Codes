#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 40005, B = 700;
bitset<maxn> bs[maxn / B + 5][maxn / B + 5];

int n, m, a[maxn];
vector<int> a0;
int fa[maxn], dep[maxn], son[maxn], size[maxn], mxd[maxn], topf[maxn];
int id[maxn], tot, stk[maxn], FF[maxn], top;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v) {
    to[++cnte] = v, nxt[cnte] = head[u], head[u] = cnte;
    return;
}

void dfs1(int u, int pre) {
    size[u] = 1, dep[u] = dep[pre] + 1, fa[u] = pre;
    mxd[u] = dep[u];
    for (int i = head[u], v = to[i]; i; v = to[i = nxt[i]]) if (v != pre) {
        dfs1(v, u);
        size[u] += size[v];
        mxd[u] = max(mxd[u], mxd[v]);
        if (size[son[u]] < size[v]) son[u] = v;
    }
    if (mxd[u] - dep[u] >= B) id[u] = ++tot, mxd[u] = dep[u];
}

void dfs2(int u) {
    for (int i = head[u], v = to[i]; i; v = to[i = nxt[i]]) if (v != fa[u]) {
        if (id[v]) {
            int ip = id[stk[top]], in = id[v];
            for (int x = v; x != stk[top]; x = fa[x]) bs[ip][in].set(a[x]);
            FOR(i, 1, top - 1) {
                auto &tmp = bs[id[stk[i]]][in];
                tmp = bs[id[stk[i]]][ip], tmp |= bs[ip][in];
            }
            FF[v] = stk[top], stk[++top] = v;
        }
        dfs2(v);
        if (id[v]) --top;
    }
    return;
}

void dfs3(int u, int tpf) {
    topf[u] = tpf;
    if (son[u]) dfs3(son[u], tpf);
    for (int i = head[u], v = to[i]; i; v = to[i = nxt[i]])
        if (v != son[u] && v != fa[u]) dfs3(v, v);
    return;
}

int getLCA(int u, int v) {
    while (topf[u] != topf[v]) {
        if (dep[topf[u]] < dep[topf[v]]) swap(u, v);
        u = fa[topf[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], a0.emplace_back(a[i]);
    sort(a0.begin(), a0.end());
    a0.erase(unique(a0.begin(), a0.end()), a0.end());
    FOR(i, 1, n) a[i] = lower_bound(a0.begin(), a0.end(), a[i]) - a0.begin() + 1;
    FOR(i, 2, n) {
        int u, v; is >> u >> v;
        add(u, v), add(v, u);
    }
    dfs1(1, 0);
    if (!id[1]) id[1] = ++tot;
    stk[top = 1] = 1;
    dfs2(1), dfs3(1, 1);
    int last = 0;
    while (m--) {
        int u, v; is >> u >> v;
        int t = getLCA(u ^= last, v);
        bitset<maxn> ans;
        while (u != t && !id[u]) ans.set(a[u]), u = fa[u];
        while (v != t && !id[v]) ans.set(a[v]), v = fa[v];
        if (u != t) {
            int pre = u;
            while (dep[FF[pre]] >= dep[t]) pre = FF[pre];
            if (pre != u) ans |= bs[id[pre]][id[u]];
            while (pre != t) ans.set(a[pre]), pre = fa[pre];
        }
        if (v != t) {
            int pre = v;
            while (dep[FF[pre]] >= dep[t]) pre = FF[pre];
            if (pre != v) ans |= bs[id[pre]][id[v]];
            while (pre != t) ans.set(a[pre]), pre = fa[pre];
        }
        ans.set(a[t]);
        os << (last = ans.count()) << '\n';
    }
    return 0;
}
