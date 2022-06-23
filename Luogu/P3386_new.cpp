#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 505;
int n, m, e, G[maxn][maxn], ans;
int used[maxn], match[maxn];

int dfs(int u) {
    FOR(v, 1, m) if (!used[v] && G[u][v]) {
        used[v] = 1;
        if (!match[v] || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin >> n >> m >> e;
    FOR(i, 1, e) {
        int x, y; cin >> x >> y;
        G[x][y] = 1;
    }
    FOR(i, 1, n) {
        memset(used, 0, sizeof used);
        ans += dfs(i);
    }
    cout << ans << endl;
    return 0;
}