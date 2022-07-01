#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 155;
int d[maxn], n, rem;
ll binom[maxn][maxn];

int main() {
    cin >> n;
    binom[0][0] = 1;
    FOR(i, 1, n) {
        cin >> d[i], rem += d[i] - 1;
        binom[i][0] = 1;
        FOR(j, 1, i) binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
        if (!d[i] && n != 1) return cout << 0 << endl, 0;
    }
    if (n == 1) return cout << !d[1] << endl, 0;
    if (rem != n - 2) return cout << 0 << endl, 0;
    ll ans = 1;
    FOR(i, 1, n) ans *= binom[rem][d[i] - 1], rem -= d[i] - 1;
    cout << ans << endl;
    return 0;
}