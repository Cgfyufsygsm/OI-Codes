#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using db = long double;
const int maxn = 105;
int n, m, deg[maxn];
vector<pair<int, int>> G[maxn];
db a[maxn << 1][maxn << 1];

void gauss(int n) {
    FOR(i, 1, n) {
        int r = i;
        FOR(j, i, n) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        swap(a[r], a[i]);
        FOR(j, 1, n) if (i != j) {
            db div = a[j][i] / a[i][i];
            FOR(k, i + 1, n + 1) a[j][k] -= div * a[i][k];
        }
    }
    FOR(i, 1, n) a[i][n + 1] /= a[i][i];
    return;
}

void build(int k) {
    memset(a, 0, sizeof a);
    static auto f = [](int i, int j) {return i + j * n;};
    FOR(i, 1, n) FOR(j, 0, 1) {
        a[f(i, j)][f(i, j)] = -1;
        for (auto &e : G[i]) if (e.first != n) {
            int c = (e.second >> k) & 1;
            a[f(i, j)][f(e.first, j ^ c)] += 1.0 / deg[e.first];
        }
    }
    a[f(1, 0)][n << 1 | 1] = -1;
    return;
}

int main() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        if (u == v && u == n) continue;
        else if (u == v) G[u].push_back({u, w}), ++deg[u];
        else ++deg[u], ++deg[v], G[u].push_back({v, w}), G[v].push_back({u, w});
    }
    db ans = 0;
    FOR(k, 0, 30) {
        build(k);
        gauss(n << 1);
        ans += (1 << k) * a[n << 1][n << 1 | 1];
    }
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}