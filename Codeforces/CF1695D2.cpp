#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 2e5 + 5;
int n, f[maxn], ans;
vector<int> G[maxn];

void dfs(int u, int fa) {
    int tmp = 0;
    for (auto &v : G[u]) if (v != fa) {
        dfs(v, u);
        tmp += !f[v], f[u] |= f[v];
    }
    if (tmp > 1) ans += tmp - 1, f[u] = 1;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) vector<int>().swap(G[i]), f[i] = 0;
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }
        FOR(i, 1, n - 1) {
            int u, v; cin >> u >> v;
            G[u].push_back(v), G[v].push_back(u);
        }
        int rt = 0;
        FOR(i, 1, n) if (G[i].size() > 2) {
            rt = i;
            break;
        }
        ans = 0;
        if (!rt) cout << 1 << '\n';
        else cout << (dfs(rt, 0), ans) << '\n';
    }
    return 0;
}