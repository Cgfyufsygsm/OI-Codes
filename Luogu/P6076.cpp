#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 405;

ll n, m, c, binom[maxn][maxn], pow[maxn * maxn];

int main() {
    scanf("%lld %lld %lld", &n, &m, &c);
    binom[1][0] = binom[1][1] = 1;
    FOR(i, 1, 400) {
        binom[i][0] = 1, binom[i][i] = 1;
        FOR(j, 1, i - 1)
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }
    ll ans = 0;
    FOR(k, 0, c) {
        pow[0] = 1;
        FOR(i, 1, n * m) pow[i] = pow[i - 1] * (c - k + 1) % mod;
        FOR(i, 0, n)
            FOR(j, 0, m)
                ans = (ans + (((i + j + k) & 1) ? mod - 1 : 1) * binom[n][i] % mod * binom[m][j] % mod * binom[c][k] % mod * pow[(n - i) * (m - j)]) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}