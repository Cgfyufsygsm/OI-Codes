#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using ll = long long;
const int N = 2e4;
int isp[N + 5], p[N + 5], ptot;

void sieve() {
    FOR(i, 2, N) {
        if (!isp[i]) p[++ptot] = i;
        for (int j = 1; j <= ptot && i * p[j] <= N; ++j) {
            isp[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
}

const int maxn = 505;
int n;
ll p1[maxn << 1], p2[maxn << 1], ans[maxn][maxn];

ll lcm(ll x, ll y) {return (!x || !y) ? (x + y) : (x / __gcd(x, y) * y);}

int main() {
    sieve();
    cin >> n;
    if (n == 2) return puts("4 7\n 23 10"), 0;
    int it = 1;
    for (int i = 1; i <= 2 * n - 1; i += 2) p1[i] = p[it++];
    for (int i = ((1 - n) & 1) ? 1 - n : 2 - n; i <= n - 1; i += 2) p2[i + n] = p[it++];
    FOR(i, 1, n) FOR(j, 1, n) if ((i + j) & 1) ans[i][j] = p1[i + j] * p2[i - j + n];
    FOR(i, 1, n) FOR(j, 1, n) if (!((i + j) & 1)) ans[i][j] = lcm(lcm(ans[i - 1][j], ans[i + 1][j]), lcm(ans[i][j + 1], ans[i][j - 1])) + 1;
    FOR(i, 1, n) {
        FOR(j, 1, n) cout << ans[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}