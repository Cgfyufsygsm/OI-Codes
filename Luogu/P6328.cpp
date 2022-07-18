#include <bits/stdc++.h>
#include <fastio.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 1005;
int n, m, q;
int dis[maxn];
vector<int> G[maxn];
bitset<maxn> f[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    FOR(st, 1, n) {
        queue<int> q;
        memset(dis, 0x3f, sizeof dis);
        q.push(st), dis[st] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            f[st][dis[u]].set(u);
            for (auto &v : G[u]) if (dis[v] == dis[0]) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        FOR(i, 1, n) f[st][i] |= f[st][i - 1];
    }
    while (q--) {
        int a; cin >> a;
        bitset<maxn> ans;
        while (a--) {
            int x, y; cin >> x >> y;
            y = min(y, n);
            ans |= f[x][y];
        }
        cout << ans.count() << '\n';
    }
    return 0;
}