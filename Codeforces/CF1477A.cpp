#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
ll a[maxn], k; int n;

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        FOR(i, 1, n) cin >> a[i];
        if (a[1] != 0) {
            FOR(i, 2, n) a[i] -= a[1];
            k -= a[1];
        }
        ll g = a[2];
        FOR(i, 3, n) g = __gcd(g, a[i]);
        cout << (k % g ? "NO" : "YES") << '\n';
    }
    return 0;
}