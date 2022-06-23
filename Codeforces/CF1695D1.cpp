#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
const int maxn = 2e3 + 5;
int n, f[maxn];
vector<int> G[maxn];

int dfs(int u, int fa) {
    int tmp = 0, ret = 0;
    f[u] = 0;
    for (auto &v : G[u]) if (v != fa) {
        ret += dfs(v, u);
        tmp += !f[v], f[u] |= f[v];
    }
    if (tmp > 1) ret += tmp - 1, f[u] = 1;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) vector<int>().swap(G[i]);
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }
        FOR(i, 1, n - 1) {
            int u, v; cin >> u >> v;
            G[u].push_back(v), G[v].push_back(u);
        }
        int ans = 1e9;
        FOR(i, 1, n) chkmin(ans, dfs(i, 0) + 1);
        cout << ans << '\n';
    }
    return 0;
}