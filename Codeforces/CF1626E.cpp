#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 3e5 + 5;
int n, a[maxn], sum[maxn];
int f[maxn], g[maxn], fa[maxn];
vector<int> G[maxn];

void dfs1(int u, int pre) {
    fa[u] = pre, sum[u] = a[u];
    if (a[u]) f[u] = 1;
    for (auto &v : G[u]) if (v != pre) {
        dfs1(v, u);
        sum[u] += sum[v];
        if (sum[v] >= 2 && f[v]) f[u] = 1;
        if (a[v]) f[u] = 1;
    }
    return;
}

void dfs2(int u) {
    if (a[fa[u]]) g[u] = 1;
    if (f[u]) g[u] = 1;
    for (auto &v : G[u]) if (v != fa[u]) {
        if (g[u] && sum[1] - sum[v] >= 2) g[v] = 1;
        dfs2(v);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 2, n) {
        int u, v; cin >> u >> v;
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    dfs1(1, 0);
    dfs2(1);
    FOR(i, 1, n) cout << g[i] << ' ';
    return 0;
}