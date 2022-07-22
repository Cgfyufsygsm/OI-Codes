#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5, maxm = 2e5 + 5;
vector<int> G[maxn], T[maxn];
int n, m;

struct UnionFind {
    int fa[maxn];
    void init() {
        FOR(i, 1, n) fa[i] = i;
        return;
    }
    int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}
    il bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        return fa[u] = v, 1;
    }
} ufs;

int dep[maxn], vis[maxn], fa[maxn];

void dfs(int u) {
    vis[u] = 1;
    for (auto &v : G[u]) if (!vis[v]) {
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs(v);
    }
}

bool findOddCircle() {
    memset(vis, 0, sizeof vis);
    FOR(i, 1, n) if (!vis[i]) {
        dep[i] = 1;
        fa[i] = 0;
        dfs(i);
    }
    FOR(u, 1, n) for (auto &v : G[u]) {
        if (!((dep[u] + dep[v]) & 1)) {
            cout << "2\n";
            if (dep[u] < dep[v]) swap(u, v);
            cout << (dep[u] - dep[v] + 1);
            for (int x = u; x != fa[v]; x = fa[x]) cout << ' ' << x;
            cout << '\n';
            return true;
        }
    }
    return false;
}

int col[maxn];

void dfsColor(int u, int c) {
    col[u] = c;
    for (auto &v : T[u]) if (col[v] == -1) dfsColor(v, c ^ 1);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int test; cin >> test;
    while (test--) {
        cin >> n >> m;
        FOR(i, 1, n) {
            vector<int>().swap(G[i]);
            vector<int>().swap(T[i]);
        }
        ufs.init();
        FOR(i, 1, m) {
            int u, v; cin >> u >> v;
            if (ufs.merge(u, v)) T[u].emplace_back(v), T[v].emplace_back(u);
            else G[u].emplace_back(v), G[v].emplace_back(u);
        }
        if (!findOddCircle()) {
            memset(col, -1, sizeof col);
            FOR(i, 1, n) if (col[i] == -1) dfsColor(i, 0);
            cout << "1\n";
            FOR(i, 1, n) cout << ((col[i] << 1) + (dep[i] & 1)) + 1 << (i == n ? '\n' : ' ');
        }
    }
    return 0;
}