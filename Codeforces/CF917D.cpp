#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
const int maxn = 105;
const int mod = 1e9 + 7;
int n, a[maxn][maxn], G[maxn][maxn], L[maxn][maxn];

int qPow(int base, int exp = mod - 2) {
    int ret = 1;
    for (base %= mod; exp; exp >>= 1, base = 1ll * base * base % mod)
        if (exp & 1) ret = 1ll * base * ret % mod;
    return ret;
}

int MatrixTree(int x) {
    FOR(i, 1, n) FOR(j, 1, n) {
        if (i == j) {
            L[i][j] = 0;
            FOR(v, 1, n) if (v != i) L[i][j] += (G[i][v] ? x : 1);
        } else L[i][j] = G[i][j] ? mod - x : mod - 1;
    }
    --n;
    int rev = 1;
    int ans = 1;
    FOR(i, 1, n)
        FOR(j, i + 1, n) {
        while (L[i][i]) {
            int div = L[j][i] / L[i][i];
            FOR(k, i, n)
                L[j][k] = (L[j][k] - 1ll * div * L[i][k] % mod + mod) % mod;
            swap(L[i], L[j]), rev = -rev;
        }
        swap(L[i], L[j]), rev = -rev;
    }
    FOR(i, 1, n) ans = 1ll * ans * L[i][i] % mod;
    ++n;
    return rev > 0 ? ans : mod - ans;
}

int main() {
    cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        G[u][v] = G[v][u] = 1;
    }
    FOR(i, 1, n) {
        int tmp = 1;
        FOR(j, 1, n) a[i][j] = tmp, tmp = 1ll * tmp * i % mod;
        a[i][n + 1] = MatrixTree(i);
    }
    FOR(i, 1, n) {
        int inv = qPow(a[i][i]);
        FOR(j, 1, n) if (i != j) {
            int t = 1ll * a[j][i] * inv % mod;
            FOR(k, i, n + 1) a[j][k] = (a[j][k] - 1ll * t * a[i][k] % mod + mod) % mod;
        }
    }
    FOR(i, 1, n) cout << 1ll * a[i][n + 1] * qPow(a[i][i]) % mod << ' ';
    return 0;
}