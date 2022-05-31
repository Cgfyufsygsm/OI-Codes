#include <bits/stdc++.h>
#include <atcoder/modint>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
using mint = atcoder::modint1000000007;
const int maxn = 2005, N = 4e6;
int n, k;
mint fac[N + 5], ifac[N + 5], f[maxn][maxn];

mint binom(int n, int m) {return n < m ? 0 : fac[n] * ifac[m] * ifac[n - m];}

int main() {
    fac[0] = 1;
    FOR(i, 1, N) fac[i] = i * fac[i - 1];
    ifac[N] = fac[N].inv();
    DEC(i, N - 1, 0) ifac[i] = (i + 1) * ifac[i + 1];
    cin >> n >> k;
    if (k == 1) return puts("1"), 0;
    FOR(i, 1, n) {
        f[i][0] = 1;
        FOR(j, 1, i)
            f[i][j] = f[i - 1][j] + f[i][j - 1] * binom(n * k - i - (j - 1) * (k - 1) - 1, k - 2);
    }
    cout << (f[n][n] * fac[n]).val() << endl;
    return 0;
}