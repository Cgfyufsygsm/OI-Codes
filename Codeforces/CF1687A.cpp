#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
ll a[maxn], n, k;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        ll ans = 0;
        FOR(i, 1, n) cin >> a[i];
        if (k <= n) {
            ll t = k * (k - 1) / 2;
            ll f = 0;
            FOR(i, 1, k) f += a[i];
            chkmax(ans, t + f);
            FOR(i, k + 1, n) f -= a[i - k], f += a[i], chkmax(ans, t + f);
            cout << ans << endl;
        } else {
            FOR(i, 1, n) ans += a[i];
            ans += (k - n) * n + n * (n - 1) / 2;
            cout << ans << endl;
        }
    }
    return 0;
}