#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
int n, vis[maxn], ans;
vector<int> G[maxn];

int dfs(int u, int fa) {
    if (G[u].size() > 2) return u;
    for (auto &v : G[u]) if (v != fa) return dfs(v, u);
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        ++u, ++v;
        G[u].push_back(v), G[v].push_back(u);
    }
    FOR(i, 1, n) if (G[i].size() == 1) vis[dfs(i, 0)] = 1, ++ans;
    FOR(i, 1, n) ans -= vis[i];
    cout << (ans ? ans : 1) << endl;
    return 0;
}