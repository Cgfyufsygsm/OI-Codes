#include <cstdio>
#include <cmath>
#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

typedef long long ll;

ll n, sqrtn;
const ll mod = 998244353;

int main() {
    scanf("%lld", &n);
    ll ans = 0;
    for (ll d = 1; d * d <= n; ++d) {
        ll l = d, r = n, ret = d;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (2 * mid * d - d * d <= n) ret = mid, l = mid + 1;
            else r = mid;
        }
        ans += (ret - d + 1);
        ans %= mod;
    }
    printf("%lld\n", ans);
    return 0;
}