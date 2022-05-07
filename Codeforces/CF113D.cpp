#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using db = long double;
db p[25], f[505][505];
int deg[25], G[25][25], n, m, sa, sb;

inline int encode(int i, int j) {return (i - 1) * n + j;}

int main() {
    cin >> n >> m >> sa >> sb;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        ++deg[u], ++deg[v], G[u][v] = G[v][u] = 1;
    }
    FOR(i, 1, n) cin >> p[i];
    FOR(i, 1, n) {
        FOR(j, 1, n) {
            f[encode(i, j)][encode(i, j)] = -1;
            if (i != j) f[encode(i, j)][encode(i, j)] += p[i] * p[j];
            FOR(a, 1, n) if (G[a][i]) {
                FOR(b, 1, n) if (G[b][j] && a != b) {
                    f[encode(i, j)][encode(a, b)] += (1 - p[a]) * (1 - p[b]) / deg[a] / deg[b];
                }
            }
            FOR(a, 1, n) if (a != j && G[a][i]) f[encode(i, j)][encode(a, j)] += (1 - p[a]) / deg[a] * p[j];
            FOR(b, 1, n) if (b != i && G[b][j]) f[encode(i, j)][encode(i, b)] += (1 - p[b]) / deg[b] * p[i];
        }
    }
    int tot = encode(n, n);
    f[encode(sa, sb)][tot + 1] = -1;
    FOR(i, 1, tot) { 
        int r = i;
        FOR(j, i + 1, tot) if (fabs(f[j][i]) > fabs(f[r][i])) r = j;
        swap(f[i], f[r]);
        FOR(j, 1, tot) if (j != i) {
            db div = f[j][i] / f[i][i];
            FOR(k, 1, tot + 1) f[j][k] -= div * f[i][k];
        }
    }
    cout << fixed << setprecision(12);
    FOR(i, 1, n) cout << f[encode(i, i)][tot + 1] / f[encode(i, i)][encode(i, i)] << ' ';
    return 0;
}