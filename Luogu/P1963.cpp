#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 1e4 + 5;
int n, m, cnt;
int used[maxn], match[maxn], ans[maxn];
vector<int> G[maxn];

int dfs(int u) {
    for (auto &v : G[u]) if (!used[v]) {
        used[v] = 1;
        if (!match[v] || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin >> n;
    FOR(i, 0, n - 1) {
        int d; cin >> d;
        if (d > n / 2) return puts("No Answer"), 0;
        G[i].push_back((i + d) % n);
        G[i].push_back((i - d + n) % n);
        sort(G[i].begin(), G[i].end());
    }
    DEC(i, n - 1, 0) {
        memset(used, 0, sizeof used);
        cnt += dfs(i);
    }
    if (cnt != n) return puts("No Answer"), 0;
    FOR(i, 0, n - 1) ans[match[i]] = i;
    FOR(i, 0, n - 1) cout << ans[i] << ' ';
    return 0;
}