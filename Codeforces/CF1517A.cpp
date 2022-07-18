#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using ll = long long;
ll x2050[17];

int main() {
    x2050[0] = 2050;
    for (int i = 1; (10.0) * x2050[i - 1] <= 1e18; ++i) x2050[i] = x2050[i - 1] * 10;
    int T; cin >> T;
    while (T--) {
        ll n; cin >> n;
        if (n % 2050) {
            cout << -1 << '\n';
            continue;
        }
        int cnt = 0;
        DEC(i, 14, 0) {
            while (n >= x2050[i]) n -= x2050[i], ++cnt;
        }
        cout << cnt << '\n';
    }
    return 0;
}