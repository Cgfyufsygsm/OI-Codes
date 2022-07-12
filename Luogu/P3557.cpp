#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 5e5 + 5;
int vis[maxn], n, m, k;
vector<int> G[maxn], ans;

void dfs(int u, int fa, int dep) {
    vis[u] = 1;
    if (dep >= 2) return;
    for (auto &v : G[u]) if (v != fa) dfs(v, u, dep + 1);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    FOR(i, 1, n) if (!vis[i]) {
        dfs(i, 0, 0);
        ans.push_back(i);
    }
    cout << ans.size() << endl;
    for (auto &x : ans) cout << x << ' ';
    return 0;
}