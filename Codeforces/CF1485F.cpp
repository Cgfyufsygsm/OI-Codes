#include <bits/stdc++.h>
#include <fastio.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using namespace YangTY::fastIO;
using ll = long long;
const int maxn = 2e5 + 5, mod = 1e9 + 7;
int n; ll b[maxn], delta, ans;

int main() {
    int T; is >> T;
    while (T--) {
        map<ll, ll> f;
        is >> n;
        FOR(i, 1, n) is >> b[i];
        f[0] = 1, delta = 0, ans = 1;
        FOR(i, 1, n) {
            delta -= b[i];
            ll tmp = (ans - f[b[i] + delta] + mod) % mod;
            f[b[i] + delta] = ans;
            ans = (ans + tmp) % mod;
        }
        os << ans << '\n';
    }
    return 0;
}