#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 35, maxm = 105, mod = 998244353;
int n, m, K, v[maxm][maxn], f[maxm][maxn][maxn][maxn], binom[maxn][maxn];

int main() {
    scanf("%d %d %d", &n, &m, &K);
    binom[0][0] = binom[1][0] = binom[1][1] = 1;
    FOR(i, 2, n) {
        binom[i][0] = 1;
        FOR(j, 1, i) binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % mod;
    }
    FOR(i, 0, m) {
        scanf("%d", v[i] + 1), v[i][0] = 1;
        FOR(j, 2, n) v[i][j] = 1ll * v[i][j - 1] * v[i][1] % mod;
    }
    f[0][0][0][0] = 1;
    FOR(i, 0, m) FOR(j, 0, n) FOR(k, 0, K) FOR(p, 0, n >> 1) FOR(t, 0, n - j) {
        f[i + 1][j + t][k + ((t + p) & 1)][(t + p) >> 1] += 1ll * f[i][j][k][p] * v[i][t] % mod * binom[n - j][t] % mod;
        f[i + 1][j + t][k + ((t + p) & 1)][(t + p) >> 1] %= mod;
    }
    int ans = 0;
    FOR(k, 0, K) FOR(p, 0, n >> 1) if (__builtin_popcount(p) + k <= K) ans = (ans + f[m + 1][n][k][p]) % mod;
    printf("%d\n", ans);
    return (0 - 0);
}
