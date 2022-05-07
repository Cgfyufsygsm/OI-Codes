#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using db = long double;
const int maxn = 305;
int deg[maxn], G[maxn][maxn], n, m;
db a[maxn][maxn], p, q;

int main() {
    cin >> n >> m >> p >> q;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        G[u][v] = G[v][u] = 1, ++deg[u], ++deg[v];
    }
    FOR(u, 1, n) {
        FOR(v, 1, n) if (G[u][v]) a[u][v] = (1 - p / q) / deg[v];
        a[u][u] = -1;
    }
    a[1][n + 1] = -1;
    FOR(i, 1, n) {
        int r = i;
        FOR(j, i + 1, n) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        swap(a[r], a[i]);
        FOR(j, 1, n) {
            if (j == i) continue;
            db div = a[j][i] / a[i][i];
            FOR(k, i + 1, n + 1) a[j][k] -= div * a[i][k];
        }
    }
    cout << fixed << setprecision(13);
    FOR(i, 1, n) cout << a[i][n + 1] / a[i][i] * p / q << endl;
    return 0;
}