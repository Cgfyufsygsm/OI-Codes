#include <cstdio>

#include <iostream>
#include <cmath>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 1e5 + 5;
int n, m, p;
int f[maxn], g[400][maxn];
using namespace std;

int main() {
    scanf("%d %d", &n, &p);
    m = sqrt(n) + 1;
    f[0] = 1;
    FOR(i, 1, m - 1) {
        FOR(j, i, n) {
            f[j] += f[j - i];
            f[j] %= p;
        }
    }
    g[0][0] = 1;
    FOR(i, 1, m - 1) {
        FOR(j, i, n) {
            g[i][j] = g[i][j - i];
            if (j >= m) g[i][j] += g[i - 1][j - m], g[i][j] %= p;
        }
    }
    long long ans = 0;
    FOR(i, 0, n) {
        long long sum = 0;
        FOR(j, 0, m - 1) sum += g[j][n - i], sum %= p;
        ans = (ans + 1ll * sum * f[i]) % p;
    }
    printf("%d\n", ans);
    return 0;
}