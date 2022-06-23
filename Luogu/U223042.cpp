#include <cstdio>
#include <cmath>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using ll = long long;
const ll mod = 999292927;

int main() {
    ll n, ans = 0; scanf("%lld", &n);
    for (ll l = 1, r = 0; l <= n; l = r + 1) {
        if (n / (l * l) < 1) break;
        r = sqrt(n / (n / (l * l)));
        ans = (ans + (l + r) * (r - l + 1) / 2 % mod * (n / (l * l)) % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}