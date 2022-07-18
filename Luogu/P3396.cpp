#include <bits/stdc++.h>
#include <fastio.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 1.5e5 + 5, B = 387;
int sum[B + 5][B + 5], a[maxn], n, m;

int main() {
    is >> n >> m;
    FOR(i, 1, n) {
        is >> a[i];
        FOR(p, 1, min(B, n - 1)) sum[p][i % p] += a[i];
    }
    while (m--) {
        char s[2];
        int x, y; is >> s >> x >> y;
        if (s[0] == 'C') {
            FOR(p, 1, min(B, n - 1)) sum[p][x % p] += y - a[x];
            a[x] = y;
        } else {
            if (x <= B) os << sum[x][y] << '\n';
            else {
                int ans = 0;
                for (int i = y; i <= n; i += x) ans += a[i];
                os << ans << '\n';
            }
        }
    }
    return 0;
}