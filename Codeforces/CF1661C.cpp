#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}

using ll = long long;
const int maxn = 3e5 + 5;
int n; ll a[maxn];

ll solve(ll tar) {
    ll tot = 0, odd = 0, sum = 0;
    FOR(i, 1, n) tot += ((tar - a[i] - ((tar - a[i]) & 1)) >> 1), odd += ((tar - a[i]) & 1), sum += tar - a[i];
    return odd > tot ? odd * 2 - 1 : sum / 3 * 2 + sum % 3;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        ll maxa = 0;
        FOR(i, 1, n) cin >> a[i], chkmax(maxa, a[i]);
        cout << min(solve(maxa + 1), solve(maxa)) << endl;
    }
    return 0;
}